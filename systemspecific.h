/*
 * systemspecific.h
 *
 *  Created on: Apr 18, 2026
 *      Author: noeld
 */

#ifndef SYSTEMSPECIFIC_H_
#define SYSTEMSPECIFIC_H_

#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASE)
#define RCC     ((RCC_RegDef_t*) RCC_BASE)
#define USART2  ((USART_RegDef_t*) USART2_BASE)


typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_RegDef_t;







typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_RegDef_t;


typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    uint32_t RESERVED2[3];
    volatile uint32_t APB1ENR;
} RCC_RegDef_t;



#endif /* SYSTEMSPECIFIC_H_ */
