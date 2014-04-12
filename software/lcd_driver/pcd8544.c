#include "pcd8544.h"

extern uint8_t lcdBuf[LCD_BUFSIZE];

inline void lcdWrite(uint8_t data, uint8_t cd) {
  LCD_PORT.OUT &= ~(1<<LCD_CE);
  // select D/~C mode
  if(cd == LCD_CMD)
    LCD_PORT.OUT  &= ~(1<<LCD_DC);
  else
    LCD_PORT.OUT|= (1<<LCD_DC);

  LCD_SPI.DATA = data;
  // wait for last xfer to complete
  while(!(LCD_SPI.STATUS & (1<<7)));
  LCD_PORT.OUT |= (1<<LCD_CE);
}

void lcdReset(){
  LCD_PORT.OUT &= ~(1<<LCD_RST);
  _delay_ms(1);
  LCD_PORT.OUT |= (1<<LCD_RST);
}

void lcdClear() {
  for (int index = 0; index < LCD_BUFSIZE; index++) {
    lcdWrite(0x00, LCD_DATA);
  }
}

void lcdUpdate(){
  lcdWrite(CMD_YADDR, LCD_CMD);
  lcdWrite(CMD_XADDR, LCD_CMD);
  for(uint16_t p = 0; p < LCD_BUFSIZE; ++p)
    lcdWrite(lcdBuf[p], LCD_DATA);
}


/*
TODO FIXME
void lcdUpdateRange(uint8_t x_0, uint8_t y_0, uint8_t x_f, uint8_t y_f){
  if(y_0 & 0xF8) { // partial byte
    ++y_0;
    y_0>>=3;
  } else
    y_0>>=3;

  lcdWrite(CMD_YADDR | y_0, LCD_CMD);
  lcdWrite(CMD_XADDR | (x_0 & 0x7F), LCD_CMD);

//  for(;y_0<y_f;++y_0){
    for(;x_0<x_f;++x_0)
      //lcdWrite(lcdBuf[x_0][y_0], LCD_DATA);
      lcdWrite(0xFF, LCD_DATA);
 // }
} */
