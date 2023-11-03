#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pwm.h"

uint pwm_slice_num_0;
uint pwm_chan_1;
uint pwm_chan_0;

bool pwm_myinit() {
    // Establecer los pines de GPIO como PWM
    gpio_set_function(PWM_GPIO_LED, GPIO_FUNC_PWM);
    gpio_set_function(PWM_GPIO_MOTOR, GPIO_FUNC_PWM);

    // Determinar a cuál SLICE y CANAL corresponden ambos pines de GPIO
    pwm_slice_num_0 = pwm_gpio_to_slice_num(PWM_GPIO_LED);
    pwm_chan_0 = pwm_gpio_to_channel(PWM_GPIO_LED);
    uint pwm_slice_num_1 = pwm_gpio_to_slice_num(PWM_GPIO_MOTOR);
    pwm_chan_1 = pwm_gpio_to_channel(PWM_GPIO_MOTOR);

    // Si los SLICES son diferentes, se debe cambiar los pines GPIO
    if (pwm_slice_num_0 != pwm_slice_num_1)
        return false;

    // Establecer la frecuencia y dureza del PWM
    pwm_set_wrap(pwm_slice_num_0, PWM_WRAP_VALUE);
    pwm_set_chan_level(pwm_slice_num_0, pwm_chan_0, PWM_LEVEL_VALUE);
    pwm_set_chan_level(pwm_slice_num_0, pwm_chan_1, PWM_LEVEL_VALUE);

    // Habilitar el SLICE de PWM correspondiente
    pwm_set_enabled(pwm_slice_num_0, true);    
}

/* Función para cambiar la dureza (Duty) de un determinado canal en el SLICE seleccionado */
void pwm_change_level(uint chan, uint16_t value) {
    pwm_set_chan_level(pwm_slice_num_0, chan, value);
}

