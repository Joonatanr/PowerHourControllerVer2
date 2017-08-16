/*
 * display_drv.c
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#include "display_drv.h"
#include <driverlib.h>
#include "spi_drv.h"
#include "register.h"

#define NUMBER_OF_PAGES 8u
#define NUMBER_OF_COLUMNS 128u

/* TODO : Some of these could be replaced with macros, or inline functions. */

Private void disp_command(U8 cmd, Boolean reg_select);
Private void set_page_address(U8 page);
Private void set_column(U8 column);
Private void clear_display(void);
Private void write_data(U8 data);

Private void display_reset(void);


/* Set up A0 pin for display. */
Public void display_init(void)
{
    //Set the chip select pin as high initially.
    display_reset();
    set_cs_pin(1u);
}

Public void display_test_sequence(void)
{
    U8 ix;

    //Low CS, means that it is active.
    //GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
    set_cs_pin(0u);

    //Display start line set.
    disp_command(0x40u, FALSE);

    //Set ADC in reverse
    disp_command(0xA1u, FALSE);
    //Common output mode select
    disp_command(0xC0u, FALSE);

    //display normal
    disp_command(0xA6u, FALSE);

    //LCD bias set
    disp_command(0xA2u, FALSE);

    //Power control set
    disp_command(0x2Fu, FALSE);

    //Booster ratio set.
    disp_command(0xF8u, FALSE);
    disp_command(0x00u, FALSE);

    //Contrast set.
    disp_command(0x27u, FALSE);
    disp_command(0x81u, FALSE);
    disp_command(0x10u, FALSE);

    //Static indicator set.
    disp_command(0xACu, FALSE);

    //Turn on display.
    disp_command(0x00u, FALSE);
    disp_command(0xAFu, FALSE);

    delay_msec(200);
    //Turn on all points.
    disp_command((0xA4u | 0x01u), FALSE);
    clear_display();
    delay_msec(2000);
    //Turn off all points.
    disp_command(0xA4u, FALSE);

    //Lets try writing something.


    //Set to page address 2.
    set_page_address(4u);
    set_column(0u);

    for (ix = 0u; ix < 128u; ix++)
    {
        //Write data.
        //disp_command(0x00u, TRUE);
        write_data(0x00u);
    }

    set_column(8u);

    for (ix = 0u; ix < 128u; ix++)
    {
        //Write data.
        //disp_command(0xAAu, TRUE);
        write_data(0xAAu);
    }
}


Private void disp_command(U8 cmd, Boolean reg_select)
{
    spi_transmit_byte(cmd, reg_select);
}


Private void set_page_address(U8 page)
{
    disp_command(0xB0u | (page & 0x0fu), FALSE);
}


Private void write_data(U8 data)
{
    disp_command(data, TRUE);
}


Private void set_column(U8 column)
{
    //Set column MSB.
    disp_command(0x10u | (column >> 4u),  FALSE);
    //Set column LSB.
    disp_command(column & 0x0fu, FALSE);
}


Private void clear_display(void)
{
    U8 ix;
    U8 yx;

    for (ix = 0u; ix < NUMBER_OF_PAGES; ix++)
    {
        set_page_address(ix);
        set_column(0);
        for (yx = 0u; yx < NUMBER_OF_COLUMNS; yx++)
        {
            write_data(0x00u);
        }
    }
}


Private void display_reset(void)
{
    set_disp_reset_pin(0u);
    delay_msec(100);
    set_disp_reset_pin(1u);
    delay_msec(100);
}



