/*
 * global.c
 *
 *  Created on: Nov 22, 2024
 *      Author: phuct
 */

#include "global.h"

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t command_flag = 0;

uint32_t ADC_value = 0;
char response[50] = {0};
uint8_t str[12] = {0};

int status = 0;
int state = 11;
