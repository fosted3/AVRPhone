#ifndef __LCD_H
#define __LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define LCD_SPI  SPIC
#define LCD_PORT PORTC.OUT
#define LCD_DDR  PORTC.DIR

#define LCD_RST // Reset can be tied to chip rst in a pinch
#define LCD_CE  PC4 // Enable can be tied gnd
#define LCD_DC  // Data/Command select
#define LCD_DIN PC5 // Data
#define LCD_CLK PC7 // Clock

#define LCD_CMD  1
#define LCD_DATA 0

// LCD command bases - variables |'d to these
#define CMD_FUNC  0x20  // function set
#define CMD_DISP  0x08  // display control
#define CMD_YADDR 0x40 // set ram y addr
#define CMD_XADDR 0x80 // set ram x addr

// LCD command bases - extended instruction mode (FUNC_EXT set)
#define CMD_TEMP 0x04  // set temperature coefficient
#define CMD_BIAS 0x10  // set bias system
#define CMD_VOP  0x80   // write Vop register

// function set options
#define FUNC_POWER 0x04 // powerdown control
#define FUNC_VERT  0x02 // set vertical addressing
#define FUNC_EXT   0x01 // extended mode

// display control options
#define DISP_BLANK 0x00 // blank display
#define DISP_NORM  0x20 // normal display mode
#define DISP_TEST  0x01 // all segments on (test) mode
#define DISP_INV   0x05 // inverted normal mode

// LCD properties
#define LCD_H 48
#define LCD_W 84

// send 8 bits of data/cmd (cd var) to lcd
void lcdWrite(uint8_t & data, uint8_t & cd);

// flush buffers, restart lcd
void lcdReset();

// flush buffers, push to lcd
void lcdClear();

// send entire new buffer to lcd - may be able to offload most of this
void lcdUpdate(uint8_t *buf);

#endif // __LCD_H
