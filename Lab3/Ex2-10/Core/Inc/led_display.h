/*
 * led_display.h
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"
#include "global.h"
#include "timer.h"
#define MAX_MATRIX 10
#define MAX_BUFF 4

void display7SEG();
void updateClockBuffer();
void scanLed();

#endif /* INC_LED_DISPLAY_H_ */
