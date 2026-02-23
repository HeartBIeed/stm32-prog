#include "main.h"


uint8_t hour;
uint8_t min;
uint8_t sec;
char data_ds[32];


void RTC_IRQHandler()
{

if(RTC->ISR & (RTC_ISR_ALRAF)) // ALRAF - flag
	{

	RTC->ISR &= ~(RTC_ISR_ALRAF); // ALRAF clear flag 
	EXTI->PR = (1<<17); //17 линия внешних прерываний RTC WUT 1 = ОЧИСТИТЬ pending bit!

	RTC_get_time(&hour,&min,&sec);
	sprintf(data_ds,"Time: %02u:%02u:%02u \n\r",hour,min,sec); // %02 /0- дополнить нулем /2 ширина
	usart1_send_str(data_ds);

	}
}



int main(void)
{

	SystemClock_HSE_8MHz();
	SysTick_init();

	UART_init(9600);
//	ds18_init();
//	I2C_init();
//	DMA_init();

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  

	usart1_send_str("UART EN");


	RTC_init();
	RTC_set_time(13,58);
	RTC_alarm_sec();

 while( 1 )
	{

		RTC_get_time(&hour,&min,&sec);
		sprintf(data_ds,"Time: %02u:%02u:%02u \n\r",hour,min,sec); // %02 /0- дополнить нулем /2 ширина
		usart1_send_str(data_ds);
			_delay_ms(500);




	}
}

