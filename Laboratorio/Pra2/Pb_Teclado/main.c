#include <stdio.h>
#include "pico/stdlib.h"

#include "gpio.h"
#include "timer.h"
#include "keyboard.h"

const uint led_pin = 0;
bool estado_led = false;

bool start_timer=false;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    keyboard_init();// inicializamos el keyboard  
    sleep_ms(1000);
    printf("------Presione cualquier tecla---.\n");
    while (true) {

        if(gpio_req){
            timer_init_(TIMER_PERIOD_MS);
            start_timer = true;
            gpio_req = false;
        }
        if(timer_req){
            printf("Tecla: %c.\n",capture_key());
            start_timer = false;
            timer_req = false;
        }
        // Entrar en modo de bajo consumo
        __asm volatile ("wfi");

    }
 
    return 0;
}