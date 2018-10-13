#include "time.h"
void Init_time2()
{
    TIM2_DeInit();
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);    
    TIM2_TimeBaseInit(TIM2_Prescaler_2, TIM2_CounterMode_Up, 1000);
    TIM2_ARRPreloadConfig(ENABLE);  
    TIM2_ITConfig(TIM2_IT_Update , ENABLE);  
    TIM2_Cmd(ENABLE);
}



