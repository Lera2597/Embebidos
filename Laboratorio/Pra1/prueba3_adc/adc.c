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
   //adc_fifo_setup(true,true,1,true,false);
}

//verificamos si la conversión esta lista 
bool adc_ready(){
     if((ADC_CS & (1<<8) )== (1<<8)){
         printf("Ready\n");
         return true;
     }
     else{
         return false;
         printf("Not Ready\n");
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
void adc_fifo_init(){
     //init fifo con capacidad de 4 valores
     ADC_FCS = 0x04000001;
}
bool adc_fifo_empty(){
    if ((ADC_FCS & (1<<8)) == (1<<8)){
        return true;
    }
    else{
        return false;
    }
}
 unsigned int adc_capture_data(){
     return adc_fifo_get();
}

