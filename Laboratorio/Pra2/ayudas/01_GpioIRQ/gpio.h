#ifndef _GPIO_H
#define _GPIO_H

#define INPUT_PIN   0               // GP0

void gpioInitialization(void);
bool gpioCheckIfPinLevelIsLow(void);

#endif