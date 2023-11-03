#include <stdio.h>
#include "pico/stdlib.h"

#include "adc.h"
#include "hardware/adc.h"
void adc_init_(){
    ADC_CS = 0x00000401;
    /*printf("Inicializacion ADC: %x\n", ADC_CS); 
    printf("Inicializacion ADC: %u\n", ADC_CS); 
    printf("Inicializacion ADC: %p\n", ADC_CS); 
    */
}

//verificamos si la conversión esta lista 
 bool adc_ready(){
     if(ADC_CS & (1<<8) == (1<<8)){
         printf("Ready\n");
         return true;
     }
     else{
         return false;
         printf("Not Ready\n");
     }
 }
 void adc_init_convert(uint32_t canal){
     if(canal==0){
         ADC_CS = 0x00000405; // inicializamos la conversión en canal 0
     }
     else{
         ADC_CS = 0x00001405; // inicializamos la conversión en canal 1   
     }
 }
 void adc_fifo_init(){
     //init fifo con capacidad de 4 valores
     ADC_FCS = 0x04000001;
 }
 unsigned int adc_capture_data(){
     return ADC_RESULT;
 }

