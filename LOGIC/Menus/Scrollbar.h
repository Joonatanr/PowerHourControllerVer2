/*
 * Scrollbar.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Joonatan
 */

#ifndef LOGIC_MENUS_SCROLLBAR_H_
#define LOGIC_MENUS_SCROLLBAR_H_

#include "typedefs.h"
#include "menu.h"

typedef struct
{
    U8 value;
    U8 max_value;
    U8 min_value;
    SelectionMenu * parent;
    char * text;
} ScrollBar_T;

extern ScrollBar_T test_bar;

extern void enterScrollBar(ScrollBar_T * bar);

#endif /* LOGIC_MENUS_SCROLLBAR_H_ */
