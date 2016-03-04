/*******************************************************************************
 * LBF_PWR_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "LBF_lowlev_API.h"


/* Static variables:  
   accessible only from this C file and retain their value 
   between different calls of the functions where they're used */
static bool VDDH_On;



/* =====    OLED related   =========================================*/

/************
* Function :	bool LBF_Check_VDDH_On(void)
* Description :	Checks whether the high voltage VDDH (13V) for the OLED display has been enabled or not.
* Parameters :  -
* Return Value: True if VDDH has been enabled, else false
**************/

bool LBF_Check_VDDH_On (void)
{
    return VDDH_On;
}



/****************
Function :	void LBF_Turn_VDDH_On(void)
Description :	Enable high voltage VDDH (13V) to  OLED display 
Parameters :  -
Return Value: -
****************/

void LBF_Turn_VDDH_On (void)
{
    GPIO_HIGH(VDDH_EN_PORT, VDDH_EN_PIN);
    VDDH_On = true;
}



/****************
Function :	void LBF_Turn_VDDH_Off(void)
Description :	Disable high voltage VDDH (13V) to  OLED display 
Parameters :  -
Return Value: -
****************/

void LBF_Turn_VDDH_Off (void)
{
    GPIO_LOW(VDDH_EN_PORT, VDDH_EN_PIN);
    VDDH_On = false;
}



/* =====    VCC_LDO related   =========================================*/



/**************
* Function :	void LBF_Enable_LDO(void)
* Description :	Enable LDO, VCC_LDO (3.3V) available on extension port 
* Parameters :  -
* Return Value: -
***************/

void LBF_Enable_LDO(void)
{
    GPIO_HIGH( LDO_ON_PORT, LDO_ON_PIN);
}




/**************
* Function :	void LBF_Disable_LDO(void)
* Description :	Disable LDO
* Parameters :  -
* Return Value: -
***************/

void LBF_Disable_LDO(void)
{
    GPIO_LOW( LDO_ON_PORT, LDO_ON_PIN);
}




/***************************************************************END OF FILE****/
