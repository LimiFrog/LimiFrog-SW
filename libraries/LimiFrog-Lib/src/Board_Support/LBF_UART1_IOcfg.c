/*************************************************************************
 * LBF_UART1_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_UART1_IOcfg.h"

/*******************************************************************************
* @brief  : Initialize & configure pins for UART1 alternate function
* Input          : None.
* Return         : None.
*******************************************************************************/

#ifdef  __LBF_LEGACY   // UART1 was used for exchanges with BLE
		       // changed to UART3 from LimiFrog 0.1, UART1 no longer available

void LBF_UART1_IOcfg (void)
{
//Based on Cube MX

GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> UART1_TX
    PA10     ------> UART1_RX 
    */
    GPIO_InitStruct.Pin = UART1_TX_PIN|UART1_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(UART1_PORT, &GPIO_InitStruct);

}

#endif

/***************************************************************END OF FILE****/

