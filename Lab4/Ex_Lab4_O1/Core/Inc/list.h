/*
 * list.h
 *
 *  Created on: Nov 2, 2024
 *      Author: phuct
 */

#ifndef INC_LIST_H_
#define INC_LIST_H_

#include "scheduler.h"
#include "stdlib.h"
#include "stdint.h"
#include "main.h"

#define CYCLE 1

typedef struct {
    void (*pTask) (void);
    uint32_t DELAY;
    uint32_t PERIOD;
    uint32_t TaskID;
    uint8_t RunMe;
} sTask;

typedef struct
{
    sTask data;
    struct node* next;
} node;

typedef struct
{
    node* head;
    node* tail;
    uint32_t size;
} list;

unsigned char LIST_Add_Task_Head(list* my_list, void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD, uint32_t TaskID);

unsigned char LIST_Delete_Task(list* my_list, uint32_t TaskID);

unsigned char LIST_Delete_Head_Task(list* my_list);

#endif /* INC_LIST_H_ */
