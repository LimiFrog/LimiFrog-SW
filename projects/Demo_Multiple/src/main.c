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




/* --  Private Functions ----------------------------------------  */

static void   VL6180X_Tuning_Settings(void);

void 	SplashScreen(void);
void 	Carroussel_Demo(void);
void 	Tilt_Demo(void);
void 	DistEval_Demo(void);
void 	Pressure_Voltage(void);
void    Accelero_Viz(void);
void    Magneto_FFT_Demo(void);
 
void 	NextDemoRequest_Init(void);

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

uint8_t	DemoStep = 0;



/* ==  Body     ======================================== */



// ===  User Initializations  ===  

    LBF_OLED_Switch_ON();
    // Provide power (13V) to OLED panel, enable display


    // -- VL6180X Inits -------------------------------------------

    //Check VL6180X can be accessed
    Success = ( LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, VL6180X_WHOAMI) == VL6180X_WHOAMI_CONTENTS);
    LBF_Led_StopNBlinkOnFalse ( Success );


    // Make sure VL6180X is out of reset before continuing
    while ( LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, 0x0016) != 0x01);

    // Clear out-of-reset bit
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0016, 0x00);

    //Apply Tuning Settings
    VL6180X_Tuning_Settings();


    // -- Inits for detecting next demo request (ADC WDog) --------       
    NextDemoRequest_Init();


// ===  Main Loop  ===  


while (1)
{

    switch( DemoStep)    
    { 
        case 0 :	SplashScreen();
        break;

        case 1 :	Carroussel_Demo();
        break;

        case 2 :	Accelero_Viz();
        break;
 
        case 3 :	Magneto_FFT_Demo();
        break;
 
        case 4 :	DistEval_Demo();
        break;

        case 5 :	Pressure_Voltage();  //Only pressure shown for now
        break;

        default :	SplashScreen();
 
    }

    if(DemoStep++ == 5)  DemoStep = 0;
}

}  // end of main()



/****  PRIVATE FUNCTIONS  of main()      **************************/

 

void VL6180X_Tuning_Settings(void)
{
/* as per AN DT0037 Rev 1 from ST */
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0207, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0208, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0133, 0x01); 
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
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0109, 0x07);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x010a, 0x30);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x003f, 0x46);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01a6, 0x1B);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01ac, 0x3E);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x01a7, 0x1F);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0103, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0030, 0x00);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x001b, 0x0A);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x003e, 0x0A);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0131, 0x04);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0011, 0x10);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0014, 0x24);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0031, 0xFF);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00d2, 0x01);
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x00f2, 0x01);
}


/**************************************END OF FILE****/// 
