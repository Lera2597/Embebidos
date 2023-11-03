#include <stdio.h>
#include "pico/stdlib.h"


#include "timer.h"

const uint led_pin = 0;
bool estado_led = false;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    timer_init_(TIMER_PERIOD_MS);
    
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while (true) {

        if(timer_req){
            timer_req = false;
            
            estado_led = !estado_led;
            gpio_put(led_pin, estado_led);
        }

        // Entrar en modo de bajo consumo
        __asm volatile ("wfi");

    }
 
    return 0;
}