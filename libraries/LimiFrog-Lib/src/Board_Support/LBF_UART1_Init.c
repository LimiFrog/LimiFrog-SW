/*************************************************************************
 * LBF_UART1_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"
#include "LBF_UART1_Init.h"

UART_HandleTypeDef huart1;  // global variable used by HAL functions 



/*******************************************************************************
* Description  : Configures GPIO connected to header pins - either as std GPIO or as selected alternate function
* Input          : None.
* Return         : None.
*******************************************************************************/

void LBF_UART1_Init (uint32_t BaudRate)
{
// Based on Cube MX

  huart1.Instance = USART1;
  huart1.Init.BaudRate = BaudRate;  
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/***************************************************************END OF FILE****/
