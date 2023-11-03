#ifndef _ADC_H
#define _ADC_H

#define ADC_PIN             26
#define ADC_CHANNEL         0
#define ADC_CONVERSION(X)   ((float)(X) * 3.3f / (1 << 12))
#define MAX_ADC_VALUE       (1 << 12)
#define ADC_FIFO_SAMPLES    2

extern volatile uint16_t    adc_samples[ADC_FIFO_SAMPLES];

void  adc_myinit(void);
void adc_isr(void);

#endif