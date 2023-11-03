#include <stdio.h>
#include "pico/stdlib.h"

#include "gpio.h"
#include "timer.h"
const uint led_pin = 0;
bool estado_led = false;
bool estado_puerto = true;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    gpio_init_(15);
    
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    while (true) {

        if(gpio_req){
            if(timer_req){
                gpio_req = false;
                timer_req = false;
                estado_puerto = gpio_get(15);
            }
        }
        if(estado_puerto== false){
            estado_led = !estado_led;
            gpio_put(led_pin, estado_led);
            estado_puerto = true;
        }
        // Entrar en modo de bajo consumo
        __asm volatile ("wfi");

    }
 
    return 0;
}