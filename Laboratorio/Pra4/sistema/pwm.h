#ifndef _PWM_H
#define _PWM_H

#define PWM_GPIO_LED    18
#define PWM_GPIO_MOTOR  19

#define PWM_WRAP_VALUE      1250 //10k Hz
#define PWM_LEVEL_VALUE     0
#define PWM_ADC_MIN_LEVEL   50

bool pwm_myinit(void);
void pwm_change_level(uint, uint16_t);

#endif