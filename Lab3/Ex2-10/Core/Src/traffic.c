/*
 * traffic.c
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#include "traffic.h"

void setTrafficRed1(){
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_RESET);
}

void setTrafficAmber1(){
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_RESET);
}

void setTrafficGreen1(){
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AMBER1_GPIO_Port, AMBER1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, GPIO_PIN_SET);
}

void setTrafficRed2(){
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_RESET);
}

void setTrafficAmber2(){
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_RESET);
}

void setTrafficGreen2(){
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AMBER2_GPIO_Port, AMBER2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, GPIO_PIN_SET);
}
