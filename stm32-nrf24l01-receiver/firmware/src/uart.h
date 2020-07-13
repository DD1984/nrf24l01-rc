#ifndef __UART_H__
#define __UART_H__

#define BAUD_RATE 9600

void uart_init(void);
int __io_putchar(int ch);

#endif
