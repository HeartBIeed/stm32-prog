#ifndef DMA_H_
#define DMA_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void DMA_init();
void DMA_uart1_Tx(uint8_t *data, uint16_t len);
void DMA_uart1_Rx(uint32_t len);

#endif /* DMA_H_ */
