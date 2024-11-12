/*
 * button.h
 *
 *  Created on: Oct 30, 2024
 *      Author: phuct
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

void button_reading(void);

unsigned char is_button_pressed_short(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);

// We aim to work with more than one button
#define NO_OF_BUTTONS 1 // Updated to handle 3 buttons

#endif /* INC_BUTTON_H_ */
