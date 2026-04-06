#include "extint.h"

void EXTI_init(){
RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN

GPIOB->MODER &= ~(3 << (PB0 * 2)); //вход / 0x00


// SYSCFG external interrupt configuration register 1 
SYSCFG->EXTICR &= ~(0x000F); 
SYSCFG->EXTICR |=(1<< 0) ; //x001: PB[x] pin 
// PB0


//Interrupt mask register (EXTI_IMR)
EXTI->IMR |= (1 << 0); //линия 0

EXTI->FTSR |= (1 << 0); 

NVIC_EnableIRQ(EXTI0_1_IRQn); /* (1) Включение прерывания на EXTI0_0 */
NVIC_SetPriority(EXTI0_1_IRQn,0); /* (2) Установка приоритета для EXTI0_0 */
}

void EXTI0_1_IRQHandler(void)
{
    
    if (EXTI->PR & (1 << 0)) 
    {
        
        EXTI->PR |= (1 << 0); // Сбрасываем флаг 
        
       //****
    }
    
}