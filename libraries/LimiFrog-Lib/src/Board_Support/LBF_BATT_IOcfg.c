/*******************************************************************************
 * LBF_BATT_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_BATT_IOcfg.h"


/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Configures IOs used to monitor battery voltage.
 * @param  : None.
 * @return : None.
 ******************************************************************************/
void LBF_BATT_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// PC7 = BATT_MEAS_ENB (active low)
// Open-drain output, no pull-up/-down resistor, low speed
  GPIO_InitStruct.Pin = BATT_MEAS_ENB_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(BATT_PORT, &GPIO_InitStruct); 

// PC1 = BATT_ADC_MEAS_PIN
// Analog input, no pull-up/-down resistor
  GPIO_InitStruct.Pin = BATT_ADC_MEAS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  HAL_GPIO_Init(BATT_PORT, &GPIO_InitStruct); 

// Initialise measurement enable pin in high (inactive) state 
  GPIO_HIGH(BATT_PORT, BATT_MEAS_ENB_PIN );

}





/***************************************************************END OF FILE****/
