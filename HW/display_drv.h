/*
 * display_drv.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#ifndef HW_DISPLAY_DRV_H_
#define HW_DISPLAY_DRV_H_

#include "typedefs.h"
#include "bitmaps.h"
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

#define NUMBER_OF_PAGES 8u
#define NUMBER_OF_COLUMNS 128u
#define NUMBER_OF_ROWS (NUMBER_OF_PAGES * 8u)

#define GET_SEGMENT(column) ((column) >> 3u) //Divided by 8, since there are 8 columns per segment.
#define GET_FIRST_COLUMN(segment) ((segment) << 3u) //Multiplied with 8, returns the first column index of a segment.

extern void display_init(void);
extern void display_start(void);
extern void display_cyclic_50msec(void);

extern void display_drawChar(char c, U8 xloc, U8 yloc, Size * destSize);
extern void display_drawString(const char * str, U8 xloc, U8 yloc, FontType font);
extern void display_drawStringCenter(const char * str, U8 centerPoint, U8 yloc, FontType font);
extern void display_fillRectangle(U16 x, U16 y, U16 height, U16 width, FillPatternType patternType);
extern void display_drawBitmap(const Bitmap * bmp, U16 x, U16 y);
extern void display_drawBitmapCenter(const Bitmap * bmp, U16 centerPoint, U16 y);

Public void display_clear(void);


#endif /* HW_DISPLAY_DRV_H_ */
