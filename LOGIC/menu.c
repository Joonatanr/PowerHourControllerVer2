/*
 * menu.c
 *
 *  Created on: Oct 12, 2017
 *      Author: Joonatan
 */


#include "menu.h"
#include "display_drv.h"
#include "font.h"

#define MENU_FONT FONT_MEDIUM_FONT


Public void menu_setSelectedItem(SelectionMenu * menu, U8 selected_item)
{
    menu->selected_item = selected_item;
    menu_drawMenu(menu);
}


Public void menu_MoveCursor(SelectionMenu * menu, Boolean dir)
{
    Boolean changed = FALSE;
    //dir is TRUE : move up, dir is FALSE, move down.
    if (dir)
    {
        if (menu->selected_item > 0u)
        {
            menu->selected_item --;
            changed = TRUE;
        }
    }
    else
    {
        if (menu->selected_item < (menu->number_of_items - 1))
        {
            menu->selected_item++;
            changed = TRUE;
        }
    }

    if (changed)
    {
        menu_drawMenu(menu);
    }
}

Public const MenuItem * menu_getSelectedItem(SelectionMenu * menu)
{
    return menu->items[menu->selected_item];
}

Public void menu_drawMenu(SelectionMenu * menu)
{
    //First lets see how large the menu to be drawn is.
    U8 height;
    U8 ypos;
    U8 x;
    U8 font_height;

    font_height = font_getFontHeight(MENU_FONT);

    height = (font_height + 2u) * menu->number_of_items;
    ypos = (NUMBER_OF_ROWS >> 1u) - (height >> 1u);

    for (x = 0u; x < menu->number_of_items; x++)
    {
        if(x == menu->selected_item)
        {
            display_drawStringCenter(menu->items[x]->text, 64u, ypos, MENU_FONT, TRUE);
        }
        else
        {
            display_drawStringCenter(menu->items[x]->text, 64u, ypos, MENU_FONT, FALSE);
        }
        ypos += font_height;
        ypos += 2u;
    }
}

