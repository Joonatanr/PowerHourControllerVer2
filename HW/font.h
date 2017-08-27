/*
 * font.h
 *
 *  Created on: Aug 25, 2017
 *      Author: Joonatan
 */

#ifndef HW_FONT_H_
#define HW_FONT_H_


#include "typedefs.h"
#include "bitmaps.h"

typedef enum
{
    FONT_SMALL_FONT,
    FONT_LARGE_FONT,
    FONT_NUMBERS_LARGE,
    NUMBER_OF_FONTS
} FontType;

extern const Bitmap large_font_bitmap;

extern void font_getFontChar(char asc, Bitmap * dest);
extern void font_setFont(FontType font);
extern U16 font_getFontHeight(void);


#endif /* HW_FONT_H_ */
