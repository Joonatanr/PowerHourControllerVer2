/*
 * ScrollBar.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Joonatan
 */

#include <misc.h>
#include "Bargraph.h"
#include "display_drv.h"
#include "buttons.h"

#define BARGRAPH_BEGIN_X   14u
#define BARGRAPH_WIDTH    100u
#define BARGRAPH_HEIGHT     4u
#define BARGRAPH_OFFSET_Y   52u

#define UP_ARROW_OFFSET_Y   10u
#define DOWN_ARROW_OFFSET_Y 40u

#define NUMBER_OFFSET_Y     30u /* Currently this offset is from center, others are from top. */
#define NUMBER_BOX_WIDTH    20u
#define NUMBER_BOX_HEIGHT   20u

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

Public Bargraph_T TEST_BARGRAPH =
{
     .max_value = 100u,
     .min_value = 0u,
     .value = 50u,
     .parent = NULL,
     .text = "Test Bar"
};

/*******************/

Private Bargraph_T * priv_active_bar;
Private char priv_buf[10];

Private const Rectangle priv_number_box =
{
     .location = { GET_X_FROM_CENTER(64u, NUMBER_BOX_WIDTH), NUMBER_OFFSET_Y   },
     .size =     { NUMBER_BOX_HEIGHT,                        NUMBER_BOX_WIDTH  }
};

/***************************** Private function forward declarations  ******************************/

Private void drawBarGraph(void);
Private void drawBackGround(void);

Private void handleButtonUp(void);
Private void handleButtonDown(void);
Private void handleButtonAck(void);


/***************************** Public function definitions  ******************************/


/* Called when a scrollbar becomes active. */
Public void enterBarGraph(Bargraph_T * bar)
{
    priv_active_bar = bar;

    buttons_subscribeListener(RED_BUTTON, handleButtonUp);
    buttons_subscribeListener(BLUE_BUTTON, handleButtonDown);
    buttons_subscribeListener(BLACK_BUTTON, handleButtonAck);
    buttons_subscribeListener(GREEN_BUTTON, handleButtonAck);

    //priv_number_box = CreateRectangleAroundCenter((Point){64u, NUMBER_OFFSET_Y }, (Size){ 20u, 20u });

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
    display_fillRectangle(BARGRAPH_BEGIN_X, BARGRAPH_OFFSET_Y , BARGRAPH_HEIGHT, BARGRAPH_WIDTH, PATTERN_WHITE);
    /* Then draw the actual line. */
    display_fillRectangle(BARGRAPH_BEGIN_X, BARGRAPH_OFFSET_Y , BARGRAPH_HEIGHT, percentage, PATTERN_BLACK);

    //Draw the number.
    /* TODO : We should clear the previous number, but should do initial test before implementing this. */
    long2string(priv_active_bar->value, priv_buf);

    //display_drawStringCenter(priv_buf, 64u , NUMBER_OFFSET_Y, FONT_MEDIUM_FONT, FALSE);*/
    display_drawTextBox(&priv_number_box, priv_buf, FONT_MEDIUM_FONT);
}


/* Draws the arrows on the scrollbar sides. */
Private void drawBackGround(void)
{
    //Draw up arrow.
    display_drawBitmapCenter(&upArrowBitmap, 64u, UP_ARROW_OFFSET_Y , FALSE);

    //Draw down arrow.
    display_drawBitmapCenter(&downArrowBitmap, 64u, DOWN_ARROW_OFFSET_Y, FALSE);

    //Draw rectangle around the bar.
    /* TODO */
}


Private void handleButtonUp(void)
{
    if (priv_active_bar->value < priv_active_bar->max_value)
    {
        priv_active_bar->value++;
    }

    //Update the displayed data.
    drawBarGraph();
}

Private void handleButtonDown(void)
{
    if (priv_active_bar->value > priv_active_bar->min_value)
    {
        priv_active_bar->value--;
    }

    //Update the displayed data.
    drawBarGraph();
}

Private void handleButtonAck(void)
{
    if (priv_active_bar->parent != NULL)
    {
        buttons_unsubscribeAll();
        menu_enterMenu(priv_active_bar->parent);
        priv_active_bar = NULL;
    }
    /* Else, I guess we are stuck here...   */
    /* Maybe should restart, just in case?  */
}
