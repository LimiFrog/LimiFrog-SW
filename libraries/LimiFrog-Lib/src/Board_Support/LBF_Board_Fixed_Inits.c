/*******************************************************************************
 * LBF_Board_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "IT_Priorities_UserDefinable.h"

#include "LBF_Board_Fixed_Inits.h"
#include "LBF_lowlev_API.h"

#include "LBF_SysClkCfg.h"
#include "LBF_LSE_RTC_Cfg.h"

#include "LBF_I2C2_IOcfg.h"
#include "LBF_I2C2_Init.h"

#include "LBF_SPI1_IOcfg.h"
#include "LBF_SPI1_Init.h"

#include "LBF_SPI3_IOcfg.h"
#include "LBF_SPI3_Init.h"

#ifdef __LBF_LEGACY  //exchanges with BLE were thru UART1
  #include "LBF_UART1_IOcfg.h"
  #include "LBF_UART1_Init.h"
#else  // ...now thru UART3
  #include "LBF_UART3_IOcfg.h"
  #include "LBF_UART3_Init.h"
#endif

#include "LBF_USB_IOcfg.h"

#include "LBF_BATT_IOcfg.h"

#include "LBF_MIC_IOcfg.h"

#include "LBF_FLASH_IOcfg.h"
#include "LBF_FLASH_Init.h"

#include "LBF_LED+Switches_IOcfg.h"

#include "LBF_PWR_IOcfg.h"

#include "LBF_OLED_IOcfg.h"

#include "LBF_BTLE_IOcfg.h"



/* Privates prototypes -------------------------------------------------------*/

static void HAL_Init_Private(void);


/*******************************************************************************/

/** Full Board Initializations and Configurations          **/
/** except OLED VDDH powering and init, handled separately **/
/** (as OLED may or may not be present)                    **/


void LBF_Board_Fixed_Inits(void) 
{


/* -------- Configure eFlash Prefetch,        ---------------- */
/* --       Init and launch SysTick time base ---------------- */
/* --       Set NVIC for pre-emption only (no sub-prio)    --- */
    
     HAL_Init_Private();


/* -------- Configure system clocks with default values  -------*/
/* --       User may override this in his own code if desired   */
/* -- NOTE: LSE not handled here (long start-up not compatible  */
/* --       with max latency to acknowledge PMIC after power-up)*/

     LBF_SysClkCfg();  


/* --------  STM32 IO Configuration  ------------------------  */

    /* First, enable GPIO clocks */
     __GPIOA_CLK_ENABLE();
     __GPIOB_CLK_ENABLE();
     __GPIOC_CLK_ENABLE();
     __GPIOD_CLK_ENABLE();


     LBF_PWR_IOcfg();  		// GPIO <--> PMIC IO interfacing

     LBF_SPI3_IOcfg();   	// SPI3 - interfacing with: Data Flash

     LBF_SPI1_IOcfg();		// SPI1 - interface to OLED

#ifdef __LBF_LEGACY
     LBF_UART1_IOcfg();		// UART1 -interfacing with: BTLE
#else
     LBF_UART3_IOcfg();		// UART3 -interfacing with: BTLE
#endif

     LBF_BATT_IOcfg();   	// GPIO <--> Battery VBat: measurement enable and analog voltage pins

     LBF_MIC_IOcfg();   	// GPIO <--> Microphone IO interfacing

     LBF_LED_IOcfg();  		// GPIO <--> LED IO interfacing

     LBF_SelSwitches_IOcfg();   // GPIO <--> Selection switches (push-button) IO interfacing

     LBF_I2C2_IOcfg();   	// I2C2 - interfacing with: all sensors 

     LBF_FLASH_IOcfg();  	// GPIO <--> Data Flash IO interfacing (SPI3 done separately)

     LBF_OLED_IOcfg();          // GPIO <--> OLED IO interfacing
				// SPI1 done separately

     LBF_BTLE_IOcfg();  	// BlueTooth Low-Energy IO interfacing (UART3 done separately)

     LBF_USB_IOcfg();		// USB IO interfacing (DP/DM and VBUS_SENSE)



/* -------- On-Chip Peripheral Inits  -----------------------  */  
    

    /* Always-enabled peripherals : */

     LBF_SPI1_Init();  // used by OLED 

     LBF_SPI3_Init();  // used by DataFlash

     LBF_I2C2_Init();  // used by all sensors (+ optionnally BTLE) 

     LBF_LSE_RTC_Cfg(); // External 32KHz (Low-Speed External, LSE) init
		       // used by RTC (NB: osc. start-up takes some time)


/* --------  Inits required by other on-board chips   ----------  */


     LBF_FLASH_Init();    // ADESTO Data Flash


}


/*******************************************************************************/

/********************************************************************
 * HAL_Init_Private():    
 *     Equivalent to HAL_Init() with custom SysTick priority, 
 *     defined by _SysTick_IRQn_PRIO                        
 ********************************************************************/
 
void HAL_Init_Private(void) 
{

  /* Configure Flash prefetch, Instruction cache, Data cache */
  /* Default configuration at reset is:                      */
  /* - Prefetch disabled                                     */
  /* - Instruction cache enabled                             */
  /* - Data cache enabled                                    */

#if (INSTRUCTION_CACHE_ENABLE == 0)
   __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();
#endif /* INSTRUCTION_CACHE_ENABLE */

#if (DATA_CACHE_ENABLE == 0)
   __HAL_FLASH_DATA_CACHE_DISABLE();
#endif /* DATA_CACHE_ENABLE */

#if (PREFETCH_ENABLE != 0)
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif /* PREFETCH_ENABLE */


//     __SYSCFG_CLK_ENABLE();
// Don't call it here, else USB will not work (...why ???!?)
// Keep it in LBF_SysClkCfg


     HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
     	    // Leads to 4 bits to define preemption priority 
            // and 0 for sub-priority (i.e., not used)

     HAL_InitTick(__SysTick_IRQn_PRIO);   
    	    // Use SysTick as time base source and configure 1ms tick 
            // __SysTick_IRQn_PRIO is defined in UserConfiguration file
            // Caution: SysTick prio must be numerically lower (higher pre-emption)
            //          than any ISR making use of SysTick - else will hang !

     // HAL_MspInit() not called as empty anyway - not used 
     // (IO config and periph init done in LBF_Board_Fixed_Inits(), above )

}




/***************************************************************END OF FILE****/
