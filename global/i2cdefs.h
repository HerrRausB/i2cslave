#ifndef __I2CDEFS_H__
#define __I2CDEFS_H__

#define WC_I2C_ADDRESS			0x70
#define WC_I2C_SPEED			100000
#define RASPI_I2C_BUS_FILE		"/dev/i2c-1"			

#define STDVAL					42

#define WC_I2C_CMD_MASK			0xF0
#define WC_I2C_PRM_MASK			0x0F

// commands

#define WC_I2C_CMD_SWITCH_ON	0x10
#define WC_I2C_CMD_SWITCH_OFF	0x20
#define WC_I2C_CMD_READ_SENSOR	0x30
#define WC_I2C_CMD_READ_BARREL	0x40
#define WC_I2C_CMD_CHECK_BARREL	0x50
#define WC_I2C_CMD_DEF_PROGRAM	0x60
#define WC_I2C_CMD_RESET		0xF0

// parameters

#define WC_I2C_PRM_VALVE1		0x00
#define WC_I2C_PRM_VALVE2		0x01
#define WC_I2C_PRM_VALVE3		0x02
#define WC_I2C_PRM_VALVE4		0x03
#define WC_I2C_PRM_VALVE5		0x04
#define WC_I2C_PRM_VALVE6		0x05
#define WC_I2C_PRM_VALVE7		0x06
#define WC_I2C_PRM_VALVE8		0x07
#define WC_I2C_PRM_5V			0x08
#define WC_I2C_PRM_12V			0x09
#define WC_I2C_PRM_PUMP			0x0A

#define WC_I2C_PRM_SENSOR1		0x00
#define WC_I2C_PRM_SENSOR2		0x01
#define WC_I2C_PRM_SENSOR3		0x02
#define WC_I2C_PRM_SENSOR4		0x03
#define WC_I2C_PRM_SENSOR5		0x04
#define WC_I2C_PRM_SENSOR6		0x05
#define WC_I2C_PRM_SENSOR7		0x06
#define WC_I2C_PRM_SENSOR8		0x07
#define WC_I2C_PRM_BARREL		0x08
#define WC_I2C_PRM_ALL_SENSORS	0x09

// responses

#define WC_I2C_RSP_TYPE_OK		0x00
#define WC_I2C_RSP_TYPE_ERROR	0x10

#define WC_I2C_RSP_NONE			0x00
#define WC_I2C_RSP_RESET		0x0F

#define WC_I2C_ERR_NO_WATER		0x01
#define WC_I2C_ERR_NO_READING	0x02
#define WC_I2C_ERR_NOT_YET_IMP	0x0D
#define WC_I2C_ERR_INVALID_PRM	0x0E
#define WC_I2C_ERR_INVALID_CMD	0x0F

#define _getcmd(x) (x & WC_I2C_CMD_MASK)
#define _getprm(x) (x & WC_I2C_PRM_MASK)
#define _iserror(x) ((x&WC_I2C_CMD_MASK)==WC_I2C_RSP_TYPE_ERROR)
#define _getrsp(x) (x & WC_I2C_PRM_MASK)

#endif
