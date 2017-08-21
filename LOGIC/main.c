//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "typedefs.h"
#include "register.h"
#include "comm.h"
#include "display_drv.h"
#include "parser.h"

Private void timer_hi_prio(void);
Private void timer_lo_prio(void);

Private void timer_1sec(void);

//Callback for register.c
Public TimerHandler timer_10msec_callback = timer_hi_prio;
Public TimerHandler timer_40msec_callback = timer_lo_prio;

Private U8 timer_sec_counter = 0u;
Private U8 priv_uart_buffer[UART_BUF_LEN];

//volatile Boolean myTestFlag = FALSE;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    register_init();

    delay_msec(500);
    //Execute test sequence for testing the functionality of the LCD display.
    display_test_sequence();

    //Currently this function never returns.
    register_enable_low_powermode();
}

//Periodically called from interrupt context.
//Called every 10msec.
Private void timer_hi_prio(void)
{
    if (isBtnOne())
    {
        set_led_two_blue(0x01u);
    }
    else
    {
        set_led_two_blue(0x00u);
    }

    if (isBtnTwo())
    {
        set_led_two_red(0x01u);
    }
    else
    {
        set_led_two_red(0x00u);
    }

}

/* Maybe this should not be called from interrupt context??? */
//TODO : Might need to remove this.
Private void timer_1sec(void)
{
    static U8 led_state = 0x00u;

    led_state = !led_state;
    set_led_one(led_state);
/*
    if(led_state)
    {
        comm_send_str("Hi! ");
    }
    else
    {
        comm_send_str("World");
    }
*/
}

Rectangle test_rect;

//This is called every 40 milliseconds.
//Maybe this should be called more frequently?
Private void timer_lo_prio(void)
{
    U8 msg_len;

    msg_len = comm_receiveData(priv_uart_buffer);

    if (msg_len > 0u)
    {
        if (priv_uart_buffer[0] == 'R')
        {
            if (parseRectangle((char *)priv_uart_buffer, &test_rect))
            {
                display_drawRectangle(test_rect.location, test_rect.size);
                comm_send_str("OK");

            }
            else
            {
                comm_send_str("ERROR");
            }
        }
    }

    //TODO : Call display cyclic function.
    display_cyclic_40msec();

    //1 second timer.
    if (++timer_sec_counter >= 25u)
    {
        timer_sec_counter = 0;
        timer_1sec();
    }
}


