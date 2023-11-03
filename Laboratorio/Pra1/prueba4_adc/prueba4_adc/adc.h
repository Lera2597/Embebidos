#ifndef _ADC_H
#define _ADC_H

#define BASE_ADC 0x4004c000 
//extern unsigned int  * ADC_CS
#define ADC_CS (*((volatile unsigned int *)(BASE_ADC + 0x00)))
#define ADC_RESULT (*((volatile unsigned int *)(BASE_ADC + 0x04)))
#define ADC_FCS (*((volatile unsigned int *)(BASE_ADC + 0x08)))
bool adc_ready();
void adc_init_convert(uint32_t);
#endif
