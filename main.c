#include "stm32f0xx.h"
#include "stm32f030x6.h"
#include "core_cm0.h"


void _init(void){}

int main(void)
{
    // Включаем тактирование порта A
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Настраиваем PA0 как выход (MODER = 01)
    GPIOA->MODER &= ~(0x3 << (0 * 2)); // Сбрасываем биты
    GPIOA->MODER |=  (0x1 << (0 * 2)); // Устанавливаем выход

    while(1)
    {
        GPIOA->ODR ^= GPIO_ODR_0; // Инвертируем состояние PA0
  for (volatile int i = 0; i < 8000; i++);

    }
}


