#include "main.h"

void RCC_Init();

int main(void)
{
	RCC_Init();
	delay_Init();
	SPIandPA_Init();
	ssd1306_Init();
	while(1){
		ssd1306_DrawCircle(60, 40, 15, White);
		ssd1306UpdateScreen();
	}
}

void RCC_Init()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL7;
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	SystemCoreClockUpdate();
}
