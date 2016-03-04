/*************************************************************************
 * LBF_UART3_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"
//#include "LBF_UART3_Init.h"

UART_HandleTypeDef huart3;  // global variable used by  HAL functions 



/*******************************************************************************
* Description  : Configures GPIO connected to header pins - either as std GPIO or as selected alternate function
* Input          : None.
* Return         : None.
*******************************************************************************/

void LBF_UART3_Init (uint32_t BaudRate)
{
// Based on Cube MX

  huart3.Instance = USART3;
  huart3.Init.BaudRate = BaudRate;  
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS; // CTS and RTS hw flow control enabled
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart3);

}

/***************************************************************END OF FILE****/
