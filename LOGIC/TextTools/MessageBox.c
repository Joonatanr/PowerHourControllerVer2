/*
 * MessageBox.c
 *
 *  Created on: Sep 4, 2018
 *      Author: Joonatan
 */

#include "MessageBox.h"
#include "display_drv.h"
#include "misc.h"
#include "register.h"
#include "buttons.h"
#include "LOGIC/Scheduler.h"

#define MSGBOX_FONT FONT_MEDIUM_FONT
//#define MSGBOX_FONT FONT_SMALL_FONT

#define MSGBOX_MIN_HEIGHT 25u
#define MSGBOX_MIN_WIDTH  35u

#define MSGBOX_MARGIN     10u

#define BUTTON_AREA_HEIGHT 18u

/**************************** Private function forward declarations **************************/

Private void drawMessageBox(const char * text, Boolean includeButtonArea);
Private void drawButton(const char * text, U8 xloc);
Private Size getMessageSize(const char * text);
Private void clearBox(void);
Private void handleOkPress(void);

Private Rectangle priv_msg_box;


/**************************** Public function definitions **************************/

/* TODO : Rework this... */
Public void MessageBox_Show(const char * text, U16 period)
{
    drawMessageBox(text, FALSE);
    delay_msec(period);
    clearBox();
}

/* TODO : Add also option for cancel button and to get info on user feedback. */
Public void MessageBox_ShowWithOk(const char * text)
{
    buttons_unsubscribeAll();
    buttons_subscribeListener(OK_BUTTON , handleOkPress);

    drawMessageBox(text, TRUE);
    drawButton("OK", 63u);

    //while(!priv_is_ok_pressed); Won't work because we currently only have 1 thread...

    /* So we pause the active module until OK has been pressed. */
    Scheduler_SetActiveModulePause(TRUE);
}

/**************************** Private function definitions **************************/

Private void drawMessageBox(const char * text, Boolean includeButtonArea)
{
    Size textSize = getMessageSize(text);
    Size rectSize;
    Point rectLocation;
    Rectangle box;

    rectSize.height = MAX(MSGBOX_MIN_HEIGHT, (textSize.height + MSGBOX_MARGIN));
    rectSize.width =  MAX(MSGBOX_MIN_WIDTH,  (textSize.width + MSGBOX_MARGIN));

    if (includeButtonArea)
    {
        rectSize.height += BUTTON_AREA_HEIGHT;
    }

    rectSize.height = MIN(rectSize.height, NUMBER_OF_ROWS);
    rectSize.width = MIN(rectSize.width, NUMBER_OF_COLUMNS);

    rectLocation.x = GET_X_FROM_CENTER(NUMBER_OF_COLUMNS / 2, rectSize.width);
    rectLocation.y = GET_Y_FROM_CENTER(NUMBER_OF_ROWS / 2, rectSize.height);

    box.location = rectLocation;
    box.size = rectSize;

    if (includeButtonArea)
    {
        box.size.height -= BUTTON_AREA_HEIGHT;
    }

    /* Draw just 1 line for now. */
    display_drawTextBox(&box, text, MSGBOX_FONT);

    /* This area won't be cleared otherwise. */
    if (includeButtonArea)
    {
        display_fillRectangle(rectLocation.x , rectLocation.y + box.size.height, BUTTON_AREA_HEIGHT, rectSize.width, PATTERN_WHITE);
    }

    //Draw the border.
    display_drawRectangle(rectLocation.x, rectLocation.y, rectSize.height, rectSize.width, 2u);

    priv_msg_box.location = rectLocation;
    priv_msg_box.size = rectSize;
}


Private void drawButton(const char * text, U8 xloc)
{
    U8 yloc;
    Rectangle buttonBox;
    Size textSize;

    yloc = (priv_msg_box.location.y + priv_msg_box.size.height) - BUTTON_AREA_HEIGHT;
    yloc++;

    textSize = getMessageSize(text);
    textSize.width += 8u; //Create some margins here.

    buttonBox.location.x = GET_X_FROM_CENTER(xloc, textSize.width);
    buttonBox.location.y = yloc;
    buttonBox.size = textSize;

    display_drawTextBox(&buttonBox, text, MSGBOX_FONT);
    display_drawRectangle(buttonBox.location.x,
                          buttonBox.location.y,
                          buttonBox.size.height,
                          buttonBox.size.width,
                          1u);
}


/* Should be called at the end to clear up the box. */
Private void clearBox(void)
{
    /* TODO : Should record display buffer before opening box, and then restore that here... */
    display_fillRectangle(priv_msg_box.location.x,
                          priv_msg_box.location.y,
                          priv_msg_box.size.height,
                          priv_msg_box.size.width,
                          PATTERN_WHITE);
}

/* Returns physical size of the text to be displayed */
Private Size getMessageSize(const char * text)
{
    Size ret;
    U8 number_of_rows = 1u;
    U8 current_row_width = 0u;
    U8 max_row_width = 0u;
    U8 fontsize = font_getFontHeight(MSGBOX_FONT);

    const char *ps = text;
    while (*ps)
    {
        if (*ps == '\n')
        {
          number_of_rows++;
          max_row_width = MAX(current_row_width, max_row_width);
          current_row_width = 0u;
        }
        else
        {
            current_row_width += font_getCharWidth(*ps, MSGBOX_FONT);
            current_row_width++; //Account for one bit in between chars.
        }
        ps++;
    }

    max_row_width = MAX(current_row_width, max_row_width);
    /* Lets try this with 1 row at first, and later test with multiple rows... */
    ret.height = fontsize * number_of_rows;
    ret.width = max_row_width;

    return ret;
}


Private void handleOkPress(void)
{
    Scheduler_SetActiveModulePause(FALSE);
}