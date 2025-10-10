#include "uart.h"

extern volatile uint8_t uart1_flag = 0;


void UART_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //APB bus
//moder 10 - alt 2 bit
	GPIOA->MODER &= ~( 0x3 << (9*2)); //pa2 / clear
	GPIOA->MODER |= ( 0x2 << (9*2)); //pa2 set tx

	GPIOA->MODER &= ~( 0x3 << (10*2)); //pa3 / clear
	GPIOA->MODER |= ( 0x2 << (10*2)); //pa3 set rx
//otyper 0- push-pull 1 bit
	GPIOA->OTYPER &= ~((1<<9)|(1<<10)); //pa2 pa3 to  0
//speed 10 high 2 bit
	GPIOA->OSPEEDR |= ((0x2<<(9*2))|(0x2<<(10*2))); //pa2 pa3 to  0b10

	GPIOA->AFR[1] &= ~((0xF<<((9-8)*4))|(0xF<<((10-8)*4))); //0b001 usart tx rx enable mode
	GPIOA->AFR[1] |= ((7<<((9-8)*4))|(7<<((10-8)*4)));  //0b001/ 4 bit on 1 pin
//AFR[1] — пины 8–15
	USART1->CR1 = 0;
	USART1->CR2 = 0;
	USART1->CR3 = 0;

	uint32_t fcpu = 8000000u;
	uint32_t baud = 9600u;

	USART1->BRR = (uint16_t)((fcpu+(baud/2))/baud); 
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; //tx rx usart enable

}

void usart1_send_byte(uint8_t tx_data)
	{
		while ((USART1->SR & USART_SR_TXE) == 0);
	 	USART1->DR = tx_data;
	}

uint8_t usart1_recieve_byte()
	{
		while ((USART1->SR & USART_SR_RXNE) == 0);
	 	return (uint8_t)USART1->DR;
	
	}

void usart1_rxen_flag()
	{

	if (USART1->SR & USART_SR_RXNE)
		{
		uart1_flag = 1;
		}

		else
		{
		uart1_flag =0;
		}
		
	}


void usart1_echo()
	{
	
	if (USART1->SR & USART_SR_RXNE)
		usart1_send_byte((uint8_t)USART1->DR);

	}

void usart1_ptr_str(uint8_t *str) // TX string
	{
		while (*str) 
		{

		usart1_send_byte(*str++);
		
		}

	}












