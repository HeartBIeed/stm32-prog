#ifndef DS1302_H_
#define DS1302_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
//PAn
#define DS1302_CLK  7 
#define DS1302_DIO  6 
#define DS1302_CE   5 
#define DIO_INPUT   (GPIOA->MODER &= ~(0x03 << 12)) //  input 6*2=12
#define DIO_OUTPUT  (GPIOA->MODER = (GPIOA->MODER & ~(0x03 << 12)) | (0x01<<12)) //  output 

void DS1302_Init();
void DS1302_setTtime(uint8_t hour,uint8_t min);
void DS1302_getTtime(uint8_t *hour,uint8_t *min,uint8_t *sec);


#endif /* DS1302_H_ */
