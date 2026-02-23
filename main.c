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


	//DMA_init();
//	GPIO();
	ds18_init();
	RTC_init();

	usart1_send_str("UART EN");

char data_ds[32];
//uint8_t string[] = "dma string \n\r";

uint8_t hour;
uint8_t min;
RTC_set_time(21,30);

 while( 1 )
	{



	RTC_get_time(&hour,&min);
	sprintf(data_ds,"Time: %02u:%02u \n\r",hour,min); // %02 /0- дополнить нулем /2 ширина
	usart1_send_str(data_ds);



//dma_uart1_tx(string, strlen((char*)string));
//	_delay_ms(500);



	sprintf(data_ds,"SRCH = %u \n\r",ds18_search());
	usart1_send_str(data_ds);

	sprintf(data_ds,"DS = %u \n\r",ds18_get() /16 );
	usart1_send_str(data_ds);

	AHT_to_uart();

		_delay_ms(1000);

/*	//	I2C_scan();

	_delay_ms(500);
*/
//	echo();


	}
}

