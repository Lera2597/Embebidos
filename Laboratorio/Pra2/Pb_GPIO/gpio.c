#include <stdio.h>
#include "pico/stdlib.h"

#include "gpio.h"
#include "timer.h"

volatile uint8_t gpio_req = false;
struct repeating_timer timer;
//uint8_t timer_counter = TIMER_INTS_TO_GEN;

/* Manejador de interrupción o callback */
void gpio_callback(uint gpio,uint32_t evento) {
    if(gpio_req==false){
        gpio_req = true;
        timer_init_(TIMER_PERIOD_MS);
    }
      
}

/* Rutina para preparar el timer */
void gpio_init_(uint num_gpio) {
    //gpio_init(num_gpio);
    gpio_pull_up(num_gpio);
    gpio_set_irq_enabled_with_callback(num_gpio,2,true, &gpio_callback);
    printf("GPIO Configurado!\n");
}