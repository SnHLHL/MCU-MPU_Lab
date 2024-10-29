/*
 * led_display.c
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#include "led_display.h"

uint16_t led_matrix[MAX_MATRIX] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// Create a buffer for led matrix corresponding to num 0 to 9
//	| 0x3F = 00111111 = Num 0 | 0x06 = 00000110 = Num 1 | 0x5B = 01011011 = Num 2 | 0x4F = 01001111 = Num 3
//	| 0x66 = 01100110 = Num 4 | 0x6D = 01101101 = Num 5 | 0x7D = 01111101 = Num 6 |
//	| 0x07 = 00000111 = Num 7 | 0x7F = 01111111 = Num 8 | 0x6F = 01101111 = Num 9 |
int led_buffer[MAX_BUFF] = {0,0,0,0};

//------Display LED 7SEG--------//
void display7SEG(int number){
	uint16_t bit_var = led_matrix[number];
	HAL_GPIO_WritePin(GPIOB, bit_var, RESET);
	HAL_GPIO_WritePin(GPIOB, ~bit_var, SET);	// "~" mean NOT operator, inverts the bit from 1 to 0 and vice versa
}

//------Update Clock Buffer--------//
//If counter1 < 10, e.g. value = 2, 7SEG1 display 0 and 7SEG2 display 2
//If counter1 > 10, e.g. value = 12, 7SEG1 display 1 and 7SEG2 display 2
void updateClockBuffer(int counter1, int counter2){
	    led_buffer[0] = counter1 / 10;	// The divider / is to take the digit at tens
		led_buffer[1] = counter1 % 10;	// The divider % is to take the digit at units
		led_buffer[2] = counter2 / 10;
		led_buffer[3] = counter2 % 10;
}

//------Update Clock Buffer to LED 7SEG--------//
// show which led 7 segment is ON and the value it display
void update7SEG(int index){
	switch(index){
	case 0:
		// Display the first 7 SEG with led_buffer[0]
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin, SET);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer[1]
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, SET);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		// Display the third 7 SEG with led_buffer[2]
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN3_Pin, SET);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		// Display the forth 7 SEG with led_buffer[3]
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, EN0_Pin| EN1_Pin | EN2_Pin , SET);
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}
//-----Display Clock in LED 7SEG with 250ms for each LED-----//
int index_led = 0;
void scanLed(){
	if(timer3_flag == 1){
		if(status == 2 || 3 || 4 || 5){
			if(is_button_pressed_short(2) == 1){
				if(tmpRED != defaultTimeRed) tmpRED = defaultTimeRed;
				if(tmpAMBER != defaultTimeAmber) tmpAMBER = defaultTimeAmber;
				if(tmpGREEN != defaultTimeGreen) tmpRED = defaultTimeGreen;
			}
			if(is_button_pressed_1s(2) == 1){
				if((defaultTimeRed - (defaultTimeGreen + defaultTimeAmber)) != 0){
					if((defaultTimeRed - (defaultTimeGreen + defaultTimeAmber)) > 0){
						defaultTimeAmber++;
						defaultTimeGreen = defaultTimeRed - defaultTimeAmber;
					}
					if((defaultTimeRed - (defaultTimeGreen + defaultTimeAmber)) < 0){
						if(defaultTimeRed < (defaultTimeGreen + defaultTimeAmber)){
							defaultTimeAmber = 2;
							defaultTimeGreen = 3;
							defaultTimeRed = 5;
						}
					}
				}
			}
		}
		if(status == MAN_MODE2)
			updateClockBuffer(2, tmpRED);
		if(status == MAN_MODE3)
			updateClockBuffer(3, tmpAMBER);
		if(status == MAN_MODE4)
			updateClockBuffer(4, tmpGREEN);
		update7SEG(index_led++);
		if(index_led > 3) index_led = 0;
		setTimer3(250);
	}
}
