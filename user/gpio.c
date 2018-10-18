#include "gpio.h"

void Init_gpio()
{
    GPIO_Init(GPIOA,GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);
    
}



