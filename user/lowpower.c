#include "lowpower.h"
/*!
 * @file lowpower.c
 * @brief �͹��Ĺ���ʵ��
 * @author jason
 * @date 2018-10-18
 * @version ver1.0
 */

void Inti_lowpower()
{
    CLK_LSEConfig(CLK_LSE_ON);//RTCʱ��Դѡ��
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTCʱ�ӷ�Ƶ
    while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);//�ȴ�ʱ��Դ����
    
    RTC_WakeUpCmd(DISABLE);//�ر�RTC����
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ���ſ�ʹ��
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//RTC����ʱ�ӷ�Ƶ
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//RTC�����ж�ʹ��
    RTC_SetWakeUpCounter(2047*2);//1/(32.768/16)*2048=1S.
    ITC_SetSoftwarePriority(RTC_IRQn, ITC_PriorityLevel_3);//���ȼ�

    PWR_UltraLowPowerCmd(ENABLE);//���͹���
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//���Ѷ�ʱ���ж�ʹ��
    RTC_WakeUpCmd(ENABLE);//RTC����ʹ��
}

void Delay(uint16_t num)
{
    uint16_t i;
    for(i=0;i<num;i++)
        ;
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    RTC_WakeUpCmd(DISABLE);
    GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
    RTC_ClearITPendingBit(RTC_IT_WUT);  
    RTC_WakeUpCmd(ENABLE);
    
}





