#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
//#include "hardware/pwm.h"

#include "events.h"
#include "general.h"
#include "timer.h"
#include "temperature.h"
#include "pwm.h"
#include "hc_sr04.h"
#include "uart.h"

volatile _events_str _events;
volatile uint32_t con_time_data= 0;

states_main currentState_main = IDLE;
states_capture_data  currentState_data= HEADER;
states_capture_data  BAN = IDLE;

uint8_t id_process=0;
uint8_t value_process=0;
uint8_t check_sum_received =0;
uint8_t  trama[5]= {0};
bool undefine_process = false;
uint8_t check_sum =0;
uint16_t duty=0;

void send_trama(uint8_t value);
// Events controller
void eventsController(void) {

	if (!PENDING_EVENTS) {
		WAITFORINT();
	}

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
		if(++con_adc == DEADLINE_ADC){
			adc_fifo_drain();
			adc_run(true);
			con_adc=0;
		}
		
	}
	if(EV_UART){
		EV_UART = 0;
		con_time_data= 0;
		currentState_main = IDLE;
		//printf("dato byte: %x\n",data_phone);
		//CODIGO PARA HACER EL CAMBIO DE ESTADOS
		//SOLO SE CAMBIA LOS ESTADOS CUANDO SE ENVIA LOS COMANDOS DESDE EL CELULAR
		switch (currentState_data) {
		case HEADER:
			if(data_phone == '$'){
				currentState_data = MONITOR_CONTROL;
				trama[0]=data_phone;
			}
		break;
		case MONITOR_CONTROL:		
			if((data_phone & 0x80)==0x00){//verificamos el bit mas significante
				BAN = TRASMITING;//monitoreo
			}
			else {
				BAN = RECEIVING;//control
			}
			if((data_phone & 0x7f)==ID_TEM){//Temperatura
				id_process=ID_TEM;
			}
			else if((data_phone & 0x7f)==ID_DIS){//Distancia
				id_process=ID_DIS;
			}
			else if((data_phone & 0x7f)==ID_LED){//led
				id_process=ID_LED;
			}
			else if((data_phone & 0x7f)==ID_MOT){//motor
				id_process=ID_MOT;
			}
			else{
				//En este caso enviar un mensaje de error
				// Id del proceso no esta disponible
				undefine_process=true;
			}
			trama[1]=(uint8_t) data_phone;
			currentState_data = VALUE;
		break;
		case VALUE:
			if (BAN == RECEIVING){
				if(data_phone>100)value_process=100;
				else value_process=data_phone;
			}
			else{
				value_process=0;
			}
			currentState_data = CHECK_SUM;
			trama[2]=data_phone;
		break;
		case CHECK_SUM:
			check_sum_received = data_phone;
			currentState_data = HEADER;
			currentState_main = VALIDITY;
		break;
		default:
		break;
    	}
	}
	switch (currentState_main) {
        case IDLE:
        break;
        case VALIDITY:
			if(undefine_process){

				//enviamos el msj de error al celular 
				//prodria se una trama con ceros 
				printf("Id del proceso no esta disponible\n");
				currentState_main = IDLE;
				undefine_process=true;
			}
			else{
				check_sum = (trama[0] + trama[1] + trama[2]) % 256;
				if(check_sum == check_sum_received){
					currentState_main = BAN;
				}
				else{
					printf("Error en la Trama de datos\n");
					currentState_main = IDLE;
				}
			}
        break;		
		case RECEIVING:
		//MODIFICAMOS EL VALOR DE PWM PARA MOTOR O LED UNA SOLA VEZ 
		//HASTA QUE NUEVAMENTE SE ENVIE LA ORDEN DESDE EL CELULAR 
			
			duty= ((float)value_process/100.0f)*PWM_WRAP_VALUE;
			printf("Duty: %d.\n",value_process);

			if(id_process == ID_LED){
				pwm_change_level(0,duty);						
			}
			else if (id_process == ID_MOT) {
				pwm_change_level(1, duty);
			}
			/*for(int i=0;i<4;i++){
				printf("trama [%d]: %x\n",i,trama[i]);
			}*/
			send_trama( value_process );
			currentState_main = IDLE;

		break;
		case TRASMITING:
		//ENVIAMOS DATOS DE TEMPERATURA Y DISTANCIA AL CELULAR CONSTANTEMENTE
			if(id_process == ID_TEM ){
				printf("Temperatura: %d.\n", temperature_get() );
				send_trama(temperature_get() );						
			}
			else if(id_process == ID_DIS ) {
				printf("Distancia: %d.\n", sr04_get_distance());
				send_trama(sr04_get_distance());
			}
			currentState_main = IDLE;//por el momento para que imprima una vez		
		break;
		default:
		break;
    }	
}
void send_trama(uint8_t value){
	trama[2]=value;
	check_sum = (trama[0] + trama[1] + trama[2]) % 256;
	trama[3] = check_sum;
	if (uart_is_writable(UART_ID)){
		uart_puts(UART_ID,trama);
		//implementarlo con putc
		//printf("Trama enviada\n");
	}



}


