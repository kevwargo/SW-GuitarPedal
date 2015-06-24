#include "main.h"

#define MAX_ADC_COUNTER    100000

static ADC_HandleTypeDef AdcHandle;
static DAC_HandleTypeDef dacHandle;
static DAC_ChannelConfTypeDef dacChannel;
static TIM_HandleTypeDef tim2handle;


/* static uint32_t adcCounter = 0; */

int distortionEnabled = 1;
uint32_t distortion = 0;
uint8_t EXTI3_Counter = 0;
int adcChannelFinished = 0;
/* uint8_t Sample = 127; */


void DAC_Start()
{
    GPIO_InitTypeDef dac_gpio;
    dac_gpio.Mode = GPIO_MODE_ANALOG;
    dac_gpio.Pull = GPIO_NOPULL;
    dac_gpio.Speed = GPIO_SPEED_HIGH;
    dac_gpio.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &dac_gpio);

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

void adc_init()
{
    
    ADC_ChannelConfTypeDef sConfig;

    
    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle.Instance          = ADC1;
  
    AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
    AdcHandle.Init.Resolution            = ADC_RESOLUTION8b;
    /* AdcHandle.Init.Resolution            = ADC_RESOLUTION12b; */
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

void pc3_int_init()
{
    GPIO_InitTypeDef gpio_init;
    
    gpio_init.Pin = GPIO_PIN_3;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOC, &gpio_init);

    gpio_init.Pin = GPIO_PIN_1;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(GPIOC, &gpio_init);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0x0F, 0x00);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0x0F, 0x00);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
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

void EXTI15_10_IRQHandler()
{
    EXTI->PR |= (1 << 13);

    /* HAL_TIM_Base_Stop(&tim2handle); */
    /* HAL_TIM_Base_DeInit(&tim2handle); */

    /* if (timPeriod > 50) */
    /*     timPeriod -= 10; */
    /* else */
    /*     timPeriod = 200; */
    
    /* TIM2_Start(); */

    if (distortion < 0x7f)
        distortion += 0x8;
    else
        distortion = 0;
}

void EXTI1_IRQHandler()
{
    EXTI->PR |= (1 << 2);
    BSP_LED_Off(0);
    EXTI3_Counter--;
}

void EXTI3_IRQHandler()
{
    EXTI->PR |= (1 << 3);
    /* EXTI3_Counter++; */
    if (distortionEnabled)
    {
        /* BSP_LED_Off(0); */
        distortionEnabled = 0;
    }
    else
    {
        /* BSP_LED_On(0); */
        distortionEnabled = 1;
    }
        
}



/**
  * @brief  This function handles ADC interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
    if (__HAL_ADC_GET_FLAG(&AdcHandle, ADC_FLAG_EOC))
    {
        uint8_t adcValue = HAL_ADC_GetValue(&AdcHandle);
        if (adcChannelFinished == 0)
        {
            adcChannelFinished = 1;
            if (distortionEnabled || 1)
            {
                /* distortion = 100; */
                /* BSP_LED_On(0); */
                if (adcValue > 0xff - distortion)
                {
                    adcValue = 0xff - distortion;
                    BSP_LED_On(0);
                }
                else if (adcValue < distortion)
                {
                    BSP_LED_On(0);
                    adcValue = distortion;
                }
                else
                {
                    BSP_LED_Off(0);
                }
            }
            else
            {
                /* BSP_LED_Off(0); */
                
            }
            /* if (adcValue == 0xff) */
            /*     BSP_LED_On(0); */
            /* else */
            /*     BSP_LED_Off(0); */
            DAC_SetValue8(adcValue);
        }
        else
        {
            uint8_t value = adcValue >> 4;
            value &= 0x0f;
            /* GPIOB->ODR &= 0xfff0; */
            /* GPIOB->ODR |= value; */

            /* distortion = adcValue; */
            
            adcChannelFinished = 0;
        }
    }
    
    HAL_ADC_IRQHandler(&AdcHandle);
}


int main(void)
{
    HAL_Init();
    SystemClock_Config();

    BSP_PB_Init(0, BUTTON_MODE_EXTI);
    BSP_LED_Init(0);
    BSP_LED_Off(0);
    pc3_int_init();

    /* HAL_Delay(1000); */

    EXTI3_Counter = 0;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    /* DAC_Start(); */
    /* adc_init(); */
    /* TIM2_Start(); */

    /* generate_signal(127, 64); */
    

    while (1)
    {
        
    }
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
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

}


void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    __GPIOA_CLK_ENABLE();
    __DAC1_CLK_ENABLE();
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac)
{
    __DAC1_CLK_DISABLE();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *timhandle)
{
    __TIM2_CLK_ENABLE();
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *timhandle)
{
    __TIM2_CLK_DISABLE();
}
