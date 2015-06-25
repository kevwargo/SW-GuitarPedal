#include "timer.h"
#include "misc.h"
#include "led.h"

TIM_HandleTypeDef tim2handle;

void TIM2_Start()
{
    tim2handle.Instance = TIM2;
    tim2handle.Init.Prescaler = 1024;
    tim2handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim2handle.Init.Period = 50000;
    tim2handle.Init.ClockDivision = 0;
    tim2handle.State = HAL_TIM_STATE_RESET;

    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    HAL_TIM_Base_Init(&tim2handle);
    TIM2->ARR = 1;

    HAL_TIM_Base_Start_IT(&tim2handle);
}



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *timhandle)
{
    __TIM2_CLK_ENABLE();
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *timhandle)
{
    __TIM2_CLK_DISABLE();
}


void TIM2_IRQHandler()
{
    /* float tmp = sinf(2 * 3.141593 * (float)counter / (float)maxCounter); */
    /* uint32_t res = tmp * 0x7ff + 0x7ff; */
    /* HAL_DAC_SetValue(&dacHandle, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, res); */
    /* HAL_DAC_SetValue(&dacHandle, DAC1_CHANNEL_1, DAC_ALIGN_8B_R, Sample); */

    /* if (counter < maxCounter) */
    /*     counter++; */
    /* else */
    /*     counter = 0; */

    /* BSP_LED_On(0); */

    HAL_TIM_IRQHandler(&tim2handle);
}
