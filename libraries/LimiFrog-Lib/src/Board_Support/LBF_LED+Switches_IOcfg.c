/*******************************************************************************
 * LBF_LED+Switches_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_LED+Switches_IOcfg.h"



/*******************************************************************************
* Function Name  : Led_Config
* Description    : configure the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/
void LBF_LED_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  // Standard output, no pull-up/-down resistor, low speed
  // STM32_LED (PC3)
  GPIO_InitStruct.Pin = STM32_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(STM32_LED_PORT, &GPIO_InitStruct);

}

/*******************************************************************************
* Function Name  : LBF_SelSwitches_IOcfg
* Description    : Configure the 2 selection switches 
* Input          : None.
* Return         : None.
*******************************************************************************/
void LBF_SelSwitches_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

// Push-button switches have changed polarity with LimiFrog0.1
#ifdef __LBF_LEGACY
  GPIO_InitStruct.Pull = GPIO_PULLUP;
#else
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
#endif

  //Slider Switch Position 1: SWITCH1 (PA15)    
  GPIO_InitStruct.Pin = SWITCH1_PIN;
  HAL_GPIO_Init(SWITCH1_PORT, &GPIO_InitStruct);

  //Slider Switch Position 2 SWITCH1 (PC8)    
  GPIO_InitStruct.Pin = SWITCH2_PIN;
  HAL_GPIO_Init(SWITCH2_PORT, &GPIO_InitStruct);


}





/***************************************************************END OF FILE****/
