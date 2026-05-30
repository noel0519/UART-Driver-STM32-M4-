
#include<stdint.h>
#include "uart.h"
#include "systemspecific.h"

#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASE)
#define RCC     ((RCC_RegDef_t*) RCC_BASE)
#define USART2  ((USART_RegDef_t*) USART2_BASE)

void UART2_Clock_Enable();
void UART2_GPIO_Init(void);
void UART2_SetBaudRate(void);
void UART2_Init(void);
void UART2_WriteChar(char c);
void UART2_WriteString(char* str);
char UART2_ReadChar(void);





void UART2_Clock_Enable(){

RCC->AHB1ENR |= (1 << 0); // GPIO
RCC->APB1ENR |= (1<<17);// USART2

}

void UART2_GPIO_Init(void)
{

    GPIOA->MODER &= ~(0xF << (2 * 2));
    GPIOA->MODER |=  (0xA << (2 * 2)); // AF mode

    // Set AF7 (USART2)
    GPIOA->AFR[0] &= ~(0xF << (4 * 2));
    GPIOA->AFR[0] |=  (0x77 << (4 * 2));

    // Set output type to push-pull
    GPIOA->OTYPER &= ~(1 << 2);

    // Set speed (optional but good practice)
    GPIOA->OSPEEDR |= (2 << (2 * 2));

    // Enable pull-up (important for TX stability)
    GPIOA->PUPDR &= ~(3 << (2 * 2));
    GPIOA->PUPDR |=  (1 << (2 * 2));
}

void UART2_SetBaudRate(void){
	USART2->BRR = 16000000 / 9600;

}
void UART2_Init(void){
	UART2_Clock_Enable();
	UART2_GPIO_Init();
	UART2_SetBaudRate();

	USART2->CR1 |= (1<<3);
	USART2->CR1 |= (1<<2);
	USART2->CR1 |= (1<<13);


}

void UART2_WriteChar(char c){
	while(!(USART2->SR & (1<<7)));
	USART2->DR = c;
}

void UART2_WriteString(char* str){
	while(*str){
		UART2_WriteChar(*str++);
	}
}

char UART2_ReadChar(void)
{
    while(!(USART2->SR & (1 << 5))); // RXNE
    return USART2->DR;
}
