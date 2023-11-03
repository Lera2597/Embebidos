#include <stdio.h>
#include "pico/stdlib.h"
 
#include "timer.h"

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();

    // Pausa para esperar a que la terminal serial esté lista
    printf("\nGenerador de interrupciones periodicas!\n\n");


    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);
    bool estado=true;
    // Inicializar el TIMER (Alarm)
    timer_init(TIMER_PERIOD_MS);
    
    // Wait for alarm callback to set timer_fired
    while (true) {
        if (timer_req) {
            timer_req = false;
            estado=!estado;
            gpio_put(0, estado);
            printf("Interrupcion de timer generada. Timestamp %ld\n", time_us_32());
            /*if (--timer_counter == 0) {
                bool cancelled = cancel_repeating_timer(&timer);
                printf("Timer cancelado: %d\n", cancelled);
            }*/
        }

        // Entrar en modo de bajo consumo
        __asm volatile ("wfi");

    }
 
    return 0;
}