#include "handler.h"

volatile uint8_t _byte = 0;
volatile bool _isInit = false;

void _initHandlers (void);

void _initHandlers (void)
{
	if (!_isInit)
	{
		TX_DDR |= _BV(TX_LED);
		TX_PORT &= ~_BV(TX_LED);
		RX_DDR |= _BV(RX_LED);
		RX_PORT &= ~_BV(RX_LED);
	}
}

void TX (uint8_t status, uint8_t * pbyte)
{
	*pbyte = _byte++;
}

void RX (uint8_t status, uint8_t * pbyte)
{
	_byte = *pbyte;
}
