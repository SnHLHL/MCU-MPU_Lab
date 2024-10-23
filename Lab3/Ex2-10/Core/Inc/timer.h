/*
 * timer.h
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

void setTimer1(int);
void setTimer2(int);
void setTimer3(int);
void timer_run(void);

#endif /* INC_TIMER_H_ */
