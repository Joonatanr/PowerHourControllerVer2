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
#include "buzzer.h"
#include "parser.h"
#include "clockDisplay.h"
#include "buttons.h"
#include "backlight.h"


Private void timer_hi_prio(void);
Private void timer_lo_prio(void);

Private void timer_1sec(void);
Private void showStartScreen(void);
Private void showStartDialog(void);

//Callback for register.c
Public TimerHandler timer_10msec_callback = timer_hi_prio;
Public TimerHandler timer_50msec_callback = timer_lo_prio;

Private U8 timer_sec_counter = 0u;
Private U8 priv_uart_buffer[UART_BUF_LEN];

//volatile Boolean myTestFlag = FALSE;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    //Initialise HW layer.
    register_init();

    //Set backlight to 100 percent.
    backlight_set_level(100);

    //Initialise logic layer.
    clockDisplay_init();

    delay_msec(250);

    //Start HW layer.
    display_start();

    //We show the initial start screen for a while.
    showStartScreen();
    delay_msec(5000);

    showStartDialog();
    while(!isRedButton());

    display_clear();

    //Start LOGIC layer.
    clockDisplay_start();

    //Currently this function never returns.
    register_enable_low_powermode();
}

//Periodically called from interrupt context.
//Called every 10msec.
Private void timer_hi_prio(void)
{
    //All high priority tasks should be put in here.
    //This means hardware tasks, such as reading buttons, changing PWM etc.
    set_led_two_blue(isBlueButton());
    set_led_two_red(isRedButton());
    set_led_two_green(isGreenButton());
}

//Called from low priority context.
Private void timer_1sec(void)
{
    static U8 led_state = 0x00u;

    led_state = !led_state;
    set_led_one(led_state);
    clockDisplay_cyclic1000msec();
}

Rectangle test_rect;

//This is called every 50 milliseconds.
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
                display_fillRectangle(test_rect.location.x,
                                      test_rect.location.y,
                                      test_rect.size.height,
                                      test_rect.size.width,
                                      PATTERN_GRAY);
                comm_send_str("OK");

                comm_send_str("X : ");
                comm_send_number(test_rect.location.x);

                comm_send_str(", Y : ");
                comm_send_number(test_rect.location.y);

                comm_send_str(", Height: ");
                comm_send_number(test_rect.size.height);

                comm_send_str(", Width: ");
                comm_send_number(test_rect.size.width);

                comm_send_rn();
            }
            else
            {
                comm_send_str("ERROR");
            }
        }
        else if(priv_uart_buffer[0] == 'C')
        {
            display_clear();
        }
    }

    //1 second timer.
    if (++timer_sec_counter >= 20u)
    {
        timer_sec_counter = 0;
        timer_1sec();
    }

    if (timer_sec_counter % 2u == 0u)
    {
        buzzer_Cyclic100msec();
    }

    // Make sure this is called at the very end, so that all logic
    // tasks can write to the display without problems.
    display_cyclic_50msec();
}


Private void showStartScreen(void)
{
    display_clear();
    display_drawStringCenter("Power Hour", 64u, 20u, FONT_LARGE_FONT);
    display_drawStringCenter("Machine 2.0", 64u, 40u, FONT_LARGE_FONT);
}

//TODO : This is a placeholder, should add proper start menu.
Private void showStartDialog(void)
{
    display_clear();
    display_drawStringCenter("Press red button", 64u, 16u, FONT_MEDIUM_FONT);
    display_drawStringCenter("to begin", 64u, 32u, FONT_MEDIUM_FONT);
}


