#include <avr/io.h>
#include <util/delay.h>

#define DELAY 100

int main(void) {

  PORTA.DIRSET = 0xFF; 
  PORTA.OUTSET = 0xAA; 

  while(1){ 
    _delay_ms(DELAY) ; 
    PORTA.OUT = PORTA.OUT ^ 1;
    _delay_ms(DELAY) ; 
  }
}


