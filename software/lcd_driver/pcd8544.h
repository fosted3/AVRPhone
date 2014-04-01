#ifndef __LCD_H
#define __LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define LCD_SPI  SPIC
#define LCD_PORT PORTC.OUT
#define LCD_DDR  PORTC.DIR

#define LCD_RST 1 // Reset can be tied to chip rst in a pinch
#define LCD_CE  4 // Enable can be tied gnd
#define LCD_DC  3 // Data/Command select
#define LCD_DIN 5 // Data
#define LCD_CLK 7 // Clock

#define LCD_MASK (1<<LCD_RST) | (1<<LCD_CE) | (1<< LCD_DC) | (1<<LCD_DIN) | (1<<LCD_CLK)

#define LCD_CMD  0
#define LCD_DATA 1

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
#define DISP_NORM  0x04 // normal display mode
#define DISP_TEST  0x01 // all segments on (test) mode
#define DISP_INV   0x05 // inverted normal mode

// LCD properties
#define LCD_H 48
#define LCD_W 84

#define LCD_BUFSIZE (48*84/8)

// send 8 bits of data/cmd (cd var) to lcd
void lcdWrite(uint8_t, uint8_t);

// flush buffers, restart lcd
void lcdReset();

// flush buffers, push to lcd
void lcdClear();

// send entire new buffer to lcd
void lcdUpdate();

// send rect within buffer bounded by args to lcd (x_0,y_0) to (x_f,y_f)
// will round to full bytes in y-dir
// initial coords must be > final coords
void lcdUpdateRange(uint8_t x_0, uint8_t y_0, uint8_t x_f, uint8_t y_f);

#endif // __LCD_H
