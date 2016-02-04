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

#include "stm32l4xx_ll_dma.h"  // Low-layer driver for DMA

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
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;  //separate Tx and Rx(not used) lines

  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
			// set to 8-bit by default, so when SPI used to transfer
			// rgb565 on 16-bits, will have to be temporarily changed

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


	
  // ---    Also prepare DMA for possible use by SPI1    ----------

  // --> only TX needed as SPI1 is for OLED which cannot be read.
  // SPI1 TX is on Channel 3 of DMA1 (see User Man 11.4.7)
  // and uses request line (dreq) #1 for this channel (see Table 38)
 
  __DMA1_CLK_ENABLE();

  // Using below Low-Level Driver rather than HAL :

  // Configure  DMA1_Channel3 functional parameters :
  LL_DMA_ConfigTransfer(DMA1, 
			LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT | 
                        LL_DMA_PDATAALIGN_WORD |   
			LL_DMA_MDATAALIGN_HALFWORD);  // DMA expected to be used for rgb565 data on 16 bits

  // Assign request line
  LL_DMA_SetPeriphRequest(DMA1,LL_DMA_CHANNEL_3, LL_DMA_REQUEST_1); 

  // Enable DMA interrupts on DMA Tx complete and DMA error 
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);  // DMA Tx Complete IT 
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_3);  // DMA error
	// note: this will set IT flags internally to DMA periph
	// but won't trigger IT on Cortex core as long as NVIC not set


}



/***************************************************************END OF FILE****/
