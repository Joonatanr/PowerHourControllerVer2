/*
 * register.c
 *
 *  Created on: 28. mai 2017
 *      Author: Joonatan
 */

#include "register.h"
#include "display_drv.h"
#include <driverlib.h>
#include <spi_drv.h>

//Hi priority timer runs at 10msec interval (might need to be faster)
Private const Timer_A_UpModeConfig hi_prio_timer_config =
{
     .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, /* We enable capture compare, since this is a periodic timer. */
     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_16, //Currently divided by 16.
     .timerClear = TIMER_A_DO_CLEAR,
     .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE, //Disable general interrupt.
     .timerPeriod = 7500u
};


//Lo priority timer runs at 40msec interval
Private const Timer_A_UpModeConfig lo_prio_timer_config =
{
     .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, /* We enable capture compare, since this is a periodic timer. */
     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64, //Currently divided by 64.
     .timerClear = TIMER_A_DO_CLEAR,
     .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE, //Disable general interrupt.
     .timerPeriod = 7500u
};

Private const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

/*****************************************************************************************************
 *
 * Function Prototypes
 *
 *****************************************************************************************************/

Private void clocks_init(void);
Private void ports_init(void);
Private void TA0_0_IRQHandler(void);
Private void TA1_0_IRQHandler(void);
Private void timerA_init(void);
Private void uart_init(void);

/*****************************************************************************************************
 *
 * Private variables.
 *
 *****************************************************************************************************/

Public volatile U16 priv_delay_counter = 0u;

/*****************************************************************************************************
 *
 * Public Functions
 *
 *****************************************************************************************************/

Public void register_init(void)
{
    //Initialise system clocks first.
    clocks_init();

    //Initialise input/output pins.
    ports_init();

    //Initialise main timer.
    timerA_init();

    //Initialise UART
    uart_init();

    //Initialise SPI for LCD display.
    spi_init();

    //Not quite sure what this does yet.
    MAP_Interrupt_enableSleepOnIsrExit();

    //Enable interrupts in general.
    Interrupt_enableMaster();

    //Initialise display driver.
    display_init();
}

Public void register_enable_low_powermode(void)
{
    //Go to low power mode with interrupts.
    while(1)
    {
        PCM_gotoLPM0();
    }
}

Public void delay_msec(U16 msec)
{
    priv_delay_counter = msec / 10;
    while(priv_delay_counter > 0u);
}

/*****************************************************************************************************
 *
 * Private Functions
 *
 *****************************************************************************************************/

Private void clocks_init(void)
{
    WDT_A_holdTimer();

    //Lets configure the DCO to 12MHz
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Initializing the clock source as follows:
     *      MCLK = MODOSC/4 = 6MHz
     *      ACLK = REFO/2 = 16kHz   --- Not used, should remove.
     *      HSMCLK = DCO/2 = 6Mhz
     *      SMCLK = DCO =  12MHz
     *      BCLK  = REFO = 32kHz    --- Not used, should remove.
     */
    MAP_CS_initClockSignal(CS_MCLK,     CS_MODOSC_SELECT,   CS_CLOCK_DIVIDER_4);
    MAP_CS_initClockSignal(CS_ACLK,     CS_REFOCLK_SELECT,  CS_CLOCK_DIVIDER_2);
    MAP_CS_initClockSignal(CS_HSMCLK,   CS_DCOCLK_SELECT,   CS_CLOCK_DIVIDER_2);
    MAP_CS_initClockSignal(CS_SMCLK,    CS_DCOCLK_SELECT,   CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_BCLK,     CS_REFOCLK_SELECT,  CS_CLOCK_DIVIDER_1);
}

Private void ports_init(void)
{
    //First lets set up LED ports as outputs.
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

    //Lets set up S1 and S2 as input pins.
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN4);

    // Set pin 4.3 as CS pin.
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);

    // Set pin 1.7 as A0 pin.
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);

    // Set pin 2.5 as reset pin.
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);

    //Clear other LEDs.
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
}

Private void timerA_init(void)
{
    //Set up timer for high priority interrupts.
    Timer_A_configureUpMode(TIMER_A0_BASE, &hi_prio_timer_config);
    Timer_A_registerInterrupt(TIMER_A0_BASE, TIMER_A_CCR0_INTERRUPT, TA0_0_IRQHandler);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    //Enable this interrupt in NVIC.
    Interrupt_setPriority(INT_TA0_0, 254u); //TODO : Definately should review this.

    //Set offset, so that interrupts will not
    TA0CCR0 = 2500u;

    Interrupt_enableInterrupt(INT_TA0_0);


    //TODO : Set up timer for low priority interrupts.
    Timer_A_configureUpMode(TIMER_A1_BASE, &lo_prio_timer_config);
    Timer_A_registerInterrupt(TIMER_A1_BASE, TIMER_A_CCR0_INTERRUPT, TA1_0_IRQHandler);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    Interrupt_setPriority(INT_TA1_0, 255u);
    Interrupt_enableInterrupt(INT_TA1_0);
}

/* This should be fired every 10 msec */
//Hi priority interrupt handler.
Private void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if (priv_delay_counter > 0u)
    {
        priv_delay_counter--;
    }
    timer_10msec_callback();
}

//Fired every 40 mseconds, this is lo prio interrupt handler.
Private void TA1_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    timer_40msec_callback();
}


Private void uart_init(void)
{
    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
}



/****************************************************************************************
 * INPUT OUTPUT PORTS
 ****************************************************************************************/

Public void set_led_one(U8 state)
{
    if (state == 1u)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}

Public void set_led_two_red(U8 state)
{
    if (state == 1u)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }
}

Public void set_led_two_green(U8 state)
{
    if (state == 1u)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }
}

Public void set_led_two_blue(U8 state)
{
    if (state == 1u)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }
}

/* Set function for the RS or A0 pin. */
Public void set_reg_select(U8 state)
{
    if (state)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
    }
}

/* Set function for Chip Select pin. */
Public void set_cs_pin(U8 state)
{
    if (state)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    }
}

Public void set_disp_reset_pin(U8 state)
{
    if (state)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN5);
    }
    else
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);
    }
}

Public U8 isBtnOne(void)
{
    U8 res = 0x00u;
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)
    {
        res = 0x01u;
    }
    return res;
}

Public U8 isBtnTwo(void)
{
    U8 res = 0x00u;
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == GPIO_INPUT_PIN_LOW)
    {
        res = 0x01u;
    }
    return res;
}

