#ifndef __I2CTEST_H__
#define __I2CTEST_H__

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "i2cs.h"
#include "handler.h"

#define STATUS_DDR		DDRB
#define STATUS_PORT		PORTB
#define STATUS_LED		PB6

#endif
