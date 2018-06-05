#include "i2ctest.h"

int fdI2C = 0, fdTemp;

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{	
		exit (0);
	}
}

int executeDefaultProgram (void)
{
	int retval = 0;
	
	if (!((fdI2C = open(RASPI_I2C_BUS_FILE, O_RDWR)) < 0))
	{
		printf ("open = %d\n", fdI2C);
		if (!(ioctl(fdI2C, I2C_SLAVE, WC_I2C_ADDRESS) < 0))
		{
			printf ("ioctl OK\n");
			//printf ("write = %d\n", i2c_smbus_write_byte (fdI2C, WC_I2C_CMD_DEF_PROGRAM));
			printf ("read = %d\n", i2c_smbus_read_byte (fdI2C));
			retval = 1;
		}
		close (fdI2C);
	}
	return retval;
}

int main (int argc, char * argv[])
{

	int i, success;
	uint8_t out = 0, in = 0, buffer[10];
/*
	printf ("Content-type: t/*ext/html\n\n");
	printf ("<html><head><title>Axels Balkonbew&auml;sserung</title></head>\n");
	printf ("<body ><center><h1><h1>Axels Balkonbew&auml;sserung</h1><p>\n");
	success = executeDefaultProgram();
	printf ("<img src=\"/watercontrol/%s\"><p><h1>%s\n", success?"happy.png":"sad.png",success?"Alles OK!":"Irgendwas ist schief gegangen...");
	printf ("</h1></center></body></html>");

	bmp085_Calibration();
	
	printf("Temperature\t%0.1f °C\n", (double)bmp085_ReadUT()/10);
	printf("Pressure\t%0.2f hPa\n", (double)bmp085_ReadUP()/100);
	printf("Temperature\t%0.1f °C\n", (double)bmp085_GetTemperature(bmp085_ReadUT())/10);
	printf("Pressure\t%0.2f hPa\n", (double)bmp085_GetPressure(bmp085_ReadUP())/100);
*/	

	int retval = 0;
	
	if (argc > 1)
	{
		if (!((fdI2C = open(RASPI_I2C_BUS_FILE, O_RDWR)) < 0))
		{
			printf ("open = %d\n", fdI2C);
			if (!(ioctl(fdI2C, I2C_SLAVE, WC_I2C_ADDRESS) < 0))
			{
				printf ("ioctl OK\n");
				
				uint8_t * pbytes = (uint8_t *)malloc ((argc-1)*sizeof(uint8_t));
				if (pbytes)
				{
					printf ("malloc OK\n");
					for (i = 0; i < argc-1; i++)
					{	
						pbytes[i] = atoi(argv[i+1]);
					}
					printf ("write = %d\n", i2c_smbus_write_i2c_block_data (fdI2C, 0, argc-1, pbytes));
					free (pbytes);
				}
				/*
				printf ("read = %d\n", (uint8_t)i2c_smbus_read_i2c_block_data (fdI2C, 0, sizeof(buffer), buffer));
				for (i = 0; i < sizeof(buffer); i++)
				{
					printf ("0x%02X ", buffer[i]);
				}
				printf ("\n");
				*/
			}
			close (fdI2C);
		}
	}
	return retval;
}
