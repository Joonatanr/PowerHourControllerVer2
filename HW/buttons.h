/*
 * buttons.h
 *
 *  Created on: Sep 7, 2017
 *      Author: Joonatan
 */

#ifndef HW_BUTTONS_H_
#define HW_BUTTONS_H_

#include "typedefs.h"


extern void buttons_init(void);

extern U8 isRedButton(void);
extern U8 isBlueButton(void);
extern U8 isGreenButton(void);
extern U8 isBlackButton(void);

#endif /* HW_BUTTONS_H_ */
