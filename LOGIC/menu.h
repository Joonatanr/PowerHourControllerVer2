/*
 * menu.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Joonatan
 */

#ifndef LOGIC_MENU_H_
#define LOGIC_MENU_H_

#include "typedefs.h"

typedef enum
{
    MENU_ACTION_NONE,                   //We don't do anything, basically means that this is not yet implemented.
    MENU_ACTION_SUBMENU,                //We enter a submenu. This is currently not yet implemented.
    MENU_ACTION_FUNCTION,               //We perform an attached function. This also means that we leave the menu.
    NUMBER_OF_MENU_ACTIONS
} MenuActionType;

typedef void (*MenuActionHandler)(void);

typedef struct
{
    const char * text;
    const U8 txt_len;

    MenuActionType Action;

    union
    {
        struct SelectionMenu *     subMenu;
        MenuActionHandler          function;
    } ActionArg;

} MenuItem;

typedef struct
{
    const MenuItem ** items;
    const U8 number_of_items;
    U8 selected_item;
} SelectionMenu;

extern void menu_enterMenu(SelectionMenu * menu);
extern void menu_exitMenu(void);

extern void menu_setSelectedItem(SelectionMenu * menu, U8 selected_item);
extern const MenuItem * menu_getSelectedItem(SelectionMenu * menu);
extern void menu_MoveCursor(SelectionMenu * menu, Boolean dir);

#endif /* LOGIC_MENU_H_ */
