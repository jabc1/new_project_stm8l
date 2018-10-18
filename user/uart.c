#include "uart.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x.h"  
/*!
 * @file uart.c
 * @brief ��Ҫʵ��muc���贮����ع���
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */


Fifo_t      Uart_Rx;
Fifo_t      Uart_Tx;
uint8_t     Uart_Rx_buff[Uart_Rx_len],Uart_Tx_buff[Uart_Tx_len];

UART1   Uart1;
void Init_uart()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //��λUART1

    USART_Init(USART1,9600, USART_WordLength_8b, USART_StopBits_1, \
               USART_Parity_No, USART_Mode_Tx|USART_Mode_Rx);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//���������ж�
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
    //USART_ITConfig(USART1, USART_IT_PE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_ERR, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    USART_Cmd(USART1, ENABLE);
    memset(Uart1.buff,0,sizeof(Uart1.buff));
    Uart1.flag = FALSE;
    Uart1.len = 0;    
}

/*******************************************************************************
* ����: UART1_SendByte
* ����: UART1����һ���ֽ�
* �β�: data -> Ҫ���͵��ֽ�
* ����: ��
* ˵��: ��
******************************************************************************/
void UART1_SendByte(u8 data)
{
    USART_SendData8(USART1, data);
    /* �ȴ�������� */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/*******************************************************************************
* ����: UART1_SendStr
* ����: UART1����len���ַ�
* �β�: data -> ָ��Ҫ���͵��ַ���
*       len -> Ҫ���͵��ֽ���
* ����: ��
* ˵��: ��
******************************************************************************/
void UART1_SendStr(u8 *str)
{
    while(*str != '\0')
    {
        UART1_SendByte(*str++); /* ѭ�����÷���һ���ַ����� */
    }   
}

void uart_test()
{
    if(Uart1.flag == TRUE)
    {
        //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        //UART1_SendStr("This is a UART Demo \r\n");
        UART1_SendStr(Uart1.buff);
        memset(Uart1.buff,0,sizeof(Uart1.buff));
        Uart1.flag = FALSE;
        Uart1.len = 0;
    }
}

INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    unsigned char ch = 0;
    if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//�����жϴ���
    {
        USART_ClearITPendingBit (USART1,USART_IT_RXNE);//���жϱ�־      
        ch = USART_ReceiveData8(USART1);
        Uart1.buff[Uart1.len ++] = ch;
        if(ch == '\n')
        {
            Uart1.flag = TRUE;
        }
    }
    /*
    if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
    {
        USART_ClearITPendingBit (USART1,USART_IT_IDLE);
        Uart1.flag = TRUE;
        USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
    */
}







