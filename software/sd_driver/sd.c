#include "sd.h"

inline uint8_t tradeByte(uint8_t d){
  SD_SPI.DATA = d;
  while(!(SD_SPI.STATUS & (1<<7)));
  return SD_SPI.DATA;
}

inline void selectSD(){
    SD_PORT.OUT &= ~(1<<SD_CS);
}

inline void deselectSD(){
  SD_PORT.OUT |= (1<<SD_CS);
  // clock out dummy byte so card will release MISO
  SD_SPI.DATA = 0xFF;
  while(!(SD_SPI.STATUS & (1<<7)));
}

uint8_t sendCommand(uint8_t cmd, uint32_t arg){
  tradeByte(cmd | 0x40);
  tradeByte(arg>>24);tradeByte(arg>>16);tradeByte(arg>>8);tradeByte(arg);

  // hardcoded CRC values for CMD0 and CMD8
  if(cmd == CMD0)
    tradeByte(0x95);
  else if (cmd == CMD8)
    tradeByte(0x87);
  else
    tradeByte(0xFF);
  
  
  uint8_t i = 0;
  uint8_t buf = 0;
  while((buf = tradeByte(0xFF) == 0xFF) && (i < 9))
    ++i;

  // throw away CRC and anything else
  while(tradeByte(0xFF) != 0xFF); 

  return buf;
}

int8_t initSD() {
  uint8_t _buf = 0;
  uint32_t _OCR = 0;

  // Deselect SD card and clock >74 times
  deselectSD();
  for(uint8_t i; i < 10; ++i)
    tradeByte(0xFF);
  
  // bring the card up, attempt to init
  selectSD();
  _buf = sendCommand(CMD0, 0x00);
  if(_buf != 0x01)
    return _buf;

  _buf = sendCommand(CMD8, 0x000001AA);

  if(_buf != 0x05) { // 0x05 -- illegal cmd, therefore SDv1/MMC
    if(_buf != 0x01)
      return -1; // init error
    else {
      _OCR =  (uint32_t)tradeByte(0xFF) << 24;
      _OCR |= (uint32_t)tradeByte(0xFF) << 16;
      _OCR |= (uint32_t)tradeByte(0xFF) << 8;
      _OCR |= (uint32_t)tradeByte(0xFF);
    }
    if((_OCR & 0xFFF) != 0x1AA)
      return -3; // OCR error
  }

  // now wait for internal init
  // TODO - add timeout!
  while(sendCommand(CMD1, 0x00) != 0x00);

  _buf = sendCommand(CMD16, 512); // sector size
  if(_buf != 0x00)
    return -4; // TODO - put these in the header. 
  else
    return 0;
}
