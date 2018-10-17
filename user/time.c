#include "time.h"
#include "stm8l15x.h"
#include "rtc.h"
#include "uart.h"
#include "gpio.h"


unsigned char tbuff[20] ={0};
TIME2   Time2 = {0,0,0,0,0};

void Init_time2()
{
    TIM2_DeInit();
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);    
    TIM2_TimeBaseInit(TIM2_Prescaler_2, TIM2_CounterMode_Up, 1000);//1ms
    TIM2_ARRPreloadConfig(ENABLE);  
    TIM2_ITConfig(TIM2_IT_Update , ENABLE);  
    TIM2_Cmd(ENABLE);
}
void tiem2_test()
{
    RTC_TimeTypeDef RTC_TimeStr;

    if(Time2.flag == TRUE)
    {
        Time2.flag = FALSE;
        GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
        rtc_get_time(tbuff);
        rtc_get_date(tbuff);
        //UART1_SendStr(tbuff);
    }

}
/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  
    if (TIM2_GetITStatus(TIM2_IT_Update) != RESET)
    {
        TIM2_ClearITPendingBit(TIM2_IT_Update);      //清除中断标记
        if(Time2.count++ >= 999)//s
        {
            Time2.count = 0;
            Time2.flag = TRUE;
            if(Time2.sec ++ >= 59)//min
            {
                Time2.sec = 0;
                if(Time2.min++ >= 59)//hour
                {
                    Time2.min = 0;
                    Time2.hours++;
                }
            }
        }
    }
}



