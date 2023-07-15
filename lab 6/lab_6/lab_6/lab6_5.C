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
#include <avr/interrupt.h>

/*****************************END OF DEPENDENCIES******************************/
volatile uint8_t accel_flag;
void intr_init(void);
int main(void)
{
	spi_init();
	usartd0_init();
	LSM_init();
	intr_init();
	uint8_t data = 0;
	accel_flag = 0;
	/*
	data = LSM_read((OUTX_L_XL));
	data = LSM_read((OUTX_L_XL));
	usartd0_out_char(data);
	data = LSM_read((OUTX_H_XL));
	usartd0_out_char(data);
	data = LSM_read((OUTY_L_XL));
	usartd0_out_char(data);
	data = LSM_read((OUTY_H_XL));
	usartd0_out_char(data);
	data = LSM_read((OUTZ_L_XL));
	usartd0_out_char(data);
	data = LSM_read((OUTZ_H_XL));
	usartd0_out_char(data);
	*/
	while(1)
	{
		if(accel_flag == 1)
		{
			//send out data
			//spi data register
			data = LSM_read((OUTX_L_XL));
			//data = LSM_read((OUTX_L_XL));
			usartd0_out_char(data);
			data = LSM_read((OUTX_H_XL));
			usartd0_out_char(data);
			data = LSM_read((OUTY_L_XL));
			usartd0_out_char(data);
			data = LSM_read((OUTY_H_XL));
			usartd0_out_char(data);
			data = LSM_read((OUTZ_L_XL));
			usartd0_out_char(data);
			data = LSM_read((OUTZ_H_XL));
			usartd0_out_char(data);
			accel_flag = 0;
			PORTC_INTCTRL = (0|PORTC_INT0MASK);
		}
	}
	return 0;
}

ISR(PORTC_INT0_vect)
{
	//disable interrupt
	PORTC_INTCTRL = (0 & PORTC_INT0MASK);
	accel_flag = 1;
	//reti();
}

void intr_init(void)
{
	PMIC.CTRL = (PMIC_MEDLVLEN_bm);
	sei();
}


//put gyroscope data here