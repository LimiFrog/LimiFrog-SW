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


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = true;

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
    // LBF_Delay_ms(1000);
    // Success &= LBF_LaunchUSB_MassStorage();
 
    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    // Success &= LBF_FatFS_Init();

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

void  Get_ZeroGauss_OffsetXY( int16_t* pMField_X_Raw_Offset, int16_t* pMField_Y_Raw_Offset ); 
void Get_Magnetic_FieldXY( int16_t MField_X_Raw_Offset, int16_t MField_Y_Raw_Offset,
			   int16_t* pMField_X_mGauss,  int16_t* pMField_Y_mGauss);

uint8_t ReadValue;

int16_t		MField_X_Raw_Offset, MField_Y_Raw_Offset ;
int16_t		MField_X_mGauss, MField_Y_mGauss;

int32_t 	MField_X_mGauss_2 =0, MField_Y_mGauss_2 =0;
int32_t 	MField_X_mGauss_1 =0, MField_Y_mGauss_1 =0;
int32_t		MField_X_mGauss_Filtd, MField_Y_mGauss_Filtd;
int32_t         Field_Magnitude;

int32_t 	X_Gfx_Vector, Y_Gfx_Vector;
int32_t 	X_Previous_Gfx_Vector = 0, Y_Previous_Gfx_Vector=0;


#define  MGAUSS_MAX  450  //Max expected magnitude of magnetic field to display
#define  BKGND_COLOR 0x102020  // dark grey
#define  FOREGND_COLOR 0x00AAA0  // blue-green




/* ==  Body     ====================================================== */

  LBF_OLED_Switch_ON();
  // Provide power (13V) to OLED panel, enable display


 /* ---     Check access to Magnetometer :  ST LIS3MDL   -------- */

  ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, LIS3MDL_WHOAMI);
//  LBF_Led_StopNBlinkOnFalse ( ReadValue == LIS3MDL_WHOAMI_CONTENTS );
  if (ReadValue != LIS3MDL_WHOAMI_CONTENTS)
  {
      LBF_Led_ON(); while(1);
  }

 /* ---     Configure Magnetometer     -------------------------- */

  // Define Full Scale: Reg. CTRL_REG2 @0x21
  // NB- earth magnetic field magnitude = 0.25 to 0.65 Gauss
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 0x21, 0x00);  
	// FS = 4 Gauss

  // Define XY Performance mode and ODR: Reg. CTRL_REG1 @0x20
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 0x20, 0x90);  // 0b10010000
	// Enable T° sensor
	// Low-power mode on X and Y
	// ODR = 10Hz
  // Define Z Performance mode: Reg. CTRL_REG4 @0x23
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 0x23, 0x00);  // 0b00000000

  // Calibrate to compensate Zero Gauss Offset
  Get_ZeroGauss_OffsetXY( &MField_X_Raw_Offset, &MField_Y_Raw_Offset );


 /* ---     Prepare Display of Results    -------------------------- */

   GUI_SetFont(&GUI_Font24B_ASCII);
   GUI_SetTextMode(GUI_TM_TRANS);

   GUI_SetColor(BKGND_COLOR);
   GUI_FillRect(0, 0, X_FULL_SCREEN-1, Y_FULL_SCREEN-1);

   GUI_SetColor(0xAAAA00);  
   GUI_DrawCircle(Y_FULL_SCREEN/2, Y_FULL_SCREEN/2,  (Y_FULL_SCREEN/2)-10);
   GUI_FillCircle(Y_FULL_SCREEN/2, Y_FULL_SCREEN/2,  2);



  /* ---     Start Tracking Magnetic Field     -------------------------- */

  while(1)
  {
        // --- Capture :------------------------------------------------

        // SINGLE SHOT conversion : CTRL_REG3 @0x22 :   
         LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 0x22, 0x01);  // 0b00000001

	// Wait until data available from Magnetometer
        do 
        {
            ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x27);  // Status Reg
        } while ( (ReadValue & 0x08) != 0x08);  // bit set when new XYZ data available


	// Read Results
        Get_Magnetic_FieldXY( MField_X_Raw_Offset, MField_Y_Raw_Offset,
			      &MField_X_mGauss, &MField_Y_mGauss );


	// --- Display North ------------------------------------------------

	if (MField_X_mGauss > MGAUSS_MAX)
		MField_X_mGauss = MGAUSS_MAX;
	if (MField_X_mGauss < -MGAUSS_MAX)
		MField_X_mGauss = -MGAUSS_MAX;
	if (MField_Y_mGauss > MGAUSS_MAX)
		MField_Y_mGauss = MGAUSS_MAX;
	if (MField_Y_mGauss < -MGAUSS_MAX)
		MField_Y_mGauss = -MGAUSS_MAX;

        // Filtering to limit "jitter" effect on position
        MField_X_mGauss_Filtd = (MField_X_mGauss_2 + 2*MField_X_mGauss_1 + (int32_t)MField_X_mGauss) /4;
        MField_Y_mGauss_Filtd = (MField_Y_mGauss_2 + 2*MField_Y_mGauss_1 + (int32_t)MField_Y_mGauss) /4;
        MField_X_mGauss_2 = MField_X_mGauss_1;
        MField_X_mGauss_1 = (int32_t)MField_X_mGauss;
        MField_Y_mGauss_2 = MField_Y_mGauss_1;
        MField_Y_mGauss_1 = (int32_t)MField_Y_mGauss;

        Field_Magnitude = ( MField_X_mGauss_Filtd * MField_X_mGauss_Filtd)
                         + ( MField_Y_mGauss_Filtd *  MField_Y_mGauss_Filtd);

        X_Gfx_Vector = 
	  ( ( MField_X_mGauss_Filtd + MGAUSS_MAX) * (Y_FULL_SCREEN-1) ) / (2*MGAUSS_MAX) ;
        Y_Gfx_Vector = 
	  ( (-MField_Y_mGauss_Filtd + MGAUSS_MAX) * (Y_FULL_SCREEN-1) ) / (2*MGAUSS_MAX) ;
        // Only Y_FULL_SCREEN to avoid distorsion due to shape of screen

        // Compensate for size of letter "N" displayed as its x,y correspond to top left corner
        X_Gfx_Vector -= 6;
        Y_Gfx_Vector -= 12;

        // Skip Display if vector falls out of range

        if  (Field_Magnitude <  MGAUSS_MAX*MGAUSS_MAX   )
        {
	  if ( (X_Gfx_Vector != X_Previous_Gfx_Vector) || (Y_Gfx_Vector !=  Y_Previous_Gfx_Vector) ) 
	  // Redraw only if needed
	  {
	          // Erase Previous
        	  GUI_SetColor( BKGND_COLOR );
        	  GUI_DispStringAt("N", X_Previous_Gfx_Vector, Y_Previous_Gfx_Vector);

        	  // Draw New 
        	  GUI_SetColor( FOREGND_COLOR );
        	  GUI_DispStringAt("N", X_Gfx_Vector, Y_Gfx_Vector);

                  X_Previous_Gfx_Vector = X_Gfx_Vector;
                  Y_Previous_Gfx_Vector = Y_Gfx_Vector;
	  }  // end if
        }  // end if
        LBF_Delay_ms(500);


  }  //  end while(1)


}


/* ===========   PRIVATE FUNCTIONS ======================================== */


/* ---  Zero-Gauss Calibration of Magnetometer ----------------------- */

void  Get_ZeroGauss_OffsetXY( int16_t* pMField_X_Raw_Offset, int16_t* pMField_Y_Raw_Offset )
{

#define  NUM_CALIB_CIRCLES 1   
  // Calibration performed by taking 8 measurements 45deg apart, 
  // repeated NUM_CALIB_CIRCLES times

uint8_t i;
uint8_t		MField_X_LowByte, MField_X_HighByte;
uint8_t		MField_Y_LowByte, MField_Y_HighByte;
int16_t		MField_X_Raw, MField_Y_Raw;
int32_t		MField_X_Acc = 0, MField_Y_Acc = 0;
uint16_t 	ColorSequence[8] = {RED, WHITE, GREEN, BLUE, CYAN, ORANGE, LIGHT_BLUE, YELLOW } ;  


  // Display Instructions :
  LBF_OLED_PrintString("CALIBRATION\n\n");
  LBF_OLED_PrintString("Lay LimiFrog flat\n");
  LBF_OLED_PrintString("Then rotate it 45 deg.\n  at each change of color:");
  LBF_Delay_ms(5000);

  // Go --- 8 equally spaced magnetic field measurements, repeatable n times per #define
  for (i=0; i < 8*NUM_CALIB_CIRCLES; i++)   
  {
          LBF_OLED_Fill( X_FULL_SCREEN/2 -20, Y_FULL_SCREEN/2-20, 40, 40, ColorSequence[i] );
          LBF_Delay_ms(2500);

	  LBF_Led_ON();

          // SINGLE SHOT conversion : CTRL_REG3 @0x22 :   
          LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 0x22, 0x01);  // 0b00000001

          while ( (LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x27)& 0x08) != 0x08);  
                    // read status reg until it flags new XYZ data available

	  // Accumulate Results
	  MField_X_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x28);
	  MField_X_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x29);
	  MField_X_Raw =  
	         (int16_t)( (MField_X_HighByte <<8 ) | MField_X_LowByte );
	  MField_X_Acc += (int32_t)(MField_X_Raw);
	  MField_Y_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x2A);
	  MField_Y_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x2B);
	  MField_Y_Raw =  
	         (int16_t)( (MField_Y_HighByte <<8 ) | MField_Y_LowByte );
	  MField_Y_Acc += (int32_t)(MField_Y_Raw);

	  LBF_Led_OFF();
   }
 
   *pMField_X_Raw_Offset =  (int16_t)(MField_X_Acc / i);
   *pMField_Y_Raw_Offset =  (int16_t)(MField_Y_Acc / i);

   GUI_DispStringAt("", 10, 90);
   LBF_OLED_PrintString("THANKS,\nCALIBRATION DONE !");
   LBF_Delay_ms(2000);
   LBF_OLED_Clear();

}



/* --- Read Magnetometer registers and compute magnetic field in mGauss --------- */

void Get_Magnetic_FieldXY( int16_t MField_X_Raw_Offset, int16_t MField_Y_Raw_Offset,
			   int16_t* pMField_X_mGauss,  int16_t* pMField_Y_mGauss)
{
uint8_t		MField_X_LowByte, MField_X_HighByte;
uint8_t		MField_Y_LowByte, MField_Y_HighByte;
int16_t		MField_X_Raw, MField_Y_Raw ;

	MField_X_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x28);
	MField_X_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x29);

	MField_Y_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x2A);
	MField_Y_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 0x2B);

        MField_X_Raw =  
         (int16_t)( (MField_X_HighByte <<8 ) | MField_X_LowByte ) - MField_X_Raw_Offset;
        MField_Y_Raw =  
         (int16_t)( (MField_Y_HighByte <<8 ) | MField_Y_LowByte ) - MField_Y_Raw_Offset;

        *pMField_X_mGauss =  (MField_X_Raw * 1024) / 7004;
        *pMField_Y_mGauss =   (MField_Y_Raw * 1024) / 7004;
        // 1024/7004 = 1/6.8398 while 1 LSB = 6.84 mGauss
}



/* ---  Get Atm Pressure  ----------------------- */

/***************************************************************END OF FILE****/
