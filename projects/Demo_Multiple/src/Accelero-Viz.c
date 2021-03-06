/*******************************************************************************
 * Accelero-Viz.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_Global.h"

bool NextDemoRequest(void);



/*******************************************************************************/
void Accelero_Viz(void)
{


uint8_t Accel_X_LowByte , Accel_X_HighByte;
uint8_t Accel_Y_LowByte , Accel_Y_HighByte;
uint8_t Accel_Z_LowByte , Accel_Z_HighByte;

int16_t  Accel_X_Signed, Accel_Y_Signed, Accel_Z_Signed;

int32_t  Accel_X_Scaled, Accel_Y_Scaled, Accel_Z_Scaled;

int32_t  Accel_X_coord, Accel_Y_coord, Accel_Z_coord;
int32_t  Accel_X_coord_prev, Accel_Y_coord_prev, Accel_Z_coord_prev;


uint8_t	ReadValue;

uint16_t	i;


/* ==  Body     ======================================== */

   LBF_OLED_Switch_ON();

   /* ---     Configure Accelerometer     -------------------------- */

    // Check Accelerometer LSM6DS3 can be accessed
    ReadValue = LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_WHOAMI);
    LBF_Led_StopNBlinkOnFalse ( ReadValue == LSM6DS3_WHOAMI_CONTENTS );


    // Start-up accelerometer
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, LSM6DS3_XG_CTRL9_XL, 0x38);  
	// enable XYZ axes
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, LSM6DS3_XG_CTRL1_XL, 0x43);  
	//  ODR= 104Hz(high-perf), FullScale=2g, Antialiasing = 50Hz: 0b01000011
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, LSM6DS3_XG_INT1_CTRL, 0x01);  
	//  Reg. INT1_CTRL: data ready on INT1


   /* ---     Prepare Display               -------------------------- */

    GUI_Clear();        	 
    GUI_SetFont(&GUI_Font8_ASCII);



   /* ---     Loop on Accel. measurements     ----------------------- */

    i = 0;
    while(1) 
    {

        if (i==0)
	{
	    GUI_DispCEOL();  //clear line
	    GUI_SetColor(0xFF0000);  // RED
            GUI_DispStringAt("X", 0, 120);
	    GUI_SetColor(0x00FF00);  // GREEN
            GUI_DispString("Y");
	    GUI_SetColor(0x0000FF);  // BLUE
            GUI_DispString("Z");
	    GUI_SetColor(0xFFFFFF);  // WHITE
            GUI_DispString("ACCELERATION");
	}

	// Wait until data available from Accelerometer
        do 
        {
            ReadValue = LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_XG_STATUS_REG);  // Status Reg
        } while ( (ReadValue & 0x01) != 0x01);  // bit set when new XYZ data available


	// Shift screen left
        LBF_OLED_WriteReg( 0x2E, i ); 
          // X that will correspond to first display memory address



        // --- Read Results :------------------------------------------------

	 Accel_X_LowByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID, LSM6DS3_XG_OUT_X_L_XL);
	 Accel_X_HighByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID,LSM6DS3_XG_OUT_X_H_XL);

	 Accel_Y_LowByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID, LSM6DS3_XG_OUT_Y_L_XL);
	 Accel_Y_HighByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID, LSM6DS3_XG_OUT_Y_H_XL);   
       
	 Accel_Z_LowByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID, LSM6DS3_XG_OUT_Z_L_XL);
	 Accel_Z_HighByte = LBF_I2CSensors_ReadSingleReg(
				LSM6DS3_CHIPID, LSM6DS3_XG_OUT_Z_H_XL);   


         Accel_X_Signed = (int16_t)( ((uint16_t)Accel_X_HighByte<<8) |
				 (uint16_t)Accel_X_LowByte );

         Accel_Y_Signed = (int16_t)( ((uint16_t)Accel_Y_HighByte<<8) |
				 (uint16_t)Accel_Y_LowByte );

         Accel_Z_Signed = (int16_t)( ((uint16_t)Accel_Z_HighByte<<8) |
				 (uint16_t)Accel_Z_LowByte );

        // --- Display Results :------------------------------------------------

         // Erase Pixels on this X coord before drawing new:
	 GUI_SetColor(0x000000);  // BLACK
	 GUI_DrawLine(i, 0, i, 119);
	    // not down to bottom to preserve scrolling text


	 GUI_SetColor(0xFF0000);  // AccelX - RED
	 Accel_X_Scaled = (( (int32_t)Accel_X_Signed * 128) / 65536);
	 Accel_X_coord = 63 + Accel_X_Scaled;
	 if (i>0)
	     GUI_DrawLine(i-1, Accel_X_coord_prev, i, Accel_X_coord);
	 else 
	     GUI_DrawPixel(0, Accel_X_coord);
	 Accel_X_coord_prev = Accel_X_coord;


	 GUI_SetColor(0x00FF00);  // AccelY - GREEN
	 Accel_Y_Scaled = (( (int32_t)Accel_Y_Signed * 128) / 65536);
	 Accel_Y_coord = 63 + Accel_Y_Scaled;
	 if (i>0)
	     GUI_DrawLine(i-1, Accel_Y_coord_prev, i, Accel_Y_coord);
	 else 
	     GUI_DrawPixel(0, Accel_Y_coord);
	 Accel_Y_coord_prev = Accel_Y_coord;


	 GUI_SetColor(0x0000FF);  // AccelZ- BLUE
	 Accel_Z_Scaled = (( (int32_t)Accel_Z_Signed * 128) / 65536);
	 Accel_Z_coord = 63 + Accel_Z_Scaled;
	 if (i>0)
	     GUI_DrawLine(i-1, Accel_Z_coord_prev, i, Accel_Z_coord);
	 else 
	     GUI_DrawPixel(0, Accel_Z_coord);
	 Accel_Z_coord_prev = Accel_Z_coord;


	if (i++ == 160)
	    i = 0;

	// Exit requested ?
        if  (NextDemoRequest())   // demo change requested
	{
	    // Stop Accelerometer: power-down
    	    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, LSM6DS3_XG_CTRL1_XL, 0x00);  

	   // Restore normal position of 1st pixel of Display
           LBF_OLED_WriteReg( 0x2E, 0x00 ); 

	    return;
	}

    } // end while(1)
    
}



/***************************************************************END OF FILE****/
