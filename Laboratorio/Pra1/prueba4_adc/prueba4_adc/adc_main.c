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

volatile float data1=0;
volatile uint32_t data2=0;
volatile bool flag = true;
extern uint32_t umbralTemp, umbralVolt;
bool menu = true;

bool menu1 = true;
bool menu2 = true;

void showMenu(void);

int main() {
    // STDIO: inicialización de USB-UART para entrada/salida
    stdio_init_all();
    // adc_init();

    // Pausa para esperar a que la terminal serial esté lista
    // printf("\nGenerador de interrupciones periodicas!\n\n");

    // Make sure GPIO is high-impedance, no pullups etc
    // adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    // adc_select_input(0);
 
    // Inicializar el TIMER (Alarm)
    // timer_init(TIMER_PERIOD_MS);

    // sleep_ms(5000);
    adc_init();
    adc_gpio_init(ADC_PIN_TEMP);
    adc_gpio_init(ADC_PIN_VOLT);
    adc_fifo_setup(true, false, THRESH, false, false);
    adc_irq_set_enabled(true);
    //Inicializar el TIMER (Alarm)
    timer_init(TIMER_PERIOD_MS);
    uart_init(uart0, 115200);
    //Inicializar la fifo
    //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
    // Wait for alarm callback to set timer_fired
    uint32_t menuValue;
    bool id = false;
    
    while (true) {
        if (timer_req) {
            timer_req = false;
            if (timer_counter0 == 0) { //podemos ponerle menor que 0
                if(adc_ready()){
                    timer_counter0 = TIME_SAMPLE0;
                    //printf("-----------Nueva muestra canal 0----------\n");
                    adc_init_convert(0);
                    id= false;
                }
            }
            else{
                timer_counter0--;
            }
            if (timer_counter1 == 0) { //podemos ponerle menor que 0
                if(adc_ready()){
                    timer_counter1 = TIME_SAMPLE1;
                    //printf("-----------Nueva muestra canal 1----------\n");
                    adc_init_convert(1);
                    id=true;
                }
            }
            else{
                timer_counter1--;
            }

            if(menu){
                showMenu();
            }
            
        }

        if(adc_ready() & !adc_fifo_is_empty() & !id){
            const float conversion_factor = 3.3f / (1 << 12);
            uint16_t result = adc_fifo_get();
            //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
            data1 = result * conversion_factor * 100;
        }
        if(adc_ready() & !adc_fifo_is_empty() & id){
                data2 = adc_fifo_get()/1000;
        }

        menuValue = GetValueMenu();
        //printf("Muestra: %d, Canal: %d\n",data,id );
        //sleep_ms(100);
        // Entrar en modo de bajo consumo
                    
        if(menuValue != PICO_ERROR_TIMEOUT && flag){
        switch (menuValue) {
        case 1:
            flag = false;
            ShowVariables(data1,data2);
            menu = true;
            menu1 = true;
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

void showMenu(){
    menu = false;
    flag = true;
    ShowMenuInTerminal();
}