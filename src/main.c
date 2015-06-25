#include "main.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    BSP_PB_Init(0, BUTTON_MODE_EXTI);
    BSP_LED_Init(0);
    BSP_LED_Off(0);

    LED_Init();

    Button1_Init();
    /* Button2_Init(); */
    DAC_Init();
    ADC_Init();

    /* Error_Handler(); */
    
    while (1)
    {
        
    }
}



