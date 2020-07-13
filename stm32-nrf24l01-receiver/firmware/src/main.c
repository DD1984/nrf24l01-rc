/******************************************************************************

    Application entry point.

    Contains the main loop and the hardware initialization.

******************************************************************************/
#include <stdio.h>
#include <stdbool.h>

#include "platform.h"

#include "spi.h"
#include "rc_receiver.h"

#ifdef ESC
#include "esc.h"
#include "tune.h"
#include "adc.h"
#endif


#define IWDG_REFRESH        0x0000AAAA
#define IWDG_START          0x0000CCCC
#define IWDG_WRITE_ACCESS   0x00005555


// Global flag that is true for one mainloop every __SYSTICK_IN_MS
bool systick;
static volatile uint32_t systick_count;

// ****************************************************************************
static void service_systick(void)
{
    if (!systick_count) {
        systick = false;
        return;
    }

    systick = true;

    // Disable the SysTick interrupt. Use memory barriers to ensure that no
    // interrupt is pending in the pipeline.
    // More info:
    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dai0321a/BIHHFHJD.html
    SysTick->CTRL &= ~(1 << 1);
    __DSB();
    __ISB();
    --systick_count;
    SysTick->CTRL |= (1 << 1);      // Re-enable the system tick interrupt
}

// ****************************************************************************
#ifdef STM32F1
void EXTI0_IRQHandler (void)
#else
void EXTI2_3_IRQHandler (void)
#endif
{
    uint32_t status = EXTI->PR;
    uint32_t pending = 0;

#ifdef STM32F1
    if (status & EXTI_PR_PR0)
    {
        pending |= EXTI_PR_PR0;
        rf_interrupt_handler();
    }
#else
    if (status & EXTI_PR_PR2)
    {
        pending |= EXTI_PR_PR2;
        rf_interrupt_handler();
        //GPIO_LED_ON();
    }
#endif

    EXTI->PR = pending;
}

// ****************************************************************************
void TIM3_IRQHandler (void)
{
    uint16_t status = TIM3->SR;
    
    if (status & TIM_SR_UIF)
    {
        hop_timer_handler();
        status &= ~(TIM_SR_UIF);
    }

    TIM3->SR = status;
}

// ****************************************************************************
void SysTick_Handler (void)
{
    if (SysTick->CTRL & (1 << 16)) {       // Read and clear Countflag
        ++systick_count;
    }
}


// ****************************************************************************
static void init_hardware(void)
{
#ifdef STM32F1
    /**
     * PB14    - LED
     * PB13    - BAT CALIBR
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
    /* GPIO config */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
    //PB14 - LED
    GPIOB->CRH &= ~(GPIO_CRH_CNF14 | GPIO_CRH_MODE14);
    GPIOB->CRH |= GPIO_CRH_MODE14_1; //2mhz out push-pull
    //PB12 - BIND
    GPIOB->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_MODE12);
    GPIOB->CRH |= GPIO_CRH_CNF12_1; //input push-pull
    GPIOB->BSRR = GPIO_BSRR_BS12; //pull up
#ifdef ESC
    //PB13 - BAT CALIBR
    GPIOB->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    GPIOB->CRH |= GPIO_CRH_CNF13_1; //input push-pull
    GPIOB->BSRR = GPIO_BSRR_BS13; //pull up
#endif

    //PA4 - NRF_CSN, PA3 - NRF_CE
    GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4 | GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
    GPIOA->CRL |= GPIO_CRL_MODE4_0 | GPIO_CRL_MODE3_0; //10mhz out push-pull
    //PB0 - NRF_IRQ
    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOB->CRL |= GPIO_CRL_CNF0_1; //input push-pull
    GPIOB->BSRR = GPIO_BSRR_BS0; //pull up

    //PA5, PA7, PA6 - floating input
    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5 | GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOA->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0; //10mhz alt push-pull

    //PA11, PA10, PA9, PA8
    GPIOA->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11
                 | GPIO_CRH_CNF10 | GPIO_CRH_MODE10
                 | GPIO_CRH_CNF9 | GPIO_CRH_MODE9
                 | GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOA->CRH |= GPIO_CRH_CNF11_1 | GPIO_CRH_MODE11_0
               | GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10_0
               | GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0
               | GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_0; //10mhz alt push-pull


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
    /* GPIO config */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

    GPIOA->MODER  &= ~(0x003CFFFF);
    GPIOA->MODER  |=   0x0028A845;
    GPIOA->OSPEEDR|=   0x003CCCCF;
    GPIOA->PUPDR  |=   0x00001110;
    GPIOA->AFR[0] &= ~(0xFFF00000);
    GPIOA->AFR[0] |=   0x00000000;
    GPIOA->AFR[1] &= ~(0x00000FF0);
    GPIOA->AFR[1] |=   0x00000220;
    

    GPIOB->MODER  &= ~(0x0000000C);
    GPIOB->MODER  |=   0x00000008;
    GPIOB->OSPEEDR|=   0x0000000C;
    GPIOB->AFR[0] &= ~(0x000000F0);
    GPIOB->AFR[0] |=   0x00000000;
    
#endif

    /* EXTI config */
#ifdef STM32F1
    AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0);
    AFIO->EXTICR[0] |=   AFIO_EXTICR1_EXTI0_PB;

    EXTI->FTSR |= EXTI_FTSR_TR0; /* Falling trigger event configuration */
    EXTI->IMR  |= EXTI_IMR_MR0;  /* Interrupt Mask on line 0 */
#else
    SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI2);
    SYSCFG->EXTICR[0] |=   SYSCFG_EXTICR1_EXTI2_PA;
 
    EXTI->FTSR |= EXTI_FTSR_TR2; /* Falling trigger event configuration */
    EXTI->IMR  |= EXTI_IMR_MR2;  /* Interrupt Mask on line 2 */
#endif


    /* PWM Timers config */
#ifndef STM32F1
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
    TIM14->PSC = (24-1); /* Ftim = 2 Mhz */
    TIM14->ARR = ((2000000/CH1_FREQUENCY) - 1);
    TIM14->CCR1 = 2*1500; /* width = 1.5 ms */
    TIM14->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
    TIM14->CCER |= TIM_CCER_CC1E;
    TIM14->CR1 |= TIM_CR1_CEN;
    TIM14->EGR = TIM_EGR_UG;	//	generate event and reload PSC
    while ((TIM14->SR & TIM_SR_UIF) == 0){}
    TIM14->SR = 0;
#endif
    
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;   
#ifdef STM32F1
    TIM1->PSC = (SystemCoreClock / 1000000 / 2 - 1); /* Ftim = 2 Mhz */
    TIM1->ARR = ((2000000/CH2_CH3_FREQUENCY) - 1);
    TIM1->CCR1 = TIM1->CCR2 = TIM1->CCR3= TIM1->CCR4 = 2*1500; /* width = 1.5 ms */

    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE
                | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;

    TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE
                | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE;

    TIM1->CCER = TIM_CCER_CC1E  | TIM_CCER_CC3E | TIM_CCER_CC4E;
#ifndef DEBUG
    TIM1->CCER |= TIM_CCER_CC2E;
#endif

#else

    TIM1->PSC = (24-1); /* Ftim = 2 Mhz */
    TIM1->ARR = ((2000000/CH2_CH3_FREQUENCY) - 1);
    TIM1->CCR2 = 2*1500; /* width = 1.5 ms */
    TIM1->CCR3 = 2*1500; /* width = 1.5 ms */
    TIM1->CCMR1 = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
    TIM1->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
    TIM1->CCER = TIM_CCER_CC2E | TIM_CCER_CC3E;
#endif

    TIM1->BDTR = TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->EGR = TIM_EGR_UG;	//	generate event and reload PSC
    while ((TIM1->SR & TIM_SR_UIF) == 0){}
    TIM1->SR = 0;
    
    /* hop Timer config */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
#ifdef STM32F1
    TIM3->PSC = (SystemCoreClock / 1000000 - 1); /* Ftim = 1 Mhz */
#else
    TIM3->PSC = (48-1); /* Ftim = 1 Mhz */
#endif
    TIM3->ARR = (65536 - 1);
    TIM3->CNT = (65536 - 1);
    TIM3->CR1 =  TIM_CR1_DIR;
    TIM3->EGR = TIM_EGR_UG;	//	generate event and reload PSC
    while ((TIM3->SR & TIM_SR_UIF) == 0){}
    TIM3->SR = 0;
    TIM3->DIER = TIM_DIER_UIE;
    
    /* delay Timer config */
    RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
#ifdef STM32F1
    TIM16->PSC = (SystemCoreClock / 1000000 - 1); /* Ftim = 1 Mhz */
#else
    TIM16->PSC = (48-1); /* Ftim = 1 Mhz */
#endif
    TIM16->ARR = (65536 - 1);
    TIM16->CNT = 0;
    TIM16->CR1 = TIM_CR1_OPM;
    TIM16->EGR = TIM_EGR_UG;	//	generate event and reload PSC
    while ((TIM16->SR & TIM_SR_UIF) == 0){}
    TIM16->SR = 0;

#ifdef DEBUG
    uart_init();
#endif

#ifdef ESC
    pwm_timer_init();
    adc_init();
#endif


}

// ****************************************************************************
static void init_hardware_final(void)
{
    /* SysTick config */
#ifdef STM32F1
    SysTick_Config(SystemCoreClock / 1000 *__SYSTICK_IN_MS); // need /8 ???

    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);

#else

    SysTick_Config(48000*__SYSTICK_IN_MS);
    NVIC_EnableIRQ(SysTick_IRQn);
    
    NVIC_SetPriority(EXTI2_3_IRQn, 0);
    NVIC_EnableIRQ(EXTI2_3_IRQn);
    
#endif

    NVIC_SetPriority(TIM3_IRQn, 1);
    NVIC_EnableIRQ(TIM3_IRQn);
    
}

// ****************************************************************************
void resetWatchdog (void);
void delay_us(uint32_t microseconds)
{
    TIM16->SR = 0;
    while (microseconds)
    {
        resetWatchdog();
        if (microseconds > 65535)
        {
            TIM16->CNT = 0;
            microseconds -= 65535;
        }
        else
        {
            TIM16->CNT = 65535 - microseconds;
            microseconds = 0;
        }
        TIM16->CR1 |= TIM_CR1_CEN;
        while ((TIM16->SR & TIM_SR_UIF) == 0);
        TIM16->SR = 0;	
    }
}


// ****************************************************************************
void startWatchdog (uint16_t ms)
{
    uint32_t reload = ((uint32_t)ms * LSI_VALUE)/(1000 * 32);
    IWDG->KR = IWDG_START;
    IWDG->KR = IWDG_WRITE_ACCESS;
    IWDG->PR = IWDG_PR_PR_0 | IWDG_PR_PR_1; /* divider = 32 */
    IWDG->RLR = IWDG_RLR_RL & reload;
    while (IWDG->SR) {};
    IWDG->KR = IWDG_REFRESH;
}

// ****************************************************************************
void resetWatchdog (void)
{
    IWDG->KR = IWDG_REFRESH;
}

// ****************************************************************************
int main(void)
{
    startWatchdog(200);
    init_hardware();
    init_spi();
    init_hardware_final();

    LOG("hello world\n");
    
#ifdef ESC
    start_sound();
    int bl = bat_level();
    if (bl)
        bat_beep(bl);
    else
        alarm_beep();
#endif
    
    // Wait a for a short time after power up before talking to the nRF24
    delay_us(20000);
    init_receiver();

    while (1)
    {
        resetWatchdog();
        service_systick();
        process_receiver();
    }
}
