#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS     1000
#define TIMER_INTS_TO_GEN     20

extern volatile uint8_t timer_req;
extern struct repeating_timer timer;
extern uint8_t timer_counter;

void timer_init(uint32_t);

#endif