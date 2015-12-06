/*******************************************************************************
 * LBF_PWR_IOcfg.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_PWR_IOcfg.h"

#include "IT_Priorities_UserDefinable.h"

/*******************************************************************************
 * @brief  : Configure GPIOs dedicated to PMIC - LTC533, VDD_OLED Power Switch
 * @param  : none.
 * @return : none.
 ******************************************************************************/
void LBF_PWR_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;


/* --- LTC3533 PMIC ---*/


// Inputs

    // ONOFF_STAT Input to STM32: is IRQ, see Interrupt Config section
 

// Outputs

    // Pin  BUCK3V_ON -  Output  
    // Std CMOS output, no pull_up/-down res., very low speed
    GPIO_InitStruct.Pin = BUCK3V_ON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(BUCK3V_ON_PORT, &GPIO_InitStruct) ;

#ifndef  __LBF_LEGACY  // pin did not exist prior to LimiFrog0.1
    // Pin  LDO_ON   -  Output  
    // Std CMOS output, no pull_up/-down res., very low speed
    GPIO_InitStruct.Pin = LDO_ON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LDO_ON_PORT, &GPIO_InitStruct) ;
#endif

    // Pin  HPWR  -  Output, std CMOS 
    GPIO_InitStruct.Pin = HPWR_PIN;
    HAL_GPIO_Init(HPWR_PORT, &GPIO_InitStruct) ;


/* --- TPS22929 Power Switch */
/* --- (DC-DC Boost Converter On/Off for OLED) */

    // Pin  VDDH_EN   -  Output, std CMOS 
    GPIO_InitStruct.Pin = VDDH_EN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(VDDH_EN_PORT, &GPIO_InitStruct) ;


/* ---------------------------------------------- */
/* -- Init BUCK3V_ON to active state (Buck On) -- */
/* -- Init LDO_ON to inactive state (LDO off)  -- */

    GPIO_HIGH(BUCK3V_ON_PORT, BUCK3V_ON_PIN);
    GPIO_LOW(LDO_ON_PORT, LDO_ON_PIN);


/* ---------------------------------------------- */
/* -- Enable input current up to 500mA         -- */

    GPIO_HIGH(HPWR_PORT, HPWR_PIN);


/* ---------------------------------------------- */
/* -- Make sure OLED VDDH is off at start-up   -- */

    Turn_VDDH_Off();

/* ---------------------------------------------- */
/* -- Use Debounced ON/OFF form LTC3553 as    --- */
/* --  interrupt to switch off the device     --- */

    // Power Off from Debounced Push-Button   
    // ONOFF_STAT (PC13) -  Input, weak pull-up
    // Suitable for active low Open-Drain IT
    GPIO_InitStruct.Pin = ONOFF_STAT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // active low
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(ONOFF_STAT_PORT, &GPIO_InitStruct);


    // Also need to configure EXTI15_10_IRQn 
    // (since IT is on pin 13 of GPIOC) at NVIC level
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, __EXTI15_10_IRQn_PRIO , 0); 
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); 


}



/***************************************************************END OF FILE****/
