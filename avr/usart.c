
/*
  Quick and dirty functions that make serial communications work.

  Note that usartReceiveByte() blocks -- it sits and waits _forever_ for
   a byte to come in.  If you're doing anything that's more interesting,
   you'll want to implement this with interrupts.

   initUSART requires BAUDRATE to be defined in order to calculate
     the bit-rate multiplier.  9600 is a reasonable default.

  May not work with some of the older chips:
    Tiny2313, Mega8, Mega16, Mega32 have different pin macros
    If you're using these chips, see (e.g.) iom8.h for how it's done.
    These old chips don't specify UDR0 vs UDR1.
    Correspondingly, the macros will just be defined as UDR.
*/

#include "usart.h"

void _initUSART(void);

bool _usartIsInit = false;

void initUSART (void)
{
	_initUSART();
}

void _initUSART(void) 						/* requires BAUD */
{                                

	if (_usartIsInit) return;

	UBRR0H = UBRRH_VALUE;					/* defined in setbaud.h */
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif
	/* Enable USART transmitter/usartReceiver */
//	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	/* 8 data bits, 1 stop bit */

	_usartIsInit = true;
}


void usartTransmitByte(uint8_t data) 
{
	_initUSART();
	/* Wait for empty transmit buffer */
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;							/* send data */
}

uint8_t usartReceiveByte(void) 
{
	_initUSART();
	loop_until_bit_is_set(UCSR0A, RXC0);	/* Wait for incoming data */
	return UDR0;							/* return register value */
}


                       /* Here are a bunch of useful usartPrinting commands */

void usartPrintString(const char myString[]) 
{
	uint8_t i = 0;
	while (myString[i]) 
	{
		usartTransmitByte(myString[i]);
		i++;
	}
}

void usartReadString(char myString[], uint8_t maxLength) 
{
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1))			/* prevent over-runs */
	{
		response = usartReceiveByte();
		usartTransmitByte(response);			/* echo */
		if (response == '\r')			/* enter marks the end */
		{
			break;
		}
		else 
		{
			myString[i] = response;		/* add in a letter */
			i++;
		}
	}
	myString[i] = 0;					/* terminal NULL character */
}

void usartPrintByte(uint8_t byte) 
{
	/* Converts a byte to a string of decimal text, sends it */
	usartTransmitByte('0' + (byte / 100));		/* Hundreds */
	usartTransmitByte('0' + ((byte / 10) % 10));	/* Tens */
	usartTransmitByte('0' + (byte % 10));		/* Ones */
}

void usartPrintWord(uint16_t word) 
{
	usartTransmitByte('0' + (word / 10000));			/* Ten-thousands */
	usartTransmitByte('0' + ((word / 1000) % 10));	/* Thousands */
	usartTransmitByte('0' + ((word / 100) % 10));	/* Hundreds */
	usartTransmitByte('0' + ((word / 10) % 10));		/* Tens */
	usartTransmitByte('0' + (word % 10));			/* Ones */
}

void usartPrintBinaryByte(uint8_t byte) 
{
	/* Prints out a byte as a series of 1's and 0's */
	uint8_t bit;
	for (bit = 7; bit < 255; bit--) 
	{
		if (bit_is_set(byte, bit))
		{
			usartTransmitByte('1');
		}
		else
		{
			usartTransmitByte('0');
		}
	}
}

char usartNibbleToHexCharacter(uint8_t nibble) {
	/* Converts 4 bits into hexadecimal */
	return (nibble < 10)  ? ('0' + nibble) : ('A' + nibble - 10);
}

void usartPrintHexByte(uint8_t byte) {
	/* Prints a byte as its hexadecimal equivalent */
	usartTransmitByte(usartNibbleToHexCharacter((byte & 0xF0) >> 4));
	usartTransmitByte(usartNibbleToHexCharacter(byte & 0x0F));
}

uint8_t usartGetNumber(void) {
	// Gets a numerical 0-255 from the serial port.
	// Converts from string to number.
	char hundreds = '0';
	char tens = '0';
	char ones = '0';
	char thisChar = '0';
	do {							/* shift over */
		hundreds = tens;
		tens = ones;
		ones = thisChar;
		thisChar = usartReceiveByte();	/* get a new character */
		usartTransmitByte(thisChar);		/* echo */
	} 
	while (thisChar != '\r');		/* until type return */
	return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
