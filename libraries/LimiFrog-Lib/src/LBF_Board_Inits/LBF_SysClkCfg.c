/*******************************************************************************
 * LBF_SysClkCfg
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_SysClkCfg.h"
#include "LBF_lowlev_API.h"


/* Privates prototypes -------------------------------------------------------*/


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/


/* ----------------------------------------------------------------------------
 *  Assumption: 8MHz external oscillator (HSE),  32KHz external Xtal (LSE)    *
 *  Want 80MHz core clock, 48 MHz USB clock, 1ms Timer Tick,
 *  20MHz periph clock APB1 and APB2
 *  Must set Flash Latency according to core clock (80MHz here)
 * ---------------------------------------------------------------------------*/


void LBF_SysClkCfg(void)
{

 /* Begin CubeMX generated code - MODIFIED */

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
{ 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; 
    // dont touch LSE if outof standby mode
}
else 
{ 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
}


  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;  // unused for now
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;  // 8MMHz/M*N/Q=48MHz
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;  // 8MMHz/M*N/Q=72MHz
  HAL_RCC_OscConfig(&RCC_OscInitStruct);


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;	// SYSCLK = 72MHz
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // AHBCLK (HCLK) = 72MHz to Cortex

  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  // APB1 periph clock = 18MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;  // APB2 periph clock = 18MHz
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1 periph clock = 36MHz
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  // APB2 periph clock = 36MHz

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);


  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;  //Div.Q output, 48MHz
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);


  __PWR_CLK_ENABLE();

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/8000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

 /* End of CubeMX generated code */
 

   __SYSCFG_CLK_ENABLE();  
   // System Configuration Clock
   // The system configuration controller is mainly used to remap the memory accessible in the
   // code area, and manage the external interrupt line connection to the GPIOs.



}



/***************************************************************END OF FILE****/
