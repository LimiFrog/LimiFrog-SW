/*******************************************************************************
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_SPI1_IOcfg.h"



/*******************************************************************************
 * @brief  : Configuration of GPIOs used by SPI #1
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI1_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __SPI1_CLK_ENABLE();


    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO --> unused, set as floating input
    PA7     ------> SPI1_MOSI 
    */

    GPIO_InitStruct.Pin = SPI1_SCK_PIN|SPI1_MOSI_PIN;    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW; //_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(SPI1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI1_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI1_PORT, &GPIO_InitStruct);
  
}





/***************************************************************END OF FILE****/
