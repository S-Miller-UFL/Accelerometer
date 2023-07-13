#ifndef LSM6DSL_H_  // Header guard.
#define LSM6DSL_H_
 
/*------------------------------------------------------------------------------
  lsm6dsl.h --
  
  Description:
    Provides custom data types to make it easier to handle any data
    read from the LSM6DSL IMU. 
	  
	  The LSM6DSL can output accelerometer and gyroscope data. Data from both
    of these sensors is represented in a 16-bit signed format. 
  
  Author(s): Wesley Piard & Leslye Castillo & Dr. Eric M. Schwartz
  Last modified by: Dr. Eric M. Schwartz
  Last modified on: 29 June 2022
------------------------------------------------------------------------------*/


/***********************************MACROS*************************************/

#define LSM6DSL_SPI_READ_STROBE_bm 				0x80
#define LSM6DSL_SPI_WRITE_STROBE_bm				0x00
#define LSM6DSL_SPI_READ_STROBE_bm 				0x80
#define LSM6DSL_SPI_WRITE_STROBE_bm				0x00
//Miller, july 12 2023: added macros here:
#define LSM6DSL_RESET_DEVICE_BM	(0x01<<0)
#define LSM6DSL_ENABLE_XAXIS (0X01 << 7)
#define LSM6DSL_ENABLE_YAXIS (0X01 << 6)
#define LSM6DSL_ENABLE_ZAXIS (0X01 << 5)
#define LSM6DSL_ENABLE_ALLAXIS (LSM6DSL_ENABLE_XAXIS|LSM6DSL_ENABLE_YAXIS|LSM6DSL_ENABLE_ZAXIS)
#define LSM6DSL_SCALE_2 ((0X00 <<3) |(0X00 << 2))
#define LSM6DSL_SCALE_16 ((0X00 <<3) |(0X01 << 2))
#define LSM6DSL_SCALE_4 ((0X01 <<3) |(0X00 << 2))
#define LSM6DSL_SCALE_8 ((0X01 <<3) |(0X01 << 2))
#define LSM6DSL_DRDY_XL_EN_BM (0X01<<0)
#define ATX128A1U_IMU_INT1_PIN_BM (0x01 <<6)
#define ATX128A1U_IMU_INT2_PIN_BM (0x01 <<7)
#define ATX128A1U_RISING_EDGE_SENSE (0X01 <<0)

/********************************END OF MACROS*********************************/

#include <avr/io.h>
/*******************************CUSTOM DATA TYPES******************************/

/* Used to differentiate the accelerometer and gyroscope within the LSM6DSL. */
typedef enum {LSM6DSL_ACCEL, LSM6DSL_GYRO} lsm6dsl_module_t;

/* Can be used to contain the separated bytes of data as they are read from
 * the LSM6DSL. */
typedef struct lsm6dsl_data_raw
{
  uint8_t accel_x_low, accel_x_high;
  uint8_t accel_y_low, accel_y_high;
  uint8_t accel_z_low, accel_z_high;

  uint8_t gyro_x_low, gyro_x_high;
  uint8_t gyro_y_low, gyro_y_high;
  uint8_t gyro_z_low, gyro_z_high;
}lsm6dsl_data_raw_t;

/* Contains the full concatenated signed 16-bit words of data. */
typedef struct lsm6dsl_data_full
{
  int16_t accel_x, accel_y, accel_z;
  int16_t gyro_x, gyro_y, gyro_z;
}lsm6dsl_data_full_t;

/* Provides the ability to choose how to access the LSM6DSL data. */
typedef union lsm6dsl_data
{
  lsm6dsl_data_full_t  word;
  lsm6dsl_data_raw_t   byte;
}lsm6dsl_data_t;

/***************************END OF CUSTOM DATA TYPES***************************/


/*****************************FUNCTION PROTOTYPES******************************/

void LSM_write(uint8_t reg_addr, uint8_t data);
uint8_t LSM_read(uint8_t reg_addr);
void LSM_init(void);
/**************************END OF FUNCTION PROTOTYPES**************************/

#endif // End of header guard.
