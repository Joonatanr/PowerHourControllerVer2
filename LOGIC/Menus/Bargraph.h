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


typedef struct __Bargraph__
{
    U16 value;
    U16 max_value;
    U16 min_value;
    struct _Selection_Menu_ * parent;
    char * text;
} Bargraph_T;

extern Bargraph_T TEST_BARGRAPH;

extern void enterBarGraph(Bargraph_T * bar);

#endif /* LOGIC_MENUS_BARGRAPH_H_ */
