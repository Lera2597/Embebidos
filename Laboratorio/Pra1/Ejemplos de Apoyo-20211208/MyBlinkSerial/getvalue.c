#include <stdio.h>
#include "pico/stdlib.h"

#include "getvalue.h"

// Si hay un caracter enviado por serial, solicitar al usuario el valor del nuevo delay
uint32_t GetValueFromTerminal(void) {
    uint32_t acum = 0;
    int c;

    c = getchar_timeout_us(0); 
    if (c != PICO_ERROR_TIMEOUT) {
        printf("Ingrese un valor entre %d y %d.\n: ", MIN_SLEEP_VALUE, MAX_SLEEP_VALUE);
        while ((c = getchar()) != ENTER) {
            printf("caracarter ingresaod: %d\n",c);
            if (c >= '0' && c <= '9') {
                acum = acum*10 + (c & 0x0F); // Convertir ASCII a INT y acumular
            }
        }

        // Verificar que el valor esté en rango
        if (acum < MIN_SLEEP_VALUE || acum > MAX_SLEEP_VALUE) {
            printf("Valor ingresado ignorado: %d\n", acum);
            acum = PICO_ERROR_TIMEOUT;       // Para indicar que el valor fue erróneo
        }
        else {
            printf("Valor ingresado aceptado: %d\n", acum);
        }
    }
    else {
        // Indicar que no se ha presionado tecla
        acum = PICO_ERROR_TIMEOUT;
        printf("PICO_ERROR_TIMEOUT");
    }

    return (acum);
}