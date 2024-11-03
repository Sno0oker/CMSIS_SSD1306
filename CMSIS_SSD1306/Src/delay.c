#include "delay.h"
#include "stm32f1xx.h"

void delay(volatile uint32_t ms){
	uint32_t targetTime = msTicks + ms;
	while (msTicks < targetTime);
}

void SysTick_Handler(void) {
    msTicks++;
}

void delay_Init()
{
	SysTick_Config(SystemCoreClock/1000);
}
