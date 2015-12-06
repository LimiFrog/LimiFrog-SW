/*******************************************************************************
 * LBF_lsm6ds3_I2C-link.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h" //or just HAL ?

#include "LBF_lsm6ds3_I2C-link.h"

//!!!!! CAUTION
// Different interpretation of Device ID and ChipID (>>1 or not) between ST's 
// driver and LimiFrog's I2C API

/*******************************************************************************
 * @brief  : xxx
 * @param  : xxx.
 * @return : xxx.
 ******************************************************************************/
ReturnStatus_t 	LSM6DS3_IO_Init(void)
{
   // It is expected that all low level inialization of the I2C2 interface has
   // already been done prior to calling the LSM6DS3 driver, so not much to do here
   // Check chip can be accessed and who_am_i ID is read back OK

  if ( LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_WHOAMI) == 0x69)
    return OK;
  else
    return NOK;

}

/*******************************************************************************
 * @brief  : Maps IO reads from LSM6DS3 generic driver to La BlueFrog's I2C #2 
 * @param  :	pBuffer: pointer to array where to store bytes read back
 * 		DeviceAddr: I2C ChipID
 *		RegisterAddr: address of first register to access
 *		NumByteToWrite: number of successive read accesses to perform
 * @return : xxx.
 ******************************************************************************/
void	LSM6DS3_IO_Read ( 	uint8_t* pBuffer, 
				uint8_t DeviceAddr, 
				uint8_t RegisterAddr, 
				uint16_t NumByteToRead )
{
// DeviceAddr provided by generic driver is ignored, 
// we know we want to talk to LSM6DS3 anyway;
// also this solves the issue that there's a 1 bit shift between LSM6DS3_CHIPID
// and LSM6DS3_CHIPID  (different convention on conveying I2C Chip ID)

    LBF_I2CSensors_ReadMultipleReg (LSM6DS3_CHIPID, (uint16_t) RegisterAddr, pBuffer, NumByteToRead );

}


/*******************************************************************************
 * @brief  : Maps IO writes from LSM6DS3 generic driver to La BlueFrog's I2C #2 
 * @param  :	pBuffer: pointer to array containing bytes to write
 * 		DeviceAddr: I2C ChipID
 *		RegisterAddr: address of first register to access
 *		NumByteToWrite: number of successive write accesses to perform
 * @return : xxx.
 ******************************************************************************/
void	LSM6DS3_IO_Write ( 	uint8_t* pBuffer, 
				uint8_t DeviceAddr, 
				uint8_t RegisterAddr, 
				uint16_t NumByteToWrite )
{
// DeviceAddr provided by generic driver is ignored, 
// we know we want to talk to LSM6DS3 anyway;
// also this solves the issue that there's a 1 bit shift between LSM6DS3_CHIPID
// and LSM6DS3_CHIPID  (different convention on conveying I2C Chip ID)

    LBF_I2CSensors_WriteMultipleReg (LSM6DS3_CHIPID, (uint16_t) RegisterAddr, pBuffer, NumByteToWrite );

}


/***************************************************************END OF FILE****/
