/*******************************************************************************
 * LBF_lsm6ds3_I2C-link.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_LSM6DS3_I2C_LINK_H
#define __LBF_LSM6DS3_I2C_LINK_H


#include "LBF_custom_types.h"  //to use custom type defs below



/* Exported functions ------------------------------------------------------- */

ReturnStatus_t	LSM6DS3_IO_Init(void) ;

void	LSM6DS3_IO_Read( 	uint8_t* pBuffer, 
				uint8_t DeviceAddr, 
				uint8_t RegisterAddr, 
				uint16_t NumByteToRead );

void	LSM6DS3_IO_Write( 
				uint8_t* pBuffer, 
				uint8_t DeviceAddr, 
				uint8_t RegisterAddr, 
				uint16_t NumByteToWrite );


#endif  /*__LBF_LSM6DS3_I2C_LINK_H*/

/***************************************************************END OF FILE****/
