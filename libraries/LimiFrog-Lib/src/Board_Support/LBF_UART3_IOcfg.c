/*************************************************************************
 * LBF_UART3_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"

#include "LBF_UART3_IOcfg.h"

/*******************************************************************************
* @brief  : Initialize & configure pins for UART1 alternate function
* Input          : None.
* Return         : None.
*******************************************************************************/

#ifndef  __LBF_LEGACY   // UART1 rather than UART3 was used for exchanges with BLE 
		       //  before LimiFrog 0.1, UART3 wasn't available

void LBF_UART3_IOcfg (void)
{
//Based on Cube MX

GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __USART3_CLK_ENABLE();
  
    // ---  TX and RX pins  -----------------------------

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;

    GPIO_InitStruct.Pin = UART3_TX_PIN;
    HAL_GPIO_Init(UART3_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = UART3_RX_PIN;
    HAL_GPIO_Init(UART3_RX_PORT, &GPIO_InitStruct);

    // ---  CTS/RTS pins (hw flow control)  -------------

    GPIO_InitStruct.Pull = GPIO_PULLDOWN;  
    // so (n)CTS and (n)RTS are asserted if no-one drives these lines
    // therefore UART comm takes place just as tough hw flow control were disabled

    GPIO_InitStruct.Pin = UART3_RTS_PIN;
    HAL_GPIO_Init(UART3_RTS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = UART3_CTS_PIN;
    HAL_GPIO_Init(UART3_CTS_PORT, &GPIO_InitStruct);

}

#endif

/***************************************************************END OF FILE****/

