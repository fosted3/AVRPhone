#include "sd.h"

inline void writeSD(uint8_t d){
  SD_SPI.DATA = d;
  (!(SD.STATUS & (1<<7)));
}

inline void selectSD(){
    SD_PORT.OUT &= ~(1<<SD_CS);
}

inline void deselectSD(){
  SD_PORT.OUT =| (1<<SD_CS);
  // clock out dummy byte so card will release MISO
  SD_SPI.DATA = 0xFF;
  while(!(SD.STATUS & (1<<7)));
}

void sendCommand(uint8_t cmd, uint32_t arg){
  writeSD(cmd | 0x40);

  writeSD(arg>>24);writeSD(arg>>16);writeSD(arg>>8);writeSD(arg);
}
