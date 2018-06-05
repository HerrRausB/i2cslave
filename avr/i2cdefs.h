#ifndef __I2C_DEFS_H__
#define __I2C_DEFS_H__

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)

	// interrupt handling
	#define I2C_TWINT_VECT				TWI_vect
	
	// registers
	#define I2C_REG_TWAR				TWAR	// slaeaddress register
	#define I2C_REG_TWCR				TWCR	// control register
	#define I2C_REG_TWSR				TWSR	// status register
	#define I2C_REG_TWDR				TWDR	// data register
	
	// enable / disable I2C hardware
	#define I2C_ENABLE					I2C_REG_TWCR=(_BV(TWEA)|_BV(TWEN)|_BV(TWIE))
	#define I2C_DISABLE					I2C_REG_TWCR&=~(_BV(TWEA)|_BV(TWEN)|_BV(TWIE))
	
	// general utilites
	#define I2C_CONFIRM(acknack)		I2C_REG_TWCR=acknack?I2C_REG_TWCR|_BV(TWEA):I2C_REG_TWCR&~_BV(TWEA)
	#define I2C_SET_ACK					I2C_CONFIRM(true)
	#define I2C_SET_NACK				I2C_CONFIRM(false)
	
	// slave address
	#define I2C_ADDR_MASK				0xFE
	#define I2C_MAKE_ADDR(addr,gcr)		(((addr<<1)&I2C_ADDR_MASK)|(gcr?0x01:0x00))

	// status reading
	#define I2C_STATUS_MASK				0xF8
	#define I2C_STATUS					(I2C_REG_TWSR&I2C_STATUS_MASK)
	
	// general status values
	#define I2C_BUS_ERROR						0x00	// something really nasty happened...
	#define I2C_NO_RELEVANT_STATE_INFO			0xF8	// nothing happened - be patient and wait :-)
	
	// status values for slave transmitter mode as defined in datasheet for ATMEGA328P
	#define I2C_STM_SLA_R_REVCD_ACK				0xA8	// read requested by master, ACK returned --> data byte to TWDR 
	#define I2C_STM_ARB_LOST_SLA_R_REVCD_ACK	0xB0	// arbitration lost as master, read requested by other master, ACK returned --> data byte to TWDR 
	#define I2C_STM_BYTE_TRANS_ACK_RVCVD		0xB8	// data byte transmitted, ACK received --> next data byte to TWDR 
	#define I2C_STM_BYTE_TRANS_NACK_RVCVD		0xC0	// data byte transmitted, NACK received --> no TWDR action
	#define I2C_STM_LAST_BYTE_TRANS_ACK_RVCVD	0xC8	// last data byte transmitted, ACK received --> no TWDR action
	
	// possible responses (to bewritten into TWCR by interrupt handler) as defined in datasheet for ATMEGA328P
	#define I2C_STM_RSP_GENERAL				_BV(TWINT)	// always stay in not addressed slave mode
	#define I2C_STM_RSP_START				_BV(STA)	// transmit start condition when bus becomes free
	#define I2C_STM_RSP_REC_OWN_SLA			_BV(TWEA)	// recognize own slave address
	
	// status values for slave receiver mode as defined in datasheet for ATMEGA328P
	#define I2C_SRM_SLA_W_REVCD_ACK				0x60	// write requested by master, ACK returned --> no TWDR action
	#define I2C_SRM_ARB_LOST_SLA_W_REVCD_ACK	0x68	// arbitration lost as master, write requested by master, ACK returned --> no TWDR action
	#define I2C_SRM_GCA_RECVD_ACK				0x70	// general call address reveved,ACK returned --> no TWDR action
	#define I2C_SRM_ARB_LOST_GCA_RECVD_ACK		0x78	// arbitration lost as master, general call address reveved,ACK returned --> no TWDR action
	#define I2C_SRM_BYTE_RECVD_ACK_RTND			0x80	// data byte received, ACK returned --> read data byte from TWDR
	#define I2C_SRM_BYTE_RECVD_NACK_RTND		0x88	// data byte received, NACK returned --> read data byte from TWDR
	#define I2C_SRM_GC_BYTE_RECVD_ACK_RTND		0x90	// general call data byte received, ACK returned --> read data byte from TWDR
	#define I2C_SRM_GC_BYTE_RECVD_NACK_RTND		0x98	// general call data byte received, NACK returned --> read data byte from TWDR
	#define I2C_SRM_STOP_REP_START_RECVD		0xA0	// stop or repeated start received --> no TWDR action

	// possible responses (to bewritten into TWCR by interrupt handler) as defined in datasheet for ATMEGA328P
	#define I2C_SRM_RSP_GENERAL				_BV(TWINT)	// always stay in not addressed slave mode
	#define I2C_SRM_RSP_START				_BV(STA)	// transmit start condition when bus becomes free
	#define I2C_SRM_RSP_REC_OWN_SLA			_BV(TWEA)	// recognize own slave address
	#define I2C_SRM_RSP_REC_OWN_ACK			_BV(TWEA)	// reply with ACK (or NACK as default)
	
#elif defined (__AVR_ATtiny2313__) || defined (__AVR_ATtiny2313A__)

	// to be done on demand
	#error *** ATTiny2313 not yet supported by this implementation of I²C

#elif defined (__AVR_ATtiny25__) || defined (__AVR_ATtiny45__) || defined (__AVR_ATtiny85__)

	// to be done on demand
	#error *** ATTinyx5 not yet supported by this implementation of I²C

#elif defined (__AVR_ATtiny24__) || defined (__AVR_ATtiny44__) || defined (__AVR_ATtiny84__)

	// to be done on demand
	#error *** ATTinyx4 not yet supported by this implementation of I²C

#else

	// never :-)
	#error *** Current AVR platform not supported by this implementation of I²C

#endif	

#endif
