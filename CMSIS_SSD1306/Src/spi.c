#include "spi.h"

void SPIandPA_Init(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN; // Тактирование SPI и GPIOA

	GPIOA->CRL|= GPIO_CRL_MODE3 |GPIO_CRL_MODE4 | GPIO_CRL_MODE6; // 50 мгц выходы PA3, PA4, PA6
	GPIOA->CRL&= ~(GPIO_CRL_CNF3 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6);// PA3, PA5, PA6 выход push-pull

    GPIOA->CRL |= GPIO_CRL_MODE5 | GPIO_CRL_MODE7;
    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_CNF7);  // Очистка бяки
    GPIOA->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_CNF7_1; // Альт. функция для PA5, PA7 с push-pull

    SPI1->CR1 |= SPI_CR1_MSTR; // Режим мастера
    SPI1->CR1 |= (0x03 & SPI_CR1_BR); // Деление частоты на 16 (56 / 16 = 3.5 мгц)
    SPI1->CR1 |= SPI_CR1_SSM; // Программная настройка NSS
    SPI1->CR1 |= SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}
