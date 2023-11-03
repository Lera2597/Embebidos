#include <stdio.h>
#include "pico/stdlib.h"

#include "timer.h"
#include "gpio.h"
#include "general.h"
#include "events.h"

/*
 * This program increases a counter every time a falling edge GPIO interrupt occurs on pin GP0
 */ 

int main() {
    // STDIO: USB-Uart Initialization for I/O
    stdio_init_all();

    // Welcome Message after USB connection is established
    while (!stdio_usb_connected());
    printf("\nCounter increased by falling edge GPIO interrupts\n");
    printf("Connect a push button that generates a GND (logical 0) when pressed to GP0 (Pull Up already enabled)\n\n");
 
    // Timer Initialization (Debounce)
    if (!timerInitialization(TIMER_PERIOD_MS)) {
        printf("Timer initialization error.\n");
        SYSTEM_HALT();
    }
    
    // GPIO Initialization
    gpioInitialization();

    // Wait for events and process them
    while (true) {
        eventsController();
    }
 
    return 0;
}