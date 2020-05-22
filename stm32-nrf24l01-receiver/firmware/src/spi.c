#include <stdlib.h>
#include <stdint.h>

#include "platform.h"
#include "spi.h"



// ****************************************************************************
void init_spi(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
    SPI1->CR1 = 0;
    SPI1->CR2 = SPI_CR2_FRXTH |				// RXNE event is generated if the FIFO level is greater than or equal to 1/4 (8-bit)
                SPI_CR2_DS_0 |				// Data Size: 0b0111 - 8 bit
                SPI_CR2_DS_1 |
                SPI_CR2_DS_2;
    SPI1->CR1 = SPI_CR1_MSTR |
                SPI_CR1_BR_0 |				// Baud Rate - div by 4			
                SPI_CR1_SPE |				// Peripheral enabled
                SPI_CR1_SSI |				// Internal slave select
                SPI_CR1_SSM ;				// Software slave management
}


// ****************************************************************************
uint8_t spi_transaction(unsigned int count, uint8_t *buffer)
{
    GPIO_NRF_CSN_LO();

    uint8_t *ptr = buffer;
    while (count--)
    {
        while ((SPI1->SR & SPI_SR_TXE) == 0);
        *(uint8_t *)&(SPI1->DR) = (uint8_t) *ptr;
        while ((SPI1->SR & SPI_SR_RXNE) == 0);
        *ptr = (uint8_t) SPI1->DR;
        ++ptr;
    }
    
    while ((SPI1->SR & SPI_SR_BSY));
    GPIO_NRF_CSN_HI();
    
    return *buffer;
}
