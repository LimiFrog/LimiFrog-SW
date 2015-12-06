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



/*******************************************************************************
* Function Name  : Stm32_Led_ON
* Description    : Switched Red LED On.
* Return         : None.
*******************************************************************************/
void LBF_Led_ON(void)
{
    GPIO_HIGH(STM32_LED_PORT, STM32_LED_PIN);
}

/*******************************************************************************
* Function Name  : Stm32_Led_OFF
* Description    : Switched Red LED Off.
* Return         : None.
*******************************************************************************/
void LBF_Led_OFF(void)
{
    GPIO_LOW(STM32_LED_PORT, STM32_LED_PIN);
}

/*******************************************************************************
* Function Name  : Stm32_Led_TOGGLE
* Description    : Toggles Red LED.
* Return         : None.
*******************************************************************************/
void LBF_Led_TOGGLE(void)
{
    GPIO_TOGGLE(STM32_LED_PORT, STM32_LED_PIN);
}




/*******************************************************************************
* Function Name  : Get_Slider_Select1
* Description    : Determines if slider is in position #1.
* Return         : True/False
*******************************************************************************/
bool LBF_State_Switch1_IsOn(void)
{
// Push-button SWITCH1 has changed polarity with LimiFrog0.1
// Default (unpressed) output used to be Logic1, now is Logic0

#ifdef __LBF_LEGACY
  return( (HAL_GPIO_ReadPin(SWITCH1_PORT, SWITCH1_PIN)==GPIO_PIN_RESET)? true:false );
#else
  return( (HAL_GPIO_ReadPin(SWITCH1_PORT, SWITCH1_PIN)==GPIO_PIN_RESET)? false:true );
#endif
}
// Physical switch connects signal to GND when pressed ('on')


/*******************************************************************************
* Function Name  : Get_Slider_Select2
* Description    : Determines if slider is in position #2.
* Return         : True/False
*******************************************************************************/
bool LBF_State_Switch2_IsOn(void)
{
// Push-button SWITCH2 has changed polarity with LimiFrog0.1
// Default (unpressed) output used to be Logic1, now is Logic0

#ifdef __LBF_LEGACY
  return( (HAL_GPIO_ReadPin(SWITCH2_PORT, SWITCH2_PIN)==GPIO_PIN_RESET)? true:false );
#else
  return( (HAL_GPIO_ReadPin(SWITCH2_PORT, SWITCH2_PIN)==GPIO_PIN_RESET)? false:true );
#endif
}
// Physical switch connects signal to GND when pressed ('on')

/***************************************************************END OF FILE****/
