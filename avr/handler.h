#ifndef __HANDLER_C__
#define __HANDLER_C__

#include <stdbool.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define TX_DDR		DDRD
#define TX_PORT		PORTD
#define TX_LED		PD6

#define RX_DDR		DDRD
#define RX_PORT		PORTD
#define RX_LED		PD7

#define FLASH_DELAY	5000

void TX (uint8_t status, uint8_t * pbyte);
void RX (uint8_t status, uint8_t * pbyte);

#endif