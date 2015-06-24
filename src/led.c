#include "stm32f3xx_hal.h"
#include "stm32f3xx_nucleo.h"

void LED1_ON()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void LED1_OFF()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void LED2_ON()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
}

void LED2_OFF()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}

void LED1_Toggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
}

void LED2_Toggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}
