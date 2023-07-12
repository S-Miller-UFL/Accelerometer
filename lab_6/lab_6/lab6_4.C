//*******************************************
//Lab 6, Section 3
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: allows communication with IMU
//*******************************************

/********************************DEPENDENCIES**********************************/

#include "lsm6dsl.h"
#include "lsm6dsl_registers.h"
#include <avr/io.h>
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/

int main(void)
{
	//note that this is just a test for part 4, you are not expected to turn this part in.
	spi_init();
	lsm_init();
	while(1)
	{
		lsm_read(CTRL3_C);
		lsm_read(CTRL9_XL);
		lsm_read(CTRL1_XL);
		lsm_read(INT1_CTRL);
	}

	return 0;
}