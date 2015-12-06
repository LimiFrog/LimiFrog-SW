/*******************************************************************************
 * LBF_FLASH_lowlevAPI.h
 ******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_FLASH_LOWLEVAPI_H
#define __LBF_FLASH_LOWLEVAPI_H

#include <stdint.h>  // to keep this header file self-sufficient as below function prototypes use uint32_t etc.
#include "LBF_pin_aliases.h" // to keep this header file self-sufficient as below macros use pin names


/* Exported constants --------------------------------------------------------*/

/* Commands for 64Mbit Flash ADESTO AT45DB641E   */
#define LBF_FLASH_CMD_WRITE1        0x82    /* Write to Page in Main Memory thru Buffer 1 with built-in page erase */
#define LBF_FLASH_CMD_WRITE2        0x85    /* Write to Page in Main Memory thru Buffer 2 with built-in page erase */
#define LBF_FLASH_CMD_READ_LF       0x03    /* Read from Memory instruction: Continuous Array, Low Frequency Mode */
#define LBF_FLASH_CMD_RDSR          0xD7       /* Read Status Register instruction  */
#define LBF_FLASH_CMD_RDID          0x9F       /* Read ID Register instruction  */
#define LBF_FLASH_CMD_PAGESIZE1     0x3D       /* "Power of 2 Page Size" instruction, Byte1  */
#define LBF_FLASH_CMD_PAGESIZE2     0x2A       /* ... Byte2  */
#define LBF_FLASH_CMD_PAGESIZE3     0x80       /* ... Byte3  */
#define LBF_FLASH_CMD_PAGESIZE4     0xA6       /* ... Byte4 - set for 512 byte size */
#define LBF_FLASH_CMD_BULKERASE1     0xC7       /* Chip Erase instruction, Byte1  */
#define LBF_FLASH_CMD_BULKERASE2     0x94       /* ... Byte2  */
#define LBF_FLASH_CMD_BULKERASE3     0x80       /* ... Byte3  */
#define LBF_FLASH_CMD_BULKERASE4     0x9A       /* ... Byte4  */

#define LBF_FLASH_DUMMY_BYTE        0xA5

#define LBF_FLASH_READY_FLAG        0x80    /* mask to extract Flash Ready/notBusy flag in status Register */

#define LBF_FLASH_PAGE_LENGTH           0x0100  // 256 bytes per page mode
#define LBF_FLASH_NUMBER_OF_PAGES	    32768   
#define LBF_FLASH_CAPACITY	(LBF_FLASH_PAGE_LENGTH * LBF_FLASH_NUMBER_OF_PAGES) // 32768 x 256B = 83888608 = 8MB = 64Mb


/* Exported Macros    --------------------------------------------------------*/
#define LBF_FLASH_CS_LOW()          GPIO_LOW(FLASH_CS_PORT, FLASH_CS_PIN)
#define LBF_FLASH_CS_HIGH()         GPIO_HIGH(FLASH_CS_PORT, FLASH_CS_PIN)


/* Exported functions --------------------------------------------------------*/

/* Higher level */
void LBF_FLASH_EraseBulk(void);
void LBF_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void LBF_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void LBF_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
uint32_t LBF_FLASH_ReadID(void);

/* Low-level */
uint8_t LBF_FLASH_SendByte(uint8_t byte);
void LBF_FLASH_WaitForWriteEnd(void);



#endif  /*__LBF_FLASH_LOWLEVAPI_H */ 

/***************************************************************END OF FILE****/
