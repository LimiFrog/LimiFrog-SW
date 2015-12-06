/*******************************************************************************
 * LBF_SPI3_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "LBF_lowlev_API.h"
#include "LBF_SPI3_Init.h"


SPI_HandleTypeDef hspi3;  // global variable used by SPI HAL functions 


/*******************************************************************************
 * @brief  : Initialization of SPI #3
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI3_Init(void)
{
  // Copied from HAL MX Generator
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	// SPI3 is on APB1 in STM32L4 which is clocked at 20MHz
	// Leads to baudrate = APB2CLK/1 = 10 Mbit/s
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  HAL_SPI_Init(&hspi3);

}



/***************************************************************END OF FILE****/
