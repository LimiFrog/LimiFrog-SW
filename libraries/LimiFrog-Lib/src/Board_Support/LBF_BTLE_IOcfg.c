/*******************************************************************************
 * LBF_BTLE_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_BTLE_IOcfg.h"


/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise the Adesto Data Flash.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_BTLE_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// PC9 = BT_RST (active high)
// Std CMOS output, no pull-up/-down resistor, low speed
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;  
  GPIO_InitStruct.Pin = BT_RST_PIN;
  HAL_GPIO_Init(BT_RST_PORT, &GPIO_InitStruct);


/* Initialise pin in high (active) state */
  GPIO_HIGH(BT_RST_PORT, BT_RST_PIN); // assert BTLE reset

}





/***************************************************************END OF FILE****/
