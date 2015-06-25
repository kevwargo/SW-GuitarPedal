#include "main.h"

void LED_Init()
{
    GPIO_InitTypeDef gpio_init;
    __GPIOB_CLK_ENABLE();
    __SYSCFG_CLK_ENABLE();
    
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_HIGH;
    gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_3;

    HAL_GPIO_Init(GPIOB, &gpio_init);
}

void LED1_ON()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
}

void LED1_OFF()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}

void LED2_ON()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void LED2_OFF()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void LED1_Toggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}

void LED2_Toggle()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
}
