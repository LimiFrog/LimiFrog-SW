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




/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Check whether VDDH to OLED has been enabled on the board
 * @param  : none.
 * @return : TRUE if VDDH is on, else FALSE
 ******************************************************************************/
bool Check_VDDH_On (void)
{
    return VDDH_On;
}

/*******************************************************************************
 * @brief  : Enable generation of VDDH (14V) to OLED on the board 
 * @param  : none.
 * @return : none.
 ******************************************************************************/
void Turn_VDDH_On (void)
{
    GPIO_HIGH(VDDH_EN_PORT, VDDH_EN_PIN);
    VDDH_On = true;
}

/*******************************************************************************
 * @brief  : Disable generation of VDDH to OLED on the board 
 * @param  : xx.
 * @return : xx.
 ******************************************************************************/
void Turn_VDDH_Off (void)
{
    GPIO_LOW(VDDH_EN_PORT, VDDH_EN_PIN);
    VDDH_On = false;
}






/***************************************************************END OF FILE****/
