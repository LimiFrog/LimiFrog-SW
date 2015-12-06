/*******************************************************************************
 * LBF_FLASH_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "LBF_lowlev_API.h"
#include "LBF_SPI3_Init.h"

 /* 
 *        +--------------------------------------------------------------+
 *        |                     Pin assignment                           |
 *        +-----------------------------+------------------+-------------+
 *        |  STM32 SPI Pins             | Adesto FLASH     |    Pin      |
 *        +-----------------------------+------------------+-------------+
 *        | FLASH_CS_PIN                | ChipSelect(/CS)  |    4        |
 *        | FLASH_SPI_MISO_PIN / MISO   | SerialDataOut(SO)|    8        |
 *        | (VCC)                       | WriteProtect(/WP)|    5        |
 *        |                             | GND              |    7 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | SerialDataIn(SI) |    1        |
 *        | FLASH_SPI_SCK_PIN / SCK     | SerialClock(SCK) |    2        |
 *        | (VCC)                       | /RESET           |    3        |
 *        |                             | VCC              |    6 (3V)   |
 *        +-----------------------------+------------------+-------------+
 * 
 ******************************************************************************/




/*******************************************************************************
 * @brief  : Ecrit une page en memoire (256 octets) en une seul fois.
 * @note   : le nombre d'octet ecrit ne peut pas depasser une page de FLASH.
 * @param  : pBuffer: pointeur sur le buffer contenant les donnees a ecrire en 
 *           memoire FLASH.
 * @param  : WriteAddr: addresse ou ecrire les donnees.
 * @param  : NumByteToWrite: nombre d'octet a ecrire en memoire FLASH, doit 
 *           etre egal ou inferieur a la taille d'une page de FLASH.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t 	i=0;
    uint8_t 	Buffer[LBF_FLASH_PAGE_LENGTH];
    uint16_t    NumByteToWrite_Copy;
    uint8_t*    pBuffer_Copy;
    uint32_t    AddrTargetPage;


    /* Read full page and update relevant portions */
    NumByteToWrite_Copy = NumByteToWrite;
    pBuffer_Copy = pBuffer;
    AddrTargetPage = (WriteAddr/LBF_FLASH_PAGE_LENGTH) * LBF_FLASH_PAGE_LENGTH;
    LBF_FLASH_ReadBuffer(Buffer, AddrTargetPage, LBF_FLASH_PAGE_LENGTH);
    while (NumByteToWrite_Copy--)
    {
       Buffer[i+(WriteAddr-AddrTargetPage)] = *pBuffer_Copy;
       pBuffer_Copy++;
       i++;
    }

     /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();    

    /* Send "Write to Memory " instruction (through Buffer1 with built-in PAGE ERASE) */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_WRITE1);


    /* Send WriteAddr high nibble address byte to write to */
    LBF_FLASH_SendByte( (WriteAddr&0xFF0000)>>16);  
    /* Send WriteAddr medium nibble address byte to write to */
    LBF_FLASH_SendByte( (WriteAddr&0xFF00)>>8); 
    /* Send WriteAddr low nibble address byte to write to */
    LBF_FLASH_SendByte( WriteAddr&0xFF);  

   
    /* while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /* Send the current byte */
        LBF_FLASH_SendByte(*pBuffer);
        /* Point on the next byte to be written */
        pBuffer++;
    }
    
    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
    
    /* Wait the end of Flash writing */
    LBF_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
 * @brief  : Ecrit un block de donnees en memoire. On décompose ce bloc en pages
 *           à écrire, éventuellement partiellement pour la 1ére et la dernière
 * @param  : pBuffer: pointeur sur le buffer contenant les donnees a ecrire en 
 *           memoire FLASH.
 * @param  : WriteAddr: addresse ou ecrire les donnees.
 * @param  : NumByteToWrite: nombre d'octet a ecrire en memoire FLASH.
 * @return : Rien.
 *******************************************************************************/
void LBF_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
    uint16_t NumOfPages = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % LBF_FLASH_PAGE_LENGTH;
    count = LBF_FLASH_PAGE_LENGTH - Addr;
    NumOfPages =  NumByteToWrite / LBF_FLASH_PAGE_LENGTH;
    NumOfSingle = NumByteToWrite % LBF_FLASH_PAGE_LENGTH;
    
    if (Addr == 0) // WriteAddr is LBF_FLASH_PAGE_LENGTH aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < LBF_FLASH_PAGE_LENGTH
        {
            LBF_FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else // NumByteToWrite > LBF_FLASH_PAGE_LENGTH
        {
            while (NumOfPages--)
            {
                LBF_FLASH_WritePage(pBuffer, WriteAddr, LBF_FLASH_PAGE_LENGTH);
                WriteAddr +=  LBF_FLASH_PAGE_LENGTH;
                pBuffer += LBF_FLASH_PAGE_LENGTH;
            }
            
            LBF_FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else // WriteAddr is not LBF_FLASH_PAGE_LENGTH aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < LBF_FLASH_PAGE_LENGTH
        {
            if (NumOfSingle > count) // (NumByteToWrite + WriteAddr) > LBF_FLASH_PAGE_LENGTH
            {
                temp = NumOfSingle - count;
                
                LBF_FLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;
                
                LBF_FLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                LBF_FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else // NumByteToWrite > LBF_FLASH_PAGE_LENGTH
        {
            NumByteToWrite -= count;
            NumOfPages =  NumByteToWrite / LBF_FLASH_PAGE_LENGTH;
            NumOfSingle = NumByteToWrite % LBF_FLASH_PAGE_LENGTH;
            
            LBF_FLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;
            
            while (NumOfPages--)
            {
                LBF_FLASH_WritePage(pBuffer, WriteAddr, LBF_FLASH_PAGE_LENGTH);
                WriteAddr +=  LBF_FLASH_PAGE_LENGTH;
                pBuffer += LBF_FLASH_PAGE_LENGTH;
            }
            
            if (NumOfSingle != 0)
            {
                LBF_FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/*******************************************************************************
 * @brief  : Lit un block de donnees en memoire FLASH.
 * @param  : pBuffer: pointeur sur le buffer qui recoit les donnees a lire en 
 *           memoire FLASH.
 * @param  : ReadAddr: addresse ou les donnees sont lues.
 * @param  : NumByteToRead: nombre d'octet a lire de la memoire FLASH.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{

   /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();
    
    /* Send "Read from Memory " instruction (Continous array read, Low Frequency mode so no dummy byte after address) */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_READ_LF);

    /* Send WriteAddr high nibble address byte to read from */
    LBF_FLASH_SendByte((ReadAddr&0xFF0000)>>16);

    /* Send WriteAddr medium nibble address byte to read from */
    LBF_FLASH_SendByte((ReadAddr&0xFF00)>>8); 


    /* Send WriteAddr low nibble address byte to read from */
    LBF_FLASH_SendByte(ReadAddr&0xFF);

    
    while (NumByteToRead--) /* while there is data to be read */
    {
        /* Read a byte from the FLASH */
        *pBuffer = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
        /* Point to the next location where the byte read will be saved */
        pBuffer++;
    }
    
    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
}

/*******************************************************************************
 * @brief  : Lit l'identifiant de la memoire FLASH.
 * @param  : Aucun.
 * @return : Identification (ID) de la memoire FLASH.
 ******************************************************************************/
uint32_t LBF_FLASH_ReadID(void)
{
    uint8_t Temp0 = 0, Temp1 = 0, Temp2 = 0;
    uint32_t Temp = 0;
    
    /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();
    /* Send "RDID " instruction */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_RDID);
    /* Read a byte from the FLASH */
    Temp0 = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
    /* Read a byte from the FLASH */
    Temp1 = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
    /* Read a byte from the FLASH */
    Temp2 = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
    
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}


/*******************************************************************************
 * @brief  : Envoi un octet vers la Flash avec le SPI et retourne un octet lu.
 * @param  : byte: octet a envoyer.
 * @return : La valeur de l'octet recu.
 ******************************************************************************/

uint8_t LBF_FLASH_SendByte(uint8_t TxByte)
{

uint8_t RxByte = 0;

    HAL_SPI_TransmitReceive(&hspi3, &TxByte, &RxByte, 0x1, 1000);
    // SPI3, full duplex, blocking Tx/Rx of 1 byte with 1s timeout
    // (hspi3 is global)
    
    return RxByte;
}
 

/*******************************************************************************
 * @brief  : Efface completement la memoire FLASH.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_EraseBulk(void)
{
 
    /* Bulk Erase */
    /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();

    /* Send Full Flash Erase instructions  */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_BULKERASE1);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_BULKERASE2);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_BULKERASE3);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_BULKERASE4);

    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
    
    /* Wait until Flash ready */
    LBF_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
 * @brief  : Attend que le processus d'ecriture dans la Flash se termine.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;
    
    /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();
    
    /* Send "Read Status Register" instruction */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_RDSR);
    
    /* Loop as long as the memory is busy  */
    do
    {
        /* Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in LBF_FLASH_Status variable */
        flashstatus = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
    }
    while ((flashstatus & LBF_FLASH_READY_FLAG) != 0x80); /* Not ready, write still in progress */
    
    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
}



/***************************************************************END OF FILE****/
