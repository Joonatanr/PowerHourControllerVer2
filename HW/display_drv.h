/*
 * display_drv.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#ifndef HW_DISPLAY_DRV_H_
#define HW_DISPLAY_DRV_H_

#include "typedefs.h"
#include "font.h"

typedef enum
{
    PATTERN_WHITE,
    PATTERN_BLACK,
    PATTERN_GRAY,
    NUMBER_OF_PATTERNS,
} FillPatternType;

#define ROW_0 0
#define ROW_1 8
#define ROW_2 16
#define ROW_3 24
#define ROW_4 32
#define ROW_5 40
#define ROW_6 48
#define ROW_7 56

extern void display_init(void);
extern void display_start(void);
extern void display_cyclic_50msec(void);

extern void display_drawChar(char c, U8 xloc, U8 yloc, Size * destSize);
extern void display_drawString(const char * str, U8 xloc, U8 yloc, FontType font);
extern void display_fillRectangle(U16 x, U16 y, U16 height, U16 width, FillPatternType patternType);
extern void display_drawBitmap(const Bitmap * bmp, U16 x, U16 y);

Public void display_clear(void);


#endif /* HW_DISPLAY_DRV_H_ */
