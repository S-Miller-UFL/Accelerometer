//*******************************************
//Lab 6, Section 3
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: gets imus id number
//*******************************************

/********************************DEPENDENCIES**********************************/

#include "lsm6dsl.h"
#include "lsm6dsl_registers.h"
#include <avr/io.h>
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/

int main(void)
{
	spi_init();
	//read "who am i?" register
	while(1)
	{
		uint8_t identity = lsm_read(WHO_AM_I);

	}
	//uint8_t identity = lsm_read(WHO_AM_I);

	return 0;
}