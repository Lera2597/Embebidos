#ifndef MYEVENTS_H_
#define MYEVENTS_H_

#include "pico/stdlib.h"

#define deadline_data	100 // 100*10ms=1000ms

#define ID_TEM		0x01
#define ID_DIS		0x02
#define ID_LED		0x03
#define ID_MOT		0x04

typedef enum {IDLE,VALIDITY,RECEIVING,TRASMITING} states_main;
typedef enum {HEADER,MONITOR_CONTROL,VALUE,CHECK_SUM} states_capture_data;



typedef union {
	uint8_t reg;
	struct {
		uint8_t flag0 : 1;
		uint8_t flag1 : 1;
		uint8_t flag2 : 1;
		uint8_t flag3 : 1;
		uint8_t flag4 : 1;
		uint8_t flag5 : 1;
		uint8_t flag6 : 1;
		uint8_t flag7 : 1;
	}flags;
}_events_str;

extern volatile _events_str _events;
#define PENDING_EVENTS	_events.reg
#define EV_TIMER		_events.flags.flag0
#define EV_ADC			_events.flags.flag1
#define EV_UART			_events.flags.flag2


void eventsController(void);
void test(void);
#endif
