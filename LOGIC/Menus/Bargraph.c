/*
 * ScrollBar.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Joonatan
 */

#include "Bargraph.h"
#include "display_drv.h"

#define BARGRAPH_BEGIN_X   14u
#define BARGRAPH_WIDTH    100u
#define BARGRAPH_HEIGHT     4u


const U8 monochrom_arrow_upBitmaps[] =
{
    0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};

// Bitmap sizes for monochrom_arrow_up
#define monochrom_arrow_upWidthPixels 17u
#define monochrom_arrow_upHeightPixels 9u

Private const Bitmap upArrowBitmap =
{
     .bmp_data = monochrom_arrow_upBitmaps,
     .height = monochrom_arrow_upHeightPixels,
     .width = monochrom_arrow_upWidthPixels
};


const U8 monochrom_arrow_downBitmaps[] =
{
    0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// Bitmap sizes for monochrom_arrow_down
#define monochrom_arrow_downWidthPixels 17u
#define monochrom_arrow_downHeightPixels 9u

Private const Bitmap downArrowBitmap =
{
     .bmp_data = monochrom_arrow_downBitmaps,
     .height = monochrom_arrow_downHeightPixels,
     .width = monochrom_arrow_downWidthPixels
};


/******************/

/* Lets define all available scrollbars here as public variables. */

Public BarGraph_T test_bar =
{
     .max_value = 100u,
     .min_value = 0u,
     .value = 50u,
     .parent = NULL,
     .text = "Test Bar"
};

/*******************/

Private BarGraph_T * priv_active_bar;


/***************************** Private function forward declarations  ******************************/

Private void drawBarGraph(void);
Private void drawBackGround(void);


/***************************** Public function definitions  ******************************/


/* Called when a scrollbar becomes active. */
Public void enterBarGraph(BarGraph_T * bar)
{
    priv_active_bar = bar;
    drawBackGround();
    drawBarGraph();
}


/***************************** Private function definitions  ******************************/

/* Draws whole scrollbar */
Private void drawBarGraph(void)
{
    U16 percentage;
    U8 range = priv_active_bar->max_value - priv_active_bar->min_value;

    percentage = ((priv_active_bar->max_value - priv_active_bar->value) * 100u) / range;

    //Draw the line
    /* We clear it first. */
    display_fillRectangle(BARGRAPH_BEGIN_X, 32u - BARGRAPH_HEIGHT , BARGRAPH_HEIGHT, BARGRAPH_WIDTH, PATTERN_WHITE);
    /* Then draw the actual line. */
    display_fillRectangle(BARGRAPH_BEGIN_X, 32u - BARGRAPH_HEIGHT , BARGRAPH_HEIGHT, percentage, PATTERN_BLACK);
}


/* Draws the arrows on the scrollbar sides. */
Private void drawBackGround(void)
{
    //Draw up arrow.
    display_drawBitmapCenter(&upArrowBitmap, 64u, 10u , FALSE);

    //Draw down arrow.
    display_drawBitmapCenter(&downArrowBitmap, 64u, 54u, FALSE);

    //Draw rectangle around the bar.
    /* TODO */
}
