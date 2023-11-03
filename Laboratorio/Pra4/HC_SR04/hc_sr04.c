#include <stdio.h>
//#include "pico/stdlib.h"

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hc_sr04.h"

volatile uint32_t con_trigger=0;
volatile float distance=0;
volatile float overflow=0;
volatile uint8_t code;

uint32_t width_echo=0;
uint slice_num;
uint data1=0;
uint data2=0;
float time=0;
float   part_dec=0.0;


void pwm_callback_capture(){
    printf("overflow\n");
    overflow++;
    pwm_clear_irq(slice_num);
}
void sr04_init(){
    gpio_init(PIN_TRIGGER);
    gpio_set_dir(PIN_TRIGGER, GPIO_OUT);

    //***********inicializamos el pwm en modo captura con el slice elegido ****************
        assert(pwm_gpio_to_channel(PIN_ECHO) == PWM_CHAN_B);
    slice_num = pwm_gpio_to_slice_num(PIN_ECHO);

    // Mask our slice's IRQ output into the PWM block's single interrupt line,
    // and register our interrupt handler
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_callback_capture);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Count once for every CLK_DIV cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, CLK_DIV);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(PIN_ECHO, GPIO_FUNC_PWM); 

}
void sr04_set_trig(bool trigger){

    if(trigger){
        gpio_put(PIN_TRIGGER, true);
    }
    else {
        gpio_put(PIN_TRIGGER, false); 
    }   
}

void sr04_capture_echo(bool option){
    if(option){
        pwm_set_enabled(slice_num, true);
        data1=pwm_get_counter(slice_num);
    }
    else {
        data2 = pwm_get_counter(slice_num);
        width_echo = overflow*65535 + data2-data1;
        time = (float)width_echo*(CLK_DIV/(float)clock_get_hz(clk_sys));
        distance = time*34000.0f / 2.0f;
        //printf("Distancia: %f [cm]\n",distance);

        code=(int)distance;// obtenemos la parte entera
        part_dec= distance - code;// obtenemos la parte decimal
        if(part_dec >=0.8){
            part_dec=0;
            code++;
        }
        else if (part_dec < 0.8 && part_dec >=0.3 ) part_dec=1;//la parte decimal se apromia a 0.5
        else part_dec=0;

        code = (code<<1) | (int)part_dec;
        printf("Distancia: %f [cm] code: %x.\n",distance,code);
        pwm_set_enabled(slice_num, false);//apagamos la captura
        overflow=0;
    }
}
