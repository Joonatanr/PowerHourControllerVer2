/*
 * buttons.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Joonatan
 */


#include "buttons.h"
#include <driverlib.h>

typedef Boolean (*buttonFunction)(void);

typedef struct
{
    buttonFunction state_func;      //Used to get the state of the button.
    buttonListener listener_func;   //Can be subscribed to.
    Boolean pressed;

} ButtonContainer;

/* TODO : Make it possible to configure buttons to rising edge. */
/* TODO : Maybe it would be better to have an interrupt driven solution?? */
Private ButtonContainer priv_button_config [NUMBER_OF_BUTTONS] =
{
 { .state_func = isRedButton,    .listener_func = NULL, .pressed = FALSE },    /* RED_BUTTON       */
 { .state_func = isGreenButton,  .listener_func = NULL, .pressed = FALSE },    /* GREEN_BUTTON     */
 { .state_func = isBlackButton,  .listener_func = NULL, .pressed = FALSE },    /* BLACK_BUTTON     */
 { .state_func = isBlueButton,   .listener_func = NULL, .pressed = FALSE },    /* BLUE_BUTTON      */
};


//Set up buttons as inputs.
//4.7, 5.5, 5.4, 6.4
Public void buttons_init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN5 | GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN4);
}


//Hi priority task.
Public void buttons_cyclic10msec(void)
{
    U8 ix;
    Boolean state;

    for (ix = 0u; ix < NUMBER_OF_BUTTONS; ix++)
    {
        state = priv_button_config[ix].state_func();

        if (state)
        {
            priv_button_config[ix].pressed = TRUE;
        }
        else if (priv_button_config[ix].pressed == TRUE)
        {
            priv_button_config[ix].pressed = FALSE;
            if (priv_button_config[ix].listener_func != NULL)
            {
                priv_button_config[ix].listener_func();
            }
        }
        else
        {
            /* Do nothing. */
        }
    }
}

//Listener functions should be short functions that use flags.
//This function subscribes a listener function to a button.
Public void buttons_subscribeListener(ButtonType btn, buttonListener listener)
{
    Interrupt_disableMaster();
    //Critical section.
    if (btn < NUMBER_OF_BUTTONS)
    {
        priv_button_config[btn].listener_func = listener;
    }
    Interrupt_enableMaster();
}

Public Boolean isRedButton(void)
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN7) == 1u) ? FALSE : TRUE);
}

Public Boolean isBlueButton(void)
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN4) == 1u) ? FALSE : TRUE);
}

Public Boolean isGreenButton(void)
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5) == 1u) ? FALSE : TRUE);
}

Public Boolean isBlackButton(void)
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN4) == 1u) ? FALSE : TRUE);
}



