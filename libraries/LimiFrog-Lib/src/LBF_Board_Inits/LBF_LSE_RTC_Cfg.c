/*******************************************************************************
 * LBF_LSE_RTC_Cfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

#include "LBF_LSE_RTC_Cfg.h"
#include "LBF_lowlev_API.h"


/* Privates prototypes -------------------------------------------------------*/


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/


void LBF_LSE_RTC_Cfg(void)
{
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  // To allow write access to RTC periph
  __HAL_RCC_PWR_CLK_ENABLE(); //normally already done, also done in HAL_RCC_OscConfig...
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_BACKUPRESET_FORCE(); // reset back-up domain
  __HAL_RCC_BACKUPRESET_RELEASE();


  // Enable LSE Oscillator 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON; 
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) 
  { 
    // Error_Handler();
  }


  // RTC Clock Inits
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;  // external 32.768KHz
  if ( HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK )
  { 
    // Error_Handler();
  }

  // Enable RTC peripheral clock
  __HAL_RCC_RTC_ENABLE();

}



/***************************************************************END OF FILE****/
