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

#include "stm32l4xx_ll_dma.h"  // Low-layer driver for DMA
#include "stm32l4xx_ll_spi.h"  // Low-layer driver for SPI

#include "LBF_lowlev_API.h"
#include "LBF_SPI3_Init.h"


// Local 'helper' functions
static void LBF_FLASH_SPI_Rx_DMA( uint8_t *pRxBuffer, uint32_t TsferLength);
static void LBF_FLASH_SPI_Tx_DMA( uint8_t *pTxBuffer, uint32_t TsferLength);
static void LBF_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);



/****************
* Function :	void LBF_FLASH_EraseBulk(void) 
* Description :	Electrically erases the full Data Flash (this takes some time)
* Parameters :  -
* Return Value:  -
****************/
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




/**************
* Function :	uint32_t LBF_FLASH_ReadID(void) 
* Description :	Returns the Unique ID read from the Data Flash
* Parameters :  -
* Return Value:  Unique ID of the Data Flash
**************/

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





/************
* Function :	
	uint8_t LBF_FLASH_SendByte(uint8_t TxByte) 
* Description :	
	Transfers a byte to the Data Flash over SPI in full-duplex mode, simultaneously receive a byte from the Flash (dummy or useful depending on context)
* Parameters :    
	TxByte (In) : the byte to send to the Data Flash
* Return Value:  
	the byte received from the Flash
************/

uint8_t LBF_FLASH_SendByte(uint8_t TxByte)
{

uint8_t RxByte = 0;


    HAL_SPI_TransmitReceive(&hspi3, &TxByte, &RxByte, 0x1, 1000);
    // SPI3, full duplex, blocking Tx/Rx of 1 byte with 1s timeout
    // (hspi3 is global)

    
    return RxByte;
}
 



/*****************
* Function :	 
	void LBF_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead) 
* Description :	
	Reads from the Data Flash, starting at the adress specified by ReadAddr, the number of data bytes specified by NumByteToRead  and places them in a buffer pointer by pBuffer. 
* Parameters :  
	> pBuffer : pointer to the buffer for storing the data bytes read from the Data Flash
	> ReadAddr :  First address to read in the Data Flash
	> NumByteToRead : Number of consecutive bytes to read from the Data Flash   
* Return Value:  -
******************/

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

/*
    while (NumByteToRead--)  // while there is data to be read 
    {
        // Read a byte from the FLASH 
        *pBuffer = LBF_FLASH_SendByte(LBF_FLASH_DUMMY_BYTE);
        // Point to the next location where the byte read will be saved 
        pBuffer++;
    }
*/
// RATHER USE DMA !!! 
    if (NumByteToRead != 0)  // looks like FatFS may make reqs for 0-length transfers ???
    {
       LBF_FLASH_SPI_Rx_DMA( pBuffer, NumByteToRead); // DMA doesn't like 0-length transfers!
    }
    

    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
}




/*********************
* Function :	 
	void LBF_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite) 
* Description :	
	Writes into the Data Flash, starting at the specified adress, the specified number of data bytes located in the buffer specified through a pointer to its head. This involved chopping the operationinto a number of a successive page accesses.
* Parameters : 
	> pBuffer : pointer to the buffer that contains the data bytes to write into the Data Flash
	> WriteAddr :  First address to write in the Data Flash
	> NumByteToWrite : Number of consecutive bytes to write into the Data Flash  
* Return Value:  -
**********************/

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



/***************
* Function :	 
	void LBF_FLASH_WaitForWriteEnd(void)
* Description :	
	Wait for all required writes into the Flash to be actually (physically) done.
* Parameters :  -
* Return Value:  -
***************/

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



// ====================================================================
// Low-level functions used only by above functions,
// ====================================================================




/*********************
* Function :	 
	void LBF_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite) 
* Description :	
	Writes into a page of the Data Flash, starting at the specified adress, the specified number of data bytes located in the buffer specified through a pointer to its head. As only full pages can physically be written onto the flash, this involves reading the full page, modiyfing the required portion and writing back the full page.
* Parameters : 
	> pBuffer : pointer to the buffer that contains the data bytes to write into the page
	> WriteAddr :  First address to write in the Data Flash (absolute, NOT relative to the start of page)
	> NumByteToWrite : Number of consecutive bytes to write into the Data Flash  
* Return Value:  -
**********************/
static void LBF_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t 	i=0;
    uint8_t 	Buffer[LBF_FLASH_PAGE_LENGTH];
    uint16_t    NumByteToWrite_Copy;
    uint8_t*    pBuffer_Copy;
    uint32_t    AddrTargetPage;


//NOTE: What's done below is actually a Read-Modify-Write operation ,
// ...so could rather use RMW opcode of Flash (see DS) for more optimization ?

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


/*
    while (NumByteToWrite--)
    {
        // Send the current byte 
        LBF_FLASH_SendByte(*pBuffer);

        // Point on the next byte to be written 
        pBuffer++;
    }
*/
// RATHER USE DMA !!! 
    if (NumByteToWrite != 0)  // looks like FatFS may make reqs for 0-length transfers ???
    {
       LBF_FLASH_SPI_Tx_DMA( pBuffer, NumByteToWrite );  // DMA doesn't like 0-length transfers!
    }
    
    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();
    
    /* Wait the end of Flash writing */
    LBF_FLASH_WaitForWriteEnd();
}



/****************
* Function :	 
	void LBF_FLASH_SPI_Rx_DMA( uint8_t *pRxBuffer, uint32_t TsferLength )
* Description :	
	Receive a data stream over SPI3 from the Flash. DMA2 peripheral is supposed to have been initialized alongside SPI3 at start of program (LBF_Board_Inits), with SPI data frame at 8bits. Signals CS is not touched.
* Parameters :  
	> pRxBuffer (In) : pointer to a buffer containing the data to receive (bytes) 
	> TsferLength (In) : number of bytes to transfer 
* Return Value:  -
***************/

static void LBF_FLASH_SPI_Rx_DMA(	uint8_t *pRxBuffer, 
				uint32_t TsferLength)  
{

uint8_t const DummyByte = 0x00;


    // -------------------------------------------------
    // Set DMA parameters: Transfer Address and Length
    // -------------------------------------------------

    // DMA configuration for SPI3 (DMA2 Channels 1 and 2)
    // was mostly done at SPI3 init (LBF_SPI3_Init.c)
    // Just need to provide pointer to Tx/Rx data and transfer length

    // In Rx mode we're only interesting in receiving data over SPI,
    // but we need to send data to activate SPI clock so we're sending dummy data (a constant)

    // Set DMA Tx to "0D" mode i.e. no address increment

    LL_DMA_ConfigTransfer(DMA2,
			LL_DMA_CHANNEL_2,            // ie SPI3 MOSI
			LL_DMA_MEMORY_NOINCREMENT ); // OD-DMA



    // ---- Tx data (dummy) / SPI3 MOSI : ----

    LL_DMA_ConfigAddresses( DMA2, LL_DMA_CHANNEL_2, 
			   (uint32_t)&DummyByte, 
			    LL_SPI_DMA_GetRegAddr(SPI3),
                            LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_2));
  
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_2, TsferLength);



    // ---- Rx data i.e. SPI3 MISO : ----

    LL_DMA_ConfigAddresses( DMA2, LL_DMA_CHANNEL_1, 
			    LL_SPI_DMA_GetRegAddr(SPI3), // PAY ATTENTION TO ORDER
			    (uint32_t)pRxBuffer,  
				// uint8_t* Rx pointer viewed as address on 32-bit by LL driver
      	                    LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_1));
  
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_1, TsferLength);


    // -------------------------------------------------
    // Launch transfer 
    // -------------------------------------------------

    // Clean up all relevant status flags 
    // DMA Tx:
    LL_DMA_ClearFlag_GI2(DMA2); // clears all Ch2 DMA2 IT flags
    // DMA Rx:
    LL_DMA_ClearFlag_GI1(DMA2); // clear all Ch1 DMA2 IT flags
    // SPI3 Overrun
    LL_SPI_ClearFlag_OVR(SPI3);

    // Note: refer to Ref Manual 38.4.8 for proper prog sequence when using DMA+SPI

    // Enable generation of DMA requests by SPI Rx
    LL_SPI_EnableDMAReq_RX(SPI3);

    // Enable relevant DMA streams :
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_1); // Rx / MISO DMA channel
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_2); // Tx / MOSI DMA channel

    // Enable generation of DMA requests by SPI Tx
    LL_SPI_EnableDMAReq_TX(SPI3);

    // Enable SPI3 :
    LL_SPI_Enable(SPI3);


    // -------------------------------------------------
    // Wait for end of DMA and clear internal IT flag
    // -------------------------------------------------

    // Here using polling of IT flags rather than IT ISR (as NVIC not configured)
    // Check if transfer complete flag on DMA2 Channel1 and 2 are set
    // or if error :

    while ( LL_DMA_IsActiveFlag_TC2(DMA2) == 0 );   // Wait for end of transmission..;
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_2);  // ...then disable Tx DMA channel


    while ( LL_DMA_IsActiveFlag_TC1(DMA2) == 0  );  // Wait for end of reception
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_1);  // ...then disable Rx DMA channel

    // wait for SPI Tx FIFO empty
    while( LL_SPI_GetTxFIFOLevel(SPI3) != LL_SPI_TX_FIFO_EMPTY   );

    // Wait for last SPI frame actually transmitted
    while ( LL_SPI_IsActiveFlag_BSY(SPI3) );

    //  Disable SPI3
    LL_SPI_Disable(SPI3);

    // Disable DMA requests from SPI3
    LL_SPI_DisableDMAReq_TX(SPI3);
    LL_SPI_DisableDMAReq_RX(SPI3);


}
 

/****************
* Function :	 
	void LBF_FLASH_SPI_Tx_DMA( uint8_t *TRxBuffer, uint32_t TsferLength )
* Description :	
	Send a data stream over SPI3 to the Flash. DMA2 peripheral is supposed to have been initialized alongside SPI3 at start of program (LBF_Board_Inits), with SPI data frame at 8bits. Signals CS is not touched.
* Parameters :  
	> pTxBuffer (In) : pointer to a buffer containing the data to send (bytes) 
	> TsferLength (In) : number of bytes to transfer 
* Return Value:  -
***************/

static void LBF_FLASH_SPI_Tx_DMA( uint8_t *pTxBuffer, 
				uint32_t TsferLength)
{

    // Tx-only, specify it to avoid issues with SPI Rx FIFO containing
    // unread data when we go out of this routine
    LL_SPI_SetTransferDirection( SPI3, LL_SPI_HALF_DUPLEX); 
    LL_SPI_SetHalfDuplexDirection( SPI3, LL_SPI_DIRECTION_HALF_DUPLEX_TX);

    // -------------------------------------------------
    // Set DMA parameters: Transfer Address and Length
    // -------------------------------------------------

    // DMA configuration for SPI3 (DMA2 Channels 1 and 2)
    // was mostly done at SPI3 init (LBF_SPI3_Init.c)
    // Just need to provide pointer to Tx/Rx data and transfer length


    // Set DMA Tx to "1D" mode in case was set to 0D by LBF_Flash_Rx_DMA()
    LL_DMA_ConfigTransfer(DMA2, 
			LL_DMA_CHANNEL_2, // ie SPI3 MOSI
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT |  // 1D-DMA
                        LL_DMA_PDATAALIGN_BYTE | 
			LL_DMA_MDATAALIGN_BYTE);


    // ---- Tx data  / SPI3 MISO : ----

    LL_DMA_ConfigAddresses( DMA2, LL_DMA_CHANNEL_2, 
			   (uint32_t)pTxBuffer, 
			    LL_SPI_DMA_GetRegAddr(SPI3),
                            LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_2));
  
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_2, TsferLength);




    // -------------------------------------------------
    // Launch transfer 
    // -------------------------------------------------

    // Clean up all relevant status flags 
    // Tx:
    LL_DMA_ClearFlag_GI2(DMA2); // clear all IT flags for Ch2 DMA2

    // Note: refer to Ref Manual 38.4.8 for prog sequence when using DMA+SPI

    // Enable relevant DMA stream :
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_2);

    // Enable generation of DMA requests by SPI Tx
    LL_SPI_EnableDMAReq_TX(SPI3);  

    // Enable SPI3 :
    LL_SPI_Enable(SPI3);  //should we disbale it first when entering this routine ???


    // -------------------------------------------------
    // Wait for end of DMA and clear internal IT flag
    // -------------------------------------------------

    // Here using polling of IT flags rather than IT ISR (as NVIC not configured)
    // Check if transfer complete flag on DMA2 Channel1 and 2 are set
    // or if error :
    while ( LL_DMA_IsActiveFlag_TC2(DMA2) == 0  )
    {
	if ( LL_DMA_IsActiveFlag_TE2(DMA2) == 1 )
	{
	   // Posible Error Handler here
	   while(1);
	}
    }

   // -------------------------------------------------
   // Stop DMA2-Ch.2 and disable SPI3 transfer
   // -------------------------------------------------
   // All 3 following disables look to be needed !


    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_2);

    // wait for FIFO empty
    while( LL_SPI_GetTxFIFOLevel(SPI3) != LL_SPI_TX_FIFO_EMPTY   );

    // Wait for last SPI frame actually transmitted
    while ( LL_SPI_IsActiveFlag_BSY(SPI3) );

    LL_SPI_Disable(SPI3);

    LL_SPI_DisableDMAReq_TX(SPI3); 

    // Restore SPI configuration     
    LL_SPI_SetTransferDirection( SPI3, LL_SPI_FULL_DUPLEX); 

    // Tx only so we didn't read Rx buffer - clear Rx overrun flag (needed?)
    LL_SPI_ClearFlag_OVR(SPI3);

}





/***************************************************************END OF FILE****/
