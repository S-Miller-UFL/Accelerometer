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


/*****************************FUNCTION DEFINITIONS*****************************/
void spi_init(void)
{
	
  /* Initialize the relevant SPI output signals to be in an "idle" state.
   * Refer to the relevant timing diagram within the LSM6DSL datasheet.
   * (You may wish to utilize the macros defined in `spi.h`.) */
  PORTF.OUTSET = (SS_bm|MOSI_bm|SCK_bm);

  /* Configure the pin direction of relevant SPI signals. */
  PORTF.DIRSET = (SS_bm|MOSI_bm|SCK_bm) ;
  PORTF.DIRCLR = (MISO_bm);
	
  /* Set the other relevant SPI configurations. */
  SPIF.CTRL	=	SPI_PRESCALER_DIV4_gc | SPI_MASTER_bm|SPI_MODE_0_gc|SPI_ENABLE_bm| SPI_CLK2X_bm;
}

void spi_write(uint8_t data)
{
	//turn on chip select
	PORTF.OUTCLR = SS_bm;
	/* Write to the relevant DATA register. */
	SPIF.DATA = data;

	/* Wait for relevant transfer to complete. */
	while(SPIF.STATUS != SPI_IF_bm)
	{
		//do nothing while we wait
	}
	//turn off chip select
	PORTF.OUTSET = SS_bm;
  /* In general, it is probably wise to ensure that the relevant flag is
   * cleared at this point, but, for our contexts, this will occur the 
   * next time we call the `spi_write` (or `spi_read`) routine. 
   * Really, because of how the flag must be cleared within
   * ATxmega128A1U, it would probably make more sense to have some single 
   * function, say `spi_transceive`, that both writes and reads 
   * data, rather than have two functions `spi_write` and `spi_read`,
   * but we will not concern ourselves with this possibility
   * during this semester of the course. */
}

uint8_t spi_read(void)
{
	/* Write some arbitrary data to initiate a transfer. */
	SPIF.DATA = 0x37;

	/* Wait for relevant transfer to be complete. */
	while(SPIF.STATUS != SPI_IF_bm)
	{
		//do nothing while we wait
	}

	/* After the transmission, return the data that was received. */
	return SPIF.DATA;
}

/***************************END OF FUNCTION DEFINITIONS************************/

/***************************MAIN************************/
int main(void)
{
	spi_init();
	while(1)
	{
		spi_write(0x2a);
	}
	return 0;
}