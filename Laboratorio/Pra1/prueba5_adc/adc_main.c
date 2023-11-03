#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/uart.h"

#include "adc.h"
#include "timer.h"

#include "getshowvalue.h"

#define ADC_PIN_TEMP 26
#define ADC_PIN_VOLT 27
#define ADC_NUM 0
#define THRESH  8
#define PINLED0 0
#define PINLED1 1

volatile float data1=0;
volatile float  data2=0;

volatile bool flag = true;
extern uint32_t umbralTemp, umbralVolt;

bool menu = true;
int arreglo[THRESH];
int cont = 0;
bool id0 = false;
bool id1 = false;
void showMenu(void);
void SensarVariables(void);
const float conversion_factor = 3.3f / (1 << 12);
bool estadoLed0 = false;
bool estadoLed1 = false;

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();

    // sleep_ms(5000);
    adc_init();
    adc_gpio_init(ADC_PIN_TEMP);
    adc_gpio_init(ADC_PIN_VOLT);
    //adc_set_round_robin(0x03);
    adc_fifo_setup(true, false, THRESH, false, false);
    adc_irq_set_enabled(true);
    //Inicializar el TIMER (Alarm)
    timer_init(TIMER_PERIOD_MS);
    uart_init(uart0, 115200);
    
    gpio_init(PINLED0);
    gpio_set_dir(PINLED0, GPIO_OUT);
    gpio_init(PINLED1);
    gpio_set_dir(PINLED1, GPIO_OUT);
    uint32_t menuValue;
    sleep_ms(500);
    
    while (true) {
        if (timer_req) {
            timer_req = false;
            if (timer_counter0 == 0) { 
                if(adc_ready()){
                    timer_counter0 = TIME_SAMPLE0;
                    //printf("-----------Nueva muestra canal 0----------\n");
                    adc_init_convert(0);
                    id0 = true;
                    arreglo[cont] = 0;
                    cont++;
                }
            }
            else{
                timer_counter0--;
            }
            if (timer_counter1 == 0) { 
                if(adc_ready()){
                    timer_counter1 = TIME_SAMPLE1;
                    //printf("-----------Nueva muestra canal 1----------\n");
                    adc_init_convert(1);
                    id1=true;
                    arreglo[cont] = 1;
                    cont++;
                }
            }
            else{
                timer_counter1--;
            }

            if(menu){
                showMenu();
            }

            if(data1 > umbralTemp){
                if(--counter_led0 == 0){
                    counter_led0 = PERIODO_LED0;
                    estadoLed0=!estadoLed0;
                    gpio_put(PINLED0, estadoLed0);
                }
            } else {
                gpio_put(PINLED0, 0);
            }
            
            if(data2 > umbralVolt){
                if(--counter_led1 == 0){
                    counter_led1 = PERIODO_LED1;
                    estadoLed1=!estadoLed1;
                    gpio_put(PINLED1, estadoLed1);
                }
            } else {
                gpio_put(PINLED1, 0);
            }


        }

        if(adc_callback()){
            adc_fifo_drain();
            cont = 0;
        }

        if(id0 && id1){
            SensarVariables();
        }
        menuValue = GetValueMenu();
                    
        if(menuValue != PICO_ERROR_TIMEOUT && flag){
        switch (menuValue) {
        case 1:
            flag = false;
            ShowVariables(data1,data2);
            menu = true;
            break;
        case 2:
            ChangeVariables();
            flag = false;
            menu = true;
            break;
        default:
            ErrorMenu();
            menu = true;
            break;
        }
        }
        __asm volatile ("wfi");
    }
    return 0;
}

void showMenu(void){
    menu = false;
    flag = true;
    ShowMenuInTerminal();
}

void SensarVariables(void){
    while(cont!=0){
        if(arreglo[cont] == 0 && id0){
            uint16_t result = adc_fifo_get();
            data1 = result * conversion_factor * 100;
            id0=false;
        } else if(arreglo[cont] == 1 && id1){
            uint16_t result = adc_fifo_get();
            data2 = result * conversion_factor;
            id1=false;
        }
        cont--;
    }   
}