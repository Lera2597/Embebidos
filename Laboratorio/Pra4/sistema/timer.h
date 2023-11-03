#ifndef _TIMER_H
#define _TIMER_H


#define TIMER_PERIOD_MS      10         // Periodo de 10ms

extern struct repeating_timer timer;

bool timer_init(uint32_t);

#endif