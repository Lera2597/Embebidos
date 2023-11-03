#include <stdio.h>
#include "pico/stdlib.h"
#include "getshowvalue.h"

uint32_t umbralTemp, umbralVolt;

uint32_t GetValueFromTerminal(void) {
    uint32_t acum = 0;
    int c;
    c = getchar_timeout_us(0);
    if (c != PICO_ERROR_TIMEOUT) {
        printf("Ingrese un valor de sleep entre %d y %d: ", MIN_DELAY_VALUE, MAX_DELAY_VALUE);
        while ((c = getchar()) != ENTER) {
            if (c >= '0' && c <= '9') {
                acum = acum * 10 + (c & 0x0F);
            }
        }
        if (acum < MIN_DELAY_VALUE || acum > MAX_DELAY_VALUE) {
            printf("Valor erroneo: %d\n", acum);
            acum = PICO_ERROR_TIMEOUT;
        } else {
            printf("Valor aceptado: %d\n", acum);
        }
    }
    else {
        acum = PICO_ERROR_TIMEOUT;
    }
    return acum;
}

uint32_t GetValueMenu(void){
    uint32_t option = 0;
    int c = ENTER;
    c = getchar_timeout_us(0);
    if(c != ENTER && (c == '1' || c == '2')){
        option = (c&0x0F);
    } else {
        option = PICO_ERROR_TIMEOUT;
    }
    return option;
}

void ShowMenuInTerminal(void){
    printf("\n\t\t\tSensado y Control\n\n");
    printf("1.Ver valor variables.\n");
    printf("2.Cambiar umbrales.\n Opcion:");
}

void ShowVariables(float variable1, uint32_t variable2){
    printf("\nTemperatura: %f\nVoltaje: %d\n",variable1,variable2);
}

void ChangeVariables(void){
    uint32_t umbralT=0, umbralV=0;
    int c = getchar_timeout_us(0);
    printf("Umbral Temperatura (%d-%d): ",MIN_TEMPERATURA_VALUE,MAX_TEMPERATURA_VALUE);
    while ((c = getchar_timeout_us(0)) != ENTER) {
        if (c >= '0' && c <= '9') {
            umbralT = umbralT * 10 + (c & 0x0F);
        }
    }
    if (umbralT < MIN_TEMPERATURA_VALUE || umbralT > MAX_TEMPERATURA_VALUE) {
            printf("Valor erroneo: %d\n", umbralT);
    } else {
        printf("Valor aceptado: %d\n", umbralT);
        umbralTemp = umbralT;
    }
    printf("Umbral Voltaje (%d-%d): ",MIN_VOLTAGE_VALUE,MAX_VOLTAGE_VALUE);
    while ((c = getchar_timeout_us(0)) != ENTER) {
        if (c >= '0' && c <= '9') {
            umbralV = umbralV * 10 + (c & 0x0F);
        }
    }
    if (umbralV < MIN_VOLTAGE_VALUE || umbralV > MAX_VOLTAGE_VALUE) {
            printf("Valor erroneo: %d\n", umbralV);
    } else {
        printf("Valor aceptado: %d\n", umbralV);
        umbralVolt = umbralV;
    }

}

void ErrorMenu(void){
    printf("\nIngrese 1 o 2");
}