#include <stdio.h>
#include "events.h"
#include "general.h"
#include "gpio.h"

volatile _events_str _events;
volatile uint8_t debounceCounter = 0;
volatile bool    pendingCounting = false;
volatile uint8_t counter = 0;

// Events controller
void eventsController(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = 0;

			if (pendingCounting && --debounceCounter == 0) {
				// Increase counter, desactivate debouncing mechanism and print new counter value
				pendingCounting = false;
				if (gpioCheckIfPinLevelIsLow()) {				// If pin is still LOW, increase counter
					counter++;
					printf("New counter value: %d\n", counter);
				}
			}
		}

		if (EV_GPIO) {
			EV_GPIO = 0;

			debounceCounter = DEBOUNCECOUNT;	// Starts debouncing mechanism
			pendingCounting = true;
		}
	}
}
