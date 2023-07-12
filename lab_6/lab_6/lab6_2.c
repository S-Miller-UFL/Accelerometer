//*******************************************
//Lab 6, Section 2
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: continuously sends data over spi
//*******************************************

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/


/***************************MAIN************************/
int main(void)
{
	spi_init();
	while(1)
	{
		//turn on chip select
		PORTF.OUTCLR = SS_bm;
		spi_write(0x2a);
		//turn off chip select
		PORTF.OUTSET = SS_bm;
	}
	return 0;
}