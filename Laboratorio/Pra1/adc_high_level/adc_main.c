#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "adc.h"


int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();


    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_run(true);//Muestreo libre
    adc_set_round_robin(3);
    adc_irq_set_enabled(false);//habilitar interrupción

    adc_fifo_setup(true,true,1,true,false);

    sleep_ms(5000);
    // Wait for alarm callback to set timer_fired
    while (true) {
        if (adc_interrupt() == true){
            printf("Dato: %d, canal: %d\n", data , canal );
        }
        sleep_ms(100);
        __asm volatile ("wfi");
    }
 
    return 0;
}