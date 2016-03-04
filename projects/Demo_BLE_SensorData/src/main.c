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

   LBF_Board_Inits();
        // actions partly driven by User_Configuration.h


   LBF_Led_ON();

/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    Success &= LBF_LaunchUSB_MassStorage();
    // LBF_Delay_ms(1000);

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

// --------------------------------------------------------
// BlueTooth Low-Energy (BTLE or BLE) must be enabled by 
// #define in User_Configuration.h
// Name of the file containing code to download by STM32 
// into BTLE module also defined there -- download occurs
// during LBF_Board_Selective_Inits() phase.
// This executable must be present on FAT File System on Flash 
// (typically stored there from PC through USB).
// In this demo, code is supposed to be Serial Port Service
// snippet provided by Dialog -- this configures the BTLE
// to behave as UART cable replacement. Data sent to
// BTLE module over UART at 115200 baud is transitted over BTLE
// This data can be received by DSPS application running in iOS
// or Android, provided by Dialog, available on Appple/Android
// app stores
// --------------------------------------------------------
//
// UART3 is dedicated to STM32-BLE module interface from
// LimiFrog0.1 onwards
//
// --------------------------------------------------------



/* ==  User Declarations =============================== */

uint32_t  LoopCnt = 0;
#define MAX_LOOP_CNT  2 //8

uint32_t  counter = 0;
#define MAX_COUNTER 9
uint16_t color_table[7] = {YELLOW, RED, WHITE, GREEN, BLUE, ORANGE, CYAN} ;
uint32_t index = 0;


// Raw results from Magnetometer
uint8_t MField_X_LowByte, MField_X_HighByte;
uint8_t MField_Y_LowByte, MField_Y_HighByte;
uint8_t MField_Z_LowByte, MField_Z_HighByte;

int16_t	MField_X_Offset=0, MField_Y_Offset=0, MField_Z_Offset=0 ;

// Magnetometer results including offset compensation
int16_t	MField_X_Comp, MField_Y_Comp, MField_Z_Comp ;
uint8_t MField_X_Comp_LowByte, MField_X_Comp_HighByte;
uint8_t MField_Y_Comp_LowByte, MField_Y_Comp_HighByte;
uint8_t MField_Z_Comp_LowByte, MField_Z_Comp_HighByte;



uint8_t Accel_X_LowByte , Accel_X_HighByte;
uint8_t Accel_Y_LowByte , Accel_Y_HighByte;
uint8_t Accel_Z_LowByte , Accel_Z_HighByte;

uint8_t	ReadValue;



void  Get_ZeroGauss_OffsetXYZ( int16_t* pMField_X_Raw_Offset, int16_t* pMField_Y_Raw_Offset, int16_t* pMField_Z_Raw_Offset );

void Display_TextInfo(void);


/* ==  Body     ======================================== */


  LBF_OLED_Switch_ON();  // DON'T FORGET #define USE_OLED in User_Configuration.h

  LBF_OLED_PrintString("\nStarting...\n");

 /* ---     Configure Magnetometer     -------------------------- */

  //Check Magnetometer LIS3MDL can be accessed
  ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, LIS3MDL_WHOAMI);
  if (ReadValue != LIS3MDL_WHOAMI_CONTENTS)
	LBF_OLED_PrintString("\nMagneto access pb\n");

  // Define Full Scale: Reg. CTRL_REG2 @0x21
  // NB- earth magnetic field magnitude = 0.25 to 0.65 Gauss
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
	LIS3MDL_CONTROL_REGISTER_2_REG, 0x00);  
	// FS = 4 Gauss

  // Define XY Performance mode and ODR: Reg. CTRL_REG1 @0x20
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
	LIS3MDL_CONTROL_REGISTER_1_REG, 0x90);  // 0b10010000
	// Enable T° sensor
	// Low-power mode on X and Y
	// ODR = 10Hz
  // Define Z Performance mode: Reg. CTRL_REG4 @0x23
  LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID,
	LIS3MDL_CONTROL_REGISTER_4_REG, 0x00);  // 0b00000000



 /* ---     Configure Accelerometer     -------------------------- */
/*
  //Check Accelerometer LSM6DS3 can be accessed
  ReadValue = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_WHOAMI);
//  Led_StopNBlinkOnFalse ( ReadValue == LSM6DS3_WHOAMI_CONTENTS );
  if (ReadValue != LSM6DS3_WHOAMI_CONTENTS)
	OLED_PrintString("\nAccel. access pb\n");

  

  // Start-up accelerometer
  I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x18, 0x38);  // Reg. CTRL9_XL: enable XYZ axes
  I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x10, 0x60);  // Reg. CTRL1_XL: 416Hz (high-perf), FullScale=2g
  I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x0D, 0x01);  // Reg. INT1_CTRL: data ready on INT1
*/

    Display_TextInfo();

    while(1)
    {

	LBF_Delay_ms(100);  // ==> Update and Transmit data at this rate

	{
	  if (LoopCnt++ == MAX_LOOP_CNT)  
		// Position of colored square on screen changed after every so many data updates
          {
            LoopCnt = 0;
	    switch (index++) 
	    {
		case 0:
		    LBF_OLED_Fill_XY(120, 87, 160, 127, BLACK);
		    LBF_OLED_Fill_XY(0, 0, 40, 40, color_table[(counter)%7]);  
		    break;
		case 1:
		     LBF_OLED_Fill_XY(0, 0, 40, 40, BLACK );  
             	     LBF_OLED_Fill_XY(41, 0, 80, 40, color_table[(counter)%7]);
		    break;
		case 2:
             	     LBF_OLED_Fill_XY(41, 0, 80, 40, BLACK);
           	     LBF_OLED_Fill_XY(81, 0, 120, 40, color_table[(counter)%7]);
		    break;
		case 3:
           	     LBF_OLED_Fill_XY(81, 0, 120, 40, BLACK);
	             LBF_OLED_Fill_XY(121, 0, 160, 40, color_table[(counter)%7]);
		    break;
		case 4:
	            LBF_OLED_Fill_XY(121, 0, 160, 40, BLACK);
		    LBF_OLED_Fill_XY(0, 87, 40, 127, color_table[(counter)%7]);
		    break;
		case 5:
             	    LBF_OLED_Fill_XY(0, 87, 40, 127, BLACK);
             	     LBF_OLED_Fill_XY(41, 87, 80, 127, color_table[(counter)%7]);
		    break;
		case 6:
	             LBF_OLED_Fill_XY(41, 87, 80, 127, BLACK);
           	     LBF_OLED_Fill_XY(81, 87, 120, 127, color_table[(counter)%7]);
		    break;
		case 7:  
		default:          
	             LBF_OLED_Fill_XY(81, 87, 120, 127, BLACK);
		     LBF_OLED_Fill_XY(120, 87, 160, 127, color_table[(counter)%7]);
		     index = 0;
	        }
	      }

	    if (counter++ == MAX_COUNTER)
		counter = 0;

	}

    // ===  Calibrate Magnetometer (offset cancel) under user control ====
	if ( LBF_State_Switch1_IsOn() )  //if side-push button pressed
	{
	    Get_ZeroGauss_OffsetXYZ( &MField_X_Offset, &MField_Y_Offset,  &MField_Z_Offset );
	    Display_TextInfo();
	}



    // ===  Magnetometer: Capture  ========================================

        LBF_Led_ON();

        // SINGLE SHOT conversion : CTRL_REG3 @0x22 :   
         LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_3_REG, 0x01);  // 0b00000001


	// Wait until data available from Magnetometer
        do 
        {
            ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
			 LIS3MDL_STATUS_REGISTER_REG);  // Status Reg
        } while ( (ReadValue & 0x08) != 0x08);  // bit set when new XYZ data available


        LBF_Led_OFF();


        // --- Read Results :------------------------------------------------
    
	 MField_X_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_X_LOW_REG);
	 MField_X_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_X_HIGH_REG);

	 MField_Y_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Y_LOW_REG);
	 MField_Y_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Y_HIGH_REG);

	 MField_Z_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Z_LOW_REG);
	 MField_Z_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Z_HIGH_REG);


         // --- Compensate Results :------------------------------------------------
         MField_X_Comp =
           (int16_t)( (MField_X_HighByte <<8 ) | MField_X_LowByte ) - MField_X_Offset;
         MField_Y_Comp =
           (int16_t)( (MField_Y_HighByte <<8 ) | MField_Y_LowByte ) - MField_Y_Offset;
         MField_Z_Comp =
           (int16_t)( (MField_Z_HighByte <<8 ) | MField_Z_LowByte ) - MField_Z_Offset;

         MField_X_Comp_LowByte =  (uint8_t)(MField_X_Comp & 0x00FF);
         MField_X_Comp_HighByte = (uint8_t)((MField_X_Comp & 0xFF00) >>8);

         MField_Y_Comp_LowByte =  (uint8_t)(MField_Y_Comp & 0x00FF);
         MField_Y_Comp_HighByte = (uint8_t)((MField_Y_Comp & 0xFF00) >>8);

         MField_Z_Comp_LowByte =  (uint8_t)(MField_Z_Comp & 0x00FF);
         MField_Z_Comp_HighByte = (uint8_t)((MField_Z_Comp & 0xFF00) >>8);



    // ===  Accelerometer: Capture  ========================================

/*
        Stm32_Led_ON();

	// Wait until data available from Accelerometer
        do 
        {
            ReadValue = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x1E);  // Status Reg
        } while ( (ReadValue & 0x01) != 0x01);  // bit set when new XYZ data available

        Stm32_Led_OFF();


        // --- Read Results :------------------------------------------------

	 Accel_X_LowByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x28);
	 Accel_X_HighByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x29);

	 Accel_Y_LowByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2A);
	 Accel_Y_HighByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2B);   
       
	 Accel_Z_LowByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2C);
	 Accel_Z_HighByte = I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2D);   
*/
Accel_X_LowByte = 0; Accel_X_HighByte = 0;
Accel_Y_LowByte = 0; Accel_Y_HighByte = 0;
Accel_Z_LowByte = 0; Accel_Z_HighByte = 0;



    // ===  Transmit Results  ========================================

        // --- Start of Frame (SOF) :---------------------------------

         LBF_UART_BLE_SendByte (0x11); 

         LBF_UART_BLE_SendByte (0x22); 

         LBF_UART_BLE_SendByte (0x33); 

         LBF_UART_BLE_SendByte (0x44); 


        // --- Magnetometer Resuts :---------------------------------

         LBF_UART_BLE_SendByte (MField_X_Comp_LowByte); 

         LBF_UART_BLE_SendByte (MField_X_Comp_HighByte); 

         LBF_UART_BLE_SendByte (MField_Y_Comp_LowByte); 

         LBF_UART_BLE_SendByte (MField_Y_Comp_HighByte); 

         LBF_UART_BLE_SendByte (MField_Z_Comp_LowByte); 

         LBF_UART_BLE_SendByte (MField_Z_Comp_HighByte); 



        // --- Accelerometer Resuts :---------------------------------

         LBF_UART_BLE_SendByte (Accel_X_LowByte); 


         LBF_UART_BLE_SendByte (Accel_X_HighByte); 

         LBF_UART_BLE_SendByte (Accel_Y_LowByte); 

         LBF_UART_BLE_SendByte (Accel_Y_HighByte); 

         LBF_UART_BLE_SendByte (Accel_Z_LowByte); 

         LBF_UART_BLE_SendByte (Accel_Z_HighByte); 

    }  // end of while(1)



return 0;
}


// ======= PRIVATE FUNCTIONS   =================================================


/* ---  Zero-Gauss Calibration of Magnetometer ----------------------- */

void  Get_ZeroGauss_OffsetXYZ( int16_t* pMField_X_Raw_Offset, int16_t* pMField_Y_Raw_Offset, int16_t* pMField_Z_Raw_Offset )
{

#define  NUM_CALIB_CIRCLES 1   
  // Calibration performed by taking 8 measurements 45deg apart, 
  // repeated NUM_CALIB_CIRCLES times

uint8_t i;
uint8_t		MField_X_LowByte, MField_X_HighByte;
uint8_t		MField_Y_LowByte, MField_Y_HighByte;
uint8_t		MField_Z_LowByte, MField_Z_HighByte;
int16_t		MField_X_Raw, MField_Y_Raw, MField_Z_Raw ;
int32_t		MField_X_Acc = 0, MField_Y_Acc = 0, MField_Z_Acc = 0;
uint16_t 	ColorSequence[8] = {RED, WHITE, GREEN, BLUE, CYAN, ORANGE, LIGHT_BLUE, YELLOW } ;  




  // ---  XY plane calibration ---------------------------------------

  // Display Instructions :
  LBF_OLED_Clear();
  GUI_DispStringAt("\n", 0,0);  // back to top left corner
  LBF_OLED_PrintString(" XY CALIBRATION\n\n");
  LBF_OLED_PrintString(" Lay La BlueFrog flat\n");
  LBF_OLED_PrintString(" Then rotate it 45 deg.\n  at each change of color:");
  LBF_Delay_ms(3000);
  LBF_OLED_Clear();

  // Go --- 8 equally spaced magnetic field measurements, repeatable n times per #define
  for (i=0; i < 8*NUM_CALIB_CIRCLES; i++)   
  {
          LBF_OLED_Fill( X_FULL_SCREEN/2 -20, Y_FULL_SCREEN/2-20, 40, 40, ColorSequence[i] );
          LBF_Delay_ms(2500);

	  LBF_Led_ON();

          // SINGLE SHOT conversion : CTRL_REG3 @0x22 :   
          LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
			LIS3MDL_CONTROL_REGISTER_3_REG, 0x01);  

          while ( (LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
			 LIS3MDL_STATUS_REGISTER_REG)& 0x08) != 0x08);  
                    // read status reg until it flags new XYZ data available

	  // Accumulate Results
	  MField_X_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_X_LOW_REG);
	  MField_X_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_X_HIGH_REG);
	  MField_X_Raw =  
	         (int16_t)( (MField_X_HighByte <<8 ) | MField_X_LowByte );
	  MField_X_Acc += (int32_t)(MField_X_Raw);

	  MField_Y_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Y_LOW_REG);
	  MField_Y_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Y_HIGH_REG);
	  MField_Y_Raw =  
	         (int16_t)( (MField_Y_HighByte <<8 ) | MField_Y_LowByte );
	  MField_Y_Acc += (int32_t)(MField_Y_Raw);


	  LBF_Led_OFF();
   }
 
   *pMField_X_Raw_Offset =  (int16_t)(MField_X_Acc / i);
   *pMField_Y_Raw_Offset =  (int16_t)(MField_Y_Acc / i);

   LBF_OLED_Clear();
   GUI_DispStringAt("", 10, 90);
   LBF_OLED_PrintString("XY CALIBRATION DONE,\n NOW LET'S DO Z\n");
   LBF_Delay_ms(3000);
   LBF_OLED_Clear();
//   OLED_Switch_OFF();

  // ---  XZ plane calibration ---------------------------------------

  // Display Instructions :
  GUI_DispStringAt("", 10, 10);
  LBF_OLED_PrintString("Z CALIBRATION\n\n");
  LBF_OLED_PrintString("Put La BlueFrog upright\n i.e. lid on top)\n");
  LBF_OLED_PrintString("Then rotate it 45 deg.\n around vertical axis \nat each change of color:");
  LBF_Delay_ms(4000);
  LBF_OLED_Clear();

  // Go --- 8 equally spaced magnetic field measurements, repeatable n times per #define
  for (i=0; i < 8*NUM_CALIB_CIRCLES; i++)   
  {
          LBF_OLED_Fill( X_FULL_SCREEN/2 -20, Y_FULL_SCREEN/2-20, 40, 40, ColorSequence[i] );
          LBF_Delay_ms(2500);

	  LBF_Led_ON();

          // SINGLE SHOT conversion : CTRL_REG3 @0x22 :   
          LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID,
		 LIS3MDL_CONTROL_REGISTER_3_REG, 0x01); 

          while ( (LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
			 LIS3MDL_STATUS_REGISTER_REG)& 0x08) != 0x08);  
                    // read status reg until it flags new XYZ data available

	  // Accumulate Results

	  MField_Z_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Z_LOW_REG);
	  MField_Z_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
				 LIS3MDL_MAGNETO_Z_HIGH_REG);
	  MField_Z_Raw =  
	         (int16_t)( (MField_Z_HighByte <<8 ) | MField_Z_LowByte );
	  MField_Z_Acc += (int32_t)(MField_Z_Raw);

	  LBF_Led_OFF();
   }
 
   *pMField_Z_Raw_Offset =  (int16_t)(MField_Z_Acc / i);

   GUI_DispStringAt("", 10, 90);
   LBF_OLED_PrintString("THANKS,\nCALIBRATION DONE !\n");
   LBF_Delay_ms(4000);
   LBF_OLED_Clear();

}


/* ---- Information Message at center of screen  ---- */

void Display_TextInfo()
{
    LBF_OLED_Clear();

   GUI_SetTextMode(GUI_TM_TRANS);
   GUI_SetFont(&GUI_Font13B_ASCII);
   GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
   GUI_DispStringAt( "Magnetom'r data over BLE",  X_FULL_SCREEN/2, Y_FULL_SCREEN/2);  

}


/***************************************************************END OF FILE****/// 
