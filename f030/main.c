#include "stm32f030x6.h"


void UART_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //APB bus
//moder 10 - alt 2 bit
	GPIOA->MODER &= ~( 0x3 << (2*2)); //pb2 / clear
	GPIOA->MODER |= ( 0x2 << (2*2)); //pa2 set tx

	GPIOA->MODER &= ~( 0x3 << (3*2)); //pb3 / clear
	GPIOA->MODER |= ( 0x2 << (3*2)); //pa3 set rx
//otyper 0- push-pull 1 bit
	GPIOA->OTYPER &= ~((1<<2)|(1<<3)); //pb2 pb3 to  0
//speed 10 high 2 bit
	GPIOA->OSPEEDR |= ((0x2<<(2*2))|(0x2<<(3*2))); //pb2 pb3 to  0b10

	GPIOA->AFR[0] &= ~((0xF<<(2*4))|(0xF<<(3*4))); //0b001 usart tx rx enable mode
	GPIOA->AFR[0] |= ((0x1<<(2*4))|(0x1<<(3*4)));  //0b001/ 4 bit on 1 pin

	USART1->CR1 = 0;
	USART1->CR2 = 0;
	USART1->CR3 = 0;

	uint32_t fcpu = 8000000u;
	uint32_t baud = 9600u;

	USART1->BRR = fcpu/baud; //????????
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; //tx rx usart enable

}

void usart1_send_byte(uint8_t tx_data)
	{
		while ((USART1->ISR & USART_ISR_TXE) == 0);
	 	USART1->TDR = tx_data;
	}

uint8_t usart1_recieve_byte()
	{
		while ((USART1->ISR & USART_ISR_RXNE) == 0);
	 	return (uint8_t)USART1->RDR;
	
	}

int main( void )
{
 
	UART_init();

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

	GPIOB->MODER &= ~( 0xFF << (1*2)); //pb1 / input 00
	GPIOB->MODER |= ( 0x01 << (3*2)); //pb3 / output 01
	GPIOA->MODER |= ( 0x01 << (15*2)); //pa15 / output 01
	 
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //pb1 / up 01



 while( 1 )
	{

usart1_send_byte('A');


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

		    

	}
}
















