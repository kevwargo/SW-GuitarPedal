#include "misc.h"
#include "led.h"

void Error_Handler()
{
    while (1)
    {
        LED1_ON();
        HAL_Delay(100);
        LED2_ON();
        HAL_Delay(100);
        LED1_OFF();
        HAL_Delay(100);
        LED2_OFF();

        HAL_Delay(700);
    }
}
