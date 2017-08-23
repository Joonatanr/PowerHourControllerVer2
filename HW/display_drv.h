/*
 * display_drv.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#ifndef HW_DISPLAY_DRV_H_
#define HW_DISPLAY_DRV_H_

#include "typedefs.h"

typedef enum
{
    PATTERN_WHITE,
    PATTERN_BLACK,
    PATTERN_GRAY,
    NUMBER_OF_PATTERNS,
} FillPatternType;

typedef struct
{
    Size bmp_size;
    const U8 * bmp_data;
} Bitmap;

extern void display_init(void);
extern void display_start(void);
extern void display_cyclic_50msec(void);

extern void display_fillRectangle(Point p, Size s, FillPatternType pattern);
extern void display_drawBitmap (const Bitmap * bmp, Point location);

Public void display_clear(void);


#endif /* HW_DISPLAY_DRV_H_ */
