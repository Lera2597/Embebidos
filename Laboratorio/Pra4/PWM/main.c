#include <stdio.h>
#include "pico/stdlib.h"

#include "pwm.h"
#include "events.h"

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();

    // Mensaje de bienvenida
    while (!stdio_usb_connected());    
    printf("\nControlador de LED y Motor DC!\n\n");
 
    // Inicializar el PWM
    if (!pwm_myinit()) {
        printf("Error inicializando el PWM: los canales pertenecen a diferentes slices de PWM.\n");
        //SYSTEM_HALT();
    }

    uint16_t con=0;
    uint8_t value=0;
    pwm_change_level(1,value);
    printf("inicio.\n");
    // Evitar que el main termine
    while (true){
        
        if (con<6000){
            //printf("con: %d.\n",con);
            con +=100;
        }
        else{
            con =0;
        }
        pwm_change_level(1,con);
        printf("Incremento Luminocidad\n");
        sleep_ms(50);
        
    }
    
    return 0;
}