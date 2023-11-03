#include <stdio.h>
#include "pico/stdlib.h"

const uint led_pin = 25;
 
int main(){
    // Inicialización del Pin para el led 
    gpio_init(led_pin);
    gpio_set_dir(led_pin,GPIO_OUT);

    // Loop Infinito
    for (;;){
        //Blink LED
        gpio_put(led_pin,true);
        sleep_ms(5000);
        gpio_put(led_pin,false);
        sleep_ms(5000);
    }
}