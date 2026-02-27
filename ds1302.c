#include "ds1302.h"

uint8_t DecToBSD(uint8_t chin) // 10 >> 0x10
    {
     uint8_t chout = ((chin / 10)<<4)|(chin % 10);
     return chout;
    }

uint8_t BSDtoDec(uint8_t chin) // 0x10 >> 10
    {
     uint8_t chout = ((chin >> 4 )*10) + (0b00001111 & chin);
     return chout;
    }




void DS1302_Init() {
//PA 5/6/7
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

    GPIOA->MODER &= ~((3 << (DS1302_CLK*2))|(3 << (DS1302_CE*2))); 
    GPIOA->MODER |= (1 << (DS1302_CLK*2))|(1 << (DS1302_CE*2)); 
    DIO_OUTPUT; 

    GPIOA->OSPEEDR &= ~((3 << (DS1302_CLK*2))|(3 << (DS1302_DIO*2))|(3 << (DS1302_CE*2))); 
    GPIOA->OSPEEDR |= (1 << (DS1302_CLK*2))|(1 << (DS1302_DIO*2))|(1 << (DS1302_CE*2)); 
;
}

void DS1302_Select() {
  SET_BIT(GPIOA->BSRR, 1<< DS1302_CE);    // set CE high
          _delay_us(4);

}

void DS1302_Deselect() {
  SET_BIT(GPIOA->BSRR, 1<< (DS1302_CE +16));    // set CE low
}

void DS1302_Clk() {

    SET_BIT(GPIOA->BSRR, 1<< DS1302_CLK);
        _delay_us(3);
    SET_BIT(GPIOA->BSRR, 1<< (DS1302_CLK +16)); 
}

void DS1302_TransmitByte(uint8_t byte) {
    
    DIO_OUTPUT;
    SET_BIT(GPIOA->BSRR, 1<< (DS1302_DIO +16)); // DIO - output, set low

    // transmit byte, lsb-first
    for(uint8_t i = 0; i < 8; i++) {
        if((byte >> i) & 0x01) {
            
            SET_BIT(GPIOA->BSRR, 1<< DS1302_DIO); // set high
        } else {
            
            SET_BIT(GPIOA->BSRR, 1<< (DS1302_DIO +16)); // set low
        }

    DS1302_Clk();
    }
}

uint8_t DS1302_ReceiveByte() {

    DIO_INPUT;
    // receive byte, lsb-first
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; i++) {
        if(GPIOA->IDR & (1 << DS1302_DIO)) {
            byte |= (1 << i);
        }

        DS1302_Clk();
    }
return byte;
}

void DS1302_setTtime(uint8_t hour,uint8_t min) {

   uint8_t h = DecToBSD(hour);
   uint8_t m = DecToBSD(min);

    const uint8_t bytes[8] =
      // sec   min  hour   day   mon  dow(1-7) year  wp (in BCD!)
      { 0x00, m, h, 0x27, 0x02, 0x04, 0x26 ,0x00 };

    DS1302_Select();
    
    DS1302_TransmitByte(0xBE);// 0xBE = clock burst write

    for(uint8_t i = 0; i < sizeof(bytes); i++) {
        DS1302_TransmitByte(bytes[i]);
    }

    DS1302_Deselect();
}

void DS1302_getTtime(uint8_t *hour,uint8_t *min,uint8_t *sec) {

    uint8_t bytes[8];

    DS1302_Select();
    
    DS1302_TransmitByte(0xBF);// 0xBF = clock burst read
        
        for(uint8_t i = 0; i < sizeof(bytes); i++) {
            bytes[i] = DS1302_ReceiveByte();
        }
    DS1302_Deselect();

    *hour = BSDtoDec(bytes[2]);
    *min =  BSDtoDec(bytes[1]);
    *sec =  BSDtoDec(bytes[0]);
}







