#ifndef __ESC_H__
#define __ESC_H__

#include <stdint.h>

#define PWM_FREQ 1000
#define PWM_RES 7 //bit
#define DEAD_GAP 10

typedef enum {
    STOP,
    FORWARD,
    BACKWARD,
    SOUND,
} pwm_mode_t;

void pwm_gpio_cfg(pwm_mode_t mode) ;
void pwm_stop(void);
void pwm_timer_init(void);
void pwm_run(pwm_mode_t mode, uint16_t level);
void pwm_beep(uint32_t freq);

#endif
