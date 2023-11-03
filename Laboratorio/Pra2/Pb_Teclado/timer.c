#include <stdio.h>
#include "pico/stdlib.h"

#include "timer.h"

volatile uint8_t timer_req = false;

/* Manejador de interrupción o callback */
int64_t timer_callback( __unused alarm_id_t id, __unused void *user_data) {
    timer_req = true;
    return 0;
}

/* Rutina para preparar el timer */
void timer_init_(uint32_t delay_ms) {
    add_alarm_in_ms(delay_ms, timer_callback, NULL, true);
    //add_repeating_timer_ms(-delay_ms, timer_callback, NULL, &timer);
}