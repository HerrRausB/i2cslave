#ifndef __LOG_H__
#define __LOG_H__

#include <string.h>
#include <stdlib.h>

#include <avr/interrupt.h>

#include "usart.h"

#define LOG_SIZE	128

#ifndef __LOG__
	#define logInit()
	#define logFlush()
	#define logAdd(x)
	#define logDump()
#else
	#define logInit()	_logInit()
	#define logFlush()	_logFlush()
	#define logAdd(x)	_logAdd(x)
	#define logDump()	_logDump()
#endif

void _logInit (void);
void _logFlush (void);
void _logAdd (uint8_t byte);
void _logDump (void);

#endif
