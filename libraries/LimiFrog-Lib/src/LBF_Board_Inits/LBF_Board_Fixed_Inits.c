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


#include "LBF_DFU_If_Needed.h"

#include "IT_Priorities_UserDefinable.h"

#include "LBF_lowlev_API.h"

#include "LBF_SysClkCfg.h"
#include "LBF_LSE_RTC_Cfg.h"

#include "LBF_I2C2_IOcfg.h"
#include "LBF_I2C2_Init.h"

#include "LBF_SPI1_IOcfg.h"
#include "LBF_SPI1_Init.h"

#include "LBF_SPI3_IOcfg.h"
#include "LBF_SPI3_Init.h"

#include "LBF_UART3_IOcfg.h"
#include "LBF_UART3_Init.h"

#include "LBF_USB_IOcfg.h"

#include "LBF_BATT_IOcfg.h"

#include "LBF_Mic_IOcfg.h"

#include "LBF_FLASH_IOcfg.h"
#include "LBF_FLASH_Init.h"

#include "LBF_LED_Switches_IOcfg.h"

#include "LBF_PWR_IOcfg.h"

#include "LBF_OLED_IOcfg.h"

#include "LBF_BTLE_IOcfg.h"



/*******************************************************************************/


/** Full Board Initializations and Configurations          **/
/** except :                                               **/
/** - OLED powering and init, handled separately           **/
/** - BLE module initialization (FW download)              **/
/** - pin configurations for extension port                **/
/** which can be selectively enabled and are handled by	   **/
/** LBF_Board_Selective_Inits()                            **/



/***********
* Function :	
	void LBF_Board_Fixed_Inits(void)
* Description : 
	Performs all « fixed » initializations, which do not depend on some user choices. This includes configuring the clocks, the Interrupt Controller, all « fixed-role » GPIOs and peripherals, etc.
* Parameters :
	  -
* Return Value: 
	 -
* Notes:  
	LBF_Board_Inits() combines LBF_Board_Fixed_Inits() and LBF_Board_Selective_Inits() in a single function call.
************/

void LBF_Board_Fixed_Inits(void) 
{

/* -------- Check if LimiFrog alternative Boot is selected --- */
/* --       (typically to downalod code through USB)         - */
/* --       Alternative boot is selected by pulling posn.10  - */
/* --       of the extension port (PB8)                      - */
/* --       In this case application code will not continue  - */
/* --       and will branch to STM32 bootloader in ROM       - */
/* --       (System Flash) 				     - */
/* --       See source code of the function for rationale    - */
/* --       and details                                      - */

     LBF_DFU_If_Needed();

     // !!! if you remove (or move) that function call, it will 
     // no longer be possible to download any code via USB 
     // (DFU mode) and then you MUST use an STLink dongle
     // for your next code download


/* -------- Configure eFlash Prefetch,        ---------------- */
/* --       Init and launch SysTick time base ---------------- */
/* --       Set NVIC for pre-emption only (no sub-prio)    --- */
    
//     HAL_Init_Private();
       HAL_Init();
       // Function described in stm32l4xx_hal.c,
       // - Enables/disables I-cache, D-cache, Prefetch buffer
       // - Sets NVIC to use 4 bits for preemption priority 
       //    and 0 for sub-priority (i.e., not used)
       // - Sets SysTick IT priority to TICK_INT_PRIORITY
       //    defined in stm32l4xx_hal.h to 0xFF


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

     LBF_UART3_IOcfg();		// UART3 -interfacing with: BTLE

     LBF_BATT_IOcfg();   	// GPIO <--> Battery VBat: measurement enable and analog voltage pins

     LBF_Mic_IOcfg();   	// GPIO <--> Microphone IO interfacing

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

     LBF_I2C2_Init();  // used by all sensors  

     LBF_LSE_RTC_Cfg(); // External 32KHz (Low-Speed External, LSE) init
		       // used by RTC (NB: osc. start-up takes some time)


/* --------  Inits required by other on-board chips   ----------  */


     LBF_FLASH_Init();    // ADESTO Data Flash


}



/***************************************************************END OF FILE****/
