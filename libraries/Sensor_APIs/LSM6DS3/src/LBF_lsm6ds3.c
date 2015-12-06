/*******************************************************************************
 * Adapted by: LimiFrog, 2015
 *
 * from :
*/

/**
 ******************************************************************************
 * @file    lsm6ds3.c
 * @author  MEMS Application Team
 * @version V1.2.0
 * @date    28-January-2015
 * @brief   This file provides a set of functions needed to manage the LSM6DS3 sensor
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#include "LBF_lowlev_API.h"

#include "LBF_lsm6ds3.h"
#include "LBF_lsm6ds3_I2C-link.h"

#include <math.h>    //for obtaining ...-GetAxes from ...-GetAxes_Raw: using float

// -----------------------------------------------------------------------
// --  This code is a slightly stripped down version of ST's code
// --   and it returns fewer error status flags
// --  Physical accesses to the LSM6DS3 are invoked by functions
// --   LSM6DS3_IO_Read/Write/Init :
// --  In LimiFrog this corresponds to I2C accesses (on I2C2 ports),
// --   the mapping in done in file LBF_lsm6ds3_I2C-link.c
// -----------------------------------------------------------------------


/* NAMING CONVENTION: 
 * Parameters pertaining to the Gyroscope are identified by letter 'G' in their name
 *  Those pertaining to the Accelerometer ("X"elero phonetically) are identified 
 *    by letter 'X' in their name
 */




/**
 * @brief  Set LSM6DS3 Initialization
 * @param  LSM6DS3_InitStruct is a structure that must contain the configuration 
 *         settings for the LSM6DS3
 * @retval OK in case of success, NOK error code otherwise
 */

 ReturnStatus_t    LSM6DS3_Init( IMU_6AXES_InitTypeDef *LSM6DS3_InitStruct )
{
    /*Here we could add the check if the parameters are valid*/

    uint8_t tmp1 = 0x00;

    /* Configure the low level interface -------------------------------------*/
    if (LSM6DS3_IO_Init() == NOK )  
    {
      return NOK;   // if issue at initialization, exit here
    }


    /******** Common init *********/

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL3_C, 1);

    /* Enable register address automatically incremented during a multiple byte
       access with a serial interface (I2C or SPI) */
    tmp1 &= ~(LSM6DS3_XG_IF_INC_MASK);
    tmp1 |= LSM6DS3_XG_IF_INC;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL3_C, 1);

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_FIFO_CTRL5, 1);


    /* FIFO ODR selection */
    tmp1 &= ~(LSM6DS3_XG_FIFO_ODR_MASK);
    tmp1 |= LSM6DS3_XG_FIFO_ODR_NA;

    /* FIFO mode selection */
    tmp1 &= ~(LSM6DS3_XG_FIFO_MODE_MASK);
    tmp1 |= LSM6DS3_XG_FIFO_MODE_BYPASS;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_FIFO_CTRL5, 1);



    /******* Gyroscope init *******/

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL2_G, 1) ;

    /* Output Data Rate selection */
    tmp1 &= ~(LSM6DS3_G_ODR_MASK);
    tmp1 |= LSM6DS3_InitStruct->G_OutputDataRate;

    /* Full scale selection */
    tmp1 &= ~(LSM6DS3_G_FS_MASK);
    tmp1 |= LSM6DS3_InitStruct->G_FullScale;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL2_G, 1);

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL10_C, 1);


    /* Enable X axis selection */
    tmp1 &= ~(LSM6DS3_G_XEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->G_X_Axis;

    /* Enable Y axis selection */
    tmp1 &= ~(LSM6DS3_G_YEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->G_Y_Axis;

    /* Enable Z axis selection */
    tmp1 &= ~(LSM6DS3_G_ZEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->G_Z_Axis;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL10_C, 1);



    /***** Accelerometer init *****/

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1);

    /* Output Data Rate selection */
    tmp1 &= ~(LSM6DS3_XL_ODR_MASK);
    tmp1 |= LSM6DS3_InitStruct->X_OutputDataRate;

    /* Full scale selection */
    tmp1 &= ~(LSM6DS3_XL_FS_MASK);
    tmp1 |= LSM6DS3_InitStruct->X_FullScale;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1);

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL9_XL, 1);

    /* Enable X axis selection */
    tmp1 &= ~(LSM6DS3_XL_XEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->X_X_Axis;

    /* Enable Y axis selection */
    tmp1 &= ~(LSM6DS3_XL_YEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->X_Y_Axis;

    /* Enable Z axis selection */
    tmp1 &= ~(LSM6DS3_XL_ZEN_MASK);
    tmp1 |= LSM6DS3_InitStruct->X_Z_Axis;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL9_XL, 1);
    
    /* Configure interrupt lines */
    // LSM6DS3_IO_ITConfig();
    //TODO 

    return OK;
}


/**
 * @brief  Read ID of LSM6DS3 Accelerometer and Gyroscope
 * @param  xg_id the pointer where the ID of the device is stored
 * @retval none
 */

void    LSM6DS3_Read_XG_ID( uint8_t *xg_id)
{
    LSM6DS3_IO_Read(xg_id, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WHO_AM_I_ADDR, 1);
}



/**
 * @brief  Read raw data from LSM6DS3 Accelerometer output register
 * @param  pData the pointer where the accelerometer raw data are stored
 * @retval none
 */

void   LSM6DS3_X_GetAxesRaw( int16_t *pData )
{
    /*Here we could add the check if the parameters are valid*/
  
    uint8_t tempReg[2] = {0,0};

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_X_L_XL, 2);
    pData[0] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_Y_L_XL, 2);
    pData[1] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_Z_L_XL, 2);
    pData[2] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);
    
}



/**
 * @brief  Read data from LSM6DS3 Accelerometer and calculate linear acceleration in mg
 * @param  pData the pointer where the accelerometer data are stored
 * @retval none
 */

void   LSM6DS3_X_GetAxes( int32_t *pData )
{
    /*Here we could check if the parameters are valid*/
  
    uint8_t tempReg = 0x00;
    int16_t pDataRaw[3];
    float sensitivity = 0;

    LSM6DS3_X_GetAxesRaw(pDataRaw);

    LSM6DS3_IO_Read(&tempReg, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1);

    tempReg &= LSM6DS3_XL_FS_MASK;

    switch(tempReg)
    {
      case LSM6DS3_XL_FS_2G:
        sensitivity = 0.061;
        break;
      case LSM6DS3_XL_FS_4G:
        sensitivity = 0.122;
        break;
      case LSM6DS3_XL_FS_8G:
        sensitivity = 0.244;
        break;
      case LSM6DS3_XL_FS_16G:
        sensitivity = 0.488;
        break;
    }

    pData[0] = (int32_t)(pDataRaw[0] * sensitivity);
    pData[1] = (int32_t)(pDataRaw[1] * sensitivity);
    pData[2] = (int32_t)(pDataRaw[2] * sensitivity);
  
}



/**
 * @brief  Read raw data from LSM6DS3 Gyroscope output register
 * @param  pData the pointer where the gyroscope raw data are stored
 * @retval none
 */

void  LSM6DS3_G_GetAxesRaw( int16_t *pData )
{
    /*Here we could check if the parameters are valid*/
  
    uint8_t tempReg[2] = {0,0};

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_X_L_G, 2);
    pData[0] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_Y_L_G, 2);
    pData[1] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);

    LSM6DS3_IO_Read(&tempReg[0], LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_OUT_Z_L_G, 2);
    pData[2] = ((((int16_t)tempReg[1]) << 8)+(int16_t)tempReg[0]);
    
}


/**
 * @brief  Read data from LSM6DS3 Gyroscope and calculate angular rate in mdps
 * @param  pData the pointer where the gyroscope data are stored
 * @retval none
 */

void    LSM6DS3_G_GetAxes( int32_t *pData )
{
    /*Here we could check if the parameters are valid*/
  
    uint8_t tempReg = 0x00;
    int16_t pDataRaw[3];
    float sensitivity = 0;

    LSM6DS3_G_GetAxesRaw(pDataRaw);

    LSM6DS3_IO_Read(&tempReg, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL2_G, 1);

    tempReg &= LSM6DS3_G_FS_MASK;

    switch(tempReg)
    {
      case LSM6DS3_G_FS_125:
        sensitivity = 4.375;
        break;
      case LSM6DS3_G_FS_245:
        sensitivity = 8.75;
        break;
      case LSM6DS3_G_FS_500:
        sensitivity = 17.50;
        break;
      case LSM6DS3_G_FS_1000:
        sensitivity = 35;
        break;
      case LSM6DS3_G_FS_2000:
        sensitivity = 70;
        break;
    }

    pData[0] = (int32_t)(pDataRaw[0] * sensitivity);
    pData[1] = (int32_t)(pDataRaw[1] * sensitivity);
    pData[2] = (int32_t)(pDataRaw[2] * sensitivity);
  
}

/**
 * @brief  Read Accelero Sensitivity
 * @param  pfData the pointer where the accelerometer sensitivity is stored
 * @retval none
 */
void    LSM6DS3_X_GetSensitivity( float *pfData )
{
    /*Here we could check if the parameters are valid*/
    
    uint8_t tempReg = 0x00;
    
    
    LSM6DS3_IO_Read( &tempReg, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1 );
    
    tempReg &= LSM6DS3_XL_FS_MASK;
    
    switch( tempReg ) {
    case LSM6DS3_XL_FS_2G:
        *pfData = 0.061;
        break;
    case LSM6DS3_XL_FS_4G:
        *pfData = 0.122;
        break;
    case LSM6DS3_XL_FS_8G:
        *pfData = 0.244;
        break;
    case LSM6DS3_XL_FS_16G:
        *pfData = 0.488;
        break;
    default:
        break;
    }
    
}



/**
 * @brief  Read Gyro Sensitivity
 * @param  pfData the pointer where the gyroscope sensitivity is stored
 * @retval none
*/
void    LSM6DS3_G_GetSensitivity( float *pfData )
{
    /*Here we have to add the check if the parameters are valid*/
    
    uint8_t tempReg = 0x00;
    
    
    LSM6DS3_IO_Read( &tempReg, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL2_G, 1 );
    
    tempReg &= LSM6DS3_G_FS_MASK;
    
    switch( tempReg ) {
    case LSM6DS3_G_FS_125:
        *pfData = 4.375;
        break;
    case LSM6DS3_G_FS_245:
        *pfData = 8.75;
        break;
    case LSM6DS3_G_FS_500:
        *pfData = 17.50;
        break;
    case LSM6DS3_G_FS_1000:
        *pfData = 35;
        break;
    case LSM6DS3_G_FS_2000:
        *pfData = 70;
        break;
    default:
        break;
    }
    
}

/**
 * @brief  Enable free fall detection
 * @param  None
 * @retval none
*/
void   LSM6DS3_Enable_Free_Fall_Detection( void )
{
    uint8_t tmp1 = 0x00;
    
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1);

    /* Output Data Rate selection */
    tmp1 &= ~(LSM6DS3_XL_ODR_MASK);
    tmp1 |= LSM6DS3_XL_ODR_416HZ;

    /* Full scale selection */
    tmp1 &= ~(LSM6DS3_XL_FS_MASK);
    tmp1 |= LSM6DS3_XL_FS_2G;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_CTRL1_XL, 1);
    
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_UP_DUR, 1);

    /* FF_DUR5 setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_FF_DUR5_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_FF_DUR5_DEFAULT;

    /* WAKE_DUR setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_WAKE_DUR_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_WAKE_DUR_DEFAULT;
    
    /* TIMER_HR setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_TIMER_HR_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_TIMER_HR_DEFAULT;
    
    /* SLEEP_DUR setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_UP_DUR_SLEEP_DUR_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_UP_DUR_SLEEP_DUR_DEFAULT;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_UP_DUR, 1);
    
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_FREE_FALL, 1);

    /* FF_DUR setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_TYPICAL;

    /* FF_THS setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_312MG;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_FREE_FALL, 1);
    
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_MD1_CFG, 1);

    /* INT1_FF setting */
    tmp1 &= ~(LSM6DS3_XG_MD1_CFG_INT1_FF_MASK);
    tmp1 |= LSM6DS3_XG_MD1_CFG_INT1_FF_ENABLE;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_MD1_CFG, 1);
  
}


/**
 * @brief  Disable free fall detection
 * @param  None
 * @retval none
*/
void    LSM6DS3_Disable_Free_Fall_Detection( void )
{
    uint8_t tmp1 = 0x00;
    
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_MD1_CFG, 1);
    
    /* INT1_FF setting */
    tmp1 &= ~(LSM6DS3_XG_MD1_CFG_INT1_FF_MASK);
    tmp1 |= LSM6DS3_XG_MD1_CFG_INT1_FF_DISABLE;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_MD1_CFG, 1);

    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_FREE_FALL, 1);

    /* FF_DUR setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_DUR_DEFAULT;

    /* FF_THS setting */
    tmp1 &= ~(LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_MASK);
    tmp1 |= LSM6DS3_XG_WAKE_FREE_FALL_FF_THS_156MG;

    LSM6DS3_IO_Write(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_FREE_FALL, 1);
    
}

/**
 * @brief  Get status of free fall detection
 * @param  status the pointer where the status of free fall detection is stored; 0 means no detection, 1 means detection happened
 * @retval none
*/
void    LSM6DS3_Get_Status_Free_Fall_Detection( uint8_t *status )
{
    uint8_t tmp1 = 0x00;
   
    LSM6DS3_IO_Read(&tmp1, LSM6DS3_XG_MEMS_ADDRESS, LSM6DS3_XG_WAKE_UP_SRC, 1);
    
    tmp1 &= LSM6DS3_XG_WAKE_UP_SRC_FF_IA_MASK;
    
    switch( tmp1 )
    {
    case LSM6DS3_XG_WAKE_UP_SRC_FF_IA_ENABLE:
        *status = 1;
        break;
    case LSM6DS3_XG_WAKE_UP_SRC_FF_IA_DISABLE:
    default:
        *status = 0;
        break;
    }
    
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
