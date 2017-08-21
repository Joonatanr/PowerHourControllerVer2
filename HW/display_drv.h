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
extern void display_test_sequence(void);
extern void display_cyclic_40msec(void);
extern void display_drawRectangle(Point p, Size s);


#endif /* HW_DISPLAY_DRV_H_ */
