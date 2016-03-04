/*******************************************************************************
 * LBF_Global.h
 ******************************************************************************/


// =============================================================================
// This files contains all the includes that are typically required when
// writing a main() program for LimiFrog
// =============================================================================

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GLOBAL_H
#define __LBF_GLOBAL_H


// --- ST's HAL and CMSIS Libraries   -----------
// #include "stm32l4xx.h" - TRY THIS:
#include "stm32l4xx_hal.h" 


// ---  For LimiFrog Board Initializations -----
//      Called from main()
#include "LBF_Board_Inits.h"  // pulls next two
#include "LBF_Board_Fixed_Inits.h"
#include "LBF_Board_Selective_Inits.h"


// ---  APIs to LimiFrog Hardware USB_  ----------
#include "LBF_lowlev_API.h"


// ---  Utilities   -----------------------
#include "LBF_Led_Based_Debug.h"
#include "xprintf.h"

// ---  Sensor APIs :   ----------------------

// LSM6DS3 Accelero + Gyro
#include "LBF_lsm6ds3.h"

// LPS25H Pressure Sensor
#include "LBF_lps25h.h"

// VL6180X Distance & Proximity Detector / ALS
#include "LBF_vl6180x.h"

// LIS3MDL Magnetometer
#include "LBF_lis3mdl.h"

// ---  MiddleWare APIs :   ----------------------

// emWin Graphics Library
#include "LBF_emWin_Init.h" // for inits called from main()
#include "WM.h" // to use emWin Windows Manager
#include "GUI.h"  // to use emWin API

// FatFS File System
#include "ff_gen_drv.h"   // in turn, pulls ff.h and diskio.h
// #include "DataFlash_diskio.h"
#include "LBF_FatFS_Init.h" // for inits called from main()

// USB Device Drivers
#include "LBF_USB_MassStorage.h"


// ---  To use ARM's DSP and floating point libraries ---
#define  ARM_MATH_CM4
#include "arm_math.h"


// ---  Central file to hold user-defined IT priorities ---
#include "IT_Priorities_UserDefinable.h"


#endif  /*__LBF_GLOBAL_H*/

/***************************************************************END OF FILE****/
