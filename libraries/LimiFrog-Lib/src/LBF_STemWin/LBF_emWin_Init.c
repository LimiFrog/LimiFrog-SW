/*******************************************************************************
 * LBF_emWin_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "WM.h" //Windows Manager
#include "GUI.h"

#include "LBF_lowlev_API.h"

/* Private variables ---------------------------------------------------------*/



/* Functions -----------------------------------------------------------------*/


bool LBF_emWin_Init(void) 
{

    // The CRC module (in RCC peripheral clock enable register) must be enabled 
    //  before using the STemWin library
    // It has already been enabled in stm32l4xx_hal_conf.h)
    // Also need to enable the Peripheral clock  
    __CRC_CLK_ENABLE();
    // RCC->AHBENR |= (RCC_AHBENR_CRCEN);

    // Activate the use of memory device feature 
    WM_SetCreateFlags(WM_CF_MEMDEV);

    // Init the STemWin GUI Library */
    return ( GUI_Init() == 0);

}
 


void LBF_emWin_DeInit(void) 
{
    // DeInit the STemWin GUI Library */
    GUI_Exit() ;
}

/***************************************************************END OF FILE****/
