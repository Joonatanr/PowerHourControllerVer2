/*
 * SpecialTasks.c
 *
 *  Created on: Sep 5, 2017
 *      Author: Joonatan
 */

#include "SpecialTasks.h"
#include "bitmaps.h"
#include "font.h"
#include "display_drv.h"

#define SMALL_SHOT_X 20u
#define SMALL_SHOT_Y 32u
#define SMALL_SHOT_INTERVAL 20u

typedef struct
{
    const char * upper_text;
    const char * middle_text;
    const char * lower_text;
} MultiString;


//Private Boolean DrinkTwiceTask(U8 sec, const char * headerWord);
Private Boolean DrinkTwiceTask(U8 sec, SpecialTaskType type);
Private Boolean SpecialTaskWithRandomText(U8 sec, SpecialTaskType type);

Private const SpecialTaskFunc priv_special_tasks_girls_array[] =
{
  &SpecialTaskWithRandomText,
  &DrinkTwiceTask,
  &SpecialTaskWithRandomText,
  &SpecialTaskWithRandomText,
  &DrinkTwiceTask,
  &SpecialTaskWithRandomText,
  &SpecialTaskWithRandomText,
};


Private const SpecialTaskFunc priv_special_tasks_guys_array[] =
{
  &SpecialTaskWithRandomText,
  &DrinkTwiceTask,
  &SpecialTaskWithRandomText,
  &SpecialTaskWithRandomText,
  &DrinkTwiceTask,
  &SpecialTaskWithRandomText,
  &SpecialTaskWithRandomText,
};


Private char priv_str_buf[64];
Private SpecialTaskFunc priv_selected_task_ptr;

/* TODO : Generate more tasks. */
Private const MultiString priv_specialTaskArrayGirls[] =
{
     {"The girl with ",     "the fanciest clothes"  , "drinks 2x"           },
     {"The girl with  ",    "the largest boobs"     , "drinks 2x"           },
     {NULL,                 "Only girls drink"      , NULL                  },
     {"Girls",              "I have never ever"     , NULL                  },
     {"The girl with ",     "the sexiest voice"     , "drinks 2x "          },
     {"All girls lose" ,    "One Item of Clothing"  , NULL                  },
     {"Girls drink",        "without "      ,         "using hands"         },
};

Private const MultiString priv_specialTaskArrayGuys[] =
{
     {  NULL                    , "Only guys drink",            NULL            },
     {  "Guys drink"            , "without",                    "using hands"   },
     {  "The toughest guy"      , "drinks 3x",                  NULL            },
     {  "The biggest playboy"   , "drinks 3x",                  NULL            },
     {  "All guys lose"         , "One Item of Clothing",       NULL            },
     {  "Guys"                  , "Never have I ever",          NULL            },
     {  NULL                    , "Guys must sing",         "a song together"   },
};


//TODO : This is still a placeholder.
Public Boolean girlsSpecialTask(U8 sec)
{
    Boolean res = FALSE;
    static U8 test_counter = 0u;

    /* If sec is 0, then we have just begun. */
    if (sec == 0u)
    {
        priv_selected_task_ptr = priv_special_tasks_girls_array[test_counter];
        test_counter++;
        if(test_counter >= NUMBER_OF_ITEMS(priv_special_tasks_girls_array))
        {
            test_counter = 0u;
        }
    }

    res = priv_selected_task_ptr(sec, TASK_FOR_GIRLS);
    return res;
}


Public Boolean guysSpecialTask(U8 sec)
{
    Boolean res = FALSE;
    static U8 test_counter = 0u; //TODO : This should be reviewed.

    if (sec == 0u)
    {
        //priv_selected_task_ptr = &DrinkTwiceTask;
        priv_selected_task_ptr = priv_special_tasks_guys_array[test_counter];
        test_counter++;
        if(test_counter >= NUMBER_OF_ITEMS(priv_special_tasks_guys_array))
        {
            test_counter = 0u;
        }
    }

    res = priv_selected_task_ptr(sec, TASK_FOR_GUYS);
    return res;
}


Private Boolean DrinkTwiceTask(U8 sec, SpecialTaskType type)
{
    Boolean res = FALSE;

    switch(sec)
    {
    case(1u):
       display_clear();
       if (type == TASK_FOR_GIRLS)
       {
           strcpy(priv_str_buf, "Girls");
       }
       else if(type == TASK_FOR_GUYS)
       {
           strcpy(priv_str_buf, "Guys");
       }

       strcat(priv_str_buf, " drink");
       display_drawStringCenter(priv_str_buf, 64u, 2u, FONT_LARGE_FONT, FALSE);
       display_drawStringCenter("2x", 64u ,20u, FONT_LARGE_FONT, FALSE);
       break;
    case (2u):
       display_drawBitmapCenter(&small_shot_bitmap, 64 - SMALL_SHOT_INTERVAL, SMALL_SHOT_Y, FALSE);
       break;
    case (3u):
        display_drawBitmapCenter(&small_shot_bitmap, 64 + SMALL_SHOT_INTERVAL, SMALL_SHOT_Y, FALSE);
       break;
    case(10u):
       res = TRUE;
       break;
    default:
        break;
    }

    return res;
}

//We currently don't use random selection, but simply inrement the counter each time.
Private U8 test_counter_index_guys;
Private U8 test_counter_index_girls;

Private const MultiString * priv_task_str_ptr;

/* The sec parameter specifies the current second from the beginning of the task.
 * This function is called cyclically after every second. */
Private Boolean SpecialTaskWithRandomText(U8 sec, SpecialTaskType type)
{
    //This is the simplest special task, currently no bitmaps, but we just display text on screen.
    //Text is three lines and randomly selected from tasks from previous PH controller :)
    Boolean res = FALSE;

    switch(sec)
    {
    case(1u):
       if (type == TASK_FOR_GIRLS)
       {
           priv_task_str_ptr = &priv_specialTaskArrayGirls[test_counter_index_girls];
           test_counter_index_girls++;
           if(test_counter_index_girls >= NUMBER_OF_ITEMS(priv_specialTaskArrayGirls))
           {
               test_counter_index_girls = 0u;
           }
       }
       else if(type == TASK_FOR_GUYS)
       {
           priv_task_str_ptr = &priv_specialTaskArrayGuys[test_counter_index_guys];
           test_counter_index_guys++;
           if(test_counter_index_guys >= NUMBER_OF_ITEMS(priv_specialTaskArrayGuys))
           {
               test_counter_index_guys = 0u;
           }
       }
       break;
    case (2u):
         display_clear();
         display_drawStringCenter(priv_task_str_ptr->upper_text, 64u, 4u, FONT_MEDIUM_FONT, FALSE);
       break;
    case (3u):
         display_drawStringCenter(priv_task_str_ptr->middle_text, 64u, 23u, FONT_MEDIUM_FONT, FALSE);
       break;
    case(4u):
         display_drawStringCenter(priv_task_str_ptr->lower_text, 64u, 43u, FONT_MEDIUM_FONT, FALSE);
       break;
    case(12u):
       res = TRUE;
       break;
    default:
        break;
    }

    return res;
}


