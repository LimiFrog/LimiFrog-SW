/*******************************************************************************
 * LBF_SPI3_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "LBF_lowlev_API.h"

#include "LBF_SPI3_IOcfg.h"



/*******************************************************************************
 * @brief  : Configuration of GPIOs used by SPI #3
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI3_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __SPI3_CLK_ENABLE();
  
    /**SPI1 GPIO Configuration    
    PB3     ------> SPI3_SCK
    PB4     ------> SPI3_MISO
    PB5     ------> SPI3_MOSI 
    */
    GPIO_InitStruct.Pin = SPI3_SCK_PIN|SPI3_MISO_PIN|SPI3_MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(SPI3_PORT, &GPIO_InitStruct);

}





/***************************************************************END OF FILE****/
