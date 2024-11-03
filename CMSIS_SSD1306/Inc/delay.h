#include "stm32f1xx.h"

volatile static uint32_t msTicks = 0;

void delay_Init();
void delay(volatile uint32_t ms);
