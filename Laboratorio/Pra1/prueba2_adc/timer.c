#include <stdio.h>
#include "pico/stdlib.h"

#include "timer.h"

volatile uint8_t timer_req = false;
struct repeating_timer timer;
uint8_t timer_counter0 = TIME_SAMPLE0;
uint8_t timer_counter1 = TIME_SAMPLE1;

/* Manejador de interrupción o callback */
bool timer_callback(struct repeating_timer *t) {
    timer_req = true;
    return true;
}

/* Rutina para preparar el timer */
void timer_init(uint32_t delay_ms) {
    add_repeating_timer_ms(-delay_ms, timer_callback, NULL, &timer);
    printf("Timer creado!\n");
}