/*******************************************************************************
 * LBF_ExtIT_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"

#include "IT_Priorities_UserDefinable.h"

/*******************************************************************************
* Function Name  : Enable_ExtIT
* Description    : Enable selected externa interrupt pin at GPIO EXTI level and at NVIC level
* Input          : Name of the pin (GPIO_Pin), Required Edge polarity of IT
* Output         : None
* Return         : None
*******************************************************************************/

void LBF_Enable_ExtIT( GPIO_TypeDef* GPIO_Port, uint16_t  GPIO_Pin, IT_Polarity_t  IT_Polarity )
{
GPIO_InitTypeDef GPIO_InitStruct;


  // ---- Enable the GPIO as External Interrupt  -------------

    GPIO_InitStruct.Pin = GPIO_Pin;
    if ( IT_Polarity == RISING)  {
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
    }
    else {
        GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  
    }
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);



  // ---- Set Nested Vectored Interrupt Controller (NVIC)  ---

 #ifdef __LBF_LEGACY
    // Ext interrrupts that use pin 0 of ports GPIOA/B/C/D:
    if ( GPIO_Pin == IRQ_ALS_PROX_PIN )  //PA0
    {
         HAL_NVIC_SetPriority(EXTI0_IRQn, __EXTI0_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI0_IRQn);  
    }

    // Ext interrrupts that use pin 1 of ports GPIOA/B/C/D:
    // None in La BlueFrog

    // Ext interrrupts that use pin 2 of ports GPIOA/B/C/D:
    // None in La BlueFrog

    // Ext interrrupts that use pin 3 of ports GPIOA/B/C/D:
    // None in La BlueFrog

    // Ext interrrupts that use pin 4 of ports GPIOA/B/C/D:
    // None in La BlueFrog

    // Ext interrrupts that use pins 5 to 9 of ports GPIOA/B/C/D:
    if ( (GPIO_Pin == INT2_ACC_GYR_PIN) ||  // PC6
         (GPIO_Pin == CONN_POS1_PIN)    ||   // PA5
         (GPIO_Pin == CONN_POS2_PIN)    ||   // PA6  -- Caution, avoid conflict in IRQ handler with PC6=INT2_ACC_GYR_PIN
         (GPIO_Pin == CONN_POS3_PIN)    ||   // PA7 
         (GPIO_Pin == CONN_POS9_PIN)    ||   // PB8 
         (GPIO_Pin == CONN_POS10_PIN)    )   // PB9 
       //TBD: also PC8 as an IT from switch 2 ?
    {
         HAL_NVIC_SetPriority(EXTI9_5_IRQn, __EXTI9_5_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  
    }

     // Ext interrrupts that use pins 10 to 15 of ports GPIOA/B/C/D:
    if ( (GPIO_Pin == INT1_ACC_GYR_PIN) ||   // PB15
         (GPIO_Pin == IRQ_MAG_PIN)      ||   // PB14
         (GPIO_Pin == IRQ_PRESS_PIN)    ||   // PB12
         (GPIO_Pin == ONOFF_STAT_PIN)   ||   // PC13  (already configured at init by LBF_Fixed_Inits())
         (GPIO_Pin == CONN_POS5_PIN)    ||   // PC10
         (GPIO_Pin == CONN_POS6_PIN)    ||   // PC11
         (GPIO_Pin == CONN_POS7_PIN)     )   // PC12  -- Caution, avoid conflict in IRQ handler with PB12=IRQ_PRESS_PIN
    {
         HAL_NVIC_SetPriority(EXTI15_10_IRQn, __EXTI15_10_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); 
    }

#else 

    // --   ExtIT sources on pin 0 of ports GPIOA/B/C/D: ----
    if ( GPIO_Pin == CONN_POS8_PIN )  //PA0
    {
         HAL_NVIC_SetPriority(EXTI0_IRQn, __EXTI0_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI0_IRQn);  
    }

    // --   ExtIT sources on pin 1 of ports GPIOA/B/C/D    ----------
    if ( GPIO_Pin == CONN_POS7_PIN )  //PA1
    {
         HAL_NVIC_SetPriority(EXTI1_IRQn, __EXTI1_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI1_IRQn);  
    }

    // --   ExtIT sources on pin 2 of ports GPIOA/B/C/D    ----------
    if ( (GPIO_Pin == IRQ_ALS_PROX_PIN) ||  //PB2
         (GPIO_Pin == CONN_POS1_PIN)    )   // PA2    
    {
         HAL_NVIC_SetPriority(EXTI2_IRQn, __EXTI2_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI2_IRQn);  
    }
      // Caution: if enabling multiple sources for same EXTIxx_IRQn,
      //   need to discriminate sources in IRQ handler


    // --   ExtIT sources on pin 3 of ports GPIOA/B/C/D    ----------
    if ( GPIO_Pin == CONN_POS4_PIN )  //PA3
    {
         HAL_NVIC_SetPriority(EXTI1_IRQn, __EXTI1_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI1_IRQn);  
    }

    // --   ExtIT sources on pin 4 of ports GPIOA/B/C/D    ----------
    if ( GPIO_Pin == CONN_POS3_PIN )  //PA4
    {
         HAL_NVIC_SetPriority(EXTI1_IRQn, __EXTI1_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI1_IRQn);  
    }

    // --   ExtIT sources on pins 5 to 9 of ports GPIOA/B/C/D   ----
    if ( 
	// Port GPIOA/B/C/D Pin 5 -- none usable as ExtIT
	// Port GPIOA/B/C/D Pin 6
	   (GPIO_Pin == INT1_ACC_GYR_PIN) ||   // PC6
           (GPIO_Pin == CONN_POS1_PIN)    )   // PA6  
      		// Caution: if enabling multiple sources for same EXTIxx_IRQn,
      		//   need to discriminate sources in IRQ handler
	// Port GPIOA/B/C/D Pin 7 -- none usable as ExtIT
	// Port GPIOA/B/C/D Pin 8 -- none usable as ExtIT
	   // could have SWITCH2 (PC8) but switch2 will disappear at next rel.
	// Port GPIOA/B/C/D Pin 9 -- none usable as ExtIT
    {
         HAL_NVIC_SetPriority(EXTI9_5_IRQn, __EXTI9_5_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  
    }


    // --   ExtIT sources on pins 10 to 15 of ports GPIOA/B/C/D   ----
    if (
	// Port GPIOA/B/C/D Pin 10 -- none usable as ExtIT
	// Port GPIOA/B/C/D Pin 11 -- none usable as ExtIT
	// Port GPIOA/B/C/D Pin 12
         (GPIO_Pin == IRQ_PRESS_PIN)    ||   // PB12
	// Port GPIOA/B/C/D Pin 13
         (GPIO_Pin == ONOFF_STAT_PIN)   ||   // PC13  
	       // (already configured at init by LBF_Fixed_Inits())
	// Port GPIOA/B/C/D Pin 14 -- none usable as ExtIT
	// Port GPIOA/B/C/D Pin 15 -- none usable as ExtIT
         (GPIO_Pin == IRQ_MAG_PIN)      ||   // PB15
         (GPIO_Pin == SWITCH1_PIN)      )   // PA15
      		// Caution: if enabling multiple sources for same EXTIxx_IRQn,
      		//   need to discriminate sources in IRQ handler
    {
         HAL_NVIC_SetPriority(EXTI15_10_IRQn, __EXTI15_10_IRQn_PRIO , 0); 
         HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); 
    }



#endif  // __LBF_LEGACY
}


/* --------------------------------------------------------------------------------------------- */

/*******************************************************************************
* Function Name  : Disable_ExtIT
* Description    : Disable selected external interrupt pin - configure as std input
*                   ** at GPIO EXTI level ONLY ** (because NVIC maye shared with other IT lines)
* Input          : Name of the pin (GPIO_Pin)
* Output         : None
* Return         : None
*******************************************************************************/

void LBF_Disable_ExtIT( GPIO_TypeDef* GPIO_Port, uint16_t  GPIO_Pin )
{
GPIO_InitTypeDef GPIO_InitStruct;


  // ----Set GPIO as input with weak pull-down  -------------

    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct); 

}


/***************************************************************END OF FILE****/
