#include <util/delay.h>
#include "i2cs.h"
#include "handler.h"
#include "usart.h"

/* private */

void _defTXHandler (uint8_t status, uint8_t * pbyte);
void _defRXHandler (uint8_t status, uint8_t * pbyte);
void _defGCHandler (uint8_t status, uint8_t * pbyte);


i2c_handler_t * _pTXHandler = _defTXHandler;
i2c_handler_t * _pRXHandler = _defRXHandler;
i2c_handler_t * _pGCHandler = _defGCHandler;

uint8_t dummy = 42;

void _defTXHandler (uint8_t status, uint8_t * pbyte)
{
	*pbyte = dummy;
}

void _defRXHandler (uint8_t status, uint8_t * pbyte)
{
	dummy = *pbyte;
}

void _defGCHandler (uint8_t status, uint8_t * pbyte)
{
	dummy = *pbyte;
}

ISR (I2C_TWINT_VECT) 
{
	uint8_t	byteTWSR = I2C_STATUS,
			byteTWDR = 0;
	
	logAdd(byteTWSR);

	switch (byteTWSR)
	{
		// transmitter mode:
		case I2C_STM_ARB_LOST_SLA_R_REVCD_ACK:
		case I2C_STM_SLA_R_REVCD_ACK :			
		case I2C_STM_BYTE_TRANS_ACK_RVCVD :
		{
			_pTXHandler (byteTWSR, &byteTWDR);
			I2C_REG_TWDR = byteTWDR;
			I2C_REG_TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
			logAdd(byteTWDR);
			break;
		}
	
		// receiver mode:
		case I2C_SRM_BYTE_RECVD_NACK_RTND :	
		case I2C_SRM_BYTE_RECVD_ACK_RTND :
		{
			byteTWDR = I2C_REG_TWDR;
			_pRXHandler (byteTWSR, &byteTWDR);
			I2C_REG_TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
			logAdd(byteTWDR);
			break;
		}
		
		// general call mode:
		case I2C_SRM_GC_BYTE_RECVD_NACK_RTND :	
		case I2C_SRM_GC_BYTE_RECVD_ACK_RTND :
		{
			byteTWDR = I2C_REG_TWDR;
			_pGCHandler (byteTWSR, &byteTWDR);
			I2C_REG_TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
			logAdd(byteTWDR);
			break;
		}

		// no state:
		
		case I2C_BUS_ERROR :
		{
			I2C_REG_TWCR = 0;
			I2C_REG_TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
			break; // catch this for good measure...
		}
		default : // bus error and everything we dont handle yet
		{    
			I2C_REG_TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
		}
	}
}

/* API */

/*
char * i2csStatusToString (uint8_t s)
{
#ifdef __DEBUG__
	if ((s >= I2C_SRM_SLA_W_REVCD_ACK) && (s <= I2C_STM_LAST_BYTE_TRANS_ACK_RVCVD))
	{
		return _byteTWSRDefs[(s>>3) - (I2C_SRM_SLA_W_REVCD_ACK>>3)];
	}
	else
#endif
	{
		sprintf (_byteTWSRBuffer, "0x%02X", s);
		return _byteTWSRBuffer;
	}	
}
*/

void initI2CS (uint8_t addr, 
               i2c_handler_t * pTXHandler,
			   i2c_handler_t * pRXHandler,
			   i2c_handler_t * pGCHandler)
{	
	if (pTXHandler != null) _pTXHandler = pTXHandler;
	if (pRXHandler != null) _pRXHandler = pRXHandler;
	if (pGCHandler != null) _pGCHandler = pGCHandler;
	
	logDump();
	logFlush();

	I2C_REG_TWAR = I2C_MAKE_ADDR(addr, pGCHandler != null);
//	I2C_REG_TWAR = (addr << 1);
	I2C_REG_TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
	sei();
}