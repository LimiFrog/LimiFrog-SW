/*******************************************************************************
 * main.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_Global.h"
#include "User_Configuration.h"

#include "string.h"

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = TRUE;

/* ================================================================ */
/* Board Initializations and Configurations except OLED             */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)                */
/* ================================================================ */

   LBF_Board_Fixed_Inits();
   LBF_Board_Selective_Inits(); 
             // actions driven by User_Configuration.h

   LBF_Led_ON();


/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

// UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    // Delay_ms(1000);
    Success &= LBF_LaunchUSB_MassStorage();
 
    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    Success &= LBF_FatFS_Init();

    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();



/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

// Variables
FIL		MyFile;
uint32_t 	wbytes_count; /* File write counts */
uint8_t 	wtext[] = "LPS25H access successful\r\n"; /* File write buffer */
uint8_t	 	ReadValue;
int32_t		Pressure_mbar;

// Private functions
int32_t  	Get_Pressure_mb(void);


/* ==  Body     ====================================================== */


 /* ---     Check I2C access to Pressure Sensor :  ST LPS25H  -------- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_WHOAMI);
    LBF_Led_StopNBlinkOnFalse ( ReadValue == LPS25H_WHOAMI_CONTENTS ); 
		// to stop here and blink LED if failure
  
 /* ---     Log success in file system                    -------- */

    if(f_open(&MyFile, "LPS25H.LOG", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    {
        f_write(&MyFile, wtext, sizeof(wtext)-1, (void *)&wbytes_count);
        f_close(&MyFile);
    }

 /* ---     Prepare Pressure Sensor    ------------------------ */

  // Enable single shot mode with internal IT generated when data ready
  LBF_I2CSensors_WriteSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG1_ADDR, 0x84);


 /* ---     Prepare Display of Results    ----------------------- */

   LBF_OLED_Switch_ON();
   // Provide power (13V) to OLED panel, enable display

   // Draw background: 
   //rounded rectangle filled with yellow to red vertical gradient 
   GUI_DrawGradientRoundedV(10, 10, X_FULL_SCREEN-10, Y_FULL_SCREEN-10, 10,
				0xFF0000, 0xFFFF00);


  /* ---     Track  Pressure            ------------------------- */

  while(1)
  {

        Pressure_mbar =  Get_Pressure_mb();

	LBF_Led_TOGGLE();

        // --- Display Result:------------------------------------------------

        GUI_SetFont(&GUI_Font24B_ASCII);
        GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
        GUI_DispDecAt( Pressure_mbar,  X_FULL_SCREEN/2, Y_FULL_SCREEN/4, 4);  
        // Display pressure with 4 digits, centered on specified position

        GUI_SetFont(&GUI_Font16B_ASCII);
        GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
        GUI_DispStringAt( "mbar", X_FULL_SCREEN/2, Y_FULL_SCREEN*3/4 );
        // Display units, centered on specified position

        LBF_Delay_ms(1000);


  }  //  end while(1)


}


/* ==  PRIVATE FUNCTIONS             ========================================= */

int32_t  Get_Pressure_mb(void)
{

uint8_t		Pressure_Bytes[4]; 
int32_t		Pressure_Signed;

        // Launch Single Shot Measurement, bit will auto-cleared when data ready
         LBF_I2CSensors_WriteSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG2_ADDR, 0x01);  

	// Wait until data available from Pressure Sensor
        while ( LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG2_ADDR) != 0x00);  


	// Read Results on 3 Bytes (24 bits)
        Pressure_Bytes[0] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_XL_ADDR);
        Pressure_Bytes[1] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_L_ADDR);
        Pressure_Bytes[2] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_H_ADDR);
        // Expand to 4th MSByte according to sign of result on 24 bits
        ( (Pressure_Bytes[2]&0x80) == 0x80) ?  (Pressure_Bytes[3] = 0xFF) :  (Pressure_Bytes[3] = 0x00) ;

        Pressure_Signed = (int32_t)( (uint32_t)Pressure_Bytes[3]<<24
                                   | (uint32_t)Pressure_Bytes[2]<<16
                                   | (uint32_t)Pressure_Bytes[1]<<8
                                   | (uint32_t)Pressure_Bytes[0]      );

        return( Pressure_Signed / 4096 );  //in mbar, as per LPS25H datasheet
}

/***************************************************************END OF FILE****/
