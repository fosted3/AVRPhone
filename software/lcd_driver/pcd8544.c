#include "pcd8544.h"

inline void lcdWrite(uint8_t data, uint8_t cd) {
  LCD_PORT &= ~(1<<LCD_CE);
  // select D/~C mode
  if(cd == LCD_CMD)
    LCD_PORT &= ~(1<<LCD_DC);
  else
    LCD_PORT |= (1<<LCD_DC);

  LCD_SPI.DATA = data;
  // wait for last xfer to complete
  while(!(LCD_SPI.STATUS & (1<<7)));
  LCD_PORT |= (1<<LCD_CE);
}

void lcdReset(){
  LCD_PORT &= ~(1<<LCD_RST);
  _delay_ms(1);
  LCD_PORT |= (1<<LCD_RST);
}

void lcdClear() {
  for (int index = 0; index < LCD_BUFSIZE; index++) {
    lcdWrite(0x00, LCD_DATA);
  }
}

void lcdUpdate(uint8_t *buf){
// TODO
}
