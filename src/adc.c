#include "main.h"

ADC_HandleTypeDef AdcHandle;

int CurrentADCChannel = 0;
int distortion = 0;

void ADC_Init()
{
    
    ADC_ChannelConfTypeDef sConfig;

    
    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle.Instance          = ADC1;
  
    AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
    /* AdcHandle.Init.Resolution            = ADC_RESOLUTION8b; */
    AdcHandle.Init.Resolution            = ADC_RESOLUTION12b;
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle.Init.ScanConvMode          = ENABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    AdcHandle.Init.EOCSelection          = EOC_SINGLE_CONV;
    AdcHandle.Init.LowPowerAutoWait      = DISABLE;
    AdcHandle.Init.ContinuousConvMode    = ENABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    AdcHandle.Init.NbrOfConversion       = 2;                             /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
    AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    AdcHandle.Init.DMAContinuousRequests = ENABLE;
    AdcHandle.Init.Overrun               = OVR_DATA_OVERWRITTEN;
  
    if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
    {
        /* ADC initialization Error */
        Error_Handler();
    }

    /*##-2- Configure ADC regular channel ######################################*/
    sConfig.Channel      = ADC_CHANNEL_1;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_61CYCLES_5;
    sConfig.SingleDiff   = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;

    if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
    {
        /* Channel Configuration Error */
        Error_Handler();
    }

    /* configure channel 2 */
    sConfig.Channel      = ADC_CHANNEL_2;
    sConfig.Rank         = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
    {
        /* Channel Configuration Error */
        Error_Handler();
    }

    /*##-3- Start the conversion process #######################################*/
    /* if (HAL_ADC_Start(&AdcHandle) != HAL_OK) */
    if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)
    {
        /* Start Conversation Error */
        Error_Handler();
    }

}


void ADC1_2_IRQHandler()
{
    if (__HAL_ADC_GET_FLAG(&AdcHandle, ADC_FLAG_EOC))
    {
        uint16_t adcValue = HAL_ADC_GetValue(&AdcHandle);
        if (CurrentADCChannel == 0)
        {
            if (distortionEnabled)
            {
                if (adcValue > 0xfff - distortion)
                {
                    LED1_ON();
                    adcValue = 0xfff - distortion;
                }
                else if (adcValue < distortion)
                {
                    LED1_ON();
                    adcValue = distortion;
                }
                else
                {
                    LED1_OFF();
                }
            }
            else if (adcValue == 0xfff)
            {
                LED1_ON();
            }
            else
            {
                LED1_OFF();
            }
            
            DAC_SetValue12(adcValue);

            CurrentADCChannel = 1;
        }
        else
        {
            distortion = (int)((float)adcValue / 4095.0 * 3000);

            CurrentADCChannel = 0;
        }
    }
    
    HAL_ADC_IRQHandler(&AdcHandle);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    GPIO_InitTypeDef          GPIO_InitStruct;

    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* ADC3 Periph clock enable */
    __ADC1_CLK_ENABLE();
    /* Enable GPIO clock ****************************************/
    __GPIOA_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* ADC Channel GPIO pin configuration */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
}
