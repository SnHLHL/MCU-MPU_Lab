/*
 * timer.c
 *
 *  Created on: Nov 22, 2024
 *      Author: phuct
 */

#include "timer.h"

#define TICK 10

int timer1_counter = 0;
int timer1_flag = 0;
int timer2_counter = 0;
int timer2_flag = 0;

void setTimer1(int duration){
	if(duration > 0){
		timer1_counter = duration/TICK;
		timer1_flag = 0;
	}
}

void setTimer2(int duration){
	if(duration > 0){
		timer2_counter = duration/TICK;
		timer2_flag = 0;
	}
}

void timerRun(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}
	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0){
			timer2_flag = 1;
		}
	}
}
