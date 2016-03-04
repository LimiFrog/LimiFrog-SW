/*******************************************************************************
 * LBF_I2C2_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_I2C2_IOcfg.h"


/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialize & configure pins for I2C  #2.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_I2C2_IOcfg (void)
{
GPIO_InitTypeDef GPIO_InitStruct;


    /* Peripheral clock enable */
     __I2C2_CLK_ENABLE();
  
  
    /**I2C2 GPIO Configuration    
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA 
    */
    GPIO_InitStruct.Pin = I2C2_SCL_PIN|I2C2_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(I2C2_PORT, &GPIO_InitStruct) ;

}


/***************************************************************END OF FILE****/
