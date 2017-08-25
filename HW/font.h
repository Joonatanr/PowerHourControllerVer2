/*
 * font.h
 *
 *  Created on: Aug 25, 2017
 *      Author: Joonatan
 */

#ifndef HW_FONT_H_
#define HW_FONT_H_


#include "typedefs.h"

typedef enum
{
    FONT_SMALL_FONT,
    FONT_LARGE_FONT,
    NUMBER_OF_FONTS
} FontType;

extern const Bitmap large_font_bitmap;

extern void font_getFontChar(char asc, Bitmap * dest, FontType font);


#endif /* HW_FONT_H_ */
