#ifndef DS18_H_
#define DS18_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define PA0_INPUT 	(GPIOA->MODER &= ~(0x03)) // PA0 input 
#define PA0_OUTPUT 	(GPIOA->MODER = (GPIOA->MODER & ~(0x03))| 0x01) // PA0 output 

void DS18_init();
uint8_t DS18_search();
uint8_t DS18_startMeasure();
int16_t DS18_getData();

#endif /* DS18_H_ */
