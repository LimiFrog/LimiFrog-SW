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

#include "LBF_Led_Based_Debug.h" 

/**************
* Function :	
	void LBF_Board_Selective_Inits(void)
* Description :	
	Performs all « selective » initializations, which depend on some user choices,  expressed as directives in a user configuration file « User_Configuration.h ».
Selective initializations include :
> configuring the STM32 IO that are routed to the extension port according to user's wishes
> configuring the BlueTooth Low-Energy Module if its usage is enabled by the user
> initializing the OLED display controller if usage of the OLED is enabled by the user
Parameters : 
	 -
* Return Value:  
	-
* Notes: 
	1) LBF_Board_Inits() combines LBF_Board_Fixed_Inits() and LBF_Board_Selective_Inits() in a single function call.
	2) Make sure User_Configuration.h contains all the required information for this function to configure the OLED, the BLE module and the extension port I/Os as desired. See the proposed template configuration file (…/projects/LimiFrog_PROJECT_TEMPLATE) for guidance. 
**************/

void LBF_Board_Selective_Inits(void) 
{

/******************************************************************
 * Actions performed by following functions 
 * depend on user settings in user file User_Configuration.h   
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
