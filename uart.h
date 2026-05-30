

#ifndef UART_H_
#define UART_H_

void UART2_Init();
void UART2_WriteString(char* str);


#define PERIPH_BASE        0x40000000U
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x00020000U)
#define APB1PERIPH_BASE    PERIPH_BASE

#define GPIOA_BASE         (AHB1PERIPH_BASE + 0x0000U)
#define RCC_BASE           (AHB1PERIPH_BASE + 0x3800U)
#define USART2_BASE        (APB1PERIPH_BASE + 0x4400U)



#endif /* UART_H_ */
