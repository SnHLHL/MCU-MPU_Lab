/*
 * fsm_setting.c
 *
 *  Created on: Oct 24, 2024
 *      Author: phuct
 */

#include "fsm_setting.h"

void fsm_setting_run(){
	switch(status){
	case SET_MODE1:
		updateClockBuffer(1, defaultTimeRed);
		setTrafficRed1();
		setTrafficRed2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeRed--;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeRed--;
		}
		if(is_button_pressed_short(2) == 1){
			defaultTimeRed++;
		}
		if(is_button_pressed_1s(2) == 1){
			defaultTimeRed++;
		}
		if(defaultTimeRed < 0){
			defaultTimeRed = 99;
		}
		if(defaultTimeRed > 99){
			defaultTimeRed = 0;
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = SET_MODE2;
		}
		if(is_button_pressed_1s(1) == 1){
			setTimer1(250);
			status = AUTO_RED_GREEN;
		}
		break;
	case SET_MODE2:
		updateClockBuffer(2, defaultTimeAmber);
		setTrafficAmber1();
		setTrafficAmber2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeAmber--;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeAmber--;
		}
		if(is_button_pressed_short(2) == 1){
			defaultTimeAmber++;
		}
		if(is_button_pressed_1s(2) == 1){
			defaultTimeAmber++;
		}
		if(defaultTimeAmber < 0){
			defaultTimeAmber = 99;
		}
		if(defaultTimeAmber > 99){
			defaultTimeAmber = 0;
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = SET_MODE3;
		}
		if(is_button_pressed_1s(1) == 1){
			setTimer1(250);
			status = AUTO_GREEN_RED;
		}
		break;
	case SET_MODE3:
		updateClockBuffer(3, defaultTimeGreen);
		setTrafficGreen1();
		setTrafficGreen2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeGreen--;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeGreen--;
		}
		if(is_button_pressed_short(2) == 1){
			defaultTimeGreen++;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeGreen++;
		}
		if(defaultTimeGreen < 0){
			defaultTimeGreen = 99;
		}
		if(defaultTimeGreen > 99){
			defaultTimeGreen = 0;
		}
		if(is_button_pressed_1s(1) == 1 || is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = AUTO_GREEN_RED;
		}
		break;
	default:
		break;
	}
}
