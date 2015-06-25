#include "main.h"

int distortionEnabled = 0;

void Button1_Init()
{
    GPIO_InitTypeDef gpio_init;
    
    gpio_init.Pin = GPIO_PIN_1;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOC, &gpio_init);

    HAL_NVIC_SetPriority(EXTI1_IRQn, 0x0F, 0x00);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void Button2_Init()
{
    GPIO_InitTypeDef gpio_init;
    
    gpio_init.Pin = GPIO_PIN_3;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOC, &gpio_init);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0x0F, 0x00);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void Button1_Pressed()
{
    if (distortionEnabled)
    {
        distortionEnabled = 0;
        LED2_OFF();
    }
    else
    {
        distortionEnabled = 1;
        LED2_ON();
    }    
}

void Button2_Pressed()
{
    
}

void EXTI15_10_IRQHandler()
{
    EXTI->PR |= (1 << 13);
}

void EXTI1_IRQHandler()
{
    EXTI->PR |= (1 << 1);
    Button1_Pressed();
}

void EXTI3_IRQHandler()
{
    EXTI->PR |= (1 << 3);
    Button2_Pressed();
}

