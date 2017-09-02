

#include "ShotGlassAnimation.h"

#define NUMBER_OF_ANIMATION_FRAMES 9u


//
//  Image data for shot_0_8
//

const U8 shot_0_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xC0, 0x40, 0x60, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0x60, 0x40, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x7E, 0xE7, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC3, 0xC3, 0x66, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_0_8
#define shot_0_8WidthPixels 33
#define shot_0_8HeightPixels 64

Private const Bitmap priv_shot_0_bmp =
{
 .bmp_data = shot_0_8Bitmaps,
 .height = shot_0_8HeightPixels,
 .width = shot_0_8WidthPixels,
};

//
//  Image data for shot_1_8
//

const U8 shot_1_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xC0, 0x60, 0x20, 0x30, 0x10, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x18, 0x10, 0x30, 0x20, 0xE0, 0xC0, 0x80, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x0E, 0x0C, 0x18, 0x10, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0x60, 0x60, 0x60, 0x20, 0x20, 0x20, 0x20, 0x30, 0x10, 0x18, 0x18, 0x0E, 0xFF, 0x0F, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_1_8
#define shot_1_8WidthPixels 33
#define shot_1_8HeightPixels 64

Private const Bitmap priv_shot_1_bmp =
{
 .bmp_data = shot_1_8Bitmaps,
 .height = shot_1_8HeightPixels,
 .width = shot_1_8WidthPixels,
};


//
//  Image data for shot_2_8
//

const U8 shot_2_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFC, 0x66, 0xE3, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0xC3, 0x67, 0xFC, 0x78, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_2_8
#define shot_2_8WidthPixels 33
#define shot_2_8HeightPixels 64


Private const Bitmap priv_shot_2_bmp =
{
 .bmp_data = shot_2_8Bitmaps,
 .height = shot_2_8HeightPixels,
 .width = shot_2_8WidthPixels,
};

//
//  Image data for shot_3_8
//

const U8 shot_3_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0x00, 0xC0, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x0C, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x0C, 0x08, 0x08, 0x18, 0x18, 0x30, 0x70, 0xC0, 0x80, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x06, 0x0C, 0x08, 0x18, 0x10, 0x30, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x30, 0x30, 0x10, 0x18, 0x18, 0x0C, 0x06, 0xFF, 0x07, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_3_8
#define shot_3_8WidthPixels 33
#define shot_3_8HeightPixels 64

Private const Bitmap priv_shot_3_bmp =
{
 .bmp_data = shot_3_8Bitmaps,
 .height = shot_3_8HeightPixels,
 .width = shot_3_8WidthPixels,
};

//
//  Image data for shot_4_8
//

const U8 shot_4_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0xC0, 0xE0, 0x20, 0x30, 0x30, 0x10, 0x18, 0x08, 0x0C, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x0C, 0x08, 0x18, 0x18, 0x10, 0x30, 0x60, 0x60, 0xC0, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xC6, 0x0C, 0x0C, 0x18, 0x18, 0x10, 0x30, 0x30, 0x30, 0x20, 0x20, 0x60, 0x60, 0x60, 0x60, 0x20, 0x30, 0x30, 0x30, 0x10, 0x10, 0x18, 0x08, 0x0C, 0x06, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xF8, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_4_8
#define shot_4_8WidthPixels 33
#define shot_4_8HeightPixels 64

Private const Bitmap priv_shot_4_bmp =
{
 .bmp_data = shot_4_8Bitmaps,
 .height = shot_4_8HeightPixels,
 .width = shot_4_8WidthPixels,
};


//
//  Image data for shot_5_8
//

const U8 shot_5_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0xFC, 0x6E, 0xC2, 0xC3, 0x83, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x81, 0x83, 0xC6, 0x66, 0xFC, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x01, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xF8, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_5_8
#define shot_5_8WidthPixels 33
#define shot_5_8HeightPixels 64

Private const Bitmap priv_shot_5_bmp =
{
 .bmp_data = shot_5_8Bitmaps,
 .height = shot_5_8HeightPixels,
 .width = shot_5_8WidthPixels,
};

//
//  Image data for shot_6_8
//

const U8 shot_6_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x09, 0x09, 0x09, 0x0B, 0x1B, 0x1A, 0x1A, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1A, 0x1A, 0x1B, 0x0B, 0x0B, 0x09, 0x09, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0xC0, 0xE0, 0x20, 0x30, 0x30, 0x10, 0x58, 0xA8, 0x48, 0x08, 0x48, 0x28, 0x58, 0xA8, 0x08, 0x68, 0x08, 0x48, 0xA8, 0x38, 0x98, 0x18, 0x10, 0x70, 0x60, 0x60, 0xC0, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0xFF, 0x06, 0x0C, 0x1C, 0x18, 0x32, 0x37, 0x22, 0x25, 0x32, 0x27, 0x32, 0x65, 0x72, 0x60, 0x64, 0x32, 0x24, 0x32, 0x27, 0x32, 0x35, 0x12, 0x19, 0x0C, 0x06, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xF8, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_6_8
#define shot_6_8WidthPixels 33
#define shot_6_8HeightPixels 64

Private const Bitmap priv_shot_6_bmp =
{
 .bmp_data = shot_6_8Bitmaps,
 .height = shot_6_8HeightPixels,
 .width = shot_6_8WidthPixels,
};

//
//  Image data for shot_7_8
//

const U8 shot_7_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0x8E, 0x86, 0x86, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x86, 0x86, 0x8C, 0xCC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x03, 0x06, 0x04, 0x04, 0x0D, 0x89, 0x89, 0x89, 0x8B, 0xDB, 0xDA, 0x5A, 0xD2, 0xD2, 0xD2, 0xB2, 0xD2, 0xFA, 0xDA, 0xDB, 0xCB, 0x8B, 0x89, 0x89, 0x0D, 0x0D, 0x04, 0x06, 0x07, 0xE1, 0xFF,
    0x00, 0xFF, 0x00, 0xFC, 0x7E, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x26, 0xFE, 0x00, 0xFF, 0x03,
    0x00, 0xFF, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xF8, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x30, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_7_8
#define shot_7_8WidthPixels 33
#define shot_7_8HeightPixels 64


Private const Bitmap priv_shot_7_bmp =
{
 .bmp_data = shot_7_8Bitmaps,
 .height = shot_7_8HeightPixels,
 .width = shot_7_8WidthPixels,
};

//
//  Image data for shot_8_8
//

const U8 shot_8_8Bitmaps[] =
{
    0xF0, 0xB8, 0x7C, 0xCC, 0xFE, 0xD6, 0xDE, 0xDE, 0x7E, 0x7F, 0xFF, 0x27, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x53, 0xFF, 0x7A, 0xFE, 0xF6, 0xF6, 0xFC, 0xEC, 0x7C, 0x98, 0xF0,
    0x3F, 0xFD, 0x23, 0xFF, 0xED, 0xBD, 0xFF, 0xF9, 0xF9, 0xF9, 0xFB, 0xFB, 0xFA, 0xFF, 0xFF, 0xFF, 0xF3, 0xF2, 0xF7, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xED, 0xFF, 0xFD, 0xFD, 0xFC, 0xFE, 0xFF, 0xFD, 0xFF,
    0x00, 0xFF, 0x02, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFB, 0xFF, 0xFF, 0xFB, 0xDF, 0x8B, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0x0B,
    0x00, 0xFF, 0x80, 0xFF, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0xE3, 0xA2, 0xE7, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x05, 0x07, 0x03, 0x03, 0x01, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0xFF, 0x01, 0xF8, 0x1F, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0xC0, 0xFF, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x0E, 0x19, 0x13, 0x33, 0x66, 0x6C, 0x58, 0x50, 0xD0, 0xF0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB0, 0xF0, 0xD0, 0x50, 0x58, 0x6C, 0x26, 0x33, 0x10, 0x1C, 0x07, 0x00, 0x00,
};

// Bitmap sizes for shot_8_8
#define shot_8_8WidthPixels 33
#define shot_8_8HeightPixels 64

Private const Bitmap priv_shot_8_bmp =
{
 .bmp_data = shot_8_8Bitmaps,
 .height = shot_8_8HeightPixels,
 .width = shot_8_8WidthPixels,
};


Private const Bitmap * priv_animation_bmps[NUMBER_OF_ANIMATION_FRAMES] =
{
 &priv_shot_0_bmp,
 &priv_shot_1_bmp,
 &priv_shot_2_bmp,
 &priv_shot_3_bmp,
 &priv_shot_4_bmp,
 &priv_shot_5_bmp,
 &priv_shot_6_bmp,
 &priv_shot_7_bmp,
 &priv_shot_8_bmp,
};

Private U8 priv_animation_index;


/* Public function declarations. */
Public const Bitmap * ShotGlassAnimation_GetFirst(void)
{
    priv_animation_index = 0u;
    return priv_animation_bmps[priv_animation_index];
}

Public const Bitmap * ShotGlassAnimation_GetLast(void)
{
    priv_animation_index = NUMBER_OF_ANIMATION_FRAMES - 1u;
    return priv_animation_bmps[priv_animation_index];
}

Public const Bitmap * ShotGlassAnimation_GetNext(void)
{
    priv_animation_index++;

    if (priv_animation_index >= NUMBER_OF_ANIMATION_FRAMES)
    {
        priv_animation_index = 0u;
    }
    return priv_animation_bmps[priv_animation_index];
}

Public const Bitmap * ShotGlassAnimation_GetPrev(void)
{
    if (priv_animation_index == 0u)
    {
        priv_animation_index = NUMBER_OF_ANIMATION_FRAMES - 1u;
    }
    else
    {
        priv_animation_index--;
    }
    return priv_animation_bmps[priv_animation_index];
}




