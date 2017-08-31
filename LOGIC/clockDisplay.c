/*
 * clockDisplay.c
 *
 *  Created on: Aug 27, 2017
 *      Author: Joonatan
 */


#include "clockDisplay.h"
#include "display_drv.h"
#include "ShotGlassAnimation.h"

#define BEERSHOT_X 86
#define BEERSHOT_Y 1

#define SPECIAL_TASK_FREQUENCY 4u //TODO : This is not finished yet, current implementation is a placeholder.
#define SPECIAL_TASK_LENGTH 15u //in seconds.

/*****************************************************************************************************
 *
 * Private type definitions
 *
 *****************************************************************************************************/

typedef enum
{
    CONTROLLER_INIT,
    CONTROLLER_COUNTING,
    CONTROLLER_SPECIAL_TASK,
    CONTROLLER_NUMBER_OF_STATES
} controllerState;


/*****************************************************************************************************
 *
 * Private function Prototypes
 *
 *****************************************************************************************************/

Private void incrementTimer(void);
Private void convertTimerString(timekeeper_struct * t, char * dest_str);

Private void drawBeerShot(void);
Private void clearBeerShot(void);
Private void enterSpecialTask(void);

Private timekeeper_struct priv_timekeeper;
Private controllerState priv_timer_state;
Private U8 priv_special_task_counter;
Private char priv_timer_str[10];

Private void setUpperText(const char * str);
Private void setLowerText(const char * str);

Private void clearUpperText(void);
Private void clearLowerText(void);

Private void drawTimer(void);

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

    priv_timer_state = CONTROLLER_INIT;
}

Public void clockDisplay_start(void)
{
    //We start counting.
    priv_timer_state = CONTROLLER_COUNTING;
}

Public void clockDisplay_cyclic1000msec(void)
{
    static Boolean isFirst = TRUE; //TODO : This is placeholder, must improve.

    switch(priv_timer_state)
    {
    case CONTROLLER_INIT:
        //We do not do anything here.
        break;
    case CONTROLLER_COUNTING:
        incrementTimer();
        convertTimerString(&priv_timekeeper, priv_timer_str);

        if(isFirst)
        {
            isFirst = FALSE;
            clearBeerShot();
        }

        if ((priv_timekeeper.sec == 0u) && (priv_timekeeper.min > 0))
        {
            if ((priv_timekeeper.min % SPECIAL_TASK_FREQUENCY) == 0u)
            {
                //We do special task.
                enterSpecialTask();
                break;
            }
            else
            {
                //TODO : Insert beep here.
            }
        }
        else if(priv_timekeeper.sec == 10u)
        {
            clearBeerShot();
            //setUpperText("PROOSIT! TEST");
            //setLowerText("Viinaminut TEST");
        }
        else if((priv_timekeeper.sec <= 50u) && (priv_timekeeper.sec > 10u))
        {
            //Basically we increment the animation.
            drawBeerShot();
        }

        if (priv_timekeeper.sec == 20u)
        {
            setUpperText("Täitke pitsid!");
        }

        if (priv_timekeeper.sec == 58u)
        {
            setUpperText("Proosit!");
        }

        drawTimer();

        break;
    case CONTROLLER_SPECIAL_TASK:
        //We still increment timer.
        incrementTimer();
        if (++priv_special_task_counter > SPECIAL_TASK_LENGTH)
        {
            //We return to normal state.
            display_clear();
            priv_timer_state = CONTROLLER_COUNTING;
        }
        break;
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
   //display_drawBitmap(&beershot_bmp, BEERSHOT_X, BEERSHOT_Y);
   const Bitmap * bmp_ptr = ShotGlassAnimation_GetNext();
   display_drawBitmap(bmp_ptr, BEERSHOT_X, BEERSHOT_Y);
}

Private void clearBeerShot(void)
{
    display_fillRectangle(BEERSHOT_X, BEERSHOT_Y, 63u, 43u, PATTERN_WHITE);
    const Bitmap * bmp_ptr = ShotGlassAnimation_GetFirst();
    display_drawBitmap(bmp_ptr, BEERSHOT_X, BEERSHOT_Y);
}

//We start displaying a special task.
Private void enterSpecialTask(void)
{
    priv_timer_state = CONTROLLER_SPECIAL_TASK;
    priv_special_task_counter = 0u;

    display_clear();
    //TODO : Replace this with actual task, good enough for testing.
    display_drawBitmap(&test_girl_bitmap, 0u, 0u);
    display_drawString("Naised paljaks!", 64, 4, FONT_SMALL_FONT);
}

Private void drawTimer(void)
{
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


Private void setUpperText(const char * str)
{
    clearUpperText();
    display_drawString(str, 2u, 0u, FONT_LARGE_FONT);
}

//TODO : Replace this area with defined points.
Private void clearUpperText(void)
{
    display_fillRectangle(2u, 0u, 10u, 80u, PATTERN_WHITE);
}

Private void setLowerText(const char * str)
{
    clearLowerText();
    display_drawString(str, 2u, 50u, FONT_LARGE_FONT);
}

Private void clearLowerText(void)
{
    display_fillRectangle(2u, 0u, 50u, 80u, PATTERN_WHITE);
}




