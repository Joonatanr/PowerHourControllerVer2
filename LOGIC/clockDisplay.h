/*
 * clockDisplay.h
 *
 *  Created on: Aug 27, 2017
 *      Author: Joonatan
 */

#ifndef LOGIC_CLOCKDISPLAY_H_
#define LOGIC_CLOCKDISPLAY_H_

#include "typedefs.h"

typedef struct
{
    U8 minute;
    U8 second;
} timekeeper_struct;

extern void clockDisplay_init(void);
extern void clockDisplay_start(void);
extern void clockDisplay_cyclic1000msec(void);
extern void clockDisplay_stop(void);

#endif /* LOGIC_CLOCKDISPLAY_H_ */
