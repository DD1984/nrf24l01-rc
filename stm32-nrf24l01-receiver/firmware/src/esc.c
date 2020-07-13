#include "platform.h"
#include "esc.h"

void pwm_gpio_cfg(pwm_mode_t mode) 
{
    //PA0, PA1 reset mode
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0 | GPIO_CRL_CNF1 | GPIO_CRL_MODE1);

    switch (mode) {
        case STOP:
            //PA0, PA1 - gpio 0 level
            GPIOA->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0; //10mhz out push-pull
            GPIOA->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR1;
        break;
        case FORWARD:
            //PA0 - pwm, PA1 - gpio 0 level
            GPIOA->CRL |= GPIO_CRL_MODE0_0 | GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0;
            GPIOA->BSRR = GPIO_BSRR_BR1;
        break;
        case BACKWARD:
            //PA0 - gpio 0 level, PA1 - pwm
            GPIOA->CRL |= GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_0;
            GPIOA->BSRR = GPIO_BSRR_BR0;
        break;
        case SOUND:
            //PA0, PA1 - pwm
            GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_0 | GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_0;
        break;
    }
}

void pwm_stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC2E);
    TIM2->CNT = 0;

    pwm_gpio_cfg(STOP);
}

void pwm_timer_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    pwm_stop();
}

void pwm_run(pwm_mode_t mode, uint16_t level)
{
    if (mode != FORWARD && mode != BACKWARD)
        return;

    if (level < DEAD_GAP)
        pwm_stop();
    
    if (level >= (1 << PWM_RES))
        return;

    pwm_stop();

    TIM2->PSC = SystemCoreClock / PWM_FREQ / (1 << PWM_RES);
    TIM2->ARR = (1 << PWM_RES) - 1;
    TIM2->CCR1 = TIM2->CCR2 = level;
    
    TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM2->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE
                  | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;

    if (mode == FORWARD)
        TIM2->CCER = TIM_CCER_CC1E;
    else if (mode == BACKWARD)
        TIM2->CCER = TIM_CCER_CC2E;

    pwm_gpio_cfg(mode);

    TIM2->CR1 |= TIM_CR1_CEN;
}

void pwm_beep(uint32_t freq)
{
    pwm_stop();

    if (freq == 0)
        return;
    
    freq /= 2;
    
    TIM2->PSC = (SystemCoreClock / 1000000 - 1); /* Ftim = 1 Mhz */
    TIM2->ARR = (1000000 / freq - 1);
    TIM2->CCR1 = TIM2->CCR2 = TIM2->ARR / 2;

    TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM2->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE
                | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2PE;

    TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;

    pwm_gpio_cfg(SOUND);

    TIM2->CR1 |= TIM_CR1_CEN;
}
