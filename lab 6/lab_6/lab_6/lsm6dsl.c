/*------------------------------------------------------------------------------
  lsm6dsl.c --
  
  Description:
    Brief description of file.
	  
	  Extended description, if appropriate.
  
  Author(s):
  Last modified by: Dr. Eric M. Schwartz
  Last modified on: 8 Mar 2023
------------------------------------------------------------------------------*/

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include "lsm6dsl.h"
#include "lsm6dsl_registers.h"
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/


/*****************************FUNCTION DEFINITIONS*****************************/

void lsm_write(uint8_t reg_addr, uint8_t data)
{
	//enable imu by enabling chip select
	PORTF.OUTCLR = SS_bm;
	//send over the address bits
	//keep in mind that writing to an address in the imu takes 16 cycles(16 bits of data need to be shifted)
	//the first bit of the 8 bit address is the strobe bit. Which tells the imu whether we wanna read or write.
	//1= read, 0 = write
	spi_write(reg_addr|LSM6DSL_SPI_WRITE_STROBE_bm);
	//our spi master data register is now filled with junk data,
	//we now send out the data we wanna store in the imu.
	spi_write(data);
	//disable imu by disabling chip select
	PORTF.OUTSET = SS_bm;
}

uint8_t LSM_read(uint8_t reg_addr)
{
	//enable imu by enabling chip select
	PORTF.OUTCLR = SS_bm;
	//send over the address bits
	//keep in mind that reading from an address in the imu takes 16 cycles(16 bits of data need to be shifted)
	//the first bit of the 8 bit address is the strobe bit. Which tells the imu whether we wanna read or write.
	//1= read, 0 = write
	spi_write(reg_addr|LSM6DSL_SPI_READ_STROBE_bm);
	//our spi master data register is now filled with junk data,
	//we need to perform another read so we can activate the clock and recieve our desired data
	spi_read();
	//disable imu by disabling chip select
	PORTF.OUTSET = SS_bm;
	return SPIF.DATA;
	
}
void LSM_init(void)
{
	/*enable interrupt detection on port c PIN 6 of atx*/
	//set pin 6 as input
	PORTC.DIRCLR = (PORTC.DIRCLR|PIN6_bm);
	//enable interrupts on pin 6
	PORTC.INT0MASK = (PORTC.INT0MASK|PIN6_bm);
	//make it sense low level
	PORTC.PIN6CTRL= (PORTC.PIN6CTRL|PORT_ISC_LEVEL_gc);
	//make it medium priority
	PORTC.INTCTRL = (PORTC.INTCTRL|PORT_INT0LVL_MED_gc);
	
	//restart device
	lsm_write(CTRL3_C,LSM6DSL_RESET_DEVICE_BM);
	//make interrupts active low
	lsm_write(CTRL3_C,LSM6DSL_INT1_MAKE_ACTIVE_LOW);
	//enable all axes
	lsm_write(CTRL9_XL,LSM6DSL_ENABLE_ALLAXIS);
	//output data rate and scale setting
	lsm_write((CTRL1_XL),(LSM6DSL_208HZ|LSM6DSL_SCALE_2));
	//enable interrupt 1 for accel
	lsm_write(INT1_CTRL,LSM6DSL_DRDY_XL_EN_BM);
	//output data rate and scale setting
	lsm_write((CTRL2_G),(LSM6DSL_208HZ|LSM6DSL_SCALE_2));
	//enable interrupt 2 for gyro
	lsm_write(INT2_CTRL,LSM6DSL_DRDY_GY_EN_BM);
	
	
	
}


/***************************END OF FUNCTION DEFINITIONS************************/