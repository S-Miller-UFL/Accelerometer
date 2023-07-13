//*******************************************
//Lab 6, Section 5
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: gets imus acceleration data
//*******************************************

/********************************DEPENDENCIES**********************************/

#include "lsm6dsl.h"
#include "lsm6dsl_registers.h"
#include <avr/io.h>
#include "spi.h"
#include "usart.h"

/*****************************END OF DEPENDENCIES******************************/

int main(void)
{
	spi_init();
	usartd0_init();
	LSM_init();
	//test code
	//this polls the imu for new data and outputs it on port A
	PORTA.DIRSET = 0xff;
	PORTA.OUTSET = 0xff;
	while(1)
	{
		//PORTA.OUT = LSM_read(OUTX_L_XL);
		//PORTA.OUT = LSM_read(OUTX_H_XL);
		//uint8_t y = OUTX_H_XL;
		//char* x = (char*)OUTX_H_XL;
		//usartd0_out_string_no_null("hello world!");
		for(int i =0; i <10; i++)
		{
			//simulate x
			usartd0_out_string_no_null(i);
			//simulate y
			usartd0_out_string_no_null(i*2 + 1);
			//simulate z
			usartd0_out_string_no_null(i*3 - 10);
			
		}
		
	}
	//end of test code
	return 0;
}