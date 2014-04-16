#ifndef __SD_H
#define __SD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define SD_SPI  SPIC
#define SD_PORT PORTC

#define SD_CS   2
#define SD_CLK  7
#define SD_MOSI 5
#define SD_MISO 6

#define SD_MASK (1<<SD_CS) | (1<<SD_CLK) | (1<<SD_MOSI) | (1<<SD_MISO)

// SD/MMC commands

#define CMD0	  0		    /* GO_IDLE_STATE */
#define CMD1	  1			  /* SEND_OP_COND (MMC) */
#define	ACMD41	0x80+41	/* SEND_OP_COND (SDC) */
#define CMD8	  8			  /* SEND_IF_COND */
#define CMD9	  9			  /* SEND_CSD */
#define CMD10	  10		  /* SEND_CID */
#define CMD12	  12		  /* STOP_TRANSMISSION */
#define ACMD13	0x80+13	/* SD_STATUS (SDC) */
#define CMD16	  16		  /* SET_BLOCKLEN */
#define CMD17	  17		  /* READ_SINGLE_BLOCK */
#define CMD18	  18		  /* READ_MULTIPLE_BLOCK */
#define CMD23	  23		  /* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	0x80+23	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	  24		  /* WRITE_BLOCK */
#define CMD25	  25		  /* WRITE_MULTIPLE_BLOCK */
#define CMD55	  55		  /* APP_CMD */
#define CMD58	  58		  /* READ_OCR */

#endif // __SD_H
