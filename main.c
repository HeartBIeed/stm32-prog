#include "main.h"


uint8_t hour;
uint8_t min;
uint8_t sec;
char string[41];

/*
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
*/

int USART_commands(){

	if (strncmp((char*)usart_data_buffer,"st",2) == 0) 
	{

		char *command = strtok((char*)usart_data_buffer," ");
		char *h_char = strtok(NULL, ",");
		char *m_char = strtok(NULL, ",");

		int h = atoi(h_char);
		int m = atoi(m_char);

		DS1302_setTtime(h,m);

		char string[32];
		sprintf(string, "SET TIME -> %2d:%2d \r\n",h,m);
		USART1_sendStr(string);
	 	usart_data_buffer[0] = '\0';

	 		return 1;

	} else {
			return 0;
	}
		
}

int main(void){

	SystemClock_HSI_8MHz();
	SysTick_init();

	USART1_init(9600);
//	PWM_init(50);
//  DMA_init();
	DS18_init();
//	RTC_init();
	I2C_init();
	
	USART1_sendStr("UART EN");

//	RTC_setTime(16,00);
DS1302_Init();
//DS1302_setTtime(15,05);


uint32_t start[3] = {0}; // нулевые стартовые значения 
						 // для неблокирующих задержек

 while(1) {

	USART_commands();

	if (ms_ticks - start[0] >= 1000)
	{
		DS1302_getTtime(&hour,&min,&sec);
		sprintf(string,"DS1302_Time: %02u,%02u,%02u\n\r",hour,min,sec); 
		USART1_sendStr(string);	 

		sprintf(string,"DS:%u \n\r",DS18_getData() /16 );
		USART1_sendStr(string);	

		AHT_to_USART();		
		DS18_startMeasure();

		start[0] = ms_ticks;
	}
		
	USART1_echo();

	}
}

