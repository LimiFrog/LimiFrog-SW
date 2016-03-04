/*******************************************************************************
 * LBF_LED+Switches_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"



// Functions :
// - void LBF_Led_ON(void),
// - void LBF_Led_OFF(void),
// - void LBF_Led_TOGGLE(void)
// are in the .h file to be in-linable everywhere they are used


/**********
Function :	bool LBF_State_Switch1_IsOn(void)
Description :	Returns the state of the general-purpose push-button switch  located at the edge of board 
Parameters :  -
Return Value:  true if button being pushed, else false
**********/

bool LBF_State_Switch1_IsOn(void)
{
// Push-button SWITCH1 has changed polarity with LimiFrog0.1
// Default (unpressed) output used to be Logic1, now is Logic0

  return( (HAL_GPIO_ReadPin(SWITCH1_PORT, SWITCH1_PIN)==GPIO_PIN_RESET)? false:true );

}
// Physical switch connects signal to VCC when pressed ('on')



/***************************************************************END OF FILE****/
