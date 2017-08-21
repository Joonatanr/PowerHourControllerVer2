/*
 * parser.c
 *
 *  Created on: Aug 21, 2017
 *      Author: Joonatan
 */

#include "parser.h"


#define IS_DIGIT(a) (((a) >= '0') && ((a) <= '9'))

//We pass information with RXX,YY,HH,WW --
Public Boolean parseRectangle(char * src, Rectangle * dest)
{
    Boolean res = FALSE;
    //U32 x,y,height,length = 0u;
    U32 values[4u];
    char * ps = src;

    if (*ps == 'R')
    {
        ps++;
        if (parseCommaSeparatedU32Array(values, ps, 4u))
        {
            res = TRUE;
            dest->location.x = values[0];
            dest->location.y = values[1];
            dest->size.height = values[2];
            dest->size.width = values[3];
        }
    }

    return res;
}

//Returns the pointer to the next character.
Public char * parseU32FromString(U32 * dest, char * src)
{
    char * ps = src;
    U32 res = 0u;
    U32 dec = 1u;
    U32 temp;

    if(!IS_DIGIT(*ps))
    {
        ps++;
    }

    while (IS_DIGIT(*ps))
    {
        temp = (U32)*ps - (U32)'0';
        res += temp * dec;
        dec *= 10u;
        ps++;
    }
    return ps;
}


Public Boolean parseCommaSeparatedU32Array(U32 * dest, char * src, U32 dest_len)
{
    U8 ix = 0u;
    char * ps = src;

    do
    {
         ps = parseU32FromString(dest + ix, ps);
         ix++;
         if (ix > dest_len)
         {
             //We parsed too much for some reason.
             return FALSE;
         }
    }
    while(*ps == ',');
    return TRUE;
}





