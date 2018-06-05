#ifndef __I2CS_H__
#define __I2CS_H__

#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <i2cdefs.h>

#include "log.h"

#ifndef null
	#define null ((void *)0)
#endif

typedef void (i2c_handler_t)(uint8_t status, uint8_t * pbyte);

void initI2CS (uint8_t addr, 
               i2c_handler_t * pTXHandler,
			   i2c_handler_t * pRXHandler,
			   i2c_handler_t * pGCHandler);
			   
char * i2csStatusToString (uint8_t s);

#endif