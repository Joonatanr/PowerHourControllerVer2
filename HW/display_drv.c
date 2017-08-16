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

Private void disp_command(U8 cmd, Boolean reg_select);

/* Set up A0 pin for display. */
Public void display_init(void)
{
    //Set the chip select pin as high initially.
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
    delay_msec(2000);
    //Turn off all points.
    disp_command(0xA4u, FALSE);

    //Lets try writing something.

    //Set to page address 2.
    disp_command(0xB2u, FALSE);

    for (ix = 0u; ix < 128u; ix++)
    {
        //Set column MSB.
        disp_command(0x10u | (ix >> 4u), FALSE);
        //Set column LSB.
        disp_command(ix & 0x0fu, FALSE);

        //Write data.
        disp_command(0x00u, TRUE);
    }

    for (ix = 0u; ix < 128u; ix++)
    {
        //Set column MSB.
        disp_command(0x10u | (ix >> 4u), FALSE);
        //Set column LSB.
        disp_command(ix & 0x0fu, FALSE);

        //Write data.
        disp_command(0xAAu, TRUE);
    }
}

Private void disp_command(U8 cmd, Boolean reg_select)
{
    spi_transmit_byte(cmd, reg_select);
}



