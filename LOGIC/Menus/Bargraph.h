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

typedef struct
{
    U8 value;
    U8 max_value;
    U8 min_value;
    SelectionMenu * parent;
    char * text;
} BarGraph_T;

extern BarGraph_T test_bar;

extern void enterBarGraph(BarGraph_T * bar);

#endif /* LOGIC_MENUS_BARGRAPH_H_ */
