#include "i2ctest.h"

void setup (void);
void loop (void);

void setup ()
{
	STATUS_DDR |= _BV(STATUS_LED);
	STATUS_PORT &= ~_BV(STATUS_LED);
	
	logInit();

	initI2CS (0x70,
			  TX,
			  RX,
			  null);
}

void loop ()
{
	STATUS_PORT ^= _BV(STATUS_LED);
	_delay_ms(500);
}

int main (void)
{
	setup();
	while (1) loop();
	return 0;
}