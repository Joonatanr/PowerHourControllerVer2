/*
 * menu.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Joonatan
 */

#ifndef LOGIC_MENU_H_
#define LOGIC_MENU_H_

#include "typedefs.h"

typedef struct
{
    const char * text;
    const U8 txt_len;
} MenuItem;

typedef struct
{
    const MenuItem ** items;
    const U8 number_of_items;
    U8 selected_item;
} SelectionMenu;

extern void menu_drawMenu(SelectionMenu * menu);
extern void menu_setSelectedItem(SelectionMenu * menu, U8 selected_item);
extern const MenuItem * menu_getSelectedItem(SelectionMenu * menu);
extern void menu_MoveCursor(SelectionMenu * menu, Boolean dir);

#endif /* LOGIC_MENU_H_ */
