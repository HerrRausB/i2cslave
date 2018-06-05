#include "log.h"

#ifdef __LOG__
	#include "i2cdefs.h"
	
	#warning *** this will use a lot of memory!
	char * _byteTWSRDefs[] =
	{
		"I2C_SRM_SLA_W_REVCD_ACK",
		"I2C_SRM_ARB_LOST_SLA_W_REVCD_ACK",
		"I2C_SRM_GCA_RECVD_ACK",
		"I2C_SRM_ARB_LOST_GCA_RECVD_ACK",
		"I2C_SRM_BYTE_RECVD_ACK_RTND",
		"I2C_SRM_BYTE_RECVD_NACK_RTND",
		"I2C_SRM_GC_BYTE_RECVD_ACK_RTND",
		"I2C_SRM_GC_BYTE_RECVD_NACK_RTND",
		"I2C_SRM_STOP_REP_START_RECVD",
		"I2C_STM_SLA_R_REVCD_ACK",
		"I2C_STM_ARB_LOST_SLA_R_REVCD_ACK",
		"I2C_STM_BYTE_TRANS_ACK_RVCVD",
		"I2C_STM_BYTE_TRANS_NACK_RVCVD",
		"I2C_STM_LAST_BYTE_TRANS_ACK_RVCVD"
	};
#endif

char * i2csStatusToString (uint8_t s)
{
#ifdef __LOG__
	if ((s >= I2C_SRM_SLA_W_REVCD_ACK) && (s <= I2C_STM_LAST_BYTE_TRANS_ACK_RVCVD))
	{
		return _byteTWSRDefs[(s>>3) - (I2C_SRM_SLA_W_REVCD_ACK>>3)];
	}
	else
#endif
	{
		return "";
	}	
}
	
uint8_t _log[LOG_SIZE+1];

ISR(INT0_vect)
{
	cli();
	logDump();
	sei();
}

void _logInit (void)
{
	logFlush();
	EICRA |= _BV(ISC01) | _BV(ISC00);
	EIMSK |= _BV(INT0);
	sei();
}

void _logFlush (void)
{
	memset (_log, LOG_SIZE+1, 0);
}

void _logAdd (uint8_t byte)
{
	if (_log[LOG_SIZE] < LOG_SIZE)
	{
		_log[_log[LOG_SIZE]] = byte;	
		(_log[LOG_SIZE])++;
	}
}

void _logDump (void)
{	
	uint8_t i, log, logpos = _log[LOG_SIZE];
	char buf[10];
	
	usartPrintString ("\033[2J\033[;H");
	usartPrintString("I2C slave log with ");
	itoa (logpos, buf, 10);
	usartPrintString (buf);
	usartPrintString(" entries...\013\015");

	for (i = 0; i < logpos; i++)
	{
		usartPrintByte (i+1);
		usartPrintString (": 0x");
		usartPrintHexByte (_log[i]);
		usartPrintString (" (");
		usartPrintString (i2csStatusToString (_log[i]));
		usartPrintString (")\013\015");
	}
}
