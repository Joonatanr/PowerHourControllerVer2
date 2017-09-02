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

#define SPECIAL_TASK_FREQUENCY 2u //TODO : This is not finished yet, current implementation is a placeholder.
#define SPECIAL_TASK_LENGTH 15u //in seconds.

//Text box definitions.
#define UPPER_TEXT_XLOC 2u
#define UPPER_TEXT_YLOC 2u
#define UPPER_TEXT_HEIGHT 13u
#define UPPER_TEXT_WIDTH 80u
#define UPPER_TEXT_FONT FONT_MEDIUM_FONT

#define LOWER_TEXT_XLOC 2u
#define LOWER_TEXT_YLOC 51u
#define LOWER_TEXT_HEIGHT 13u
#define LOWER_TEXT_WIDTH 80u
#define LOWER_TEXT_FONT FONT_MEDIUM_FONT

/*****************************************************************************************************
 *
 * Private type definitions
 *
 *****************************************************************************************************/

typedef enum
{
    CONTROLLER_INIT,
    CONTROLLER_COUNTING,
    CONTROLLER_OVERRIDDEN,
    CONTROLLER_NUMBER_OF_STATES
} controllerState;

typedef enum
{
    BEERSHOT_NO_ACTION,         //No action with bitmap.
    BEERSHOT_EMPTY,             //Draw initial beershot bitmap.
    BEERSHOT_BEGIN_FILLING,     //Initiate filling animation.
    BEERSHOT_FULL,              //Draw full beershot.
    BEERSHOT_BEGIN_EMPTYING,    //Initiate emptying animation.

    //TODO
    OVERRIDE_FUNCTION,          //Overrides ordinary function, displays bitmap instead.
    RESTORE_FUNCTION,           //Restore normal handling.
} beerShotAction;

typedef enum
{
    BEERSHOT_FROZEN,    //Nothing currently to draw.
    BEERSHOT_FILLING,
    BEERSHOT_EMPTYING
} beershotState;

typedef Boolean (*OverrideFunc)(U8 sec); //Returns TRUE, if done with override.

typedef struct
{
    U8 second;                      // When the event should be triggered.
    const char * upperText;         // Text to be written to upper part of display.
    const char * lowerText;         // Text to be written to lower part of display.
    beerShotAction shot_action;     // Action to be performed on bitmap.
    OverrideFunc    func;           // Optional parameter - This function will override all behaviour, used for special actions.
} ControllerEvent;




/*****************************************************************************************************
 *
 * Private function Prototypes
 *
 *****************************************************************************************************/

Private void incrementTimer(void);
Private void convertTimerString(timekeeper_struct * t, char * dest_str);

Private void drawBeerShot(beerShotAction action);
Private Boolean girlsSpecialIntro(U8 sec);
Private Boolean girlsSpecialTask(U8 sec);

Private timekeeper_struct priv_timekeeper;
Private controllerState priv_timer_state;
Private char priv_timer_str[10];

Private void setUpperText(const char * str);
Private void setLowerText(const char * str);

Private void clearUpperText(void);
Private void clearLowerText(void);

Private void drawTimer(void);


/*****************************************************************************************************
 *
 * Private variable declarations.
 *
 *****************************************************************************************************/

Private const ControllerEvent priv_initial_event =
{
 .second = 1u,
 .upperText = "Begin!",
 .lowerText = NULL,
 .shot_action = BEERSHOT_EMPTY
};


Private const ControllerEvent priv_normal_minute_events[] =
{
     { .second = 7u,  .upperText = "",              .lowerText = "",        .shot_action = BEERSHOT_EMPTY            , .func = NULL },
     { .second = 20u, .upperText = "Fill shots",    .lowerText = NULL,      .shot_action = BEERSHOT_BEGIN_FILLING    , .func = NULL },
     { .second = 45u, .upperText = "Ready",         .lowerText = NULL,      .shot_action = BEERSHOT_FULL             , .func = NULL },
     { .second = 59u, .upperText = "Proosit!",      .lowerText = "Cheers!", .shot_action = BEERSHOT_BEGIN_EMPTYING   , .func = NULL },
};

Private const ControllerEvent priv_guys_drink_events[] =
{

};

Private const ControllerEvent priv_girls_drink_events[] =
{
     { .second = 7u,  .upperText = "",              .lowerText = "",                    .shot_action = OVERRIDE_FUNCTION         , .func = &girlsSpecialIntro   },
     { .second = 20u, .upperText = "Fill shots",    .lowerText = "Girls round",         .shot_action = BEERSHOT_BEGIN_FILLING    , .func = NULL },
     { .second = 45u, .upperText = "Ready",         .lowerText = NULL,                  .shot_action = BEERSHOT_FULL             , .func = NULL },
     { .second = 59u, .upperText = "Proosit!",      .lowerText = "Cheers girls!",       .shot_action = OVERRIDE_FUNCTION         , .func = &girlsSpecialTask    },
};


Private beershotState priv_beer_state;
Private Rectangle priv_timer_rect;
Private OverrideFunc priv_override_ptr;

#define CLOCK_FONT FONT_NUMBERS_HUGE

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

Private U8 priv_override_counter;

Public void clockDisplay_cyclic1000msec(void)
{
    U8 ix;
    const ControllerEvent * event_ptr = NULL;
    beerShotAction action = BEERSHOT_NO_ACTION;
    static Boolean isFirstRun = TRUE;

    static const ControllerEvent * controllerEvents_ptr = priv_normal_minute_events;
    static U8 controllerEvents_cnt = NUMBER_OF_ITEMS(priv_normal_minute_events);


    if (priv_timekeeper.sec == 0u)
    {
        //We decide what kind of minute we are having.
        if (((priv_timekeeper.min % SPECIAL_TASK_FREQUENCY) == 0u) && priv_timekeeper.min > 0)
        {
            controllerEvents_ptr = priv_girls_drink_events;
            controllerEvents_cnt = NUMBER_OF_ITEMS(priv_girls_drink_events);
        }
        else
        {
            controllerEvents_ptr = priv_normal_minute_events;
            controllerEvents_cnt = NUMBER_OF_ITEMS(priv_normal_minute_events);
        }
    }


    switch(priv_timer_state)
    {
    case CONTROLLER_INIT:
        //We do not do anything here.
        break;
    case CONTROLLER_COUNTING:
        incrementTimer();
        if (isFirstRun)
        {
            event_ptr = &priv_initial_event;
            isFirstRun = FALSE;
        }
        else
        {
            for (ix = 0u; ix < controllerEvents_cnt; ix++)
            {
                event_ptr = &controllerEvents_ptr[ix];
                if (event_ptr->second == priv_timekeeper.sec)
                {
                    break;
                }
                event_ptr = NULL;
            }
        }

        if (event_ptr != NULL)
        {
           if (event_ptr->upperText != NULL)
           {
               setUpperText(event_ptr->upperText);
           }

           if (event_ptr->lowerText != NULL)
           {
               setLowerText(event_ptr->lowerText);
           }

           action = event_ptr->shot_action;
        }

        //Currently we still finish this cycle and special handling begins on the next.
        if (action == OVERRIDE_FUNCTION)
        {
            priv_timer_state = CONTROLLER_OVERRIDDEN;
            priv_override_ptr = event_ptr->func;
            priv_override_counter = 0u;
        }

        drawBeerShot(action);

        drawTimer();

        break;
    case CONTROLLER_OVERRIDDEN:
        //We still increment timer.
        incrementTimer();

        if (priv_override_ptr(priv_override_counter))
        {
            display_clear();
            drawTimer();
            drawBeerShot(BEERSHOT_EMPTY);
            priv_timer_state = CONTROLLER_COUNTING;
        }
        priv_override_counter++;
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


Private void drawBeerShot(beerShotAction action)
{
   const Bitmap * bmp_ptr = NULL;

   switch(action)
   {
       case BEERSHOT_EMPTY:
           bmp_ptr = ShotGlassAnimation_GetFirst();
           priv_beer_state = BEERSHOT_FROZEN;
           break;
       case BEERSHOT_FULL:
           bmp_ptr = ShotGlassAnimation_GetLast();
           priv_beer_state = BEERSHOT_FROZEN;
           break;
       case BEERSHOT_BEGIN_FILLING:
           bmp_ptr = ShotGlassAnimation_GetFirst();
           priv_beer_state = BEERSHOT_FILLING;
           break;
       case BEERSHOT_BEGIN_EMPTYING:
           bmp_ptr = ShotGlassAnimation_GetLast();
           priv_beer_state = BEERSHOT_EMPTYING;
           break;
       case BEERSHOT_NO_ACTION:
       default:
           break;
   }

   switch(priv_beer_state)
   {
       case(BEERSHOT_FROZEN):
           //Nothing new to draw.
           break;
       case(BEERSHOT_EMPTYING):
           if(bmp_ptr == NULL)
           {
               bmp_ptr = ShotGlassAnimation_GetPrev();
           }
           break;
       case(BEERSHOT_FILLING):
           if(bmp_ptr == NULL)
           {
               bmp_ptr = ShotGlassAnimation_GetNext();
           }
           break;
       default:
           break;
   }

   //If bmp_ptr is not NULL, then we have something to draw.
   if (bmp_ptr != NULL)
   {
       display_drawBitmap(bmp_ptr, BEERSHOT_X, BEERSHOT_Y);
   }
}


//We start displaying a special task.
Private Boolean girlsSpecialIntro(U8 sec)
{
    Boolean res = FALSE;

    switch(sec)
    {
    case(1u):
        display_clear();
        display_drawBitmap(&test_girl_bitmap, 0u, 0u);
        break;
    case(2u):
        display_drawString("Girls Round!", 50, 4, FONT_MEDIUM_FONT);
        break;
    case(10u):
        res = TRUE;
    break;
    default:
        break;
    }

    return res;
}

Private Boolean girlsSpecialTask(U8 sec)
{
    Boolean res = FALSE;

    switch(sec)
    {
    case(1u):
       display_clear();
       display_drawString("Girls Drink\n          2x", 10u, 20u, FONT_LARGE_FONT);
       break;
    case(10u):
       res = TRUE;
       break;
    default:
        break;
    }

    return res;
}


Private void drawTimer(void)
{
    //Currently for testing.
    convertTimerString(&priv_timekeeper, priv_timer_str);

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
    display_drawString(str, UPPER_TEXT_XLOC, UPPER_TEXT_YLOC, UPPER_TEXT_FONT);
}

//TODO : Replace this area with defined points.
Private void clearUpperText(void)
{
    display_fillRectangle(UPPER_TEXT_XLOC, UPPER_TEXT_YLOC, UPPER_TEXT_HEIGHT, UPPER_TEXT_WIDTH, PATTERN_WHITE);
}

Private void setLowerText(const char * str)
{
    clearLowerText();
    display_drawString(str, LOWER_TEXT_XLOC, LOWER_TEXT_YLOC, LOWER_TEXT_FONT);
}

Private void clearLowerText(void)
{
    display_fillRectangle(LOWER_TEXT_XLOC, LOWER_TEXT_YLOC, LOWER_TEXT_HEIGHT, LOWER_TEXT_WIDTH, PATTERN_WHITE);
}




