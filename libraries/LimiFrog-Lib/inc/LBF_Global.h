/*******************************************************************************
 * LBF_Global.h
 ******************************************************************************/


// =============================================================================
// This files contains all the includes that are typically required when
// writing a main() program for La BlueFrog
// =============================================================================

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GLOBAL_H
#define __LBF_GLOBAL_H


// --- ST's HAL and CMSIS Libraries   -----------
#include "stm32l4xx.h"


// ---  La BlueFrog's Board Initializations -----
//#include "LBF_Board_Init.h"
#include "LBF_Board_Fixed_Inits.h"
#include "LBF_Board_Selective_Inits.h"
#include "LBF_OLED_Init.h"
#include "LBF_ExtPort_Config.h"


// ---  APIs to La BlueFrog Hardware   ----------
#include "LBF_lowlev_API.h"


// ---  Debug Utilities   -----------------------
#include "Debug_Utilities.h"


// ---  Sensor APIs :   ----------------------

// LSM6DS3 Accelero + Gyro
#include "LBF_lsm6ds3.h"

// LPS25H Pressure Sensor
#include "LBF_lps25h.h"


// ---  MiddleWare APIs :   ----------------------

// emWin Graphics Library
#include "LBF_emWin_Init.h"
#include "WM.h" // if using emWin Windows Manager
#include "GUI.h"  // if using emWin API

// FatFS File System
#include "ff_gen_drv.h"   // in turn, pulls ff.h and diskio.h
#include "DataFlash_diskio.h"
#include "LBF_FatFS_Init.h"

// USB Device Drivers
#include "LBF_LaunchUSB_MassStorage.h"




#endif  /*__LBF_GLOBAL_H*/

/***************************************************************END OF FILE****/
