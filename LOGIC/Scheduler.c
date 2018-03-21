/*
 * Scheduler.c
 *
 *  Created on: 16. m�rts 2018
 *      Author: JRE
 */

#include "Scheduler.h"
#include "clockDisplay.h"
#include "buzzer.h"
#include "buttons.h"
#include "register.h"
#include "comm.h"

/* NB! Current implementation assumes that only 1 task is active at any time, but this can be changed ofcourse. */
/* NB! All lo prio interrupt tasks should come here. I think there is no point to create a separate scheduler for the
 *     hi prio interrupt. */


/*************  Private function prototypes.  **************/
Private void timer_1sec(void);

/* NB! Currently period has to be divisible by 50. Might want to change this. */

/* Ok : Idea is this that this array contains the tasks, of which only one can be active at a time. */
Private const Scheduler_LogicTask priv_logic_modules[NUMBER_OF_LOGIC_MODULES] =
{
     { .period = 1000u, .init_fptr = clockDisplay_init, .start_fptr = clockDisplay_start, .cyclic_fptr = clockDisplay_cyclic1000msec, .stop_fptr = clockDisplay_stop },
};


/* This array contains the tasks that run all the time. */
/* Small incremental changes :) - So lets enable the modules part first and then look at this part. */
Private const Scheduler_LogicTask priv_tasks[NUMBER_OF_SCHEDULER_TASKS] =
{
     { .period = 1000u, .init_fptr = NULL,          .start_fptr = NULL, .cyclic_fptr = timer_1sec,           .stop_fptr = NULL  }, /* Debug LED task.   */
     { .period = 100u,  .init_fptr = buzzer_init,   .start_fptr = NULL, .cyclic_fptr = buzzer_cyclic100msec, .stop_fptr = NULL  }, /* Buzzer task.      */
     { .period = 100u,  .init_fptr = buttons_init,  .start_fptr = NULL, .cyclic_fptr = buttons_cyclic100msec,.stop_fptr = NULL  }, /* Buttons task      */
     { .period = 50u,   .init_fptr = uart_init,     .start_fptr = NULL, .cyclic_fptr = uart_cyclic,          .stop_fptr = NULL  }, /* Debug UART task   */
};


/*************  Private variable declarations.  **************/
Private const Scheduler_LogicTask * priv_curr_task_ptr = NULL;
Private U16 priv_task_timer = 0u;


/* Should be called once at startup. */
void Scheduler_init(void)
{
    U8 ix;
    for (ix = 0u; ix < NUMBER_OF_ITEMS(priv_logic_modules); ix++)
    {
        if (priv_logic_modules[ix].init_fptr != NULL)
        {
            priv_logic_modules[ix].init_fptr();
        }
    }

    for (ix = 0u; ix < NUMBER_OF_ITEMS(priv_tasks); ix++)
    {
        if (priv_tasks[ix].init_fptr != NULL)
        {
            priv_tasks[ix].init_fptr();
        }
    }
}

/* Should be called once at startup.. */
void Scheduler_StartTasks(void)
{
    U8 ix;

    for (ix = 0u; ix < NUMBER_OF_SCHEDULER_TASKS; ix++)
    {
        if (priv_tasks[ix].start_fptr != NULL)
        {
            priv_tasks[ix].start_fptr();
        }
    }
}


void Scheduler_SetActiveModule(Scheduler_LogicModuleEnum task)
{
    if (priv_curr_task_ptr != NULL)
    {
        priv_curr_task_ptr->stop_fptr();
    }
    priv_curr_task_ptr = &priv_logic_modules[task];
    priv_curr_task_ptr->start_fptr();
}


void Scheduler_StopActiveModule(void)
{
    if (priv_curr_task_ptr != NULL)
    {
        priv_curr_task_ptr->stop_fptr();
    }
    priv_curr_task_ptr = NULL;
}


/* Lets assume this gets called every 50 ms, by the main.c lo prio interrupt. */
void Scheduler_cyclic(void)
{
    U8 ix;

    priv_task_timer += SCHEDULER_PERIOD;

    /* Prevent overflow. */
    if (priv_task_timer > 50000u)
    {
        priv_task_timer = SCHEDULER_PERIOD;
    }

    /* Deal with the current active logical module. */
    if (priv_curr_task_ptr != NULL)
    {
        /* TODO : Review this, it will not work with a period of for example 20 .*/
        /* Might be good enough for testing. */
        if ((priv_task_timer % priv_curr_task_ptr->period) == 0u)
        {
            priv_task_timer = 0u;
            if (priv_curr_task_ptr->cyclic_fptr != NULL)
            {
                priv_curr_task_ptr->cyclic_fptr();
            }
        }
    }

    /* Deal with other constantly firing modules. */
    for (ix = 0u; ix < NUMBER_OF_ITEMS(priv_tasks); ix++)
    {
        /* No point to check this, if there is no corresponding function... */
        if (priv_tasks[ix].cyclic_fptr != NULL)
        {
            if ((priv_task_timer % priv_tasks[ix].period) == 0u)
            {
                priv_tasks[ix].cyclic_fptr();
            }
        }
    }
}



/**************************  Private functions ***********************/

Private void timer_1sec(void)
{
    static U8 led_state = 0x00u;

    /* Second counter LED is controlled here. */
    led_state = !led_state;
    set_led_one(led_state);
}



