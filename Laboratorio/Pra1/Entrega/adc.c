#include <stdio.h>
#include "pico/stdlib.h"

#include "adc.h"
#include "hardware/adc.h"

bool adc_callback(){
    if(ADC_INTR & (1<<0)){
        //printf("CALLBACK\n");
        return true;
    }
    return false;
}

//verificamos si la conversión esta lista 
bool adc_ready(){
     if((ADC_CS & (1<<8) )== (1<<8)){
        // printf("Ready\n");
         return true;
     }
     else{
         return false;
        // printf("Not Ready\n");
     }
 }
void adc_init_convert(uint32_t canal){

     //ADC_CS = 0x00000405; // inicializamos la conversión en canal 0
     if(canal==0){
         ADC_CS = 0x00000405; // inicializamos la conversión en canal 0
     }
     else if (canal==1){
         ADC_CS = 0x00001405; // inicializamos la conversión en canal 1   
     }
}