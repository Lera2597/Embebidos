#include <stdio.h>
#include "pico/stdlib.h"
//#include "hardware/adc.h"
//#include "hardware/pwm.h"

#include "events.h"
#include "general.h"
////#include "timer.h"
//#include "adc.h"
//#include "pwm.h"
//#include "hc_sr04.h"
#include "uart.h"

volatile _events_str _events;
volatile uint32_t con_time_data= 0;

states_main currentState_main = IDLE;
states_capture_data  currentState_data= HEADER;
states_capture_data  BAN = IDLE;

uint8_t id_process=0;
uint8_t value_process=0;
uint8_t check_sum_received =0;
uint8_t  trama[3];
bool undefine_process = false;
uint8_t check_sum =0;

//variables test

// Events controller
void eventsController(void) {

	if (!PENDING_EVENTS) {
		WAITFORINT();
	}
	/*
	if (EV_TIMER) {
		EV_TIMER = false;
		if(con_trigger == DL_TRIGGER){
			sr04_capture_echo(false);
			//printf("Desable\n");
			sr04_set_trigger(true);
		}
		else if (con_trigger == DL_TRIGGER + 1){
			con_trigger=0;
			sr04_set_trigger(false);
			sr04_capture_echo(true);
			//printf("Enable\n");
		}
		con_trigger++;

		if(++con_time_data == deadline_data){//Sino se recive un byte por un timepo, se retorna al estdo inicial de captura
			currentState_data= HEADER;
			con_time_data= 0;
		}

		
	}*/
	/*
	c = getchar_timeout_us(0); 
    if (c != PICO_ERROR_TIMEOUT) {
        printf("Ingrese un valor");
        while ((c = getchar()) != ENTER) {
			data_phone = c;
			printf("data: %x\n",data_phone);
			test();
        }
	}*/
	if(EV_UART){
		EV_UART = 0;
		printf("evento Dato: %x\n",data_phone);
	}
	
}