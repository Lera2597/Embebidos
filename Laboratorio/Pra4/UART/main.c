#include <stdio.h>
#include "pico/stdlib.h"


//#include "timer.h"
//#include "adc.h"
#include "events.h"
#include "general.h"
//#include "hc_sr04.h"
#include "uart.h"
//#include "pwm.h"

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    
    // Mensaje de bienvenida
    while (!stdio_usb_connected());    
    printf("\nControlador de LED y Motor DC!\n\n");
    /*
    // Inicializar el TIMER (Para disparar los eventos de ADC)
    if (!timer_init(TIMER_PERIOD_MS)) {
        printf("Error inicializando el timer.\n");
        SYSTEM_HALT();
    }*/
    /*
    // Inicializar el PWM
    if (!pwm_myinit()) {
        printf("Error inicializando el PWM: los canales pertenecen a diferentes slices de PWM.\n");
        SYSTEM_HALT();
    }*/
    //Inicialización de uart
    init_uart();

    // Inicialización del Hardware del ADC
    //adc_myinit();
    //sr04_init();


    // Evitar que el main termine
    while (true){
    // Esperar por eventos
    eventsController();

    }
    return 0;
}