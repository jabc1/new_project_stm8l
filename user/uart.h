#ifndef _uart_h
#define _uart_h
#include "stm8l15x_usart.h"

#define uart_len       255

#pragma pack(push, 1)
typedef  struct
{
    uint16_t len;
    uint8_t flag;
    uint8_t buff[uart_len];
    uint8_t back_buff[uart_len];
}UART1;
#pragma pack(pop)

extern UART1   Uart1;


void Init_uart(void);
void uart_test(void);



#endif








