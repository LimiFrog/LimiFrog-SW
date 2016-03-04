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


bool 	LBF_VL6180X_Init(void);
void 	LBF_VL6180X_Start_Continuous(void);
void 	LBF_VL6180X_Start_SingleShot(void);  // Not Used
void 	LBF_VL6180X_Disable(void);   // Not Used
uint16_t LBF_VL6180X_Get_Distance_mm();
void 	VL6180X_Tuning_Settings(void);


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


uint16_t  	Distance_mm;
uint8_t		CoarseRange;
uint16_t 	ColorTable[7] = {0x319F, 0x001F, 0x001C, 0x0017, 0x0013, 0x000F, 0x000C } ;
#define 	ORIG_BAR_X	120
#define 	ORIG_BAR_Y	10
#define 	SEGMENT_HEIGHT	15	
#define 	WIDTH_BAR	30		 
uint8_t		Slice[7] = {0, 0, 0, 0, 0, 0, 0} ;
uint8_t		i;	 


/* ==  Body     ====================================================== */

    LBF_OLED_Switch_ON();
    // Provide power (13V) to OLED panel, enable display


   /* ---     Display Scale for Proximity Results    ----------- */

   LBF_OLED_Clear();

   GUI_SetColor(0xFFFFFF);  // White
   GUI_SetTextMode(GUI_TM_TRANS);  // write with transparent background

   GUI_SetFont(&GUI_Font16_1);
   GUI_DispStringAt("How Far ?", 4 , 30);  

   GUI_SetFont(&GUI_Font13_1);
   GUI_DispStringAt("20cm --- ", ORIG_BAR_X - 30, 
		ORIG_BAR_Y +4);  
   GUI_DispStringAt("10cm --- ", ORIG_BAR_X - 30, 
		ORIG_BAR_Y+ (3*SEGMENT_HEIGHT) + (SEGMENT_HEIGHT>>2) +4);  
   GUI_DispStringAt(" 0cm --- ",  ORIG_BAR_X - 30, 
		ORIG_BAR_Y+ (6*SEGMENT_HEIGHT) + (SEGMENT_HEIGHT>>2) +4 );  



  /* ---     Initialize VL6180X               ------------------ */

    LBF_Led_StopNBlinkOnFalse( 
	LBF_VL6180X_Init() 
	);
	// stop here and blink LED in case of init error

    LBF_VL6180X_Start_Continuous();


    while (1)
    {

       Distance_mm = LBF_VL6180X_Get_Distance_mm();

       if (Distance_mm > 220)
			Distance_mm = 220;

       CoarseRange = Distance_mm / 32;	// 0 to 6

        // Display Bars according to distance

         for (i=0; i<7; i++)
	 {   
		// If Slice was ON and needs to go OFF: redraw in black
		if ( (Slice[i]==1) && (CoarseRange < i) )
		{
              	    LBF_OLED_Fill( ORIG_BAR_X, 
				ORIG_BAR_Y + (6-i)*SEGMENT_HEIGHT,		 
				WIDTH_BAR, SEGMENT_HEIGHT, 
				BLACK);
		    Slice[i] = 0;  // slice now OFF
		}
		else   // if slice was OFF and needs to go ON: 
		if  ( (Slice[i]==0) && (CoarseRange >= i) )
		{
                    LBF_OLED_Fill( ORIG_BAR_X, 
				ORIG_BAR_Y + (6-i)*SEGMENT_HEIGHT,		 
				WIDTH_BAR, SEGMENT_HEIGHT, 
				ColorTable[i] );
		    Slice[i] = 1;  // slice now ON
		 }
		 // else nothing to do: DON'T redraw (speed up rendering)

	 }  // end For


    }  // end of while(1)

}

/* ------------------------------------------------------------------ */
/* -- Private Functions ---------------------------------------------- */
/* ------------------------------------------------------------------ */

bool LBF_VL6180X_Init(void)
{

bool Success;

    // Check Access OK to VL6180X ALS + Proximity Sensor 
    Success = ( LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, VL6180X_WHOAMI) == VL6180X_WHOAMI_CONTENTS);

    // Make sure VL6180X is out of reset before continuing
    while ( LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, REG_SYSTEM_FRESH_OUT_OF_RESET) != 0x01);

    // Clear out-of-reset bit
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, REG_SYSTEM_FRESH_OUT_OF_RESET, 0x00);

    //Apply Tuning Settings
    VL6180X_Tuning_Settings();

    return Success;
}

/* ------------------------------------------------------------------ */

void    LBF_VL6180X_Start_Continuous(void)
{

    // Set bits [2:0] of Reg.0x14 to 0b100: enable internal IT on sample ready
    LBF_I2CSensors_RmodWSingleReg (VL6180X_CHIPID, REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x7, 0x4);

    // Start cont. range measurements
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, REG_SYSRANGE_START, 0x3);

}
// Note: only internal IT flag enabled here
// To use as EXTI on STM32, need to also enable relevant STM32 GPIOs as IT input
// and setup NVIC

/* ------------------------------------------------------------------ */

void    LBF_VL6180X_Start_SingleShot(void)
{

    // Set bits [2:0] of Reg.0x14 to 0b100: enable internal IT on sample ready
    LBF_I2CSensors_RmodWSingleReg (VL6180X_CHIPID, REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x7, 0x4);

    // Launch single shot range measurements
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, REG_SYSRANGE_START, 0x1);

}
// Note: only internal IT flag enabled here
// To use as EXTI on STM32, need to also enable relevant STM32 GPIOs as IT input
// and setup NVIC


/* ------------------------------------------------------------------ */

void    LBF_VL6180X_Disable(void)
{

    // Force single shot, do not launch meas.
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, REG_SYSRANGE_START, 0x0);

    // Disable ranging IT 
    LBF_I2CSensors_RmodWSingleReg (VL6180X_CHIPID, REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x7, 0x0);

    // Clear any pending ranging IT 
    LBF_I2CSensors_RmodWSingleReg (VL6180X_CHIPID, REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x1, 0x1);


}

/* ------------------------------------------------------------------ */

uint16_t  LBF_VL6180X_Get_Distance_mm()
{

uint16_t Distance_mm;

        // Wait until bits [2:0] of Reg.0x4F are 0b100 (measurement complete)
        while( (LBF_I2CSensors_ReadSingleReg(
		  VL6180X_CHIPID, 
		  REG_RESULT_INTERRUPT_STATUS_GPIO) 
		& 0x07) != 0x4 );

       // Read distance ("range value") in mm from Reg.0x0062
       Distance_mm = LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, REG_RESULT_RANGE_VAL);


       // Set bits [2:0] of Reg.0x15 to 0b111  (clear range interrupts)
       LBF_I2CSensors_RmodWSingleReg (VL6180X_CHIPID, REG_SYSTEM_INTERRUPT_CLEAR, 0x1, 0x1);


       return  Distance_mm;
}



/* ------------------------------------------------------------------ */

void VL6180X_Tuning_Settings(void)
{
/* as per AN DT0037 Rev 1 from ST */
// Update according to values used in latest ST API ?
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0207, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0208, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0133, 0x01); //gone 
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0096, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0097, 0xFD);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00e3, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00e4, 0x04);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00e5, 0x02);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00e6, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00e7, 0x03);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00f5, 0x02);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00D9, 0x05);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00DB, 0xCE);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00DC, 0x03);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00DD, 0xF8);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x009f, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00a3, 0x3C);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00b7, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00bb, 0x3C);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00b2, 0x09);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00ca, 0x09);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0198, 0x01);

    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01b0, 0x17);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01ad, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00FF, 0x05);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0100, 0x05);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0199, 0x05);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0109, 0x07); // gone 
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x010a, 0x30); // public reg
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x003f, 0x46); // public reg
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01a6, 0x1B);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01ac, 0x3E);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01a7, 0x1F);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0103, 0x01); // gone 
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0030, 0x00); // upscale
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x001b, 0x0A); // upscale
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x003e, 0x0A); // upscale
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0131, 0x04); // gone
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0011, 0x10); // public
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0014, 0x24); // public optional
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0031, 0xFF); // upscale
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00d2, 0x01); // gone
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00f2, 0x01); // gone
}



/***************************************************************END OF FILE****/
