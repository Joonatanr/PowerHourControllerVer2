/*
 * buzzer.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Joonatan
 */


#include "buzzer.h"
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#define BEEP_INTERVAL 3u /* 400msec */
#define BEEP_LENGTH 2u   /* 200msec */

/* Timer_A PWM Configuration Parameter */
Private Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK, //SMCLK has frequency of 12MHz
        TIMER_A_CLOCKSOURCE_DIVIDER_16,
        277,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0  //Set to 139 for activating.
};

Private int priv_buzzer_counter = -1;
Private int priv_beep_counter = 0;
Private U8 priv_cycle_counter;

Public void buzzer_init(void)
{
    /* Configuring GPIO2.4 as peripheral output for PWM  and P6.7 for button
     * interrupt */
    /*
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);
    */
    /* Configuring Timer_A to have a period of approximately 5ms and
     * an initial duty cycle of 50% of that  */

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);

    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}

Public void buzzer_setBuzzer(Boolean state)
{
    if(state)
    {
        pwmConfig.dutyCycle = 139;
    }
    else
    {
        pwmConfig.dutyCycle = 0;
    }
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}


Public void buzzer_playBuzzer(U8 cycles)
{
    priv_buzzer_counter = cycles;
    buzzer_setBuzzer(TRUE);
}

Public void buzzer_playBeeps(U8 beeps)
{
    priv_beep_counter = beeps;
}


//Must be called every 100 msec.
Public void buzzer_Cyclic100msec(void)
{
    priv_cycle_counter++;
    if (priv_cycle_counter >= 10u)
    {
        priv_cycle_counter = 0u;
    }

    if (priv_beep_counter > 0)
    {
        if ((priv_cycle_counter % BEEP_INTERVAL) == 0)
        {
            buzzer_playBuzzer(BEEP_LENGTH);
            priv_beep_counter--;
        }
    }


    if (priv_buzzer_counter > 0)
    {
        priv_buzzer_counter--;
    }

    if(priv_buzzer_counter == 0)
    {
        priv_buzzer_counter = -1;
        buzzer_setBuzzer(FALSE);
    }
}


