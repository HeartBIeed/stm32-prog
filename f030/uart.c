#include "stm32f030x6.h"


void UART_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHB2ENR |= RCC_AHB2ENR_USART1EN; 
//moder 10 - alt 2 bit
	GPIOA->MODER &= ~( 0x3 << (2*2)); //pb2 / clear
	GPIOA->MODER |= ( 0x2 << (2*2)); //pa2 set tx

	GPIOA->MODER &= ~( 0x3 << (3*2)); //pb3 / clear
	GPIOA->MODER |= ( 0x2 << (3*2)); //pa3 set rx
//otyper 0- push-pull 1 bit
	GPIOA->OTYPER &= ~((1<<2)|(1<<3)); //pb2 pb3 to  0
//speed 10 high 2 bit
	GPIOA->OSPEEDR |= ((0x2<<(2*2))|(0x2<<(3*2))); //pb2 pb3 to  0b10

	GPIOA->AFR &= ~((1<<2)|(1<<3)); //pb2 pb3 af1 up
//!!!!!!!!!!!!!!!!!!!!



}



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
















