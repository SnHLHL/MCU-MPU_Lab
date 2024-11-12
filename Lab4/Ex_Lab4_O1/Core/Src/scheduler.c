/*
 * scheduler_O(1).c
 *
 *  Created on: Oct 30, 2024
 *      Author: phuct
 */

#include "scheduler.h"

list my_list;
int32_t TaskID_arr[SCH_MAX_TASK];
uint32_t curID;
uint8_t dispatch;

/* For the O(1) structure, we will need an additional list to store all the tasks so that we can easily
 * manage and decide what task should be dispatched next based on the order of the tasks
 */

/*
Initially, the SCH_Init function will be called before the while(1) loop to delete all the task in
the list, reset the TaskID array to mark that all slots in the list are empty, and return all the pointer
to zero
*/

void SCH_Init(void) {
    node* tmp = my_list.head;
    while (tmp != NULL)
    {
    	node* next = tmp->next;
        SCH_Delete_Task(tmp->data.TaskID);
        tmp = next;
    }
    for (int32_t i=0; i<SCH_MAX_TASK; i++) {
        TaskID_arr[i] = -1;
    }
    curID = 0;
    dispatch = 0;
    my_list.head = NULL;
    my_list.tail = NULL;
    my_list.size = 0;
}

/* This SCH_Add_Task will search all the TaskID array via a loop until it finds an empty slot,
 * the empty slot is marked with -1. After an empty slot is found, it will find the correct insertion
 * point for the tasks in the list, based on its DELAY value, as the O(1) structure doing task in a
 * fixed pattern, the next task delay must be adjusted corresponding to the previous task, not by the
 * initial run time, the use LIST_Add_Task to add the tasks to our list.
 */

unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint32_t id_count = 0;
	node *cur = my_list.head;
	node* prev = NULL;

	// Find a free slot in TaskID_arr
    while (TaskID_arr[curID] != -1 && id_count < SCH_MAX_TASK)
    {
        curID = (curID+1)%SCH_MAX_TASK;
        id_count++;
    }

    if (id_count == SCH_MAX_TASK) {
        return SCH_MAX_TASK; // Task list is full
    }

    if (my_list.size == 0) {
    	LIST_Add_Task(&my_list, pFunction, DELAY/CYCLE, PERIOD, curID, prev, cur);
    } else {
    	uint32_t sum = 0;
    	while (DELAY >= sum + cur->data.DELAY && cur != NULL) {
    		sum += cur->data.DELAY;
    		prev = cur;
    		cur = cur->next;
    	}
    	uint32_t DELAY_NEW = DELAY - sum;
    	if (cur != NULL) {
    		cur->data.DELAY -= DELAY_NEW;
    	}
    	LIST_Add_Task(&my_list, pFunction, DELAY_NEW/CYCLE, PERIOD, curID, prev, cur);
//    }

    TaskID_arr[curID] = curID; // Update TaskID array to show that the current TaskID is in used
    return curID;
    }
}

/* The SCH_Delete_Task function, first checks if TaskID is valid (within range) and not marked as -1 in TaskID array
 * Then, it searches for the node with TaskID in the list, keeping track of the previous node to enable deletion. When
 * find the TaskID need to be deleted, call the LIST_Delete_Task to delete that TaskID and mark that ID slot as -1 (empty)
 */

unsigned char SCH_Delete_Task(uint32_t TaskID) {
    if (TaskID_arr[TaskID] == -1 || TaskID >= SCH_MAX_TASK) {
        return SCH_MAX_TASK;
    }

    // Locate and delete the specified task in list
    // This 2 lines is to start at the list head
    node* cur = my_list.head;
    node* prev = NULL;

    // Use the loop function to take a look all the TaskID in the list
    while(cur != NULL && cur->data.TaskID != TaskID){
    	prev = cur;
    	cur = cur->next;
    }

    if(cur == NULL){
    	return SCH_MAX_TASK; // Task with TaskID not found
    }


    // Delete the task and indicate an empty slot
    LIST_Delete_Head_Task(&my_list);
//    LIST_Delete_Task(&my_list, cur->data.TaskID);
    TaskID_arr[TaskID] = -1;
    return TaskID;
}

/* The SCH_Update function, we will start at the begin of the list, check if there is no dispatch flag is ON
 * In case the task located at the head of the list having the DELAY time exceed zero, we will decrease that
 * DELAY time so the head task will be executed when the DELAY reach 0.
 * In case the DELAY equal to zero already, set the dispatch flag to 1 indicating that task need to be executed
 */

void SCH_Update() {
    node* tmp = my_list.head;
    if (tmp != NULL && dispatch == 0) {
        if (tmp->data.DELAY > 0) {
            tmp->data.DELAY--;
        } else {
        	dispatch = 1;
        }
    }
}

/* The SCH_Dispatch_Tasks, in case the list head is empty, show the error. If not, we'll start the pointer at the begin of
 * the list, if there is a head task having DELAY = 0, we will execute the function of that task, then if the PERIOD is
 * set initially at 0, call the SCH_Delete_Task to remove that task from our list. But if the PERIOD is not 0, add that
 * same task to the list but with the DELAY same as the PERIOD of that task. Finally, set the dispatch flag to 0
 * to indicate that the scheduler is ready for the next execution/dispatch.
 */

void SCH_Dispatch_Tasks() {
	if (my_list.head == NULL) return;

    node* tmp = my_list.head;

    if (tmp->data.DELAY == 0 && tmp != NULL) {
        (*tmp->data.pTask)();
        if (tmp->data.PERIOD == 0) {
            SCH_Delete_Task(tmp->data.TaskID);
            return;
        } else {
        	// This else is to delete the task and add again the task to the list
            void (*pTask) (void) = tmp->data.pTask;
            uint32_t DELAY = tmp->data.DELAY;
            uint32_t PERIOD = tmp->data.PERIOD;
            uint32_t TaskID = tmp->data.TaskID;
            uint8_t RunMe = tmp->data.RunMe;

            SCH_Delete_Task(TaskID);
            SCH_Add_Task(pTask, PERIOD, PERIOD);
        }
        dispatch = 0;
    }
}

//#include <scheduler.h>
//
//static task_node* head = NULL;
//static task_node* tail = NULL;
//
//void SCH_Init(void) {
//    // Reset the task list
//    while (head != NULL) {
//        SCH_Delete_Head_Task();
//    }
//}
//
//void SCH_Update(void) {
//    // Traverse the linked list and update the delay for each task
//    task_node* current = head;
//    while (current != NULL) {
//        if (current->Delay == 0) {
//            // Task is due to run
//            current->RunMe += 1;
//            if (current->Period) {
//                // Reschedule periodic tasks
//                current->Delay = current->Period;
//            }
//        } else {
//            // Decrease the delay
//            current->Delay -= 1;
//        }
//        current = current->next;
//    }
//}
//
//unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
//    // Create a new task node
//    task_node* newTask = (task_node*)malloc(sizeof(task_node));
//    if (newTask == NULL) {
//        // Memory allocation failed
//        return SCH_MAX_TASKS;
//    }
//
//    // Initialize the new task node
//    newTask->pTask = pFunction;
//    newTask->Delay = DELAY / TICKS;
//    newTask->Period = PERIOD / TICKS;
//    newTask->RunMe = 0;
//    newTask->next = NULL;
//
//    // If the list is empty, set head and tail to the new task
//    if (head == NULL) {
//        head = newTask;
//        tail = newTask;
//    } else {
//        // Otherwise, add the new task to the end of the list
//        tail->next = newTask;
//        tail = newTask;
//    }
//
//    return 0; // Task added successfully
//}
//
//void SCH_Dispatch_Tasks(void) {
//    // Traverse the linked list and run tasks that are ready
//    task_node* current = head;
//    task_node* prev = NULL;
//
//    while (current != NULL) {
//        if (current->RunMe > 0) {
//            (*current->pTask)(); // Run the task
//            current->RunMe -= 1; // Reset the RunMe flag
//
//            // If it is a one-shot task, delete it
//            if (current->Period == 0) {
//                task_node* toDelete = current;
//
//                // Remove the node from the linked list
//                if (prev == NULL) {
//                    // We're deleting the head
//                    head = current->next;
//                    if (head == NULL) {
//                        tail = NULL; // List is empty now
//                    }
//                } else {
//                    // Remove the current node from the middle or end
//                    prev->next = current->next;
//                    if (current == tail) {
//                        tail = prev;
//                    }
//                }
//
//                // Free the memory
//                current = current->next;
//                free(toDelete);
//                continue;
//            }
//        }
//        // Move to the next task
//        prev = current;
//        current = current->next;
//    }
//}
//
//void SCH_Delete_Head_Task(void) {
//    // Remove the head task from the list if it exists
//    if (head != NULL) {
//        task_node* toDelete = head;
//        head = head->next;
//        if (head == NULL) {
//            tail = NULL; // List is empty now
//        }
//        free(toDelete);
//    }
//}
//
//void SCH_Delete_Task(void (*pFunction)()) {
//    // Check if the list is empty
//    if (head == NULL) {
//        return; // No task to delete
//    }
//
//    task_node* current = head;
//    task_node* previous = NULL;
//
//    // Traverse the linked list to find the task
//    while (current != NULL) {
//        if (current->pTask == pFunction) {
//            // Task found; remove the node
//            if (previous == NULL) {
//                // Deleting the head node
//                head = current->next;
//                if (head == NULL) {
//                    // If head becomes NULL, the list is empty, set tail to NULL
//                    tail = NULL;
//                }
//            } else {
//                // Deleting a non-head node
//                previous->next = current->next;
//                if (current == tail) {
//                    // If deleting the tail, update the tail pointer
//                    tail = previous;
//                }
//            }
//
//            // Free the memory
//            free(current);
//            return; // Task deleted successfully, exit the function
//        }
//
//        // Move to the next node
//        previous = current;
//        current = current->next;
//    }
//}
