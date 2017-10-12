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
    RED_BUTTON,
    GREEN_BUTTON,
    BLACK_BUTTON,
    BLUE_BUTTON,

    NUMBER_OF_BUTTONS
} ButtonType;

extern void buttons_init(void);
extern void buttons_cyclic10msec(void);
extern void buttons_subscribeListener(ButtonType btn, buttonListener listener);

extern Boolean isRedButton(void);
extern Boolean isBlueButton(void);
extern Boolean isGreenButton(void);
extern Boolean isBlackButton(void);

#endif /* HW_BUTTONS_H_ */
