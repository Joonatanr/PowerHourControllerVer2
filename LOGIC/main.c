//*****************************************************************************
//
// MSP432 based Power Hour Controller machine main module.
//
//****************************************************************************

#include <LOGIC/PowerHourGame/clockDisplay.h>
#include "LOGIC/TextTools/MessageBox.h"
#include <misc.h>
#include "msp.h"
#include "typedefs.h"
#include "register.h"
#include "display_drv.h"
#include "buzzer.h"
#include "buttons.h"
#include "backlight.h"
#include "Menus/menu.h"
#include "Scheduler.h"

//#define DEBUG_SEQUENCE

Private void timer_hi_prio(void);
Private void timer_lo_prio(void);

Private void showStartScreen(void);

Private void startGameHandler(void);
Private void startSnakeGame(void);

//Callback for register.c
Public TimerHandler timer_10msec_callback = timer_hi_prio;
Public TimerHandler timer_50msec_callback = timer_lo_prio;

Private const char priv_version_string[] = "Machine 2.2";


/* Settings Menu Items */
Private const MenuItem SettingsMenuItemArray[] =
{
   { .text = "Brightness",    .Action = MENU_ACTION_WIDGET  , .ActionArg.bargraph_ptr = &BRIGHTNESS_BARGRAPH   },
   { .text = "Test",          .Action = MENU_ACTION_WIDGET  , .ActionArg.bargraph_ptr = &TEST_BARGRAPH         },
   { .text = "Snake speed",   .Action = MENU_ACTION_WIDGET  , .ActionArg.bargraph_ptr = &SNAKE_SPEEED_BARGRAPH },
};

Private SelectionMenu SettingsMenu =
{
     .items = SettingsMenuItemArray,
     .number_of_items = NUMBER_OF_ITEMS(SettingsMenuItemArray),
     .selected_item = 0u
};


/** Start Menu Items.*/
Private const MenuItem StartMenuItemArray[] =
{
   { .text = "Start Game",  .Action = MENU_ACTION_FUNCTION    , .ActionArg.function_ptr = startGameHandler    },
   { .text = "Test Snake",  .Action = MENU_ACTION_FUNCTION    , .ActionArg.function_ptr = startSnakeGame      },
   { .text = "Settings",    .Action = MENU_ACTION_SUBMENU     , .ActionArg.subMenu_ptr = &SettingsMenu        },
   { .text = "Exit",        .Action = MENU_ACTION_NONE        , .ActionArg =  NULL                            },
};

Private SelectionMenu StartMenu =
{
     .items = StartMenuItemArray,
     .number_of_items = NUMBER_OF_ITEMS(StartMenuItemArray),
     .selected_item = 0u,
};

/** End of Start Menu Items. */


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    //Initialise HW layer.
    register_init();

    //Set backlight to 60 percent.
    backlight_set_level(60);

    //Initialise logic layer.
    Scheduler_initTasks();

    delay_msec(250);

    //Start all scheduler task
    Scheduler_StartTasks();

    //We show the initial start screen for a while.
    showStartScreen();
    delay_msec(4000);

    /* We pass control over to the menu handler. */
    menu_enterMenu(&StartMenu);

    //Currently this function never returns.
    register_enable_low_powermode();
}

void returnToMain(void)
{
    Scheduler_StopActiveModule();
    menu_enterMenu(&StartMenu);
}

//Periodically called from interrupt context.
//Called every 10msec.
Private void timer_hi_prio(void)
{
    //All high priority tasks should be put in here.
    //This means hardware tasks, such as reading buttons, changing PWM etc.
    set_led_two_blue(isButton(BLUE_BUTTON));
    set_led_two_red(isButton(RED_BUTTON));
    set_led_two_green(isButton(GREEN_BUTTON));

    buttons_cyclic10msec();
}


//This is called every 50 milliseconds.
//Maybe this should be called more frequently?
Private void timer_lo_prio(void)
{
    //Call the main scheduler for logic tasks.
    Scheduler_cyclic();
}


Private void showStartScreen(void)
{
    display_clear();
#ifdef    DEBUG_SEQUENCE

    //Test setPixel function.
    //display_setPixel(10, 10, TRUE);
    //display_setPixel(20, 20, TRUE);
    //display_setPixel(30, 30, TRUE);
    //display_setPixel(40, 40, TRUE);
    //display_setPixel(50, 50, TRUE);
    //display_setPixel(60, 60, TRUE);

    //Test line drawing.
    //display_drawLine((Point){70,20}, (Point){90,20}, TRUE);

    //Test rectangle drawing.
    //display_drawRectangle(0, 0, 10, 10, 1);
    //display_drawRectangle(0, 0, 6, 6, 2);
    //display_drawRectangle(24, 15, 20, 20, 3);

    //display_fillRectangle(0, 0, 3, 2, PATTERN_BLACK);
    MessageBox_ShowWithOk("Hello World!\n Power Hour");

    //delay_msec(10000);

#endif
    display_drawStringCenter("Power Hour", 64u, 20u, FONT_LARGE_FONT, FALSE);
    display_drawStringCenter(priv_version_string, 64u, 40u, FONT_LARGE_FONT, FALSE);
}

/* Starts the main Power Hour game. */
Private void startGameHandler(void)
{
    Scheduler_SetActiveModule(TASK_CYCLIC1000MS_CLOCKDP);
}

/* Starts the snake game. */
Private void startSnakeGame(void)
{
    Scheduler_SetActiveModule(TASK_CYCLIC100MS_SNAKE);
}

