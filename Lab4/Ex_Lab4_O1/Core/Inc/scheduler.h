/*
 * scheduler_O(1).h
 *
 *  Created on: Oct 30, 2024
 *      Author: phuct
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "list.h"

#define SCH_MAX_TASK    40
#define TICKS 			10

void SCH_Init(void);

unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

unsigned char SCH_Delete_Task(uint32_t TaskID);

void SCH_Update();

void SCH_Dispatch_Tasks();

#endif /* INC_SCHEDULER_H_ */
