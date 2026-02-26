#include "main.h"


uint8_t hour;
uint8_t min;
uint8_t sec;
char string[32];


void RTC_IRQHandler(){

	if(RTC->ISR & (RTC_ISR_ALRAF)) // ALRAF - flag
	{

		RTC->ISR &= ~(RTC_ISR_ALRAF); // ALRAF clear flag 
		EXTI->PR = (1<<17); //17 линия внешних прерываний RTC WUT 1 = ОЧИСТИТЬ pending bit!

		RTC_getTime(&hour,&min,&sec);
		sprintf(string,"Time: %02u:%02u:%02u \n\r",hour,min,sec); // %02 /0- дополнить нулем /2 ширина
		USART1_sendStr(string);

	}
}

int USART_commands(){

	if (strncmp((char*)usart_data_buffer,"pwm",3) == 0) 
	{

		char *command = strtok((char*)usart_data_buffer," ");
		char *duty_char = strtok(NULL, ",");
		int duty = atoi(duty_char);

		PWM_init(duty);

		char string[32];
		sprintf(string, "PWM DUTY -> %2d \r\n", duty);
		USART1_sendStr(string);
	 	usart_data_buffer[0] = '\0';

	 		return 1;

	} else {
			return 0;
	}
		
}


int main(void){

	SystemClock_HSE_8MHz();
	SysTick_init();

	USART1_init(9600);
	PWM_init(50);
    DMA_init();
	DS18_init();
	RTC_init();
	I2C_init();
	
	USART1_sendStr("UART EN");

	RTC_setTime(16,00);

 while(1) {

	USART_commands();

	RTC_getTime(&hour,&min,&sec);
	sprintf(string,"Time: %02u:%02u:%02u  \n\r",hour,min,sec); 
	USART1_sendStr(string);

		_delay_ms(1000);


//DMA_uart1_Tx(string, strlen((char*)string));
//		_delay_ms(500);

/*

	sprintf(string,"SRCH = %u \n\r",DS18_search());
	USART1_sendStr(string);

	sprintf(string,"DS = %u \n\r",DS18_getData() /16 );
	USART1_sendStr(string);

	AHT_to_USART();

		_delay_ms(1000);


*/
	USART1_echo();

	}
}

