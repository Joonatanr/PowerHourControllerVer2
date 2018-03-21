/*
 * ScrollBar.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Joonatan
 */

#include "Scrollbar.h"
#include "display_drv.h"

#define SCROLLBAR_BEGIN_X   14u
#define SCROLLBAR_WIDTH    100u
#define SCROLLBAR_HEIGHT     4u

//
//  Image data for arrow_right
//
const U8 rightArrowBitmaps[] =
{

    0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3E, 0x1C, 0x08,
    0x01, 0x01, 0x01, 0x01, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

Private const Bitmap rightArrowBmp =
{
 .bmp_data = rightArrowBitmaps,
 .height = 23u,
 .width = 16u
};

//
//  Image data for arrow_left
//

const U8 arrow_leftBitmaps [] =
{
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0,
    0x08, 0x1C, 0x3E, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0x01, 0x01, 0x01, 0x01,
};

Private const Bitmap leftArrowBmp =
{
 .bmp_data = arrow_leftBitmaps,
 .height = 23u,
 .width = 16u
};

/******************/

/* Lets define all available scrollbars here as public variables. */

Public ScrollBar_T test_bar =
{
     .max_value = 100u,
     .min_value = 0u,
     .value = 50u,
     .parent = NULL,
     .text = "Test Bar"
};

/*******************/

Private ScrollBar_T * priv_active_bar;


/***************************** Private function forward declarations  ******************************/

Private void drawScrollBar(void);
Private void drawArrows(void);


/***************************** Public function definitions  ******************************/


/* Called when a scrollbar becomes active. */
Public void enterScrollBar(ScrollBar_T * bar)
{
    priv_active_bar = bar;
    drawArrows();
    drawScrollBar();
}


/***************************** Private function definitions  ******************************/

/* Draws whole scrollbar */
Private void drawScrollBar(void)
{
    U16 percentage;
    U8 range = priv_active_bar->max_value - priv_active_bar->min_value;

    percentage = ((priv_active_bar->max_value - priv_active_bar->value) * 100u) / range;

    //Draw the line
    /* We clear it first. */
    display_fillRectangle(SCROLLBAR_BEGIN_X, 32u - SCROLLBAR_HEIGHT , SCROLLBAR_HEIGHT, SCROLLBAR_WIDTH, PATTERN_WHITE);
    /* Then draw the actual line. */
    display_fillRectangle(SCROLLBAR_BEGIN_X, 32u - SCROLLBAR_HEIGHT , SCROLLBAR_HEIGHT, percentage, PATTERN_BLACK);
}


/* Draws the arrows on the scrollbar sides. */
Private void drawArrows(void)
{
    //Draw left arrow.
    display_drawBitmapCenter(&leftArrowBmp, 10u, 32u , FALSE);

    //Draw right arrow.
    display_drawBitmapCenter(&rightArrowBmp, 118u, 32u, FALSE);
}
