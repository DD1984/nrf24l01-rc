#pragma once

#include <stdint.h>

#ifdef STM32F1

#include "stm32f1xx.h"
#include "stm32f100xb.h"


    /**
      * @brief Internal Low Speed oscillator (LSI) value.
      */
    #if !defined  (LSI_VALUE)
     #define LSI_VALUE               40000U    /*!< LSI Typical Value in Hz */
    #endif /* LSI_VALUE */                     /*!< Value of the Internal Low Speed oscillator in Hz
                                                    The real value may vary depending on the variations
                                                    in voltage and temperature. */

    #define FLASH_FKEY1 FLASH_KEY1
    #define FLASH_FKEY2 FLASH_KEY2

#else

#include "stm32f0xx.h"

#endif


#define __SYSTICK_IN_MS 10

#define NUMBER_OF_CHANNELS 3
#define SERVO_PULSE_CENTER 1500
#define INITIAL_ENDPOINT_DELTA 200

#define CH1_FREQUENCY           200 /* (50 - 400) Hz */
#define CH2_CH3_FREQUENCY       50 /* (50 - 400) Hz */

#ifdef STM32F1

/**
 * PB14    - LED
 * PB12    - BIND
 *
 * PA4     - NRF_CSN
 * PA3     - NRF_CE
 * PB0     - NRF_IRQ
 * PA5     - NRF_SCK
 * PA6     - NRF_MISO
 * PA7     - NRF_MOSI
 *
 * PA11    - CH1 - TIM1_CH4
 * PA10    - CH2 - TIM1_CH3
 * PA9     - CH3 - TIM1_CH2
 * PA8     - CH4 - TIM1_CH1 - for future use
 */
#define GPIO_NRF_CSN_LO()   do{ GPIOA->BSRR = GPIO_BSRR_BR4; }while(0)
#define GPIO_NRF_CSN_HI()   do{ GPIOA->BSRR = GPIO_BSRR_BS4; }while(0)

#define GPIO_NRF_CE_LO()    do{ GPIOA->BSRR = GPIO_BSRR_BR3; }while(0)
#define GPIO_NRF_CE_HI()    do{ GPIOA->BSRR = GPIO_BSRR_BS3; }while(0)

#define GPIO_LED_ON()       do{ GPIOB->BSRR = GPIO_BSRR_BS14; }while(0)
#define GPIO_LED_OFF()      do{ GPIOB->BSRR = GPIO_BSRR_BR14; }while(0)
#define GPIO_LED_TOGGLE()   do{ GPIOB->ODR ^= GPIO_ODR_ODR14; }while(0)

#define GPIO_BIND           ((GPIOB->IDR & GPIO_IDR_IDR12) != GPIO_IDR_IDR12)

#else

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

#endif

void delay_us(uint32_t microseconds);
