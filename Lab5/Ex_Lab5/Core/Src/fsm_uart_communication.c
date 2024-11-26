/*
 * fsm_uart_communication.c
 *
 *  Created on: Nov 22, 2024
 *      Author: phuct
 */

#include "fsm_uart_communication.h"

void uart_communication_fsm(){
	switch(state){
	case RX_COM:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		sprintf(response, "!ADC=%lu#", ADC_value);
		if(temp == '!') status = start;
		if(command_flag == 1){
			// Get ADC_value
			command_flag = 0;
			// Move to the Transmit status
			state = TX_COM;
		}
		break;
	case TX_COM:
			//Send data to console
			HAL_UART_Transmit(&huart2, (uint8_t *) response, strlen(response) , 1000);
			setTimer1(3000);
			state = WAIT;
		break;
	case WAIT:
		if(timer1_flag == 1){
			// Time out 3s waiting for OK, if running out, back to Transmitting mode
			state = TX_COM;
		}
		if(command_flag == 2){
			// In case OK, back to Receiving mode
			command_flag = 0;
			state = RX_COM;
		}
		if(temp == '!') status = start;
		break;
	default:
		break;
	}
}
