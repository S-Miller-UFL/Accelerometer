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

	//restart device
	lsm_write(CTRL3_C,LSM6DSL_RESET_DEVICE_BM | LSM6DSL_INT1_MAKE_ACTIVE_LOW);
	//enable all axes
	lsm_write(CTRL9_XL,LSM6DSL_ENABLE_ALLAXIS);
	//output data rate and scale setting
	lsm_write((CTRL1_XL),((5<<4)|LSM6DSL_SCALE_2));
	//ODR = 208 HZ
	lsm_write(INT1_CTRL,LSM6DSL_DRDY_XL_EN_BM);
	/*enable interrupt detection on port c PIN 6 of atx*/
	//set pin 6 as input
	PORTC.DIRCLR = (0|PIN6_bm);
	//enable interrupts on pin 6
	PORTC.INT0MASK = (0|PIN6_bm);
	//make it sense active low
	PORTC.PIN6CTRL= (0|PORT_ISC_LEVEL_gc);
	//make it medium priority
	PORTC.INTCTRL = (0|PORT_INT0LVL_MED_gc);
}
/***************************END OF FUNCTION DEFINITIONS************************/