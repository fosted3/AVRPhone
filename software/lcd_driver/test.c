#include "pcd8544.h"

uint8_t lcdBuf[LCD_BUFSIZE];

// set up the SPI hardware, then initialize the pcd8544 and clear the display
void lcdInit() {
  LCD_PORT.DIR |= LCD_MASK;
  LCD_SPI.CTRL = 0x52;

  lcdReset();

  lcdWrite(CMD_FUNC | FUNC_EXT, LCD_CMD);
  lcdWrite(CMD_VOP | 0x31, LCD_CMD);
  lcdWrite(CMD_TEMP, LCD_CMD); 
  lcdWrite(CMD_BIAS | 0x04, LCD_CMD);
  lcdWrite(CMD_FUNC, LCD_CMD);
  lcdWrite(CMD_DISP | DISP_NORM, LCD_CMD);

  lcdClear();
}

int main() {
  lcdInit();
  for (int index = 0; index < 100; index++) {
    lcdWrite(0x14, LCD_DATA);
    lcdWrite(0x7F, LCD_DATA);
    lcdWrite(0x14, LCD_DATA);
    lcdWrite(0x7F, LCD_DATA);
    lcdWrite(0x14, LCD_DATA);
  } 
  for(uint16_t p = 0; p < LCD_BUFSIZE; ++p)
    lcdBuf[p] = 0xAA;
  lcdUpdate();
}
