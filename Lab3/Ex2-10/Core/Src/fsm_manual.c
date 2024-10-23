/*
 * fsm_manual.c
 *
 *  Created on: Oct 22, 2024
 *      Author: phuct
 */

#include "fsm_manual.h"

void fsm_manual_run(){
	switch(status){
	case MAN_MODE1:
		//Return to status INIT / AUTO_RED_GREEN
		setTimer1(defaultTimeGreen*1000);
		setTimer2(1000);
		timeRED = defaultTimeRed;
		timeGREEN = defaultTimeGreen;
		tmpAMBER = defaultTimeAmber;
		updateClockBuffer(timeRED--, timeGREEN--);
		status = AUTO_RED_GREEN;
		break;
	case MAN_MODE2:
		//Only Red LEDs in both Road 1 and 2 are ON, other LEDs are OFF
		setTrafficRed1();
		setTrafficRed2();
		//If BUTTON1 is pressed, switch to status MAN_MODE3
		if(is_button_pressed_short(0) == 1){
			status = MAN_MODE3;
			setTimer1(500); //2Hz mean 2 LEDs turn ON for 1 sec, each LED ON for 500ms
		}
		else if(is_button_pressed_1s(0) == 1){
			status = MAN_MODE3;
			setTimer1(500);
		}
		//Blinking Red LEDs
		if(timer1_flag == 1){
			setTimer1(500);
			HAL_GPIO_TogglePin(RED1_GPIO_Port,RED1_Pin);
			HAL_GPIO_TogglePin(RED2_GPIO_Port,RED2_Pin);
		}
		//If BUTTON2 is pressed, tempRED value increase 1 unit
		//If value overcome 99, it return to 1
		if(is_button_pressed_short(1) == 1){
			tmpRED++;
			if(tmpRED > 99) tmpRED = 1;
			updateClockBuffer(2, tmpRED);
		}
		else if(is_button_pressed_1s(1) == 1){
			tmpRED++;
			if(tmpRED > 99) tmpRED = 1;
			updateClockBuffer(2, tmpRED);
		}
		//If BUTTON3 is pressed, tmpRED is assigned for defaultTimeRed
		if(is_button_pressed_short(2) == 1){
			defaultTimeRed = tmpRED;
		}
		updateClockBuffer(2, defaultTimeRed); //Num 2 display the current Mode 2 to blink Red LEDs
		break;
	case MAN_MODE3:
		//Only Amber LEDs in both Road 1 and 2 are ON, other LEDs are OFF
		setTrafficAmber1();
		setTrafficAmber2();
		//If BUTTON1 is pressed, switch to status MAN_MODE4
		if(is_button_pressed_short(0) == 1){
			status = MAN_MODE4;
			setTimer1(500);
		}
		else if(is_button_pressed_1s(1) == 1){
			status = MAN_MODE1;
			setTimer1(500);
		}
		//Blinking Amber LEDs
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(AMBER1_GPIO_Port,AMBER1_Pin);
			HAL_GPIO_TogglePin(AMBER2_GPIO_Port,AMBER2_Pin);
			setTimer1(500);
		}
		//If BUTTON2 is pressed, tmpAMBER value increase 1 unit
		//If value overcome 99, it return to 1
		if(is_button_pressed_short(1) == 1){
			tmpAMBER++;
			if(tmpAMBER > 99) tmpAMBER = 1;
			updateClockBuffer(3, tmpAMBER);
		}
		else if(is_button_pressed_1s(1) == 1){
			tmpAMBER++;
			if(tmpAMBER > 99) tmpAMBER = 1;
			updateClockBuffer(3, tmpAMBER);
		}
		//If BUTTON3 is pressed, tempAMBER is assigned for defaultTimeAmber
		if(is_button_pressed_short(2) == 1){
			defaultTimeAmber = tmpAMBER;
		}
		updateClockBuffer(3, defaultTimeAmber);	//Num 3 display the current Mode 3 to blink Amber LEDs
		break;
	case MAN_MODE4:
		//If BUTTON1 is pressed, switch to status MAN_MODE1
		if(is_button_pressed_short(0) == 1){
			status = MAN_MODE1;
		}
		if(is_button_pressed_1s(0) == 1){
			status = MAN_MODE1;
		}
		//Only Green LEDs in both Road 1 and 2 are ON, other LEDs are OFF
		setTrafficGreen1();
		setTrafficGreen2();
		//Blinking Green LEDs
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(GREEN1_GPIO_Port,GREEN1_Pin);
			HAL_GPIO_TogglePin(GREEN2_GPIO_Port,GREEN2_Pin);
			setTimer1(500);
		}
		//If BUTTON2 is pressed, tmpGREEN value increase 1 unit
		//If value overcome 99, it return to 1
			if(is_button_pressed_short(1) == 1){
				tmpGREEN++;
				if(tmpGREEN > 99) tmpGREEN = 1;
			}
			if(is_button_pressed_1s(1) == 1){
				tmpGREEN++;
				if(tmpGREEN > 99) tmpGREEN = 1;
			}
		//If BUTTON3 is pressed, tmpGREEN is assigned for defaultTimeGreen
			if(is_button_pressed_short(2) == 1){
				defaultTimeGreen = tmpGREEN ;
			}
		updateClockBuffer(4, defaultTimeGreen);	//Num 4 display the current Mode 4 to blink Green LEDs
		break;
	default:
		break;
	}
}
