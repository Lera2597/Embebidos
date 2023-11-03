#include "pico/stdlib.h"

const uint led_pin = 25;

#define DELAY   500

int main() {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while (1) {
        gpio_put(led_pin, true);
        sleep_ms(DELAY);
        gpio_put(led_pin, false);
        sleep_ms(DELAY);
        //__asm volatile("wfi");
    }

    return 0;
}