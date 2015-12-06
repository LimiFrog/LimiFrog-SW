/*******************************************************************************
 * LBF_SPI1_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"
#include "LBF_SPI1_Init.h"


SPI_HandleTypeDef hspi1;  // global variable used by SPI HAL functions 


/*******************************************************************************
 * @brief  : Initialization of SPI #1
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI1_Init(void)
{
  // Copied from HAL MX Generator
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;

  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;

  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; 
	// SPI1 is on APB2 in STM32L4 which is clocked at 20MHz
	// Leads to baudrate = APB2CLK/2 = 10 Mbit/s
	// Caution: OLED supports up to 16Mb/s SPI max
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  HAL_SPI_Init(&hspi1);

}



/***************************************************************END OF FILE****/
