#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "timer.h"



int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    adc_init();

    // Pausa para esperar a que la terminal serial esté lista
    printf("\nGenerador de interrupciones periodicas!\n\n");

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);
 
    // Inicializar el TIMER (Alarm)
    timer_init(TIMER_PERIOD_MS);

    
    // Wait for alarm callback to set timer_fired
    while (true) {
        if (timer_req) {
            timer_req = false;

            printf("Interrupcion de timer generada. Timestamp %ld\n", time_us_32());
            uint16_t result = adc_read();
            printf("Muestra: %d\n", result);

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