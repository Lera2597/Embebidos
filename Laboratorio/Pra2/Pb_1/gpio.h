#ifndef _GPIO_H
#define _GPIO_H

extern volatile uint8_t gpio_req;

void gpio_init_outputs(uint outputs[]);
void gpio_init_inputs(uint inputs[]);


#endif