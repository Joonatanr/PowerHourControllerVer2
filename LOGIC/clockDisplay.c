/*
 * clockDisplay.c
 *
 *  Created on: Aug 27, 2017
 *      Author: Joonatan
 */


#include "clockDisplay.h"
#include "display_drv.h"

#define BEERSHOT_X 80
#define BEERSHOT_Y 1

Private void incrementTimer(void);
Private void convertTimerString(timekeeper_struct * t, char * dest_str);

Private void drawBeerShot(void);
Private void clearBeerShot(void);

Private timekeeper_struct priv_timekeeper;
Private Boolean priv_isTimekeeperEnabled;
Private char priv_timer_str[10];

#define CLOCK_FONT FONT_NUMBERS_HUGE
//Private U8 priv_timer_yloc;
//Private const U8 priv_timer_xloc = 1u;
Private Rectangle priv_timer_rect;

Public void clockDisplay_init(void)
{
    U8 font_height;

    priv_timekeeper.min = 0u;
    priv_timekeeper.sec = 0u;

    font_height = font_getFontHeight(CLOCK_FONT);

    priv_timer_rect.location.x = 1u;

    priv_timer_rect.location.y = NUMBER_OF_ROWS >> 1u; //Divide by 2.
    priv_timer_rect.location.y -= (font_height >> 1u);

    priv_timer_rect.size.height = font_height;
    priv_timer_rect.size.width = 15u * 5u; //TODO : This should be changed, once font handling has been improved.
}

Public void clockDisplay_start(void)
{
    priv_isTimekeeperEnabled = TRUE;
}

Public void clockDisplay_cyclic1000msec(void)
{
    if (priv_isTimekeeperEnabled)
    {
        incrementTimer();
        convertTimerString(&priv_timekeeper, priv_timer_str);

        if ((priv_timekeeper.sec == 0u) && (priv_timekeeper.min > 0))
        {
            drawBeerShot();
        }
        else if(priv_timekeeper.sec == 10u)
        {
            clearBeerShot();
        }

        //Currently for testing.
        //TODO : This is quite inefficient, should change it to a better solution.
        display_fillRectangle(priv_timer_rect.location.x,
                              priv_timer_rect.location.y,
                              priv_timer_rect.size.height,
                              priv_timer_rect.size.width,
                              PATTERN_WHITE);

        display_drawString(priv_timer_str,
                           priv_timer_rect.location.x,
                           priv_timer_rect.location.y,
                           CLOCK_FONT);
    }
}

//Increments timekeeper with 1 second.
Private void incrementTimer(void)
{
    priv_timekeeper.sec++;
    if (priv_timekeeper.sec >= 60u)
    {
        priv_timekeeper.sec = 0u;
        priv_timekeeper.min++;
    }
}

Private void convertTimerString(timekeeper_struct * t, char * dest_str)
{
    dest_str[0] = '0' + (t->min / 10u);
    dest_str[1] = '0' + (t->min % 10u);
    dest_str[2] = ':';
    dest_str[3] = '0' + (t->sec / 10u);
    dest_str[4] = '0' + (t->sec % 10u);
    dest_str[5] = 0;
}

Private void drawBeerShot(void)
{
   display_drawBitmap(&beershot_bmp, BEERSHOT_X, BEERSHOT_Y);
}

Private void clearBeerShot(void)
{
    display_fillRectangle(BEERSHOT_X, BEERSHOT_Y, 63u, 43u, PATTERN_WHITE);
}

