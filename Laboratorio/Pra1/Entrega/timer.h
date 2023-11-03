#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_PERIOD_MS     100
#define TIME_SAMPLE0     10
#define TIME_SAMPLE1     10
#define PERIODO_LED0     5
#define PERIODO_LED1     10           

extern volatile uint8_t timer_req;
extern struct repeating_timer timer;
extern uint8_t timer_counter0;
extern uint8_t timer_counter1;
extern uint8_t counter_led0;
extern uint8_t counter_led1;

void timer_init(uint32_t);

#endif