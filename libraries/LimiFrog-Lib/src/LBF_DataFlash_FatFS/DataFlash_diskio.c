/*******************************************************************************
 * DataFlash_diskio.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Block Size in Bytes */
#define BLOCK_SIZE 	512   /* in Bytes */  //value TBC

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* Private function prototypes -----------------------------------------------*/
DSTATUS DataFlash_DISK_initialize (void);
DSTATUS DataFlash_DISK_status (void);
DRESULT DataFlash_DISK_read (BYTE*, DWORD, BYTE);
#if _USE_WRITE == 1
  DRESULT DataFlash_DISK_write (const BYTE*, DWORD, BYTE);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT DataFlash_DISK_ioctl (BYTE, void*);
#endif /* _USE_IOCTL == 1 */
  
Diskio_drvTypeDef  DataFlash_DISK_Driver =
{
  DataFlash_DISK_initialize,
  DataFlash_DISK_status,
  DataFlash_DISK_read, 
#if  _USE_WRITE == 1
  DataFlash_DISK_write,
#endif /* _USE_WRITE == 1 */  
#if  _USE_IOCTL == 1
  DataFlash_DISK_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/


/*------------------------ Initialize a Drive ---------------------------*/
/**
  * @brief  Initializes a Drive
  * @param  None
  * @retval DSTATUS: Operation status
  */
DSTATUS DataFlash_DISK_initialize(void)
{
  Stat = STA_NOINIT;
  
  // Nothing to do
  // DataFlash has been configured earlier with LBF_Board_Init()

  Stat &= ~STA_NOINIT;
  return Stat;
}

/*------------------------- Get Disk Status -----------------------------*/
/**
  * @brief  Gets Disk Status
  * @param  None
  * @retval DSTATUS: Operation status
  */
DSTATUS DataFlash_DISK_status(void)
{
  Stat = STA_NOINIT;
    if ( (LBF_FLASH_ReadID()>>16 & 0xFF) == 0x1F )  //check ability to read manufacturer ID
    {
        Stat &= ~STA_NOINIT;
    }
  return Stat;
}

/*-------------------------- Read Sector(s) -----------------------------*/
/**
  * @brief  Reads Sector(s) 
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT DataFlash_DISK_read(BYTE* pBuff, DWORD sector, BYTE count)
{
//    DRESULT res = RES_OK;
    LBF_FLASH_ReadBuffer( (uint8_t*) pBuff, (uint32_t)(sector * BLOCK_SIZE),  (uint32_t)(BLOCK_SIZE * count));  
    return RES_OK;
}

/*--------------------------- Write Sector(s) ---------------------------*/
/**
  * @brief  Writes Sector(s)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT DataFlash_DISK_write(const BYTE *pBuff, DWORD sector, BYTE count)
{
//  DRESULT res = RES_ERROR;    
    LBF_FLASH_WriteBuffer( (uint8_t*) pBuff, (uint32_t)(sector * BLOCK_SIZE),  (uint32_t)(BLOCK_SIZE * count));  
    return RES_OK;
}
#endif /* _USE_WRITE == 1 */

/*------------------------ Miscellaneous Functions ----------------------*/

/**
  * @brief  I/O control operation
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT DataFlash_DISK_ioctl(BYTE cmd, void *buff)
{
  DRESULT res = RES_ERROR;
  
// Code to control the drive specified features
// CTRL_SYNC, GET_SECTOR_SIZE, GET_SECTOR_COUNT, GET_BLOCK_SIZE

    if (Stat & STA_NOINIT) return RES_NOTRDY;
  
    switch (cmd)
    {
    /* Make sure that no pending write process */
    case CTRL_SYNC :
      res = RES_OK; 
      break;
      //may need revisiting if changing impl of DataFlash access to use DMA      

  /* Get number of sectors on the disk (DWORD) */
    case GET_SECTOR_COUNT :
      *(DWORD*)buff = LBF_FLASH_CAPACITY / BLOCK_SIZE;
      res = RES_OK;
      break;
  
  /* Get R/W sector size (WORD) */
    case GET_SECTOR_SIZE :
      *(WORD*)buff = BLOCK_SIZE;
      res = RES_OK;
      break;
  
  /* Get erase block size in unit of sector (DWORD) */
    case GET_BLOCK_SIZE :
      *(DWORD*)buff = BLOCK_SIZE;
      break;
  
    default:
      res = RES_PARERR;

    }
  
  return res;
}

#endif /* _USE_IOCTL == 1 */
  

/********    END OF FILE  *****************************************************************/

