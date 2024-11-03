#include "ssd1306.h"
#include "delay.h"
#include "spi.h"

static uint8_t display[SIZE];

void ssd1306_Reset(){
	uint16_t i;
	RES_RES;
	for(i = 0; i < SIZE; i++)
	{
		display[i] = 0;
	}
	RES_SET;
}

void ssd1306_Init()
{
	ssd1306_Reset();

	ssd1306SendCommand(0xAE); //display off
	ssd1306SendCommand(0x20); //Set Memory Addressing Mode
	ssd1306SendCommand(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
	                            // 10b,Page Addressing Mode (RESET); 11b,Invalid

	ssd1306SendCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1306SendCommand(0xC8); //Set COM Output Scan Direction
    ssd1306SendCommand(0x00); //---set low column address
    ssd1306SendCommand(0x10); //---set high column address

    ssd1306SendCommand(0x40); //--set start line address - CHECK
    ssd1306SendCommand(0x81); //set contrast control register
    ssd1306SendCommand(0xFF);
    ssd1306SendCommand(0xA1); //set segment re-map 0 to 127
    ssd1306SendCommand(0xA6); //--set normal color

    ssd1306SendCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    ssd1306SendCommand(0xD3); //-set display offset - CHECK
    ssd1306SendCommand(0x00); //-not offset

    ssd1306SendCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306SendCommand(0xF0); //--set divide ratio
    ssd1306SendCommand(0xD9); //--set pre-charge period
    ssd1306SendCommand(0x22); //
    ssd1306SendCommand(0xDA); //--set com pins hardware configuration - CHECK

    ssd1306SendCommand(0x12);
    ssd1306SendCommand(0xDB); //--set vcomh
    ssd1306SendCommand(0x20); //0x20,0.77xVcc

    ssd1306SendCommand(0x8D); //--set DC-DC enable
    ssd1306SendCommand(0x14); //
    ssd1306SendCommand(0xAF); //Enable
}

void ssd1306DrawPixel(uint16_t x, uint16_t y,COLOR color){
	if(x < SSD1306_WIDTH && y < SSD1306_HEIGHT && x >= 0 && y >= 0)
	{
		if(color == White)
		{
			display[x+(y/8)*SSD1306_WIDTH] |= (1 << (y % 8));
		}
		else if(color == Black)
		{
			display[x+(y/8)*SSD1306_WIDTH] &= ~(1 << (y % 8));
		}
	}
}

void ssd1306UpdateScreen(){
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {
        ssd1306SendCommand(0xB0 + i); // Set the current RAM page address.
        ssd1306SendCommand(0x00);
        ssd1306SendCommand(0x10);
        DATA;
        spiSendArray(&display[SSD1306_WIDTH*i], SSD1306_WIDTH);
    }
}

void ssd1306FillDisplay(COLOR color)
{
	uint16_t i;
	for(i = 0;i < SSD1306_HEIGHT * SSD1306_WIDTH; i++)
	{
		if(color == White)
			display[i] = 0xFF;
		else if(color == Black)
			display[i] = 0;
	}
}

void ssd1306_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r,COLOR par_color) {
    int32_t x = -par_r;
    int32_t y = 0;
    int32_t err = 2 - 2 * par_r;
    int32_t e2;

    if (par_x >= SSD1306_WIDTH || par_y >= SSD1306_HEIGHT) {
        return;
    }

    do {
    	ssd1306DrawPixel(par_x - x, par_y + y, par_color);
    	ssd1306DrawPixel(par_x + x, par_y + y, par_color);
        ssd1306DrawPixel(par_x + x, par_y - y, par_color);
        ssd1306DrawPixel(par_x - x, par_y - y, par_color);
        e2 = err;

        if (e2 <= y) {
            y++;
            err = err + (y * 2 + 1);
            if(-x == y && e2 <= x) {
                e2 = 0;
            }
        }

        if (e2 > x) {
            x++;
            err = err + (x * 2 + 1);
        }
    } while (x <= 0);

    return;
}

void spiSendArray(uint8_t *data, uint16_t length){
	CS_RES;
	for (uint16_t i = 0; i < length; i++) {
		while (!(SPI1->SR & SPI_SR_TXE));
		SPI1->DR = data[i];
	}
	while (SPI1->SR & SPI_SR_BSY);
	CS_SET;
}

void spiTransmit(uint8_t data)
{
	CS_RES;
	SPI1->DR = data;
	while((SPI1->SR & SPI_SR_BSY));
	CS_SET;
}

void ssd1306SendCommand(uint8_t command)
{
	COMMAND;
	spiTransmit(command);
	DATA;
}
