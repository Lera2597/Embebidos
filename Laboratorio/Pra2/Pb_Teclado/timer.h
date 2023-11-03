#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS     100

extern volatile uint8_t timer_req;


void timer_init_(uint32_t);

#endif