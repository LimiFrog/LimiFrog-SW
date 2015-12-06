/*******************************************************************************
 * LBF_FLASH_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_FLASH_IOcfg.h"


 /* 
 *        +--------------------------------------------------------------+
 *        |                     Pin assignment                           |
 *        +-----------------------------+------------------+-------------+
 *        |  STM32 SPI Pins             | Adesto FLASH     |    Pin      |
 *        +-----------------------------+------------------+-------------+
 *        | FLASH_CS_PIN  - PB7         | ChipSelect(/CS)  |    4        |
 *        | FLASH_SPI_MISO_PIN / MISO   | SerialDataOut(SO)|    8        |
 *        | (VCC)                       | WriteProtect(/WP)|    5        |
 *        |                             | GND              |    7 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | SerialDataIn(SI) |    1        |
 *        | FLASH_SPI_SCK_PIN / SCK     | SerialClock(SCK) |    2        |
 *        | (VCC)                       | /RESET           |    3        |
 *        |                             | VCC              |    6 (3V)   |
 *        +-----------------------------+------------------+-------------+
 * 
 ******************************************************************************/



/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise the Adesto Data Flash.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// PB7 = /CS
// Std CMOS output, no pull-up/-down resistor, high speed
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL; 
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;  
  GPIO_InitStruct.Pin = FLASH_CS_PIN;
  HAL_GPIO_Init(FLASH_CS_PORT, &GPIO_InitStruct);


/* Initialise pin in high (inactive) state */
  LBF_FLASH_CS_HIGH();

}





/***************************************************************END OF FILE****/
