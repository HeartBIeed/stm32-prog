#include "main.h"


int main(void)
{
	SystemInit();
	UART_init();

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 

	GPIOB->MODER &= ~( 0xFF << (1*2)); //pb1 / input 00
	GPIOB->MODER |= ( 0x01 << (3*2)); //pb3 / output 01
	GPIOA->MODER |= ( 0x01 << (15*2)); //pa15 / output 01
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //pb1 / up 01



 while( 1 )
	{

		usart1_send_byte('A');

	uint8_t str[]="string";
	usart1_echo();


		if (usart1_recieve_byte() == 'E')
		{
		usart1_ptr_str(str);
		
		}

	}

}



/*
		if (usart1_recieve_byte() == 'E')
			{


			GPIOA->ODR |= (1 << 15);
			GPIOB->ODR &= ~(1 << 3);
			}
		else 
			{
			GPIOA->ODR &= ~(1 << 15);
			GPIOB->ODR |= (1 << 3);
			}

*/