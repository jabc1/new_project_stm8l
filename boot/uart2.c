#include "uart2.h"

void Init_UART2(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
    USART_DeInit(USART1);       //复位UART1

    USART_Init(USART1,9600, USART_WordLength_8b, USART_StopBits_1, \
               USART_Parity_No, USART_Mode_Tx|USART_Mode_Rx);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启接收中断
    USART_Cmd(USART1, ENABLE);
}

void Uart2_SendByte(uint8_t Byte)
{
    USART_SendData8(USART2, Byte);
    /* 等待传输结束 */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

}

void Uart2_SendStr(u8 *pBuffer,u16 NumToWrite)
{
    while(NumToWrite--)
    {
        Uart2_SendByte(*pBuffer);
        pBuffer++;
    }
}


u8 Uart2_Receive(u8* ReceivedData,uint32_t t_count)
{
  while(t_count) 
  {
    if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)!=RESET)
    {
      *ReceivedData = USART2->DR;
      return 0 ;
    }
    t_count--;
  }
  return 1;  
}











