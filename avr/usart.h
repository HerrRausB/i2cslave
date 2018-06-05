/* Functions to initialize, send, receive over USART

   initUSART requires BAUD to be defined in order to calculate
     the bit-rate multiplier.
 */

#ifndef BAUD                          /* if not defined in Makefile... */
#define BAUD  19200                    /* set a safe default baud rate */
#endif

#include <avr/io.h>
#include <util/setbaud.h>
#include <stdbool.h>

                                  /* These are defined for convenience */
#define   USART_HAS_DATA   bit_is_set(UCSR0A, RXC0)
#define   USART_READY      bit_is_set(UCSR0A, UDRE0)

/* Takes the defined BAUD and F_CPU,
   calculates the bit-clock multiplier,
   and configures the hardware USART                   */
void initUSART(void);

/* Blocking transmit and receive functions.
   When you call receiveByte() your program will hang until
   data comes through.  We'll improve on this later. */
void usartTransmitByte(uint8_t data);
uint8_t usartReceiveByte(void);

void usartPrintString(const char myString[]);
             /* Utility function to transmit an entire string from RAM */
void usartReadString(char myString[], uint8_t maxLength);
/* Define a string variable, pass it to this function
   The string will contain whatever you typed over serial */

void usartPrintByte(uint8_t byte);
                  /* Prints a byte out as its 3-digit ascii equivalent */
void usartPrintWord(uint16_t word);
        /* Prints a word (16-bits) out as its 5-digit ascii equivalent */

void usartPrintBinaryByte(uint8_t byte);
                                     /* Prints a byte out in 1s and 0s */
char usartNibbleToHex(uint8_t nibble);
char usartNibbleToHexCharacter(uint8_t nibble);
void usartPrintHexByte(uint8_t byte);
                                   /* Prints a byte out in hexadecimal */
uint8_t usartGetNumber(void);
/* takes in up to three ascii digits,
 converts them to a byte when press enter */
