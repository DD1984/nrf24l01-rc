#include <stdint.h>
#include "platform.h"
#include "adc.h"
#include "persistent_storage.h"
#include "tune.h"

extern void delay_us(uint32_t microseconds);

void adc_init(void)
{
    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // PA2 - аналоговый вход

    RCC->APB2ENR |=  RCC_APB2ENR_ADC1EN;   //подаем тактирование АЦП 
    RCC->CFGR    &= ~RCC_CFGR_ADCPRE;      //входной делитель
    ADC1->CR1     =  0;                    //
    ADC1->SQR1    =  0;                    // 
    ADC1->CR2    |=  ADC_CR2_CAL;          //запуск калибровки 
    while (!(ADC1->CR2 & ADC_CR2_CAL)){}; //ждем окончания калибровки
    ADC1->CR2     =  ADC_CR2_EXTSEL;       //выбрать источником запуска разряд  SWSTART
    ADC1->CR2    |=  ADC_CR2_EXTTRIG;      //разр. внешний запуск регулярного канала
    ADC1->CR2    |=  ADC_CR2_ADON;         //включить АЦП

    ADC1->SQR3 = 2;
}

uint16_t get_adc_val(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;     //запустить преобразование в регулярном канале   
    while (!(ADC1->SR & ADC_SR_EOC)){};//дождаться окончания  преобразования
    return ADC1->DR; 
}

#define BAT_CHECK_CNT 100

// рассчетные значения
#define BAT_8_4v_18K_10K 3722
#define BAT_6v_18K_10K   2656

#define MAX_LEV 4 // 1 alarm, 3 normal

int bat_level(void)
{
    uint32_t adc_val = 0;
    int cnt = BAT_CHECK_CNT;
    uint32_t bat_calibr_pin = 0;
    uint16_t adc_flash_val;

    while (cnt) {
        adc_val += get_adc_val();

        if ((GPIOB->IDR & GPIO_IDR_IDR13) != GPIO_IDR_IDR13)
            bat_calibr_pin++;

        delay_us(100);
        cnt--;
    }

    adc_val /= BAT_CHECK_CNT;

    if (bat_calibr_pin * 100 / BAT_CHECK_CNT > 70) {
        uint16_t tmp = adc_val;
        nvram_set(BAT_CALIBR, (uint8_t *)&tmp);
        long_beep();
    }

    if (nvram_get(BAT_CALIBR, (uint8_t *)&adc_flash_val) != 0)
        return 0;

    uint32_t bat_6v = adc_flash_val * BAT_6v_18K_10K / BAT_8_4v_18K_10K;
    uint32_t delta = (adc_flash_val - bat_6v) / MAX_LEV;
    bat_6v = adc_flash_val - delta * MAX_LEV;

    LOG("adc: %d, delta: %d 6v: %d 8.4v: %d\n", adc_val, delta, bat_6v, adc_flash_val);

    if (adc_val < bat_6v)
        adc_val = bat_6v;
    if (adc_val > adc_flash_val)
        adc_val = adc_flash_val;
    
    uint32_t tmp = bat_6v;
    int level = 0;
    while (!(adc_val >= tmp && adc_val <= tmp + delta)) {
        level++;
        tmp += delta;
    }

    LOG("bat level: %d\n", level);

    return level;
}
