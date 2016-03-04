/*******************************************************************************
 * LBF_OLED_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"
#include "LBF_OLED_IOcfg.h"

/*******************************************************************************
 * @brief  : Initialise et configure le peripherique I2C.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_IOcfg (void)
{

GPIO_InitTypeDef GPIO_InitStruct;
 
  // GENERAL: Std CMOS outputs, no pull resistor
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  // OLED SPI CS, active low:  OLED_CS = PC5
  GPIO_InitStruct.Pin = OLED_CS_PIN;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(OLED_CS_PORT, &GPIO_InitStruct);

  // OLED Parameter&Data (high)/ Command (low) Selection:  OLED_RS = PC4
  GPIO_InitStruct.Pin = OLED_RS_PIN;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(OLED_RS_PORT, &GPIO_InitStruct);
 
  // Reset of OLED drive chip SEPS525, active low:  OLED_RESET = PB1
  GPIO_InitStruct.Pin = OLED_RESET_PIN;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(OLED_RESET_PORT, &GPIO_InitStruct);


  // Initial configuration of NCS, RS, NRESET
  LBF_OLED_RESET_LOW();
  LBF_OLED_RS_HIGH();
  LBF_OLED_CS_HIGH();
  LBF_OLED_RESET_HIGH();



}


/***************************************************************END OF FILE****/
