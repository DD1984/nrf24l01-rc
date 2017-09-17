#pragma once

#include <stdint.h>
#include "stm32f0xx.h"


#define __SYSTICK_IN_MS 10

#define NUMBER_OF_CHANNELS 3
#define SERVO_PULSE_CENTER 1500
#define INITIAL_ENDPOINT_DELTA 200

#define CH1_FREQUENCY           200 /* (50 - 400) Hz */
#define CH2_CH3_FREQUENCY       50 /* (50 - 400) Hz */
/**
 * PA0     - NRF_CSN
 * PA1     - NRF_CE
 * PA2     - NRF_IRQ
 * PA3     - LED
 * PA4     - BIND
 * PA5     - NRF_SCK
 * PA6     - NRF_MISO
 * PA7     - NRF_MOSI
 * PA9     - CH3 - TIM1_CH2
 * PA10    - CH2 - TIM1_CH3
 * PB1     - CH1 - TIM14_CH1
 */


#define GPIO_NRF_CSN_LO()   do{ GPIOA->BSRR = GPIO_BSRR_BR_0; }while(0) 
#define GPIO_NRF_CSN_HI()   do{ GPIOA->BSRR = GPIO_BSRR_BS_0; }while(0) 

#define GPIO_NRF_CE_LO()    do{ GPIOA->BSRR = GPIO_BSRR_BR_1; }while(0) 
#define GPIO_NRF_CE_HI()    do{ GPIOA->BSRR = GPIO_BSRR_BS_1; }while(0) 

#define GPIO_LED_ON()       do{ GPIOA->BSRR = GPIO_BSRR_BS_3; }while(0) 
#define GPIO_LED_OFF()      do{ GPIOA->BSRR = GPIO_BSRR_BR_3; }while(0) 
#define GPIO_LED_TOGGLE()   do{ GPIOA->ODR ^= GPIO_ODR_3; }while(0) 

#define GPIO_BIND           ((GPIOA->IDR & GPIO_IDR_4) != GPIO_IDR_4)

void delay_us(uint32_t microseconds);
