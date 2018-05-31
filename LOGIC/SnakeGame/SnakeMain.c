/*
 * SnakeMain.c
 *
 *  Created on: 23. mai 2018
 *      Author: JRE
 */

#include "SnakeMain.h"
#include "display_drv.h"
#include "buttons.h"
#include <stdlib.h>

/* This file will contain the long-planned Snake Game on the power hour machine...*/

#define GAME_BORDER_WIDTH 3u /* Set this at 3 pixels. */

typedef enum
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    NUMBER_OF_DIRECTIONS
} SnakeDirection;

typedef struct __SnakeElement__
{
    Point                      begin;
    U8                        length;
    SnakeDirection               dir;
    struct __SnakeElement__   * next;
} SnakeElement;


Private SnakeElement * priv_head;


/************************** Private function forward declarations. *****************************/


Private void drawBorder(void);

Private void setSnakeDirection(SnakeDirection dir);

Private void HandleUpButton(void);
Private void HandleDownButton(void);
Private void HandleRightButton(void);
Private void HandleLeftButton(void);

/************************** Public function definitions. *****************************/

Public void snake_init(void)
{

}

Public void snake_start(void)
{
    /* Draw the background and border. */
    display_clear();
    drawBorder();

    /* Subscribe to buttons. */
    buttons_unsubscribeAll();

    buttons_subscribeListener(UP_BUTTON,    HandleUpButton);
    buttons_subscribeListener(DOWN_BUTTON,  HandleDownButton);
    buttons_subscribeListener(RIGHT_BUTTON, HandleRightButton);
    buttons_subscribeListener(LEFT_BUTTON,  HandleLeftButton);

    /* Create initial snake... */
    priv_head = (SnakeElement *)malloc(sizeof(SnakeElement));

    if (priv_head != NULL)
    {
        priv_head->begin = (Point){ 64u, 32u };
        priv_head->dir = DIR_RIGHT;
        priv_head->length = 8u;
        priv_head->next = NULL;
    }

    /* TODO : Should raise error, if this fails. */
}


/* TODO : Current interval of 100ms is arbitrarily chosen. */
Public void snake_cyclic100ms(void)
{

}


Public void snake_stop(void)
{
    /* TODO : Must clean up all resources here. */
    SnakeElement * elem_ptr = priv_head;
    SnakeElement * prev = NULL;

    while (elem_ptr != NULL)
    {
        prev = elem_ptr;
        elem_ptr = elem_ptr->next;
        free(prev);
    }
}

/************************** Private function definitions. *****************************/

Private void drawBorder(void)
{
    /* TODO : This should be made into a drawRectangle function.... */

    display_fillRectangle(0u,
                          0u,
                          GAME_BORDER_WIDTH,
                          NUMBER_OF_COLUMNS,
                          PATTERN_BLACK);

    display_fillRectangle(0u,
                          0u,
                          NUMBER_OF_ROWS,
                          GAME_BORDER_WIDTH,
                          PATTERN_BLACK);

    display_fillRectangle(DISP_LAST_ROW - GAME_BORDER_WIDTH,
                          0u,
                          NUMBER_OF_COLUMNS,
                          GAME_BORDER_WIDTH,
                          PATTERN_BLACK);

    display_fillRectangle(0u,
                          DISP_LAST_COLUMN - GAME_BORDER_WIDTH,
                          GAME_BORDER_WIDTH,
                          NUMBER_OF_ROWS,
                          PATTERN_BLACK);
}


Private void setSnakeDirection(SnakeDirection dir)
{
    /* TODO : Implement this. */
}


Private void HandleUpButton(void)
{
    setSnakeDirection(DIR_UP);
}

Private void HandleDownButton(void)
{
    setSnakeDirection(DIR_DOWN);
}

Private void HandleRightButton(void)
{
    setSnakeDirection(DIR_RIGHT);
}

Private void HandleLeftButton(void)
{
    setSnakeDirection(DIR_LEFT);
}

