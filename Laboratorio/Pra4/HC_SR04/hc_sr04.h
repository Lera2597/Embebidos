#ifndef _HC_SR04_H
#define _HC_SR04_H

#define PIN_TRIGGER    0
#define PIN_ECHO       1
#define DL_TRIGGER     3 // 3* 10ms= 30ms
#define CLK_DIV        100

volatile extern uint8_t codice;
volatile extern float distance;
volatile extern float overflow;
volatile extern uint32_t con_trigger;

void sr04_init();
void sr04_set_trig(bool trigger);
void sr04_capture_echo(bool option);
#endif