#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/adc.h"
#include "adc.h"

uint16_t data=0 ;
uint8_t canal=0;

bool adc_interrupt(){
    if(ADC_INTS & (1<<0) == (1<<0)){
        canal = adc_get_selected_input();
        data = adc_fifo_get();
        //adc_fifo_drain();
        
        return true;
    }
    else{
        printf("vacio\n");
        return false;
    }

}

