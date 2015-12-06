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
#include "GUI.h"  // to use emWin API


/*******************************************************************************
 * @brief  : Send a byte on SPI1 output, simultaneously receive a byte on SPI input.
 * @param  : octet: byte to send.
 * @return : valoe of byte received.
 ******************************************************************************/
uint8_t LBF_OLED_SPI_TransferByte (uint8_t TxByte)
{

uint8_t RxByte = 0;

    HAL_SPI_TransmitReceive(&hspi1, &TxByte, &RxByte, 0x1, 1000);
    // SPI1, full duplex, blocking Tx/Rx of 1 byte with 1s timeout
    // (hspi1 is global)

    return RxByte;
}


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
    LBF_OLED_CS_HIGH();
    LBF_OLED_RS_HIGH();
}

/*******************************************************************************
 * @brief  : Send 16bit data or parameter to SEPS525 (driver chip on OLED FPC).
 * @param  : Value of the data.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_SendData(uint16_t Value)
{

// 16-bit per pixel :
    LBF_OLED_SPI_TransferByte((Value>>8) & 0xFF);
    LBF_OLED_SPI_TransferByte(Value & 0xFF);

}



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
    LBF_OLED_RS_HIGH();
    LBF_OLED_CS_HIGH();
    LBF_OLED_CS_LOW();
    LBF_OLED_SPI_TransferByte(RegValue);
    LBF_OLED_CS_HIGH();
}


/*******************************************************************************
 * @brief  : Start data transfer to SEPS525 memory.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DataStart(void)
{
    LBF_OLED_CS_LOW();
    LBF_OLED_RS_LOW();
    LBF_OLED_SPI_TransferByte(0x22);
    LBF_OLED_RS_HIGH();
}

/*******************************************************************************
 * @brief  : Stop data transfer to SEPS525.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_DataEnd(void)
{
    LBF_OLED_CS_HIGH();
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

    LBF_OLED_SetRegion(x, y, width, height);
    
    LBF_OLED_DataStart();
    uint16_t i;


    for (i=0; i<width*height; i++)
    {
        LBF_OLED_SendData(color565); 
    }
    


    LBF_OLED_DataEnd();

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
void LBF_OLED_DisplayBuffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t *buffer)
{
    LBF_OLED_SetRegion(x, y, width, height);
    
    LBF_OLED_DataStart();
    uint16_t i;
    for (i=0; i<width*height; i++)
    {
        LBF_OLED_SendData(buffer[i]);
    }
    LBF_OLED_DataEnd();
}


/*******************************************************************************
 * @brief  : Clear OLED screen (display black).
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_Clear(void)
{
    LBF_OLED_Fill(0, 0, 160, 128, 0x0000);
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
