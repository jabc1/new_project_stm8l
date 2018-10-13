#include "uart.h"
#include "stm8l15x_gpio.h"

void Init_uart()
{
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //��λUART1
    /*
     * ��UART1����Ϊ��
     * ������ = 115200
     * ����λ = 8
     * 1λֹͣλ
     * ��У��λ
     * ʹ�ܽ��պͷ���
     */
    USART_Init(USART1, (u32)115200, USART_WordLength_8b, USART_StopBits_1,
                USART_Parity_No, USART_Mode_Tx|USART_Mode_Rx);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//���������ж�
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);//���������ж�
    USART_Cmd(USART1, ENABLE);  //ʹ��UART2

    

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
    UART1_SendStr("This is a UART Demo \r\n");
}








