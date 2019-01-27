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
        TIMER_A_OUTPUTMODE_TOGGLE_SET,
        0
};

#define A4_NOTE 440u
#define B4_NOTE 494u
#define F4_UP_NOTE 370u
#define G4_NOTE 392u

#define E4_NOTE 324u
#define D4_NOTE 288u

/* Private type definitions */
typedef enum
{
    EIGHTH,
    QUARTER,
    HALF,
    FULL
} NoteLength_T;

typedef struct
{
    NoteLength_T length;
    U16 frequency;
    Boolean add_break;
} Note_T;

typedef struct
{
    const Note_T n1;
    const Note_T n2;
} NotePair_T;


/************* Private function forward declarations ****************/

Private void setFrequencyInterval(U16 interval);
Private void setSpeakerFrequency(U16 frequency);

Private void play_note(const Note_T * note);
Private void play_eight(U16 note);
Private void play_quarter(U16 note);
Private void play_half(U16 note);


/************************* Public function definitions  *****************************/
Public void speaker_init(void)
{
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);
}


Private const Note_T sample_music[] =
{
     { .length = EIGHTH,    .frequency = A4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = A4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },

     { .length = QUARTER,   .frequency = A4_NOTE        },
     { .length = QUARTER,   .frequency = A4_NOTE        },

     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = A4_NOTE        },

     { .length = HALF,      .frequency = F4_UP_NOTE     },

     { .length = EIGHTH,    .frequency = A4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = A4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },

     { .length = QUARTER,   .frequency = A4_NOTE        },
     { .length = QUARTER,   .frequency = A4_NOTE        },

     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = A4_NOTE        },

     { .length = HALF,      .frequency = F4_UP_NOTE     },

     /* Row... */
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },

     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = EIGHTH,    .frequency = D4_NOTE        },

     { .length = EIGHTH,    .frequency = E4_NOTE, .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE, .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = EIGHTH,    .frequency = G4_NOTE        },

     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = QUARTER,   .frequency = D4_NOTE        },

     /* Row... */
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },

     { .length = EIGHTH,    .frequency = G4_NOTE        },
     { .length = EIGHTH,    .frequency = F4_UP_NOTE     },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = EIGHTH,    .frequency = D4_NOTE        },

     { .length = EIGHTH,    .frequency = E4_NOTE, .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE, .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = EIGHTH,    .frequency = G4_NOTE        },

     { .length = EIGHTH,    .frequency = F4_UP_NOTE,    .add_break = TRUE },
     { .length = EIGHTH,    .frequency = E4_NOTE        },
     { .length = EIGHTH,    .frequency = A4_NOTE        },

};


Public void speaker_test(void)
{
    U8 ix;
    const Note_T * note_ptr;

    for (ix = 0u; ix < NUMBER_OF_ITEMS(sample_music); ix++)
    {
        note_ptr = &sample_music[ix];
        play_note(note_ptr);
    }

    speaker_mute();
}


Public void speaker_mute(void)
{
    MAP_Timer_A_stopTimer(TIMER_A3_BASE);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN4);
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

    /* Lets test */
#if 0
    speaker_mute();
    delay_msec(30);
    speaker_init();
    /* End of test code. */
#endif

    if (interval < 0xffffu)
    {
        duty_cycle = interval / 2;
        conf_ptr->timerPeriod = interval;
        conf_ptr->dutyCycle = (U16)duty_cycle;
        MAP_Timer_A_generatePWM(TIMER_A3_BASE, conf_ptr);
    }
}


Private void play_note(const Note_T * note)
{
    switch(note->length)
    {
    case(EIGHTH):
            play_eight(note->frequency);
            break;
    case(QUARTER):
            play_quarter(note->frequency);
            break;
    case(HALF):
            play_half(note->frequency);
            break;
    default:
        break;
    }

    if (note->add_break)
    {
        speaker_mute();
        __delay_cycles(10000);
        speaker_init();
    }
}


#define FULL_NOTE 3000u

Private void play_eight(U16 note)
{
    setSpeakerFrequency(note);
    delay_msec(FULL_NOTE >> 3u);
}

Private void play_quarter(U16 note)
{
    setSpeakerFrequency(note);
    delay_msec(FULL_NOTE >> 2u);
}

Private void play_half(U16 note)
{
    setSpeakerFrequency(note);
    delay_msec(FULL_NOTE >> 1u);
}

