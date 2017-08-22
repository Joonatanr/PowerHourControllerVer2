/*
 * display_drv.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#ifndef HW_DISPLAY_DRV_H_
#define HW_DISPLAY_DRV_H_

#include "typedefs.h"

extern void display_init(void);
extern void display_start(void);
extern void display_cyclic_50msec(void);
extern void display_drawRectangle(Point p, Size s);
Public void display_clear(void);


#endif /* HW_DISPLAY_DRV_H_ */
