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
    Success &= LBF_LaunchUSB_MassStorage();
 
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

uint8_t ReadValue;



/* ==  Body     ====================================================== */

    LBF_OLED_Switch_ON();
    // Provide power (13V) to OLED panel, enable display

    LBF_OLED_PrintString("\n\n");

    /* ---     Check access to ALS/Proximity Sensor : ST VL6180X  --- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, VL6180X_WHOAMI);
    if (ReadValue == VL6180X_WHOAMI_CONTENTS)
    { 
       LBF_OLED_PrintString("  VL6180X OK \n  WHO_AM_I = ");
    }
    else 
    { 
       LBF_OLED_PrintString("  VL6180X FAIL \n  Reported WHO_AM_I = ");
    }
    LBF_OLED_PrintHex(ReadValue);
    LBF_OLED_PrintString("\n\n");


    /* ---     Check access to Magnetometer :  ST LIS3MDL   -------- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, LIS3MDL_WHOAMI);
    if (ReadValue == LIS3MDL_WHOAMI_CONTENTS)
    { 
       LBF_OLED_PrintString("  LIS3MDL OK \n  WHO_AM_I = ");
    }
    else 
    { 
       LBF_OLED_PrintString("LIS3MDL FAIL \n  Reported WHO_AM_I = ");
    }
    LBF_OLED_PrintHex(ReadValue);
    LBF_OLED_PrintString("\n\n");


    /* ---     Check access to Accelerometer/Gyro :  ST LSM6DS3  ----- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_WHOAMI);
    if (ReadValue == LSM6DS3_WHOAMI_CONTENTS)
    { 
       LBF_OLED_PrintString("  LSM6DS3 OK \n  WHO_AM_I = ");
    }
    else 
    { 
       LBF_OLED_PrintString("  LSM6DS3 FAIL \n  Reported WHO_AM_I = ");
    }
    LBF_OLED_PrintHex(ReadValue);
    LBF_OLED_PrintString("\n\n");


    /* ---     Check access to Pressure/Temp Sensor : ST LPS25H  ----- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_WHOAMI);
    if (ReadValue == LPS25H_WHOAMI_CONTENTS)
    { 
       LBF_OLED_PrintString("  LPS25H OK \n  WHO_AM_I = ");
    }
    else 
    { 
       LBF_OLED_PrintString("  LPS25H FAIL \n  Reported WHO_AM_I = ");
    }
    LBF_OLED_PrintHex(ReadValue);
    LBF_OLED_PrintString("\n\n");


    while(1);

}


/***************************************************************END OF FILE****/
