#include "main.h"

DAC_HandleTypeDef dacHandle;
DAC_ChannelConfTypeDef dacChannel;

void DAC_Init()
{
    dacHandle.Instance = DAC1;
    dacHandle.State = HAL_DAC_STATE_RESET;
    if (HAL_DAC_Init(&dacHandle) != HAL_OK)
    {
        Error_Handler();
    }

    dacChannel.DAC_Trigger = DAC_TRIGGER_NONE;
    dacChannel.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
    /* dacChannel.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE; */
    if (HAL_DAC_ConfigChannel(&dacHandle, &dacChannel, DAC1_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    
    if (HAL_DAC_Start(&dacHandle, DAC1_CHANNEL_1))
    {
        Error_Handler();
    }
}


void DAC_SetValue8(uint8_t value)
{
    HAL_DAC_SetValue(&dacHandle, DAC1_CHANNEL_1, DAC_ALIGN_8B_R, value);
}

void DAC_SetValue12(uint16_t value)
{
    HAL_DAC_SetValue(&dacHandle, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, value);
}


void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    GPIO_InitTypeDef dac_gpio;
    __GPIOA_CLK_ENABLE();
    __DAC1_CLK_ENABLE();

    dac_gpio.Mode = GPIO_MODE_ANALOG;
    dac_gpio.Pull = GPIO_NOPULL;
    dac_gpio.Speed = GPIO_SPEED_HIGH;
    dac_gpio.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &dac_gpio);
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac)
{
    __DAC1_CLK_DISABLE();
}
