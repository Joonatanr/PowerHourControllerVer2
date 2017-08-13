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

Private const Timer_A_UpModeConfig timer_config =
{
     .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE, /* We enable capture compare, since this is a periodic timer. */
     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_16, //Currently divided by 16.
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
    //PCM_gotoLPM3();

    while(1)
    {
        MAP_PCM_gotoLPM0();
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

    //Clear other LEDs.
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
}

Private void timerA_init(void)
{
    //Set up timer
    Timer_A_configureUpMode(TIMER_A0_BASE, &timer_config);
    Timer_A_registerInterrupt(TIMER_A0_BASE, TIMER_A_CCR0_INTERRUPT, TA0_0_IRQHandler);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    //Enable this interrupt in NVIC.
    Interrupt_enableInterrupt(INT_TA0_0);
}

/* This should be fired every 10 msec */
Private void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if (priv_delay_counter > 0u)
    {
        priv_delay_counter--;
    }
    timer_10msec_callback();
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

