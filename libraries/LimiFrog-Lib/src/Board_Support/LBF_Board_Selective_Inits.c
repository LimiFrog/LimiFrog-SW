/*******************************************************************************
 * LBF_Board_Seelective_Inits.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_Board_Selective_Inits.h"

#include "LBF_User_Conf.h"

#include "LBF_ExtPort_Config.h"

#include "LBF_lowlev_API.h"

#include "LBF_BTLE_Init.h"

#include "LBF_OLED_Init.h"

#include "User_Configuration.h"  //configuration file in user's project

#include "Debug_Utilities.h" 


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/



void LBF_Board_Selective_Inits(void) 
{

/******************************************************************
 * Actions performed by following functions 
 * depend on user settings in user file LBF_User_Conf.c   
 *****************************************************************/


LBF_ExtPortConfig_t   ExtPortConfig ;
LBF_ExtPortConfig_t* pExtPortConfig = &ExtPortConfig;


/* ------- Configurations and inits for external connector  ---- */
/* --       as required according to user settings          ---- */
/* --       defined in his own file "LBF_User_Conf.c"       ---- */

    // Retrieve user Configuration (call his config function)
    LBF_User_Conf(pExtPortConfig);

    // Configure accordingly
    LBF_ExtPortConfig(pExtPortConfig); 



/* --------  OLED Screen  --------------------------------------  */


#ifdef  USE_OLED  // (defined in User_Configuration.h)
    LBF_OLED_Init(NULL);  
    //sets up OLED with default config - screen not yet powered here
#endif



/* --------  BlueTooth Low-Energy Module   ---------------------  */

#ifdef ENABLE_BTLE   // defined in User_Configuration.h
bool Success;

    Success = LBF_BTLE_Init(BTLE_CODE_FILENAME);
               /*  BTLE_CODE_FILENAME alias defined in User_Config.h */
	       /* Look for this binary file in File System          */
               /*  (-->Data Flash) and load it into BTLE module     */
    
    // Note:
    // Before returning, LBF_BTLE_Init() updates Baud Rate of UART 
    // used for BLE comm with value specified in User_Configuration.h 
    // so that UART is ready to use by application for STM32-BTLE exchanges

    LBF_Led_StopNBlinkOnFalse (Success); 

#endif

}





/***************************************************************END OF FILE****/
