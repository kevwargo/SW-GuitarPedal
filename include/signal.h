#ifndef __SIGNAL_H
#define __SIGNAL_H

#include <math.h>
#include "stm32f3xx_hal.h"
#include "stm32f3xx_nucleo.h"

#include "util.h"

#define DEFAULT_MAX_COUNTER 128;


extern void DAC_Start();
extern void TIM2_Start();
extern void DAC_SetValue8(uint8_t value);
extern void DAC_SetValue12(uint16_t value);
extern void generate_signal(uint32_t timPeriod, uint32_t sinPeriod);

#endif
