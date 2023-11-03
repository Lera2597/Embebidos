#include <stdio.h>
#include "pico/stdlib.h"

#include "timer.h"
#include "adc.h"
#include "events.h"
#include "general.h"

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();

    // Mensaje de bienvenida
    while (!stdio_usb_connected());    
    printf("\nControlador de LED y Motor DC!\n\n");
 
    // Inicializar el TIMER (Para disparar los eventos de ADC)
    if (!timer_init(TIMER_PERIOD_MS)) {
        printf("Error inicializando el timer.\n");
        SYSTEM_HALT();
    }

    // Inicialización del Hardware del ADC
    adc_myinit();

    // Esperar por eventos
    eventsController();

    // Evitar que el main termine
    while (true);
 
    return 0;
}