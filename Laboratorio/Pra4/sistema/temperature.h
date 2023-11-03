#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#define ADC_PIN             26
#define ADC_CHANNEL         0
#define ADC_CONVERSION(X)   ((float)(X) * 3.3f / (1<<12))
#define CONVERSION_Temp(X)   (float)(X) * 100.0f
#define MAX_ADC_VALUE       (1 << 12)
#define ADC_FIFO_SAMPLES    2
#define DEADLINE_ADC        10

extern volatile uint16_t    adc_samples[ADC_FIFO_SAMPLES];
extern volatile uint32_t    con_adc;
void  temperature_init(void);
void adc_isr(void);
uint8_t temperature_get(void);

#endif