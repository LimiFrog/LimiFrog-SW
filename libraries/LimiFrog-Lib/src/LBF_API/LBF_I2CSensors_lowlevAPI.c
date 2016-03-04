/*******************************************************************************
 * LBF_I2CSensors_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"



/**********
* Function :	
	void LBF_I2CSensors_WriteSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegVal)
* Description :	
	Writes the specified value  at the specified address of the sensor identified by I2C address ChipID (transactions occur over I2C bus #2, dedicated to sensors on LimiFrog).
* Parameters :  
	> ChipID : 7-bit I2C address of the target chip
	> RegAdd : Address of the target register in the target chip's memory map
	> RegVal : Register value to write
* Return Value:  -
**********/

void LBF_I2CSensors_WriteSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegVal)
{

uint16_t MemAddSize = I2C_MEMADD_SIZE_8BIT;


/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/

    //VL6180X uses 16-bit register addressing, other sensors on board use 8 bit
    if (ChipID==VL6180X_CHIPID)
    {
        MemAddSize = I2C_MEMADD_SIZE_16BIT;
    }

    // I2C2, blocking write into 1 register with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Write( &hi2c2, (uint16_t) (ChipID<<1), RegAdd,  
                               MemAddSize, &RegVal, 0x1, 1000) ;

}



/************
* Function :	
	void LBF_I2C_Sensors_WriteMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToWrite ) 
* Description :		
	Write the sequence of NumByteToWrite values located in a buffer pointed by pVal into consecutive addresses starting at address RegAdd of the sensor identified by I2C address ChipID (transactions occur over I2C bus #2, dedicated to sensors on LimiFrog).
* Parameters :  
	> ChipID : 7-bit I2C address of the target chip
	> RegAdd : Address of the first target register in the target chip's memory map
	> pVal : pointer to a buffer that contains the sequence of values to write 
	>  NumByteToWrite : number of consecutive bytes to write into the target chip
* Return Value:  -
*************/

void  LBF_I2CSensors_WriteMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToWrite )
{

uint16_t MemAddSize = I2C_MEMADD_SIZE_8BIT;

/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/

    //VL6180X uses 16-bit register addressing, other sensors on board use 8 bit
    if (ChipID==VL6180X_CHIPID)
    {
        MemAddSize = I2C_MEMADD_SIZE_16BIT;
    }

    // I2C2, blocking write into 'Nb' successive registers with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Write( &hi2c2, (uint16_t) (ChipID<<1), RegAdd,  
                               MemAddSize, pVal, NumByteToWrite, 1000) ;
  
}


/**********
* Function :	
	void LBF_I2CSensors_ReadSingleReg (uint8_t ChipID, uint16_t RegAdd)
* Description :	
	Return value read from address RegAdd of the sensor identified by I2C address ChipID (transactions occur over I2C bus #2, dedicated to sensors on LimiFrog).
* Parameters :  
	> ChipID : 7-bit I2C address of the target chip
	> RegAdd : Address of the target register in the target chip's memory map
* Return Value:  the value read from the target register
**********/

uint8_t LBF_I2CSensors_ReadSingleReg (uint8_t ChipID, uint16_t RegAdd)
{

uint8_t RegVal = 0;
uint16_t MemAddSize = I2C_MEMADD_SIZE_8BIT;


/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/

    //VL6180X uses 16-bit register addressing, other sensors on board use 8 bit
    if (ChipID==VL6180X_CHIPID)
    {
        MemAddSize = I2C_MEMADD_SIZE_16BIT;
    }

    // I2C2, read 1 register in blocking mode with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Read( &hi2c2, (uint16_t)(ChipID<<1), RegAdd,
                               MemAddSize, &RegVal, 0x1, 1000);

    return RegVal;
}





/************
* Function :	
	void LBF_I2C_Sensors_ReadMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToWrite ) 
* Description :		
	Read the sequence of NumByteToRead values starting at address RegAdd of the sensor identified by I2C address ChipID and place them in a buffer pointed by pVal (transactions occur over I2C bus #2, dedicated to sensors on LimiFrog).
* Parameters :  
	> ChipID : 7-bit I2C address of the target chip
	> RegAdd : Address of the first target register in the target chip's memory map
	> pVal : pointer to a buffer where to store the sequence of values read back from the target chip  
	>  NumByteToWrite : number of consecutive bytes to read from the target chip
* Return Value:  -
*************/

void LBF_I2CSensors_ReadMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToRead )
{


uint16_t MemAddSize = I2C_MEMADD_SIZE_8BIT;


/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/

    //VL6180X uses 16-bit register addressing, other sensors on board use 8 bit
    if (ChipID==VL6180X_CHIPID)
    {
        MemAddSize = I2C_MEMADD_SIZE_16BIT;
    }

    // I2C2, read 1 register in blocking mode with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Read( &hi2c2, (uint16_t)(ChipID<<1), RegAdd,
                               MemAddSize, pVal, NumByteToRead, 1000);

}



/**********
* Function :	
	void 	LBF_I2C_Sensors_RmodWSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegMask, uint8_t RegUpdateVal)
* Description :	
	Read value RegVal from address RegAdd of the sensor identified by I2C address ChipID, overwrite bits indicated by RegMask (positions with bit set at 1 in RegMask) with corresponding bits of RegUpdateVal, and write back the result at RegAdd (transactions occur over I2C bus #2, dedicated to sensors on LimiFrog).
* Parameters :  -
* Return Value:  -
***********/

void LBF_I2CSensors_RmodWSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegMask, uint8_t RegUpdateVal)
{

uint8_t RegVal = 0;
uint16_t MemAddSize = I2C_MEMADD_SIZE_8BIT;

    //VL6180X uses 16-bit register addressing, other sensors on board use 8 bit
    if (ChipID==VL6180X_CHIPID)
    {
        MemAddSize = I2C_MEMADD_SIZE_16BIT;
    }


    // Read the register
    HAL_I2C_Mem_Read( &hi2c2, (uint16_t)(ChipID<<1), RegAdd,
                               MemAddSize, &RegVal, 0x1, 1000);

    // Update read value according to mask and update bits
    RegVal =  (RegVal & ~(RegMask)) | (RegUpdateVal & RegMask) ;

    // Write back result
    HAL_I2C_Mem_Write( &hi2c2, (uint16_t) (ChipID<<1), (uint16_t) RegAdd,  
                               MemAddSize, &RegVal, 0x1, 1000) ;
  
}



/***************************************************************END OF FILE****/
