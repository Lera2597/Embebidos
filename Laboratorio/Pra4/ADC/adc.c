#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

#include "adc.h"
#include "events.h"

volatile uint16_t    adc_samples[ADC_FIFO_SAMPLES] = {0};

void adc_myinit(void) {
    adc_init();
    
    // Deshabilitar el pin GPIO como entrada y salida digital
    //adc_gpio_init(ADC_PIN);
    // Seleccionar el canal para muestreo (ADC_PIN)
    adc_select_input(ADC_CHANNEL);
    // Configurar el tamaño de muestras a almacenar en la FIFO
    adc_fifo_setup(true, false, ADC_FIFO_SAMPLES, false, false);
    // Habilitar interrupciones
    adc_irq_set_enabled(true);
    // Establecer el manejador de la interrupción
    irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_isr);
    // Habilitar interrupción de FIFOs (Global)
    irq_set_enabled(ADC_IRQ_FIFO, true);
}

/* Función de atencion a interrupción del ADC cuando el número de muestras sea igual a ADC_FIFO_SAMPLES */
void adc_isr(void) {
    int i = 0;

    adc_run(false);

    while (i < ADC_FIFO_SAMPLES && !adc_fifo_is_empty()) {
        EV_ADC = true;
        
        adc_samples[i] = adc_fifo_get();
        i++;
    }
}