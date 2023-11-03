#ifndef _UART_H
#define _UART_H

#define UART_ID uart1
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define UART_IRQ UART1_IRQ

volatile extern uint8_t data_phone;
extern volatile uint8_t contUart;

void init_uart(void);
void interrupt_rx(void);

#endif