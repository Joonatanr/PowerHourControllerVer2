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

Private void timer_10msec(void);
Private void timer_1sec(void);

//Callback for register.c
Public TimerHandler timer_10msec_callback = timer_10msec;
Private U8 timer_sec_counter = 0u;


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    register_init();

    delay_msec(200);
    //Execute test sequence for testing the functionality of the LCD display.
    display_test_sequence();

    //Currently this function never returns.
    register_enable_low_powermode();
}

//Periodically called from interrupt context.
Private void timer_10msec(void)
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

    if (++timer_sec_counter >= 100u)
    {
        timer_sec_counter = 0;
        timer_1sec();
    }
}

/* Maybe this should not be called from interrupt context??? */
Private void timer_1sec(void)
{
    static U8 led_state = 0x00u;

    led_state = !led_state;
    set_led_one(led_state);
    if (led_state)
    {
        comm_send_char('X');
    }
    else
    {
        comm_send_char('O');
    }
}


