/*
 * fsm_command_parser.c
 *
 *  Created on: Nov 22, 2024
 *      Author: phuct
 */

#include "fsm_command_parser.h"

void command_parser_fsm() {
    switch (status) {
	case INIT:
		if(buffer[index_buffer - 1] == '!') {  // Start command detection
			status = start;
		}
		break;

	case start:
		if (buffer[index_buffer - 1] == '!') {  // Handle repeated `!`
			status = start;
		} else if (buffer[index_buffer - 1] == 'R') {
			status = fsm_R;
		} else if (buffer[index_buffer - 1] == 'O') {
			status = fsm_O;
		} else {  // Invalid command
			status = INIT;
		}
		break;

	case fsm_R:  // Detected `!R`
		if (buffer[index_buffer - 1] == 'S') {
			status = fsm_S;
		} else {  // Any other character invalidates the command
			status = INIT;
		}
		break;

	case fsm_S:  // Detected `!RS`
		if (buffer[index_buffer - 1] == 'T') {
			status = fsm_T;
		} else {
			status = INIT;
		}
		break;

	case fsm_T:  // Detected `!RST`
		if (buffer[index_buffer - 1] == '#') {  // Complete `!RST#`
			command_flag = 1;  // Mark as `!RST#` command detected
			memset(buffer, 0, sizeof(buffer));
			index_buffer = 0;
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
			status = finish1;
		} else {
			status = INIT;
		}
		break;

	case fsm_O:  // Detected `!O`
		if (buffer[index_buffer - 1] == 'K') {
			status = fsm_K;
		} else {
			status = INIT;
		}
		break;

	case fsm_K:  // Detected `!OK`
		if (buffer[index_buffer - 1] == '#') {  // Complete `!OK#`
			command_flag = 2;  // Mark as `!OK#` command detected
			memset(buffer, 0, sizeof(buffer));
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			status = finish2;
		} else {
			status = INIT;
		}
		break;

	case finish1:  // `!RST#` completed
		// Reset FSM to `INIT` for new command processing
		status = INIT;
		break;

	case finish2:  // `!OK#` completed
		// Reset FSM to `INIT` for new command processing
		status = INIT;
		break;

	default:
		status = INIT;  // Fall back reset
		break;
    }
}
