/*
 * SpecialTasks.c
 *
 *  Created on: Sep 5, 2017
 *      Author: Joonatan
 */

#include <LOGIC/PowerHourGame/SpecialTasks.h>
#include "bitmaps.h"
#include "font.h"
#include "display_drv.h"
#include "register.h"
#include <stdlib.h>

#define SMALL_SHOT_X 20u
#define SMALL_SHOT_Y 32u
#define SMALL_SHOT_INTERVAL 20u

typedef struct
{
    const char * upper_text;
    const char * middle_text;
    const char * lower_text;
    U8 counter; /* Number of times, this task has been selected. */
} Task_T;


//Private Boolean DrinkTwiceTask(U8 sec, const char * headerWord);
Private Boolean DrinkTwiceTask(U8 sec, SpecialTaskType type);
Private Boolean SpecialTaskWithRandomText(U8 sec, SpecialTaskType type);
Private const Task_T * getRandomTaskFromArray(Task_T * array, U8 array_size);

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
Private Task_T priv_TextArrayGirls[] =
{
     {"The girl with ",     "the fanciest clothes"  , "drinks 2x"         , .counter = 0u  },
     {"The girl with  ",    "the largest boobs"     , "drinks 2x"         , .counter = 0u  },
     {NULL,                 "Only girls drink"      , NULL                , .counter = 0u  },
     {"Girls",              "I have never ever"     , NULL                , .counter = 0u  },
     {"The girl with ",     "the sexiest voice"     , "drinks 2x "        , .counter = 0u  },
     {"All girls lose" ,    "One Item of Clothing"  , NULL                , .counter = 0u  },
     {"Girls drink",        "without "      ,         "using hands"       , .counter = 0u  },
     {"Choose one girl",    "who drinks 3x ",         NULL                , .counter = 0u  },
};

Private Task_T priv_TextArrayGuys[] =
{
     {  NULL                    , "Only guys drink",            NULL          , .counter = 0u  },
     {  "Guys drink"            , "without",                    "using hands" , .counter = 0u  },
     {  "The toughest guy"      , "drinks 3x",                  NULL          , .counter = 0u  },
     {  "The biggest playboy"   , "drinks 3x",                  NULL          , .counter = 0u  },
     {  "All guys lose"         , "One Item of Clothing",       NULL          , .counter = 0u  },
     {  "Guys"                  , "Never have I ever",          NULL          , .counter = 0u  },
     {  NULL                    , "Guys must sing",         "a song together" , .counter = 0u  },
     {  "Last guy to put his"   , "finger on his nose",        "drinks 2x"    , .counter = 0u  },
     {  "Choose one guy"        , "who drinks 3x ",             NULL          , .counter = 0u  },
};


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

Private const Task_T * priv_task_str_ptr;

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
           priv_task_str_ptr = getRandomTaskFromArray(priv_TextArrayGirls, NUMBER_OF_ITEMS(priv_TextArrayGirls));
       }
       else if(type == TASK_FOR_GUYS)
       {
           priv_task_str_ptr = getRandomTaskFromArray(priv_TextArrayGuys, NUMBER_OF_ITEMS(priv_TextArrayGuys));
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


Private const Task_T * getRandomTaskFromArray(Task_T * array, U8 array_size)
{
    U8 ix;
    U8 min_count = 0xffu;

    U8 * index_array;
    U8 unused = 0u;
    U16 result_index;

    index_array = (U8 *)malloc(sizeof(U8) * array_size);

    if (index_array == NULL)
    {
        /* TODO : Review error handling. Currently will be stuck in infinite loop. */
        while(1);
    }

    for (ix = 0u; ix < array_size; ix++)
    {

        if (array[ix].counter < min_count)
        {
            min_count = array[ix].counter;
        }
    }

    for (ix = 0u; ix < array_size; ix++)
    {
        if (array[ix].counter <= min_count)
        {
            /* We can use this item. */
            index_array[unused] = ix;
            unused++;
        }
    }

    if (unused > 0u)
    {
        /* So now index_array should contain all the unused indexes. */
        result_index = index_array[generate_random_number(unused - 1u)];
    }
    else
    {
        /* TODO : Review this case. something has gone seriously wrong... */
        result_index = 0u;
    }

    free(index_array);
    array[result_index].counter++;
    return &array[result_index];
}

