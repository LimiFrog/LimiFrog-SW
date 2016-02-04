/*******************************************************************************
 * LFB_OLED_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

#include "LBF_lowlev_API.h"
#include "GUI.h"  // to use emWin API in LBF_OLED_Printxxx

// To use low-level drivers rather than HAL :
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_spi.h"


// #include "LBF_Global.h"


/*******************************************************************************
 * @brief  : Send a byte on SPI1 output, simultaneously receive a byte on SPI input.
 * @param  : octet: byte to send.
 * @return : valoe of byte received.
 ******************************************************************************/
uint8_t LBF_OLED_SPI_TransferByte (uint8_t TxByte)
{

uint8_t RxByte = 0;


    HAL_SPI_Transmit(&hspi1, &TxByte, 0x1, 10);
    // SPI1, full duplex, blocking Tx/Rx of 1 byte with 10ms timeout
    // (hspi1 is global)


    return RxByte;
}


/*******************************************************************************
 * @brief  : Send a data stream on SPI1 output (MOSI)
 * @param  : pTxBuffer: address of first byte to send.
 *	     TxLength: number of bytes to send
 * @return : none.
 ******************************************************************************/

/*******************************************************************************
 * @brief  : Send a data stream on SPI1 output (MOSI), 16-bit wide
 * @param  : pTxBuffer: address of first half-word to send.
 *	     TxLength: number of half-word to send
 * @return : none.
 ******************************************************************************/

void LBF_OLED_SPI1_16bTransferStream_DMA1Ch3 (uint16_t* pTxBuffer, uint32_t TxLength)
{


    // -------------------------------------------------
    // Set DMA parameters: Transfer Address and Length
    // -------------------------------------------------

    // DMA configuration for SPI1 (DMA1 Channel3, Tx only)
    // was mostly done at SPI1 init (LBF_SPI1_Init.c)
    // Just need to provide pointer to Tx data and transfer length

    LL_DMA_ConfigAddresses( DMA1, LL_DMA_CHANNEL_3, 
			    (uint32_t)pTxBuffer,  // uintxx_t* pointer viewed as address on 32-bit by LL driver
			    LL_SPI_DMA_GetRegAddr(SPI1),
                            LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
  
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, TxLength);


    // -------------------------------------------------
    // Launch transfer 
    // -------------------------------------------------

    // Clean up all relevant status flags 
    LL_DMA_ClearFlag_TE3(DMA1); // clear Transfer Error flag Ch3 DMA1
    LL_DMA_ClearFlag_TC3(DMA1); // clear Transfer Complete Flag Ch3 DMA1
    // LL_DMA_ClearFlag_GI3(DMA1); // clear Global IT flag Ch3 DMA1


    // Note: refer to Ref Manual 38.4.8 for proper prog sequence when using DMA+SPI

    // Enable relevant DMA stream :
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    // Enable generation of DMA requests by SPI
    LL_SPI_EnableDMAReq_TX(SPI1);

    // Enable SPI1 :
    LL_SPI_Enable(SPI1);

    // -------------------------------------------------
    // Wait for end of DMA and clear internal IT flag
    // -------------------------------------------------


    // Here using polling of IT flags rather than IT ISR (as NVIC not configured)
    // Check if transfer complete flag on DMA1 Channel3 is set
    // or if error :
    while ( LL_DMA_IsActiveFlag_TC3(DMA1) == 0)
    {
	if (LL_DMA_IsActiveFlag_TE3(DMA1) == 1) 
	{
	   // Posible Error Handler here
	   while(1);
	}
    }



   // -------------------------------------------------
   // Stop DMA1-Ch.3 and disable SPI1 transfer
   // -------------------------------------------------
   // All 3 following disables look to be needed !

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);


    // wait for FIFO empty
    while( LL_SPI_GetTxFIFOLevel(SPI1) != LL_SPI_TX_FIFO_EMPTY   );

    // Wait for last SPI frame actually transmitted
    while ( LL_SPI_IsActiveFlag_BSY(SPI1) );

    LL_SPI_Disable(SPI1);
    LL_SPI_DisableDMAReq_TX(SPI1);


}


/*
void LBF_OLED_SPI1_TransferStream_DMA1Ch3 (uint8_t* pTxBuffer, uint32_t TxLength)
{


    // -------------------------------------------------
    // Set DMA parameters: Transfer Address and Length
    // -------------------------------------------------

    // DMA configuration for SPI1 (DMA1 Channel3, Tx only)
    // was mostly done at SPI1 init (LBF_SPI1_Init.c)
    // Just need to provide pointer to Tx data and transfer length

    LL_DMA_ConfigAddresses( DMA1, LL_DMA_CHANNEL_3, 
			    (uint32_t)pTxBuffer,  // uint8_t* pointer viewed as address on 32-bit by LL driver
			    LL_SPI_DMA_GetRegAddr(SPI1),
                            LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
  
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, TxLength);


    // -------------------------------------------------
    // Launch transfer 
    // -------------------------------------------------

    // Clean up all relevant status flags 
    LL_DMA_ClearFlag_TE3(DMA1); // clear Transfer Error flag Ch3 DMA1
    LL_DMA_ClearFlag_TC3(DMA1); // clear Transfer Complete Flag Ch3 DMA1
    // LL_DMA_ClearFlag_GI3(DMA1); // clear Global IT flag Ch3 DMA1


    // Note: refer to Ref Manual 38.4.8 for proper prog sequence when using DMA+SPI

    // Enable relevant DMA stream :
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    // Enable generation of DMA requests by SPI
    LL_SPI_EnableDMAReq_TX(SPI1);

    // Enable SPI1 :
    LL_SPI_Enable(SPI1);

    // -------------------------------------------------
    // Wait for end of DMA and clear internal IT flag
    // -------------------------------------------------


    // Here using polling of IT flags rather than IT ISR (as NVIC not configured)
    // Check if transfer complete flag on DMA1 Channel3 is set
    // or if error :
    while ( LL_DMA_IsActiveFlag_TC3(DMA1) == 0)
    {
	if (LL_DMA_IsActiveFlag_TE3(DMA1) == 1) 
	{
	   // Posible Error Handler here
	   while(1);
	}
    }



   // -------------------------------------------------
   // Stop DMA1-Ch.3 and disable SPI1 transfer
   // -------------------------------------------------
   // All 3 following disables look to be needed !

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);


    // wait for FIFO empty
    while( LL_SPI_GetTxFIFOLevel(SPI1) != LL_SPI_TX_FIFO_EMPTY   );

    // Wait for last SPI frame actually transmitted
    while ( LL_SPI_IsActiveFlag_BSY(SPI1) );

    LL_SPI_Disable(SPI1);
    LL_SPI_DisableDMAReq_TX(SPI1);


}
*/

/*******************************************************************************
 * @brief  : Send 8bit command to SEPS525 (driver chip on OLED FPC).
 * @param  : Value of the command.
 * @return : None.
 ******************************************************************************/
void LBF_OLED_SendCmd(uint8_t Value)
{
    LBF_OLED_RS_LOW();
    LBF_OLED_CS_LOW();
    LBF_OLED_SPI_TransferByte(Value);
//    LBF_OLED_SPI1_TransferStream_DMA1Ch3(&Value, 0x1);
    LBF_OLED_CS_HIGH();
    LBF_OLED_RS_HIGH();
}

/*******************************************************************************
 * @brief  : Send 16bit data or parameter to SEPS525 (driver chip on OLED FPC).
 * @param  : Value of the data.
 * @return : Rien.
 ******************************************************************************/
/*
void LBF_OLED_SendData16b(uint16_t Value)
{

uint16_t  Value_tmp;

// Temporarily switch SPI1 to 16bit wide
   LL_SPI_SetDataWidth( SPI1, LL_SPI_DATAWIDTH_16BIT);

   Value_tmp = Value;
   LBF_OLED_SPI1_16bTransferStream_DMA1Ch3( &Value_tmp, 1);

// Switch SPI1 back to 8bit wide
   LL_SPI_SetDataWidth( SPI1, LL_SPI_DATAWIDTH_8BIT);

}
*/


/*******************************************************************************
 * @brief  : Write value in SEPS525 register
 * @param  : NomReg: nom du registre.
 *           ValeurReg: Valeur du registre.
 * @return : None.
 ******************************************************************************/
void LBF_OLED_WriteReg(uint8_t RegName, uint8_t RegValue)
{
    LBF_OLED_CS_LOW();
    LBF_OLED_RS_LOW();

LBF_OLED_SPI_TransferByte(RegName);
//    LBF_OLED_SPI1_TransferStream_DMA1Ch3( &RegName, 0x1 );

    LBF_OLED_RS_HIGH();
    LBF_OLED_CS_HIGH();
    LBF_OLED_CS_LOW();

LBF_OLED_SPI_TransferByte(RegValue);
//    LBF_OLED_SPI1_TransferStream_DMA1Ch3( &RegValue, 0x1 );

    LBF_OLED_CS_HIGH();
}


/*******************************************************************************
 * @brief  : Start data transfer to SEPS525 memory.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DataStart(void)
{
//uint8_t  MagicByte = 0x22;

    LBF_OLED_CS_LOW();
    LBF_OLED_RS_LOW();

    LBF_OLED_SPI_TransferByte(0x22);
//    LBF_OLED_SPI1_TransferStream_DMA1Ch3( &MagicByte, 0x1 );

    LBF_OLED_RS_HIGH();

   // Set SPI1 to 16bit frame for rgb565 transmission
   LL_SPI_SetDataWidth( SPI1, LL_SPI_DATAWIDTH_16BIT);

}

/*******************************************************************************
 * @brief  : Stop data transfer to SEPS525.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DataEnd(void)
{
    LBF_OLED_CS_HIGH();

   // Set SPI1 back to 8bit frame
   LL_SPI_SetDataWidth( SPI1, LL_SPI_DATAWIDTH_8BIT);

}

/*******************************************************************************
 * @brief  : Define a region where to write data in SEPS525 memory
 * @param  : x: position on x-axis of top-left corner of rectangle to draw.
 *           y: position on y-axis of top-left corner of rectangle to draw.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 * @return : none.
 ******************************************************************************/
void LBF_OLED_SetRegion(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t x1, x2, y1, y2;
    
    x1 = x;
    y1 = y;
    x2 = x + width - 1;
    y2 = y + height - 1;
    
    // Valeurs limites
    if (x1 < 0) x1=0;
    if (x1 >= 160) x1=159;
    if (x2 < 0) x2=0;
    if (x2 >= 160) x2=159;
    if (y1 < 0) y1=0;
    if (y1 >= 128) y1=127;
    if (y2 < 0) y2=0;
    if (y2 >= 128) y2=127;
    
    LBF_OLED_WriteReg(0x17, x1);   // X start
    LBF_OLED_WriteReg(0x18, x2);   // X end
    LBF_OLED_WriteReg(0x19, y1);   // Y start
    LBF_OLED_WriteReg(0x1A, y2);   // Y end
    
    LBF_OLED_WriteReg(0x20, x1);   // memory accesspointer x
    LBF_OLED_WriteReg(0x21, y1);   // memory accesspointer y
}

/*******************************************************************************
 * @brief  : Define a region where to write data in SEPS525 memory
 * @param  : x1: position on x-axis of top-left corner of rectangle to draw.
 *           y1: position on y-axis of top-left corner of rectangle to draw.
 *           x2: position on x-axis of bottom-right corner of rectangle to draw.
 *           y2: position on y-axis of bottom-right corner of rectangle to draw.
 * @return : none.
******************************************************************************/
void LBF_OLED_SetRegion_XY(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    
    // Don't draw if not specifying corectly top-left/bottom-right 
    if ( (x1 <= x2) && (y1 <= y2) )
    {
        LBF_OLED_WriteReg(0x17, x1);   // X start
        LBF_OLED_WriteReg(0x18, x2);   // X end
        LBF_OLED_WriteReg(0x19, y1);   // Y start
        LBF_OLED_WriteReg(0x1A, y2);   // Y end
    
        LBF_OLED_WriteReg(0x20, x1);   // memory accesspointer x
        LBF_OLED_WriteReg(0x21, y1);   // memory accesspointer y
    }
}
/*******************************************************************************
 * @brief  : Draw a uniformly colored rectangle on OLED screen.
 * @param  : x1: position on x-axis of top-left corner of rectangle to draw.
 *           y1: position on y-axis of top-left corner of rectangle to draw.
 *           x2: position on x-axis of bottom-right corner of rectangle to draw.
 *           y2: position on y-axis of bottom-right corner of rectangle to draw.
 *           color565: color of the rectangle in RGB565 format.
 * @return : none.
 ******************************************************************************/
void LBF_OLED_Fill_XY(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color565)
{
uint16_t color565_tmp = color565;



    LBF_OLED_SetRegion_XY(x1, y1, x2, y2);
    
    LBF_OLED_DataStart();  //includes setting SPI1 to 16 bits frame

    // For this "fill" mode (always same rgb data)
    // temporarily switch off DMA auto-increment on memory side
    LL_DMA_ConfigTransfer(DMA1, 
			LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_NOINCREMENT | 
                        LL_DMA_PDATAALIGN_WORD |   
			LL_DMA_MDATAALIGN_HALFWORD);  // DMA expected to be used for rgb565 data on 16 bits
                       // MUST PROVIDE ALL ARGUMENTS 


   // Transfer !
   LBF_OLED_SPI1_16bTransferStream_DMA1Ch3( &color565_tmp, (x2-x1+1)*(y2-y1+1));


   // Enable back auto-increment on memory side 
    LL_DMA_ConfigTransfer(DMA1, 
			LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT | 
                        LL_DMA_PDATAALIGN_WORD |   
			LL_DMA_MDATAALIGN_HALFWORD);  // DMA expected to be used for rgb565 data on 16 bits
                       // MUST PROVIDE ALL ARGUMENTS 

    LBF_OLED_DataEnd();  //includes setting SPI1 back to 8 bits frame

}

/*******************************************************************************
 * @brief  : Draw a uniformly colored rectangle on OLED screen.
 * @param  : x: position on x-axis of top-left corner.
 *           y: position on y-axis of top-left corner.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 *           color565: color of the rectangle in RGB565 format.
 * @return : none.
 ******************************************************************************/
void LBF_OLED_Fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color565)
{

uint8_t x1, x2, y1, y2;
uint16_t color565_tmp = color565;


    x1 = x;
    y1 = y;
    x2 = x + width - 1;
    y2 = y + height - 1;
    
    // Valeurs limites
    if (x1 < 0) x1=0;
    if (x1 >= 160) x1=159;
    if (x2 < 0) x2=0;
    if (x2 >= 160) x2=159;
    if (y1 < 0) y1=0;
    if (y1 >= 128) y1=127;
    if (y2 < 0) y2=0;
    if (y2 >= 128) y2=127;

    LBF_OLED_SetRegion_XY(x1, y1, x2, y2);
    
    LBF_OLED_DataStart();  //includes seeting SPI1 to 16 bits frame

    // For this "fill" mode (always same rgb data)
    // temporarily switch off DMA auto-increment on memory side
    LL_DMA_ConfigTransfer(DMA1, 
			LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_NOINCREMENT | 
                        LL_DMA_PDATAALIGN_WORD |   
			LL_DMA_MDATAALIGN_HALFWORD);  // DMA expected to be used for rgb565 data on 16 bits
                       // MUST PROVIDE ALL ARGUMENTS 

   // Transfer !
   LBF_OLED_SPI1_16bTransferStream_DMA1Ch3( &color565_tmp, width*height);


   // Enable back auto-increment on memory side (i.e. do "0D DMA")
  LL_DMA_ConfigTransfer(DMA1, 
			LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT | 
                        LL_DMA_PDATAALIGN_WORD |   // DMA expected to be used for rgb565 data on 16 bits
			LL_DMA_MDATAALIGN_HALFWORD);  

    LBF_OLED_DataEnd();  //includes setting SPI1 back to 8 bits frame

}

/*******************************************************************************
 * @brief  : Display a rectangle with user-defined content.
 * @param  : x: position on x-axis of top-left corner.
 *           y: position on y-axis of top-left corner.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 *           *buffer: pointer to pre-filled buffer.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DisplayBuffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t *pBuffer)
{
void LBF_OLED_SendData(uint16_t Value); //DEBUG

    LBF_OLED_SetRegion(x, y, width, height);
    
    LBF_OLED_DataStart();  //includes setting SPI1 to 16 bits frame

    // Transfer !
    LBF_OLED_SPI1_16bTransferStream_DMA1Ch3( pBuffer, width*height);

// DEBUG (with data width kept at 8-bit)
/*
    uint16_t i;
    for (i=0; i<width*height; i++)
    {
        LBF_OLED_SendData(*(pBuffer++) );
    }
*/

    LBF_OLED_DataEnd();  //includes setting SPI1 back to 8 bits frame

}

//!!!!!!!!!!!!!! DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void LBF_OLED_SendData(uint16_t Value)
{

// 16-bit per pixel :
    LBF_OLED_SPI_TransferByte((Value>>8) & 0xFF);
    LBF_OLED_SPI_TransferByte(Value & 0xFF);
}
//!!!!!!!!!!!!!! DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



/*******************************************************************************
 * @brief  : Display a rectangle with user-defined content.
 * @param  : x1: position on x-axis of top-left corner of rectangle to draw.
 *           y1: position on y-axis of top-left corner of rectangle to draw.
 *           x2: position on x-axis of bottom-right corner of rectangle to draw.
 *           y2: position on y-axis of bottom-right corner of rectangle to draw.
 *           *buffer: pointer to pre-filled buffer.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DisplayBuffer_XY(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t *pBuffer)
{

    LBF_OLED_SetRegion_XY( x1,  y1, x2,  y2 );
    
    LBF_OLED_DataStart();  //includes setting SPI1 to 16 bits frame

    // Transfer !
    LBF_OLED_SPI1_16bTransferStream_DMA1Ch3( pBuffer, (x2-x1+1)*(y2-y1+1));

    LBF_OLED_DataEnd();  //includes setting SPI1 back to 8 bits frame

}

/*******************************************************************************
 * @brief  : Clear OLED screen (display black).
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_Clear(void)
{
    LBF_OLED_Fill_XY(0, 0, 159, 127, 0x0000);
}

/*******************************************************************************
 * @brief  : Turn OLED screen ON (13V to OLED, display on).
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_Switch_ON(void)
{
    Turn_VDDH_On();
    LBF_Delay_ms(100); // as per DD160128FC-1A datasheet - to preserve screen lifetime
    
    // Display ON
    LBF_OLED_WriteReg(0x06, 0x01);
}

/*******************************************************************************
 * @brief  : Turn OLED screen OFF (display off, cut 13V to OLED).
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_Switch_OFF(void)
{
        // Power down OLED 
        // Recommended sequence - from DD-160128FC-1A datasheet:
	//	1. Send Display off command
	//	2. Power down VDDH
	//	3. Delay 100ms
	//	(When VDDH reach 0 and panel is completely discharged)
	//	4. Power down VDD & VDDIO 	
        // Steps 1, 2, 3 are done here

      	LBF_OLED_WriteReg(0x06, 0x00);  // Display off

        // Power down OLED panel (VDDH 14V supply)
        Turn_VDDH_Off();

	LBF_Delay_ms(100);
	    //Caution: TimerTick involved, its IRQ priority must be high (urgent) enough
	    // in Interrupt Configuration files
}

/*******************************************************************************
 * @brief  : !!! Can only be used when emWin Graphical Library has been enabled
 *           Resets position of next text to write to start of CURRENT line
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_OLED_Overwrite_CurrentLine(void)
{
      GUI_GotoX(0);
      GUI_DispCEOL();  // clear to end of line
}

/*******************************************************************************
 * @brief  : !!! Can only be used when emWin Graphical Library has been enabled
 *           Prints specified string at current location
 *           No automatic line feed (use \n)
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_OLED_PrintString(char* string)
{
      if (GUI_GetDispPosY() > Y_FULL_SCREEN-1 )   //check if end of screen reached
      {
         GUI_Clear();  // clear and back to top
      }
 
      GUI_DispString(string);
}


/*******************************************************************************
 * @brief  : !!! Can only be used when emWin Graphical Library has been enabled
 *           Prints specified string at current location
 *           No automatic line feed (use \n)
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_OLED_PrintDec(I32 SignedInteger)
{
      if (GUI_GetDispPosY() > Y_FULL_SCREEN-1 )   //check if end of screen reached
      {
         GUI_Clear();  // clear and back to top
      }
 
      GUI_DispDecMin( SignedInteger );
}

/*******************************************************************************
 * @brief  : !!! Can only be used when emWin Graphical Library has been enabled
 *           Prints specified string at current location
 *           No automatic line feed (use \n)
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_OLED_PrintHex(U16   Unsigned16)
{
      if (GUI_GetDispPosY() > Y_FULL_SCREEN-1 )   //check if end of screen reached
      {
         GUI_Clear();  // clear and back to top
      }
 
      GUI_DispHex( (U32)Unsigned16, 4 );
}




/***************************************************************END OF FILE****/
