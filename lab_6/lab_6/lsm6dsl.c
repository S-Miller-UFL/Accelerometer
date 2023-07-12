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

uint8_t lsm_read(uint8_t reg_addr)
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
void lsm_init(void)
{
	//restart device
	spi_write(CTRL3_C);
	spi_write(LSM6DSL_RESET_DEVICE_BM);
	//enable all axes
	spi_write(CTRL9_XL);
	spi_write(LSM6DSL_ENABLE_ALLAXIS);
	//output data rate and scale setting
	spi_write((CTRL1_XL));
	//ODR = 208 HZ
	spi_write(((5<<4)|LSM6DSL_SCALE_2));
	spi_write(INT1_CTRL);
	spi_write(LSM6DSL_DRDY_XL_EN_BM);
	//enable interrupt detection on port c PIN 7 of atx
	PORTC_DIRCLR = (0|ATX128A1U_IMU_INT1_PIN_BM);
	PORTC_PIN7CTRL= (0| ATX128A1U_RISING_EDGE_SENSE);
}
/***************************END OF FUNCTION DEFINITIONS************************/