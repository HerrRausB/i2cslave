#ifndef __I2CTEST_H__
#define __I2CTEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#include "../global/i2cdefs.h"

#include "BMP085.h"

void sig_handler(int signo);
int executeDefaultProgram (void);

#endif