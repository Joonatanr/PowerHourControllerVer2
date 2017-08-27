/*
 * display_drv.c
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#include "display_drv.h"
#include <driverlib.h>
#include "spi_drv.h"
#include "bitmaps.h"
#include "register.h"

#define NUMBER_OF_PAGES 8u
#define NUMBER_OF_COLUMNS 128u
#define NUMBER_OF_ROWS (NUMBER_OF_PAGES * 8u)

#define GET_SEGMENT(column) ((column) >> 3u) //Divided by 8, since there are 8 columns per segment.
#define GET_FIRST_COLUMN(segment) ((segment) << 3u) //Multiplied with 8, returns the first column index of a segment.


/*****************************************************************************************************
 *
 * Type definitions.
 *
 *****************************************************************************************************/
typedef struct
{
    FillPatternType id;
    U8 number_of_segments;
    const U8 * pattern;
} FillPattern;


/* TODO : Some of these could be replaced with macros, or inline functions. */

/*****************************************************************************************************
 *
 * Private function prototypes
 *
 *****************************************************************************************************/

Private void drawImage(Point * p, Size * s, const Bitmap * bmp);
Private void drawPattern(Point * p, Size * s, const FillPattern * patternType);
Private void disp_command(U8 cmd, Boolean reg_select);
Private void set_page_address(U8 page);
Private void set_column(U8 column);
Private void write_data(U8 data);
Private void display_reset(void);
Private void display_empty(void);


/*****************************************************************************************************
 *
 * Private variable declarations.
 *
 *****************************************************************************************************/

Private U8 priv_display_buffer[NUMBER_OF_COLUMNS][NUMBER_OF_PAGES];
Private U8 priv_split_buffer[NUMBER_OF_COLUMNS]; //Used for splitting image data between pages.

Private U16 priv_page_validity_bits[NUMBER_OF_PAGES]; //Each page is divided into 16 virtual segments.


//Display patterns.


Private const U8 priv_white_pattern = 0x00u;
Private const U8 priv_black_pattern = 0xffu;
Private const U8 priv_gray_pattern[2u] = {0xAAu, 0x55u };

Private const FillPattern priv_fill_patterns[NUMBER_OF_PATTERNS] =
{
     {PATTERN_WHITE, 1u, &priv_white_pattern    },
     {PATTERN_BLACK, 1u, &priv_black_pattern    },
     {PATTERN_GRAY,  2u, priv_gray_pattern      }
};




volatile Boolean isDisplayReady = FALSE;

/* Set up A0 pin for display. */
Public void display_init(void)
{
    //Set the chip select pin as high initially.
    memset(priv_display_buffer, 0x00u, sizeof(priv_display_buffer));
    memset(priv_page_validity_bits, 0x0000u, sizeof(priv_page_validity_bits));

    display_reset();
    set_cs_pin(1u);
}

//Should be called after display_init.
Public void display_start(void)
{
    //Low CS, means that it is active.
    set_cs_pin(0u);

    //Display start line set.
    disp_command(0x40u, FALSE);

    //Set ADC in reverse
    disp_command(0xA1u, FALSE);
    //Common output mode select
    disp_command(0xC0u, FALSE);

    //display normal
    disp_command(0xA6u, FALSE);

    //LCD bias set
    disp_command(0xA2u, FALSE);

    //Power control set
    disp_command(0x2Fu, FALSE);

    //Booster ratio set.
    disp_command(0xF8u, FALSE);
    disp_command(0x00u, FALSE);

    //Contrast set.
    disp_command(0x27u, FALSE);
    disp_command(0x81u, FALSE);
    disp_command(0x10u, FALSE);

    //Static indicator set.
    disp_command(0xACu, FALSE);

    //Turn on display.
    disp_command(0x00u, FALSE);
    disp_command(0xAFu, FALSE);

    delay_msec(200);
    //Turn on all points.
    disp_command((0xA4u | 0x01u), FALSE);
    display_empty();
    delay_msec(2000);
    //Turn off all points.
    disp_command(0xA4u, FALSE);

    //TODO : Probably should remove this delay from here.
    delay_msec(500);

    display_clear();
    //display_drawBitmap(&test_palmtree_bmp, 0,0);
    //display_drawBitmap(&test_girl_bitmap, 0,0);

    //display_drawString("Hello World! \n Yolotron", 10u, ROW_3, FONT_LARGE_FONT);
    //display_drawString("Yoloswag", 1u, ROW_5, FONT_SMALL_FONT);
    //display_drawChar('H',24u, ROW_3);

    isDisplayReady = TRUE;
}


/* TODO : Implement this. */
Public void display_cyclic_50msec(void)
{
    //Redraw display.
    U8 page, column, seg, prev_column;
    if (isDisplayReady)
    {
        for (page = 0u; page < NUMBER_OF_PAGES; page++)
        {
            if (priv_page_validity_bits[page] > 0u)
            {
                //Redraw page.
                set_page_address(page);
                prev_column = 0xffu;

                for (seg = 0u; seg < 16u; seg++) //Iterate over each segment.
                {
                    if ((priv_page_validity_bits[page] >> seg) & (U16)0x01u)
                    {
                        column = GET_FIRST_COLUMN(seg);
                        if (column != prev_column)
                        {
                            set_column(column);
                        }
                        for (; column < GET_FIRST_COLUMN(seg + 1u); column++)
                        {
                            //write_data(priv_display_buffer[column][page]);
                            write_data(~priv_display_buffer[column][page]);
                        }
                        prev_column = column;
                    }
                }

                priv_page_validity_bits[page] = 0x0000u;
            }
        }
    }
}


Public void display_drawString(const char * str, U8 xloc, U8 yloc, FontType font)
{
    const char * ps = str;
    U8 x = xloc;
    U8 y = yloc;
    Size char_size;

    font_setFont(font);
    char_size.height = font_getFontHeight();

    while (*ps)
    {
        if (*ps == '\n')
        {
            x = xloc;
            y += char_size.height;
        }
        else
        {
            display_drawChar(*ps, x, y, &char_size);
            x += char_size.width + 1u; //TODO : Make it possible to change spaces between characters.
        }
        ps++;
    }
}

//Returns width of character, this must be changed later to more complex handling.
//TODO
Public void display_drawChar(char c, U8 xloc, U8 yloc, Size * destSize)
{
    Bitmap myBitMap;

    font_getFontChar(c, &myBitMap);
    display_drawBitmap(&myBitMap, xloc, yloc);

    destSize->height = myBitMap.height;
    destSize->width = myBitMap.width;
}


Public void display_drawBitmap(const Bitmap * bmp, U16 x, U16 y)
{
    Size mySize;
    Point myPoint;

    mySize.height = bmp->height;
    mySize.width = bmp->width;
    myPoint.x = x;
    myPoint.y = y;

    if (bmp != NULL)
    {
        drawImage(&myPoint, &mySize, bmp);
    }
}


//Draw rectangle into frame buffer and invalidate pages that contain the rectangle.
Public void display_fillRectangle(U16 x, U16 y, U16 height, U16 width, FillPatternType patternType)
{
    Size mySize;
    Point myPoint;

    mySize.height = height;
    mySize.width = width;

    myPoint.x = x;
    myPoint.y = y;

    if (patternType < NUMBER_OF_PATTERNS)
    {
        drawPattern(&myPoint, &mySize, &priv_fill_patterns[patternType]);
    }
}


Public void display_clear(void)
{
    U8 x, y;
    for (x = 0u; x < NUMBER_OF_PAGES; x++)
    {
        priv_page_validity_bits[x] = (U16)0xffffu; //Invalidate whole display.
        for(y = 0u; y < NUMBER_OF_COLUMNS; y++)
        {
            priv_display_buffer[y][x] = 0x00u;
        }
    }
    //TODO : Clearing validity bits should be replaced by a macro.
}


/*****************************************************************************************************
 *
 * Private Functions
 *
 *****************************************************************************************************/

Private void drawPattern(Point * p, Size * s, const FillPattern * pattern_ptr)
{
    U8 curr_page, bottom_page, top_page;
    U8 column, right_column, bottom_row;
    U8 mask, y_offset;

    U8 left_segment, right_segment, ix;
    U8 pattern_segment = 0u;

    //TODO : Might need to check if patternType is in range.
    const U8 * data;
    U8 value;

    data = pattern_ptr->pattern;

    if ((p->x < NUMBER_OF_COLUMNS) && (p->y < NUMBER_OF_ROWS))
    {
        bottom_row = p->y + s->height - 1;
        right_column = p->x + s->width;

        bottom_page = bottom_row >> 3u; //Divide with 8
        top_page = p->y >> 3u; //Divide with 8

        if (bottom_page >= NUMBER_OF_PAGES )
        {
            bottom_page = NUMBER_OF_PAGES - 1;
        }

        if (right_column >= NUMBER_OF_COLUMNS)
        {
            right_column = NUMBER_OF_COLUMNS - 1;
        }

        left_segment = GET_SEGMENT(p->x);
        right_segment = GET_SEGMENT(right_column);

        y_offset = p->y % 8u;

        for (curr_page = top_page; curr_page <= bottom_page; curr_page++)
        {
            mask = 0xffu;
            if (curr_page == top_page)
            {
                mask = mask << y_offset;
            }

            if (curr_page == bottom_page)
            {
                mask &= (0xffu >> (7u - (bottom_row % 8u)));
            }

            for (column = p->x; column <= right_column; column++)
            {
                //We are drawing a pattern.
                pattern_segment = column % pattern_ptr->number_of_segments;
                data = pattern_ptr->pattern + pattern_segment;
                value = *data;
                //priv_display_buffer[column][curr_page] |= (mask & value);
                priv_display_buffer[column][curr_page] &= (~mask);
                priv_display_buffer[column][curr_page] |= (mask & value);
            }

            //Invalidate page segments.
            for (ix = left_segment; ix <= right_segment; ix++)
            {
                priv_page_validity_bits[curr_page] |= (U16)((U16)1u << ix);
            }
        }
    }
}


//Draw an image in a rectangular area.
Private void drawImage(Point * p, Size * s, const Bitmap * bmp)
{
    U8 curr_page, bottom_page, top_page;
    U8 column, right_column, bottom_row;
    U8 mask, y_offset;

    U8 left_segment, right_segment, ix;

    //TODO : Might need to check if patternType is in range.
    const U8 * data;
    U8 value;

    //We start drawing a bitmap.
    data = bmp->bmp_data;

    if ((p->x < NUMBER_OF_COLUMNS) && (p->y < NUMBER_OF_ROWS))
    {
        bottom_row = p->y + s->height - 1;
        right_column = p->x + s->width - 1;

        bottom_page = bottom_row >> 3u; //Divide with 8
        top_page = p->y >> 3u; //Divide with 8

        if (bottom_page >= NUMBER_OF_PAGES )
        {
            bottom_page = NUMBER_OF_PAGES - 1;
        }

        if (right_column >= NUMBER_OF_COLUMNS)
        {
            right_column = NUMBER_OF_COLUMNS - 1;
        }

        left_segment = GET_SEGMENT(p->x);
        right_segment = GET_SEGMENT(right_column);

        y_offset = p->y % 8u;

        for (curr_page = top_page; curr_page <= bottom_page; curr_page++)
        {
            mask = 0xffu;
            if (curr_page == top_page)
            {
                mask = mask << y_offset;
            }

            if (curr_page == bottom_page)
            {
                if (bottom_row < NUMBER_OF_ROWS)
                {
                    //We do not need to mask, if the bitmap is out of bounds.
                    mask &= (0xffu >> (7u - (bottom_row % 8u)));
                }
            }

            for (column = p->x; column <= right_column; column++)
            {
                //We are drawing a bitmap.
                //We need to extract the value to be written to the display.
                value = (*data) << y_offset;

                if(curr_page != top_page)
                {
                    value |= priv_split_buffer[column]; //Should contain the top bits for the bitmap image. If it is top page, then these bits are ignored anyway.
                }
                if (y_offset > 0)
                {
                    priv_split_buffer[column] = (*data) >> (8u - y_offset);
                }

                //priv_display_buffer[column][curr_page] |= (mask & value);
                priv_display_buffer[column][curr_page] &= (~mask);
                priv_display_buffer[column][curr_page] |= (mask & value);
                data++;
            }

            //Invalidate page segments.
            for (ix = left_segment; ix <= right_segment; ix++)
            {
                priv_page_validity_bits[curr_page] |= (U16)((U16)1u << ix);
            }
        }
    }
}


//TODO : Replace this with macro.
Private inline void disp_command(U8 cmd, Boolean reg_select)
{
    spi_transmit_byte(cmd, reg_select);
}


Private inline void set_page_address(U8 page)
{
    disp_command(0xB0u | (page & 0x0fu), FALSE);
}


Private inline void write_data(U8 data)
{
    disp_command(data, TRUE);
}


Private inline void set_column(U8 column)
{
    //Set column MSB.
    disp_command(0x10u | (column >> 4u),  FALSE);
    //Set column LSB.
    disp_command(column & 0x0fu, FALSE);
}


Private void display_reset(void)
{
    set_disp_reset_pin(0u);
    delay_msec(100);
    set_disp_reset_pin(1u);
    delay_msec(100);
}

//This is more of a HW function, maybe it should still remain, but not be used when wanting to clear the framebuf instead.
Private void display_empty(void)
{
    U8 ix;
    U8 yx;

    for (ix = 0u; ix < NUMBER_OF_PAGES; ix++)
    {
        set_page_address(ix);
        set_column(0);
        for (yx = 0u; yx < NUMBER_OF_COLUMNS; yx++)
        {
            write_data(0xffu);
        }
    }
}





