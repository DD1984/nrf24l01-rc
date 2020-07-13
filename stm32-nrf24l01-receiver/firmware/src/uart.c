#include <stdio.h>
#include "platform.h"
#include "uart.h"

void uart_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1
    USART1->CR1 = USART_CR1_UE; // разрешаем USART1, сбрасываем остальные биты
    USART1->BRR =  SystemCoreClock / BAUD_RATE;

    USART1->CR1 |= USART_CR1_TE; // разрешаем передатчик
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

#if 0
void hello_world(void)
{
    char buf[] = "hello world\r\n";

    char *ptr = buf;

    while (*ptr) {
        while ((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = *ptr;
        ptr++;
    }
}
#endif

int __io_putchar(int ch)
{
    while ((USART1->SR & USART_SR_TXE) == 0);
    USART1->DR = ch;

    return ch;
}
