#include <stdint.h>
#include "stm32f0xx.h"
#include "stm32f030x6.h"
#include "system_stm32f0xx.h"

#define TIMEOUT 1000000
uint32_t timeout;

void ADC1_init(){ // функция инициализации. 1 раз вызвать в main()

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // тактируем GPIOA
	RCC->AHBENR |= RCC_APB2ENR_ADCEN; // тактируем АЦП
	GPIOA->MODER |= (3 << 0); // переводим РА0 в 0x11 analog mode

	if (ADC1->CR & ADC_CR_ADEN){ // если включен АЦП
	ADC1->CR |= ADC_CR_ADDIS; // отключаем АЦП установкой ADDIS
	}

	timeout = TIMEOUT;
	while (ADC1->CR & ADC_CR_ADEN){ // ждем отключения АЦП

		if (--timeout ==0) return;
	}

	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; // отключаем ДМА (RM0360)
	ADC1->CR |= ADC_CR_ADCAL; // включаем калибровку

	timeout = TIMEOUT;
	while (ADC1->CR & ADC_CR_ADCAL){ // ждем окончания калибровки
	
		if (--timeout ==0) return;
	}

	if (ADC1->ISR & ADC_ISR_ADRDY){ //если бит готовности АЦП аппаратно выставлен в 1
	ADC1->ISR |= ADC_ISR_ADRDY; // очищаем бит прграммно записью в него 1
	}

	ADC1->CR |= ADC_CR_ADEN; // включаем АЦП

	timeout = TIMEOUT;
	while (!(ADC1->ISR & ADC_ISR_ADRDY)){ // Ждем готовности

		if (--timeout ==0) return;
	}

	ADC1->CHSELR  =  ADC_CHSELR_CHSEL0; // РА0 - 0 канал
	ADC1->SMPR   |=  (7 << ADC_SMPR_SMP_Pos); // самое большое время выборки - 111: 239.5 ADC clock cycles

}


uint16_t ADC1_read(){

    ADC1->CR |= ADC_CR_ADSTART; // Старт измерения АЦП
	
	timeout = TIMEOUT;
    while(!( ADC1->ISR & ADC_ISR_EOC )){ // ждем окончания измерения появлением флага ЕОС

		if (--timeout ==0) return 0;
	}
	
    uint16_t  ADC_Result = ADC1->DR; //получаем результат 
	return ADC_Result;
}


float ADC_convert_to_temp(){

	float data_adc = (ADC1_read() * 3300)/4095; // перевод результата АЦП в мВ. 
	// 3300 это Vcc
	// 4095 максимальный результат 12 бит АЦП

	float temperature = data_adc * 0.015; // перевод мВ. в градусы
	//	3300/50 = 0,015 мВ
	return temperature;
}


