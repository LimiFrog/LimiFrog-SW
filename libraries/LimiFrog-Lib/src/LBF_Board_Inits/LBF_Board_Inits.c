/*******************************************************************************
 * LBF_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_Board_Fixed_Inits.h"
#include "LBF_Board_Selective_Inits.h"

/***********
* Function :
	void LBF_Board_Inits(void)
* Description : 
	Performs all the low-level hardware intializations required to have the LimiFrog board up and running : set-up of all clocks, NVIC initialization, set-up of all I/Os and STM32 peripherals dedicated to on-board communications, etc.
* Parameters :
	  -
* Return Value:
	  -
* Note: 
	This function calls LBF_Board_Selective_Inits(, which requires a valid User_Configuration.h file to be present in the include file (typically under /LimiFrog_SW/projects/xxx/inc, see proposed project template), to drive the « selective » part of the intialization process 
***********/

void LBF_Board_Inits(void) 
{

    LBF_Board_Fixed_Inits();

    LBF_Board_Selective_Inits();
	// actions driven by User_Configuration.h

}




/***************************************************************END OF FILE****/
