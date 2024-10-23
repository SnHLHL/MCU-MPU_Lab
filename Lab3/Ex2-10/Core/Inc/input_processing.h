/*
 * input_processing.h
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"
#include "input_reading.h"

void fsm_for_input_processing(GPIO_PinState buttonBuffer[], int index);

#endif /* INC_INPUT_PROCESSING_H_ */
