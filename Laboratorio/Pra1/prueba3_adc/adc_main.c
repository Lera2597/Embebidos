#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "adc.h"
#include "timer.h"


int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    //adc_init();

    // Pausa para esperar a que la terminal serial esté lista
    printf("\nGenerador de interrupciones periodicas!\n\n");

    // Make sure GPIO is high-impedance, no pullups etc
    //adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    //adc_select_input(0);
    
    sleep_ms(5000);
    adc_init_();
    //Inicializar el TIMER (Alarm)
    timer_init(TIMER_PERIOD_MS);

    //Inicializar la fifo
    adc_fifo_init();
    

    //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
    // Wait for alarm callback to set timer_fired
    uint32_t data=0;
    bool id= false;
    while (true) {
        if (timer_req) {
            timer_req = false;
            if (timer_counter0 == 0 ) { //podemos ponerle menor que 0
                if(adc_ready()){
                    timer_counter0 = TIME_SAMPLE0;
                    printf("-----------Nueva muestra canal 0----------\n");
                    adc_init_convert(0);
                    id= false;
                }

            }
            else{
                timer_counter0--;
            }
           
            if (timer_counter1 == 0  ) { //podemos ponerle menor que 0
                if(adc_ready()){
                    timer_counter1 = TIME_SAMPLE1;
                    printf("-----------Nueva muestra canal 1----------\n");
                    adc_init_convert(1);
                    id=true;
                }
            }
            else{
                timer_counter1--;
            }
        }
        if( adc_ready() & !adc_fifo_empty()){
            data=adc_fifo_get();
        }
        printf("Muestra: %d, Canal: %d\n",data,id );
        sleep_ms(100);
        // Entrar en modo de bajo consumo
        __asm volatile ("wfi");
    }
 
    return 0;
}