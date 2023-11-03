#include <stdio.h>
#include "hardware/adc.h"

#include "events.h"
#include "general.h"
#include "adc.h"

volatile _events_str _events;

// Events controller
void eventsController(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;

			//printf("Iniciando muestreo con ADC (TIMER). Timestamp: %0.1f seg.\n", (float)time_us_32() / 1000000);
			adc_fifo_drain();
			adc_run(true);
		}

		if (EV_ADC) {
			EV_ADC = false;
			uint16_t lastReadValue;

			for (int i=0; i<ADC_FIFO_SAMPLES; i++) {
				float vol;
				float temp;
				lastReadValue = adc_samples[i];
				//value = ADC_CONVERSION(adc_samples[i]);
				vol = ADC_CONVERSION(adc_samples[i]);
				temp = CONVERSION_Temp(vol);
				printf("ADC: %d Voltaje: %f Temperatura Actual : %f.\n",adc_samples[i], vol ,temp);
				//printf("Valor muestreado no. %d: %0.3f (%d). Timestamp: %0.1f seg.\n", i+1, value, lastReadValue, (float)time_us_32() / 1000000);
			}
			/*
			// Cambiar canales
			if (lastReadValue < PWM_ADC_MIN_LEVEL)
				lastReadValue = 0;
			uint16_t level_0 = (uint16_t)((uint32_t)lastReadValue * PWM_WRAP_VALUE / MAX_ADC_VALUE);
			uint16_t level_1 = (uint16_t)((uint32_t)(MAX_ADC_VALUE - lastReadValue) * PWM_WRAP_VALUE / MAX_ADC_VALUE);
			pwm_change_level(PWM_GPIO_LED, level_0);
			pwm_change_level(PWM_GPIO_MOTOR, level_1);*/
		}
	}
}
