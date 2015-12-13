/*******************************************************************************
 * LBF_Mic_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_Mic_IOcfg.h"


/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Configures IOs used to monitor battery voltage.
 * @param  : None.
 * @return : None.
 ******************************************************************************/
void LBF_Mic_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// PBO = MIC_ANA
// Analog ADC input, no pull-up/-down resistor
  GPIO_InitStruct.Pin = MIC_ANA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL; 
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  HAL_GPIO_Init(MIC_ANA_PORT, &GPIO_InitStruct); 

}





/***************************************************************END OF FILE****/
