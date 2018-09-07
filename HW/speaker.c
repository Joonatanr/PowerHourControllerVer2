/*
 * speaker.c
 *
 *  Created on: 7. sept 2018
 *      Author: JRE
 */

#include "speaker.h"
#include "driverlib.h"
#include "register.h"

/* We try to drive a speaker using PWM and an amplifier in between... */

/* Need to use TIMERA3, as other timers are already being used by other modules... */
/* P10.4/TA3.0 */

#define TIMER_FREQUENCY 750000u

Private Timer_A_PWMConfig priv_pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK, //SMCLK has frequency of 12MHz
        TIMER_A_CLOCKSOURCE_DIVIDER_16,
        10000u,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0
};


Private void setFrequencyInterval(U16 interval);
Private void setSpeakerFrequency(U16 frequency);


/************************* Public function definitions  *****************************/
Public void speaker_init(void)
{
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);
}


Public void speaker_test(void)
{
    /* Lets try playing C4 on speaker. */
    setSpeakerFrequency(262u);
    delay_msec(1000);
    /* G4 */
    setSpeakerFrequency(392u);
    delay_msec(1000);
    /* C4 */
    setSpeakerFrequency(262u);
    delay_msec(1000);
    speaker_mute();
}


Public void speaker_mute(void)
{
    MAP_Timer_A_stopTimer(TIMER_A3_BASE);
}


/************************* Private function definitions  *****************************/

Private void setSpeakerFrequency(U16 frequency)
{
    U32 interval = TIMER_FREQUENCY / frequency;
    setFrequencyInterval(interval);
}

Private void setFrequencyInterval(U16 interval)
{
    /* Since this is a frequency generator then the duty cycle will always be 50% */
    Timer_A_PWMConfig * conf_ptr = &priv_pwmConfig;
    U32 duty_cycle;

    if (interval < 0xffffu)
    {
        duty_cycle = interval / 2;
        conf_ptr->timerPeriod = interval;
        conf_ptr->dutyCycle = (U16)duty_cycle;
        MAP_Timer_A_generatePWM(TIMER_A3_BASE, conf_ptr);
    }
}
