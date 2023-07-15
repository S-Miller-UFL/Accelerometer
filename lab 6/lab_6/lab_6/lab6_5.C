//*******************************************
//Lab 6, Section 5
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: gets imus acceleration data and outputs it to the computer
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
	wakeup_imu();
	while(1)
	{
		if(accel_flag == 1)
		{
			accel_flag = 0;
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
			PORTC.INTCTRL = (PORT_INT0LVL_MED_gc);
		}
	}
	return 0;
}

ISR(PORTC_INT0_vect)
{
	//disable interrupt
	PORTC.INTCTRL = (0);
	accel_flag = 1;
}

void intr_init(void)
{
	PMIC.CTRL = (PMIC_MEDLVLEN_bm);
	sei();
}

void wakeup_imu(void)
{
	uint8_t data = 0;
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
	
}

//put gyroscope data here