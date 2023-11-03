#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS      100         // Periodo de 100ms

extern struct repeating_timer timer;

bool timer_init(uint32_t);

#endif