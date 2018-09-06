/*
 * Scheduler.h
 *
 *  Created on: 16. m�rts 2018
 *      Author: JRE
 */

#ifndef LOGIC_SCHEDULER_H_
#define LOGIC_SCHEDULER_H_

#include "typedefs.h"

#define SCHEDULER_PERIOD 50u //Define this at 50 milliseconds.

typedef void (*Scheduler_TaskFunc)(void);

typedef enum
{
    TASK_CYCLIC1000MS_CLOCKDP, /* Main PH game, TODO : Rename this from clock display, as it is incorrect. */
    TASK_CYCLIC100MS_SNAKE,    /* Secondary snake game... TODO : Implement this. */
    NUMBER_OF_LOGIC_MODULES
} Scheduler_LogicModuleEnum;

/* TODO : Add all cyclic tasks here that run from lo prio interrupt. */
typedef enum
{
    TASK_CYCLIC1000MS_DEBUG_LED,
    TASK_CYCLIC100MS_BUZZER,
    TASK_CYCLIC100MS_BUTTONS,
    TASK_CYCLIC50MS_UART,
    TASK_CYCLIC100MS_MSGBOX,
    TASK_CYCLIC50MS_DISPLAY_DRIVER, /* This one should be called last. */
    NUMBER_OF_SCHEDULER_TASKS
} Scheduler_LogicTaskEnum;

typedef struct
{
    U16 period;
    Scheduler_TaskFunc init_fptr;
    Scheduler_TaskFunc start_fptr;
    Scheduler_TaskFunc stop_fptr;
    Scheduler_TaskFunc cyclic_fptr;
} Scheduler_LogicTask;

extern void Scheduler_initTasks(void);
extern void Scheduler_cyclic(void);
extern void Scheduler_StartTasks(void);

extern void Scheduler_SetActiveModule(Scheduler_LogicModuleEnum task);
extern void Scheduler_StopActiveModule(void);
extern void Scheduler_SetActiveModulePause(Boolean pause);

#endif /* LOGIC_SCHEDULER_H_ */
