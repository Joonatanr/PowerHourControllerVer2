#ifndef BITMAPS_H
#define BITMAPS_H

#include "typedefs.h"

typedef struct
{
    U16 height;
    U16 width;
    const U8 * bmp_data;
} Bitmap;


extern const Bitmap girl_1_bitmap;
extern const Bitmap girl_2_bitmap;

extern const Bitmap strong_dude_bitmap;
extern const Bitmap chad_bitmap;

extern const Bitmap test_palmtree_bmp;
extern const Bitmap beershot_bmp;
extern const Bitmap small_shot_bitmap;

#endif
