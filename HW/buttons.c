/*
 * buttons.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Joonatan
 */


#include "buttons.h"
#include <driverlib.h>

//Set up buttons as inputs.
//4.7, 5.5, 5.4, 6.4
Public void buttons_init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN5 | GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN4);
}


Public U8 isRedButton(void)
{
    return !GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN7);
}

Public U8 isBlueButton(void)
{
    return !GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5);
}

Public U8 isGreenButton(void)
{
    return !GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN4);
}

Public U8 isBlackButton(void)
{
    return !GPIO_getInputPinValue(GPIO_PORT_P6, GPIO_PIN4);
}



