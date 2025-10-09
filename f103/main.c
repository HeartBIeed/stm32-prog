
#include "Drivers/CMSIS/Device/ST/STM32F1xx/Include/stm32f103xb.h"

int main(void)
{
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

GPIOA->CRL &= ~(0xF<<0); //pa0
GPIOA->CRL |= (0x2<<0);

GPIOA->CRL &= ~(0xF<<4); //pa1
GPIOA->CRL |= (0b1000<<4);
GPIOA->ODR |= (1<<1);

  while (1)
  {


	  if (!(GPIOA->IDR & (1<<1)))
	  {
	  GPIOA->BSRR = (1<<0);

	  }
	  else{
		  GPIOA->BSRR = (1<<16);
		  for(int i =0;i < 100000; i++);
		  GPIOA->BSRR = (1<<0);
		  for(int i =0;i < 100000; i++);


	  }
  }
}

