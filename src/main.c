/*
 * Program to control up to 24 relays from Pi Zero
 * Uses mosquitto and wiringPi libraries
 * MQTT message payload is 2 bytes, channel (1 - 24) and relay state (0 = off, any other value = on)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

#include <wiringPi.h>
#include <modbus.h>

#include <wiringSerial.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int ret = 0, fd, count = 0, ready, a =-10, b = -20,c = -30;
	/*char ch;

	const int REMOTE_ID = 10;
	modbus_t *ctx;
	uint16_t tab_reg[10];

	ctx = modbus_new_rtu("/dev/ttyS0", 115200, 'N', 8, 1);
	if (ctx == NULL) {
	    fprintf(stderr, "Unable to create the libmodbus context\n");
	    return -1;
	}

	ret = wiringPiSetup();

	fd = serialOpen("/dev/ttyS0", 9600);

	if (fd == -1)
	{
		ret = -1;
	}

	while(true)
	{
		serialPutchar(fd, 'a' + count++);
		sleep(1);
		if (count == 10) count = 0;

		ready = serialDataAvail(fd);

		if (ready > 0)
		{
			for (int i=0; i < ready; i++)
			{
				ch = serialGetchar(fd);
				ch = toupper(ch);
				serialPutchar(fd, ch);
			}
		}
	}
	*/

	  modbus_t *mb;
	  uint16_t tab_reg[32] = {0};



	  mb = modbus_new_tcp("192.168.0.140", MODBUS_TCP_DEFAULT_PORT);

	  a = modbus_connect(mb);

	  b = modbus_set_slave(mb, 1);

	  if (b != -1)
	  {

		  a = 1;
		  while(true)
		  {
			  c = modbus_read_registers(mb, 0, 10, tab_reg);

			  if (c > 0)
			  {
				  fprintf(stderr, "Reading %d\n", a++);
				  for (int i=0; i < c; i++)
				  {
					  fprintf(stderr, "Register %d: %d\n", i, tab_reg[i]);
				  }

				  fprintf(stderr, "\n\n");
			  }

			  sleep(1);
		  }
	  }

	  /* Read 5 registers from the address 0 */

	  ret = errno;

	  modbus_close(mb);
	  modbus_free(mb);

	return ret;
}

