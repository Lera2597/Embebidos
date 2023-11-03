#ifndef _ADC_H
#define _ADC_H


#define BASE_ADC 0x4004c000 
#define ADC_INTS (*((volatile unsigned int *)(BASE_ADC + 0x20)))
extern uint16_t data ;
extern uint8_t canal ;

bool adc_interrupt();

#endif
