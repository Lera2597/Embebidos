#include "hardware/gpio.h"

#include "gpio.h"
#include "events.h"

// Callback for GPIO INTs
void gpioCallback(uint gpio, uint32_t events) {
    if (gpio == INPUT_PIN)
        EV_GPIO = 1;                            // In case there are several GPIO configured as interrupts
}

void gpioInitialization(void) {
    gpio_init(INPUT_PIN);                       // INPUT_PIN as a GPIO
    gpio_set_pulls(INPUT_PIN, true, false);     // Pull Up: enabled, Pull Down: disabled
    gpio_set_dir(INPUT_PIN, GPIO_IN);           // INPUT_PIN as an input
    // Configure GPIO with Falling Edge Interrupts (High to Low)
    gpio_set_irq_enabled_with_callback(INPUT_PIN, GPIO_IRQ_EDGE_FALL, true, gpioCallback);    
}

bool gpioCheckIfPinLevelIsLow(void) {
    return gpio_get(INPUT_PIN) ? false : true;  // Returns true if pin is still low
}