/*
 * buttons.h
 *
 *  Created on: Sep 7, 2017
 *      Author: Joonatan
 */

#ifndef HW_BUTTONS_H_
#define HW_BUTTONS_H_

#include "typedefs.h"

typedef void (*buttonListener)(void);

typedef enum
{
    RED_BUTTON,     /* Up button    */
    GREEN_BUTTON,   /* Left button  */
    BLACK_BUTTON,   /* Right button */
    BLUE_BUTTON,    /* Down button  */

    NUMBER_OF_BUTTONS
} ButtonType;

#define UP_BUTTON       RED_BUTTON
#define LEFT_BUTTON     GREEN_BUTTON
#define RIGHT_BUTTON    BLACK_BUTTON
#define DOWN_BUTTON     BLUE_BUTTON

extern void buttons_init(void);
extern void buttons_cyclic10msec(void);
extern void buttons_cyclic100msec(void);
extern void buttons_subscribeListener(ButtonType btn, buttonListener listener);
extern void buttons_subscribeHoldDownListener(ButtonType btn, buttonListener listener);
extern void buttons_unsubscribeAll(void);

extern Boolean isButton(ButtonType btn);


#endif /* HW_BUTTONS_H_ */
