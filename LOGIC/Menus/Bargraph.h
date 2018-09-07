/*
 * Scrollbar.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Joonatan
 */

#ifndef LOGIC_MENUS_BARGRAPH_H_
#define LOGIC_MENUS_BARGRAPH_H_

#include "typedefs.h"
#include "menu.h"

typedef void (*bargraph_func)(U16 value);

typedef struct __Bargraph__
{
    U16 value;
    U16 max_value;
    U16 min_value;
    U16 increment;
    struct _Selection_Menu_ * parent;
    char * text;
    bargraph_func value_changed;
} Bargraph_T;

extern Bargraph_T BRIGHTNESS_BARGRAPH;
extern Bargraph_T SNAKE_SPEEED_BARGRAPH;

extern void enterBarGraph(Bargraph_T * bar);

#endif /* LOGIC_MENUS_BARGRAPH_H_ */
