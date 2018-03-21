/*
 * Scheduler.h
 *
 *  Created on: 16. märts 2018
 *      Author: JRE
 */

#ifndef LOGIC_SCHEDULER_H_
#define LOGIC_SCHEDULER_H_

#include "typedefs.h"

#define SCHEDULER_PERIOD 50u //Define this at 50 milliseconds.

typedef void (*Scheduler_TaskFunc)(void);

typedef enum
{
    TASK_CYCLIC1000MS_CLOCKDP,
    NUMBER_OF_LOGIC_MODULES
} Scheduler_LogicModuleEnum;

/* TODO : Add all cyclic tasks here that run from lo prio interrupt. */
typedef enum
{
    TASK_CYCLIC1000MS_DEBUG_LED,
    TASK_CYCLIC100MS_BUZZER,
    TASK_CYCLIC100MS_BUTTONS,
    TASK_CYCLIC50MS_UART,
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

extern void Scheduler_init(void);
extern void Scheduler_cyclic(void);
extern void Scheduler_StartTasks(void);

extern void Scheduler_SetActiveModule(Scheduler_LogicModuleEnum task);
extern void Scheduler_StopActiveModule(void);


#endif /* LOGIC_SCHEDULER_H_ */
