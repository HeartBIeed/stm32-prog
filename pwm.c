#include "pwm.h"


int PWM_init(uint8_t duty){
  // GPIO PA6 TIM3_CH1 AF1
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable TIM3 clock 

	GPIOA->MODER &= ~(0x03 << (6*2)); 
	GPIOA->MODER |= (0x02 << (6*2)); 
	
	GPIOA->OSPEEDR &= ~(0x03<<(6 *2)); 
	GPIOA->OSPEEDR |= (0x02<<(6 *2)); 

	GPIOA->AFR[0] &= ~(0xF<<(6 *4)); 
	GPIOA->AFR[0] |= (0x01<<(6 *4)); 


	TIM3->PSC = 7; // 8MHz/7+1 = 1MHz 
	TIM3->ARR = 999;//auto-reload register 1MHz/1 kHz
	TIM3->CCMR1 |= (0b110 << 4) |(1 << 3); //capture/compare mode register 1
	//110: PWM mode 1 - In upcounting
	//1: Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload 
	 
	TIM3->CCER |= (1<<0); //capture/compare enable register
	TIM3->CCR1 = 10*duty-1; //TIM3 capture/compare register 1 (TIM3_CCR1)
	TIM3->CR1 |= (1<<7) | (1<<0);// ARPE: Auto-reload preload enable
	//ARPE 1: TIMx_ARR register is buffered
	//CEN: Counter enable / 1: Counter enabled
	
	return 1;
}
























