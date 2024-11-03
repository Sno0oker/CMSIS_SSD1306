#include "stm32f1xx.h"

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SIZE 1024

#define CS_SET GPIOA->BSRR = GPIO_BSRR_BS4 // CS - A4
#define CS_RES GPIOA->BSRR = GPIO_BSRR_BR4
#define RES_SET GPIOA->BSRR = GPIO_BSRR_BS3 // RES - A3
#define RES_RES GPIOA->BSRR = GPIO_BSRR_BR3
#define DATA GPIOA->BSRR = GPIO_BSRR_BS6 // DC - A6
#define COMMAND GPIOA->BSRR = GPIO_BSRR_BR6

typedef enum COLOR
{
	Black,
	White
}COLOR;

void ssd1306SendCommand(uint8_t command);
void ssd1306_Init();
void ssd1306DrawPixel(uint16_t x, uint16_t y,COLOR color);
void ssd1306UpdateScreen();
void ssd1306FillDisplay(COLOR color);
void spiSendArray(uint8_t *data, uint16_t length);
void spiTransmit(uint8_t data);
void ssd1306_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r,COLOR par_color);
