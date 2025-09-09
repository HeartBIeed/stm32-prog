

#include "stm32f030x6.h"

int
main( void )
{
  // ====================
  // Setup GPIO A pin PA0
  // ====================

  // 1. Enable GPIO Port A by setting the GPIOAEN bit in the RCC AHBENR register
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

  // 2. Set MODER0[1:0] bits in the GPIOA MODER register to 0b01 to make pin PA0 function as
  // an output.
  GPIOA->MODER |= ( 0b01 << GPIO_MODER_MODER0_Pos );

  // Endless Loop
  while( 1 )
  {
    // Flip the outpout bit for PA0 in the GPIOA ODR register.
    GPIOA->ODR ^= GPIO_ODR_0;

    // Half-second delay:
    // There are about 13 instructions executed for each cycle of the for loop. We need to
    // burn 4 million cycles to make 0.5 seconds, therefore:
    // 4E6 (0.5 second) cycles / 13 = 307,692 for-loop cycles should equal about 0.5 seconds.
    for( uint32_t x=0; x<308e3; x++) ;
  }
}
