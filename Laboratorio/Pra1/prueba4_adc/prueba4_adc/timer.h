#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS     1000
#define TIME_SAMPLE0     1
#define TIME_SAMPLE1     1

extern volatile uint8_t timer_req;
extern struct repeating_timer timer;
extern uint8_t timer_counter0;
extern uint8_t timer_counter1;

void timer_init(uint32_t);

#endif