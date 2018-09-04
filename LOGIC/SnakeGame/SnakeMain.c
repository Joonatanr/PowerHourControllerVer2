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


/*
This is the coordinate system used. Each game coordinate corresponds to 2x2 pixels.

px   0 1 2 3 4 5 6 7 8 9 ...
  crd 0   1   2   3   4
0   * *|* *|* *|* *|
1 0 * *|* *|* *|* *|
    ---+---+---+---+
2   * *|   |   |   |
3 1 * *|   |   |   |
    ---+---+---+---+
4   * *|   |   |   |
5 2 * *|   |   |   |
    ---+---+---+---+
6   * *|   |   |   |
7 3 * *|   |   |   |
    ---+---+---+---+
8   * *|   |   |   |
9 4 * *|   |   |   |
    ---+---+---+---+
...

*/

/* This file will contain the long-planned Snake Game on the power hour machine...*/

#define GAME_BORDER_WIDTH 2u /* Set this at 2 pixels.    */
#define SNAKE_SPEED       4u /* Set at 400 ms intervals. */

#define MAX_COORD_X NUMBER_OF_COLUMNS / 2u
#define MAX_COORD_Y NUMBER_OF_ROWS / 2u

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
    Point                      begin; /* Note that each snake part takes 2*2 pixels */
    U8                        length;
    SnakeDirection               dir;
    struct __SnakeElement__   * next;
} SnakeElement;


Private SnakeElement *  priv_head = NULL;
Private SnakeElement *  priv_tail = NULL;

Private Boolean priv_isDirSet = FALSE; /* Prevents from changing direction twice during the cycle. */


/************************** Private function forward declarations. *****************************/


Private void setSnakeDirection(SnakeDirection dir);
Private Point getTailOfElement(const SnakeElement * elem);

/* Drawing functions. */
Private void drawBorder(void);
Private void drawSnakeElement(SnakeElement * elem, Boolean isBlack);

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

    buttons_setButtonMode(UP_BUTTON,    RISING_EDGE);
    buttons_setButtonMode(DOWN_BUTTON,  RISING_EDGE);
    buttons_setButtonMode(RIGHT_BUTTON, RISING_EDGE);
    buttons_setButtonMode(LEFT_BUTTON,  RISING_EDGE);

    /* Create initial snake... */
    priv_head = (SnakeElement *)malloc(sizeof(SnakeElement));

    if (priv_head != NULL)
    {
        priv_head->begin = (Point){ 32u, 16u };
        priv_head->dir = DIR_RIGHT;
        priv_head->length = 8u;
        priv_head->next = NULL;

        priv_tail = priv_head; //Initially only one segment.
    }

    /* TODO : Should raise error, if this fails. */
}


/* TODO : Current interval of 100ms is arbitrarily chosen. */
Public void snake_cyclic100ms(void)
{
    static U8 cycle_counter = 0u;

    if (++cycle_counter <= SNAKE_SPEED)
    {
        return;
    }
    else
    {
        cycle_counter = 0u;
    }

    /* 1. Erase previous tail --- TODO : This could probably be done more optimally. */
    drawSnakeElement(priv_tail, FALSE);

    /* 2. Move head forward */
    switch(priv_head->dir)
    {
    case DIR_UP:
        priv_head->begin.y--;
        break;
    case DIR_DOWN:
        priv_head->begin.y++;
        break;
    case DIR_LEFT:
        priv_head->begin.x--;
        break;
    case DIR_RIGHT:
        priv_head->begin.x++;
        break;
    default:
        break;
        //Should not happen.
    }

    /*3. Increase size of the head, decrease size of the tail. */
    priv_tail->length--;
    priv_head->length++;

    if (priv_tail->length == 0u)
    {
        SnakeElement * prev = priv_tail;
        priv_tail = priv_tail->next;
        free(prev);
    }

    drawSnakeElement(priv_head, TRUE);
    drawSnakeElement(priv_tail, TRUE);

    priv_isDirSet = FALSE;
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
    display_drawRectangle(0u, 0u, NUMBER_OF_ROWS, NUMBER_OF_COLUMNS, GAME_BORDER_WIDTH);
}


Private void setSnakeDirection(SnakeDirection request)
{
    if ((priv_head->dir != request)                             &&
        !(request == DIR_DOWN && priv_head->dir == DIR_UP)      &&
        !(request == DIR_UP   && priv_head->dir == DIR_DOWN)    &&
        !(request == DIR_LEFT && priv_head->dir == DIR_RIGHT)   &&
        !(request == DIR_LEFT && priv_head->dir == DIR_RIGHT))
   {
        if (priv_isDirSet == FALSE)
        {
            priv_isDirSet = TRUE;

            SnakeElement * new_elem = (SnakeElement*)malloc(sizeof(SnakeElement));
            if (new_elem != NULL)
            {
                /* So we begin inside the old segment. */
                new_elem->begin.x = priv_head->begin.x;
                new_elem->begin.y = priv_head->begin.y;
                new_elem->length = 0u;  /* Lets hope the zero length won't cause issues... */
                new_elem->dir = request;
                priv_head->next = new_elem;
                priv_head = new_elem;
            }
            else
            {
                /* TODO : Add fault handling. */
            }
        }
   }
}


Private void drawSnakeElement(SnakeElement * elem, Boolean isBlack)
{
    Point BeginPixel;
    Point EndPixel;
    Point end;  /* This is in the game coordinate system. */
    Point head; /* This is in the game coordinate system.  */

    if (elem == NULL)
    {
        return;
    }

    end = getTailOfElement(elem);
    /* Perform sanity check. */
    /* If element is out of bounds, then we still draw it, but cut off the out of bounds part. */

    head.x = MIN(elem->begin.x , MAX_COORD_X);
    head.y = MIN(elem->begin.y , MAX_COORD_Y);
    end.x = MIN(end.x, MAX_COORD_X);
    end.y = MIN(end.y, MAX_COORD_Y);


    /* Initialize these to top left pixels. */
    BeginPixel.x = head.x * 2;
    BeginPixel.y = head.y * 2;

    EndPixel.x = end.x * 2;
    EndPixel.y = end.y * 2;

    /* Initial try  - Probably can do this better. */
    switch(elem->dir)
    {
    case DIR_UP:
        EndPixel.y++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        BeginPixel.x++;
        EndPixel.x++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        break;
    case DIR_DOWN:
        BeginPixel.y++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        BeginPixel.x++;
        EndPixel.x++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        break;
    case DIR_LEFT:
        EndPixel.x++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        BeginPixel.y++;
        EndPixel.y++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        break;
    case DIR_RIGHT:
        BeginPixel.x++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        BeginPixel.y++;
        EndPixel.y++;
        display_drawLine(BeginPixel, EndPixel, isBlack);
        break;
    default:
        break;
        //Should not happen.
    }
}

/* Returns end point of segment in the snake coordinate system. */
Private Point getTailOfElement(const SnakeElement * elem)
{
    Point res;

    switch(elem->dir)
    {
        case DIR_UP:
            res.x = elem->begin.x;
            res.y = elem->begin.y + elem->length;
            break;
        case DIR_DOWN:
            res.x = elem->begin.x;
            res.y = elem->begin.y - elem->length;
            break;
        case DIR_LEFT:
            res.x = elem->begin.x + elem->length;
            res.y = elem->begin.y;
            break;
        case DIR_RIGHT:
            res.x = elem->begin.x - elem->length;
            res.y = elem->begin.y;

            break;
    default:
        //Really should not happen.
        return (Point){0,0};
    }

    return res;
}

/* Note that this is in reverse to the logical direction that flows from head to tail. */
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

