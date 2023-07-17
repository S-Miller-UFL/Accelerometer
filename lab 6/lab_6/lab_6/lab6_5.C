//*******************************************
//Lab 6, Section 5
//Name: Steven Miller
//Class #: 11318
//PI Name: Anthony Stross
//Description: gets imus acceleration and gyroscopic data and outputs it to the computer
//*******************************************

/********************************DEPENDENCIES**********************************/

#include "lsm6dsl.h"
#include "lsm6dsl_registers.h"
#include <avr/io.h>
#include "spi.h"
#include "usart.h"
#include <avr/interrupt.h>

/*****************************END OF DEPENDENCIES******************************/
//flags
volatile uint8_t accel_flag;
void intr_init(void);
int main(void)
{
	accel_flag = 0;
	spi_init();
	usartd0_init();
	LSM_init();
	intr_init();
	wakeup_accel();
	//wakeup gyro
	read_gyro();
	while(1)
	{
		if(accel_flag == 1)
		{
			/*read accelerometer data*/
			uint8_t data = 0;
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
			/*read gyroscope data*/
			read_gyro();
			PORTC.INTCTRL = (PORT_INT0LVL_MED_gc);
			accel_flag = 0;
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
	//enable medium level interrupts
	PMIC.CTRL = (PMIC_MEDLVLEN_bm);
	sei();
}

void wakeup_accel(void)
{
	uint8_t data = 0;
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
	
}


//put gyroscope data here
void read_gyro()
{
	/*read gyroscope data*/
	uint8_t data = 0;
	data = LSM_read((OUTX_L_G));
	usartd0_out_char(data);
	data = LSM_read((OUTX_H_G));
	usartd0_out_char(data);
	data = LSM_read((OUTY_L_G));
	usartd0_out_char(data);
	data = LSM_read((OUTY_H_G));
	usartd0_out_char(data);
	data = LSM_read((OUTZ_L_G));
	usartd0_out_char(data);
	data = LSM_read((OUTZ_H_G));
	usartd0_out_char(data);
}