

#include "stm32f030x6.h"

int main( void )
{
 

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

	GPIOB->MODER &= ~( 0xFF << (1*2)); //pb1 / input 00
	GPIOB->MODER |= ( 0x01 << (3*2)); //pb3 / output 01
	GPIOA->MODER |= ( 0x01 << (15*2)); //pa15 / output 01
	 
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //pb1 / up 01


 while( 1 )
	{


		if ((GPIOB->IDR & (1<<1))==0)
			{
			GPIOA->ODR |= (1 << 15);
			GPIOB->ODR &= ~(1 << 3);
			}
		else 
			{
			GPIOA->ODR &= ~(1 << 15);
			GPIOB->ODR |= (1 << 3);
			}

		    

	}
}
