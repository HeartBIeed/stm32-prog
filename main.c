#include "stm32f0xx.h"
#include "stm32f030x6.h"
#include "core_cm0.h"


int main(void) {
    // ¬ключаем тактирование GPIOC
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // PC8 в режим выхода
    GPIOC->MODER &= ~(3 << (8 * 2));
    GPIOC->MODER |=  (1 << (8 * 2));

    while (1) {
        GPIOC->ODR ^= (1 << 8);  // мигаем ножкой
        for (volatile int i = 0; i < 100000; i++);
    }
}