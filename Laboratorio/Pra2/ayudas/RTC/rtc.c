#include <stdio.h>
#include "pico/stdlib.h"

#include "rtc.h"

volatile uint8_t alarm_req = false;

/* Manejador de interrupción o callback */
void alarm_callback() {
    alarm_req = true;
}

/* Rutina para preparar el timer */
void rtc_alarm_init(datetime_t *t) {
    rtc_set_alarm(t, &alarm_callback);
    //add_repeating_timer_ms(-delay_ms, timer_callback, NULL, &timer);
}
