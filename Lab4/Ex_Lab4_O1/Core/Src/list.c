/*
 * list.c
 *
 *  Created on: Nov 2, 2024
 *      Author: phuct
 */

#include "list.h"


/* The LIST_Add_Task function, after initialize all the parameters and pointers for the task, it will find a way to add
 * that task to the list
 * If the list is empty, our new task becomes the head (also the tail) of the list -> only task in list
 * If there is no previous node of the pointer, then we add our task to the head of the list
 * If there is no current node at the pointer, we move the pointer to the very end and add the task in
 * If not any of those cases, add the task to the middle of the list prev -> task -> current
 */
unsigned char LIST_Add_Task(list* my_list, void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD, uint32_t TaskID, node* prev, node* cur) {
	node* task = (node*)malloc(sizeof(node));
	task->data.pTask = pFunction;
	task->data.DELAY = DELAY;
	task->data.PERIOD = PERIOD;
	task->data.TaskID = TaskID;
	task->data.RunMe = 0;
	task->next = NULL;

	if (my_list->size == 0) {
		my_list->head = task;
		my_list->tail = task;
		my_list->size++;
		return TaskID;
	} else if (prev == NULL) {
		task->next = my_list->head;
		my_list->head = task;
		my_list->size++;
		return TaskID;
	} else if (cur == NULL) {
		my_list->tail->next = task;
		my_list->tail = task;
		my_list->size++;
		return TaskID;
	} else {
		prev->next = task;
		task->next = cur;
		my_list->size++;
		return TaskID;
	}
}

/* The LIST_Delete_Task, first initialize the pointers and check if the list is empty.
 * If there is only 1 task in the list (size = 1), delete that task or the head (also tail) of the list and free the pointer memory
 * The while loop is to look for the specified taskID needed to be deleted, if can't find, return error code
 * 	(prev=NULL) if that task is at the head, updates the pointer to the next head when the old head deleted
 * 	(tmp->next = NULL) if that task is at the tail, updates the pointer to the previous tail when the old tail deleted
 * 	If the task is at the middle, bypass that task A -> B -> C => A -> C -> C => A -> C (delete old C)
 */

unsigned char LIST_Delete_Task(list* my_list, uint32_t TaskID) {
    node* tmp = my_list->head;
    node* prev = NULL;
    if (my_list->size <= 0) {
        return SCH_MAX_TASK;
    }

    if (my_list->size == 1) {
        my_list->head = NULL;
        my_list->tail = NULL;
        my_list->size--;
        free(tmp);
        return TaskID;
    }

    while (tmp->data.TaskID != TaskID && tmp != NULL) {
    	prev = tmp;
    	tmp = tmp->next;
    }

    if (tmp == NULL) {
    	return SCH_MAX_TASK;
    } else if (prev == NULL) {
    	my_list->head = my_list->head->next;
    	my_list->size--;
    	free(tmp);
    	return TaskID;
    } else if (tmp->next == NULL) {
    	prev->next = NULL;
    	my_list->tail = prev;
    	my_list->size--;
    	free(tmp);
    	return TaskID;
    } else {
    	prev->next = tmp->next;
    	tmp->next = NULL;
    	free(tmp);
    	my_list->size--;
    	return TaskID;
    }
    return TaskID;
}

/* The LIST_Delete_Head_Task function, first check if the list is empty, if not continue
 * If there is only one task (size = 1), guide the pointer at the head of list, store the taskID then delete that task
 * also decrease the list size.
 * If there are more than 1 tasks, by pass the head node and then free the old head A(head) -> B => A -> B(new head) => B(head)
 */

unsigned char LIST_Delete_Head_Task(list* my_list) {
    if (my_list->size <= 0) {
        return SCH_MAX_TASK;
    } else if (my_list->size == 1) {
    	node* tmp = my_list->head;
    	uint32_t TaskID = tmp->data.TaskID;
        my_list->head = NULL;
        my_list->tail = NULL;
        my_list->size--;
        free(tmp);
        return TaskID;
    } else {
    	node*tmp = my_list->head;
    	uint32_t TaskID = tmp->data.TaskID;
    	my_list->head = my_list->head->next;
    	my_list->size--;
    	free(tmp);
    	return TaskID;
    }
}
