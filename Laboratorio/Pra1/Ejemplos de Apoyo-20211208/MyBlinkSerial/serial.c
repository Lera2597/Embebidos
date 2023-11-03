#include <stdio.h>
#include "pico/stdlib.h"

#include "getvalue.h"

const uint32_t led_pin = 25;

int main() {
    uint32_t sleepValue = MIN_SLEEP_VALUE, sleepValueTemp;

    // Inicializar Pin 25 como salida
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Inicializar las funciones de entrada/salida estándar
    stdio_init_all();
    printf("Presione cualquier tecla para cambiar el tiempo de sleep.\n");

    while (1) {
        gpio_put(led_pin, true);
        printf("Led is on\n");
        sleep_ms(sleepValue);
        gpio_put(led_pin, false);
        printf("Led is off\n");
        sleep_ms(sleepValue);
        // Tomar un nuevo valor de delay a través de la comunicación serial, si está disponible
        if ( (sleepValueTemp = GetValueFromTerminal()) != PICO_ERROR_TIMEOUT) {
            sleepValue = sleepValueTemp;
        }
    }

    return 0;
}