/*******************************************************************************
 * LBF_USB_IOcfg.c
* 
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"

#include "LBF_USB_IOcfg.h"



/*******************************************************************************
 * @brief  : Configuration of IOs used by USB (device mode)
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_USB_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

 
  /* Configure DM DP Pins */
  GPIO_InitStruct.Pin = (USB_DM_PIN | USB_DP_PIN);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;  // USE SMOOTHER SLEW RATE ?
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(USB_PORT, &GPIO_InitStruct); 
  

  /* ID-sense pin (defined for OTG) not used here as we only offer device mode */

  /* Vbus-sense not available on earlier versions than LimiFrog 0.1 */
#ifndef __LBF_LEGACY 
  GPIO_InitStruct.Pin = VBUS_SENSE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(USB_PORT, &GPIO_InitStruct);
#endif
  
}





/***************************************************************END OF FILE****/
