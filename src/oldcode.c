void gpiob_init()
{
    GPIO_InitTypeDef gpio_init;
    __GPIOB_CLK_ENABLE();
    __SYSCFG_CLK_ENABLE();
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_HIGH;

    
    for (int i = 0; i < 8; i++)
    {
        uint32_t pin = 1 << i;
        gpio_init.Pin = pin;
        HAL_GPIO_Init(GPIOB, &gpio_init);
        HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET);
    }
    
}


void gpiob_log(uint32_t value)
{
    value &= 0xff;
    GPIOB->ODR &= 0xff00;
    GPIOB->ODR |= value;
}
