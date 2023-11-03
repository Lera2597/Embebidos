#include <stdio.h>
//#include "hardware/adc.h"
//#include "hardware/pwm.h"

#include "events.h"
#include "general.h"
#include "timer.h"
//#include "adc.h"
//#include "pwm.h"
#include "hc_sr04.h"

volatile _events_str _events;

// Events controller
void eventsController(void) {
	while (true) {
		if (!PENDING_EVENTS) {
			WAITFORINT();
		}

		if (EV_TIMER) {
			EV_TIMER = false;
			if(con_trigger == DL_TRIGGER){
				sr04_capture_echo(false);
				//printf("Desable\n");
				sr04_set_trig(true);
			}
			else if (con_trigger == DL_TRIGGER + 1){
				con_trigger=0;
				sr04_set_trig(false);
				sr04_capture_echo(true);
				//printf("Enable\n");
			}
			con_trigger++;
			
		}

	}
}
