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


#include "stm32l4xx_ll_dma.h"  // Low-layer driver for DMA

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



  // ---    Also prepare DMA for possible use by SPI3    ----------

  __DMA2_CLK_ENABLE();

  // Using below Low-Level Driver rather than HAL :

  // Configure  DMA functional parameters :

  // SPI3 TX (MOSI) is on Channel 2 of DMA2 (see User Man 11.4.7)
  // and uses request line (dreq) #3 for this channel (see Table 38)
  LL_DMA_ConfigTransfer(DMA2, 
			LL_DMA_CHANNEL_2, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT | 
                        LL_DMA_PDATAALIGN_BYTE | 
			LL_DMA_MDATAALIGN_BYTE);
  
  // SPI3 RX (MISO) is on Channel 1 of DMA2 (see User Man 11.4.7)
  // and uses request line (dreq) #3 for this channel (see Table 38)
  LL_DMA_ConfigTransfer(DMA2, 
			LL_DMA_CHANNEL_1, 
                        LL_DMA_DIRECTION_PERIPH_TO_MEMORY |  
			LL_DMA_PRIORITY_MEDIUM | 
			LL_DMA_MODE_NORMAL | 
                        LL_DMA_PERIPH_NOINCREMENT | 
			LL_DMA_MEMORY_INCREMENT | 
                        LL_DMA_PDATAALIGN_BYTE | 
			LL_DMA_MDATAALIGN_BYTE);



  // Assign request lines
  LL_DMA_SetPeriphRequest(DMA2,LL_DMA_CHANNEL_2, LL_DMA_REQUEST_3);   //SPI3 MOSI
  LL_DMA_SetPeriphRequest(DMA2,LL_DMA_CHANNEL_1, LL_DMA_REQUEST_3);   //SPI3 MISO


  // Enable DMA interrupts on DMA tsfer complete and DMA error for SPI3 MOSI
  LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_2);  // DMA Tsfer Complete IT 
  LL_DMA_EnableIT_TE(DMA2, LL_DMA_CHANNEL_2);  // DMA error
	// note: this will set IT flags internally to DMA periph
	// but won't trigger IT on Cortex core as long as NVIC not set

  // Enable DMA interrupts on DMA tsfer complete and DMA error for SPI3 MOSI
  LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_1);  // DMA Tsfer Complete IT 
  LL_DMA_EnableIT_TE(DMA2, LL_DMA_CHANNEL_1);  // DMA error
	// note: this will set IT flags internally to DMA periph
	// but won't trigger IT on Cortex core as long as NVIC not set

}



/***************************************************************END OF FILE****/
