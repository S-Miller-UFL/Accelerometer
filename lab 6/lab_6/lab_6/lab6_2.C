//*******************************************
//Lab 6, Section 2
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: transmits 0x2a over mosi
//*******************************************

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/

/*****************************MAIN PROGRAM******************************/
int main()
{
	//init spi
	spi_init();
	
	//transmit 0x2a
	while(1)
	{
		//turn on chip select
		PORTF.OUTCLR = SS_bm;
		//write out to mosi
		spi_write(0x2a);
		//turn off chip select
		PORTF.OUTSET = SS_bm;
		
	}
	
	return 0;
}