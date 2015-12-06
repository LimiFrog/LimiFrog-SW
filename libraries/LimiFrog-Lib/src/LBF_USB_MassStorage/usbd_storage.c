/*
 * Adapted by LimiFrog/CYMEYA, 2015
 * for using the on-board Data Flash as storage medium
 * From STM example provided as part of package STM32Cube_FW_L4_V1.1.0
*/
/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Src/usbd_storage.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Memory management layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "usbd_libs.h"
#include "LBF_lowlev_API.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define STORAGE_LUN_NBR                  1  
#define STORAGE_BLK_NBR                  0x10000  // in ST's code but not used anywhere?
#define STORAGE_BLK_SIZ                  0x200    //  512 bytes - needs updating ?

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* USB Mass storage Standard Inquiry Data */
int8_t STORAGE_Inquirydata[] = { /* 36 */
  /* LUN 0 */
  0x00,		
  0x80,		
  0x02,		
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,	
  0x00,
  'C', 'Y', 'M', 'E', 'Y', 'A', ' ', ' ', /* Manufacturer: 8 bytes  */
  'L', 'i', 'm', 'i', 'F', 'r', 'o', 'g', /* Product     : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0','1',                      /* Version     : 4 Bytes  */
}; 

/* Private function prototypes -----------------------------------------------*/
int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);

USBD_StorageTypeDef USBD_DISK_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata, 
};

/* Private functions ---------------------------------------------------------*/


/*-------   Storage Medium :  Initialization     -------------------*/
/**
  * @brief  Initailizes the storage unit (medium)       
  * @param  lun: Logical unit number
  * @retval Status (0 : Ok / -1 : Error)
  */
int8_t STORAGE_Init(uint8_t lun)
{
    if ( (LBF_FLASH_ReadID()>>16 & 0xFF) == 0x1F )  //check manufacturer ID
    {
       return 0;
    }
       else
    {
       return -1;
    }
}


/*-------   Storage Medium :  Capacity     ------------------------*/
/**
  * @brief  Returns the medium capacity.      
  * @param  lun: Logical unit number
  * @param  block_num: Number of total block number
  * @param  block_size: Block size
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_GetCapacity(	uint8_t lun, 
				uint32_t *block_num, 
				uint16_t *block_size)
{
    *block_num =  LBF_FLASH_CAPACITY/STORAGE_BLK_SIZ  - 1;
    *block_size = STORAGE_BLK_SIZ; 
    // LBF_FLASH_CAPACITY is defined in LBF_FLASH_lowlevAPI.h
    // STORAGE_BLK_SIZE is defined at top of this file

     return 0;
}


/*-------   Storage Medium :  Readiness     ------------------------*/
/**
  * @brief  Checks whether the medium is ready.  
  * @param  lun: Logical unit number
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_IsReady( uint8_t lun )
{
    // Non amovible medium
    // Always ready in present configuration if initialized correctly
    return 0;
}


/*-------   Storage Medium :  Write Protection     ------------------*/
/**
  * @brief  Checks whether the medium is write protected.
  * @param  lun: Logical unit number
  * @retval Status (0: write enabled / -1: otherwise)
  */
int8_t STORAGE_IsWriteProtected( uint8_t lun )
{
  return 0;
}


/*-------   Storage Medium :  READ                  ------------------*/
/**
  * @brief  Reads data from the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_Read(	uint8_t lun, 
			uint8_t *buf, 
			uint32_t blk_addr, 
			uint16_t blk_len)
{
    LBF_FLASH_ReadBuffer( buf, blk_addr * STORAGE_BLK_SIZ,  blk_len * STORAGE_BLK_SIZ);
    return 0; 
}


/*-------   Storage Medium :  WRITE                  ------------------*/
/**
  * @brief  Writes data into the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0 : Ok / -1 : Error)
  */
int8_t STORAGE_Write(	uint8_t lun, 
			uint8_t *buf, 
			uint32_t blk_addr, 
			uint16_t blk_len)
{
    LBF_FLASH_WriteBuffer( buf, blk_addr * STORAGE_BLK_SIZ,  blk_len * STORAGE_BLK_SIZ);
    return 0;
}


/*-------   Storage Medium :  Supported LUNs                  ------------------*/
/**
  * @brief  Returns the Max Supported LUNs.   
  * @param  None
  * @retval Lun(s) number
  */
int8_t STORAGE_GetMaxLun(void)
{
  return(STORAGE_LUN_NBR - 1);    // defined at top of this file 
} 
 



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

