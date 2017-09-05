/*
 * SpecialTasks.h
 *
 *  Created on: Sep 5, 2017
 *      Author: Joonatan
 */

#ifndef LOGIC_SPECIALTASKS_H_
#define LOGIC_SPECIALTASKS_H_


#include "typedefs.h"

typedef enum
{
    TASK_FOR_GIRLS, //TODO : Add more types.
    TASK_FOR_GUYS,
    NUMBER_OF_TASK_TYPES
} SpecialTaskType;

typedef Boolean (*OverrideFunc)(U8 sec); //Returns TRUE, if done with override.
typedef Boolean (*SpecialTaskFunc)(U8 sec, SpecialTaskType type);

extern Boolean girlsSpecialTask(U8 sec);
extern Boolean guysSpecialTask(U8 sec);

#endif /* LOGIC_SPECIALTASKS_H_ */
