/*******************************************************************************
 * stm32_it.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_Global.h"



/* -----------------------------------------------------------------------------
   DERIVED FROM FILE stm32_it.c provided in TEMPLATE PROJECT
   REMOVING PERIPHERAL IT HANDLERS THAT ARE IRRELEVANT IN THIS EXAMPLE,  
   ---------------------------------------------------------------------------*/



/*****************************************************************************
 *  2 parts in this file :
 *  Part I:  
    Interrupt Handlers. These are the entry points to Interrupt Service
     Routines (ISR) that are reached when an interrupt request 
    is serviced by the processor.
 *  Part II: 
    Call-back functions, e.g. if you rely on the HAL library to service 
    interrupts. 
    The HAL library provides ISR functions that can be called from within the 
    former interrupt handler. These check the interrupt source, clear the
    interrupt pending flag and call a relevant call-back function where
    the user can implement whatever processing she/he needs.
     Note this method involved several function calls within the overall ISR
     and may not be desirable when servicing is needed.
 *****************************************************************************/

// --------------------------------------------------
// NOTE:
// This template pre-implements 2 interrupt handlers :
// --------------------------------------------------
//  > A handler on the EXTI received from the ON/OFF push-button
//    plus he call-back function that powers off the board when this IT is
//    received
//  > A handler on the USB interrupt OTG_FS_IRQ that calls the relevant
//    HAL function as required by ST's USB stack implementatation
// --------------------------------------------------------------------------
  



/****************************************************************************
 **                                                                        **
 **                 Part I  -  STM32 Interrupt Handlers                    **
 **                                                                        **
 ****************************************************************************/


/* ============================================================================
   A full Interrupt Vector Table is provided in Table41 of STM32L476 User Manual
   Full list of IRQ handlers can also be found in startup file :
    startup_stm32l476xx.s

   To enter the interrupt handler, the associated must have been enabled
   and its priority level set at NVIC level

   This template provides place holders for the full set of potential IRQ
   Pick those which you need for your application
   ===========================================================================*/




// ============================================================================
//    SYSTEM EXCEPTION HANDLERS
// ===============================

/*******************************************************************************

* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.

* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.

* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.

* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : UsageFault_Handler

* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : SVC_Handler

* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None

* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************

* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.

* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
  HAL_IncTick();
}



// ============================================================================
//    HANDLERS FOR EXTERNAL INTERRUPT REQUEST THRU GPIOs 
// =====================================================


/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : Handles EXT interrupts from Pins 10 to 15 of ports GPIOA/B/C/D 
* Input          : None

* Output         : None
* Return         : None
*******************************************************************************/

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - IRQ_PRESS_PIN, Interrupt from LPS25H (Pressure), through pin PB12
//  - ONOFF_STAT_PIN, Debounced ON/OFF from PMIC (LTC3553), through pin PC13
//  - SWITCH1_PIN, from Switch #1 if configured by user as IT source, on PA15
//    (caution: this switch is not debounced)
//  - IRQ_MAG_PIN, Interrupt INT from LIS3MDL (Magneto), through pin PB15
// Caution: if enabling multiple sources for same EXTIxx_IRQn,
//           need to discriminate sources in IRQ handler

void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(ONOFF_STAT_PIN);
  // Checks if ONOFF_STAT_PIN is source of IT
  // if so: HAL clears the IT and calls HAL_GPIO_EXTI_Callback (see below)
}



// ============================================================================
//   HANDLERS FOR ON-CHIP PERIPHERAL INTERRUPT REQUEST 
// ===================================================


/******************************************************************************
* Function Name  :OTG_FS_IRQHandler
* Description    : OTG_FS global interrupt
*******************************************************************************/
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}




/****************************************************************************
 **                                                                        **
 **                    Part II  -  Callback  Functions                     **
 **                                                                        **
 ****************************************************************************/



/**===========================================================================*/
/**==     Callback functions called by above IRQ handlers                     */
/**==     associated to on-chip peripherals                                   */
/**===========================================================================*/


// void HAL_xxxxCallback(xxxx)
// {
//   <your code here>
// }



/**===========================================================================*/
/**==     Callback functions called by above IRQ handlers associated to EXTI, */
/**==       (EXTI = External Interrupts through GPIO pins)                    */
/**===========================================================================*/

// If in the above IRQ handlers you implement a HAL function HAL_xxx_IRQHandler,
// this will typically check the source of the interrupt, clear the IT pending
// flag and call one the callback functions below, where you can then
// implement the specific IT servicing required by your application.
// (...and  yes that's a lot of function calls - you may want to do differently
//  if ISR execution time is an issue) 



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

// Servicing Interrupt from PWR_ONSTAT (power off required)

  if (GPIO_Pin == ONOFF_STAT_PIN)
  {
        LBF_Led_OFF();        

#ifdef USE_OLED  // (defined in User_Configuration.h)
	// Do not send command if no OLED (else SPI hangs?)

        OLED_Switch_OFF();
        LBF_Delay_ms(100); // Delay between cutting OLED VDDH (13V) and VDD (logic) 
                       // to preserve panel lifetile - as per DD160128FC-1A datasheet
	 //Caution: if TimerTick involved in delay implementation, its IRQ priority 
         // must be high (urgent) enough in Interrupt Configuration files
#endif


        // wait as long as ONOFF is active (ie. until user has finished pushing button)
        while(HAL_GPIO_ReadPin(ONOFF_STAT_PORT, ONOFF_STAT_PIN) == GPIO_PIN_RESET);

        
	//Quickly blink LED 3 times
	LBF_Led_ON();
        LBF_Delay_ms(100);        
	LBF_Led_OFF();
        LBF_Delay_ms(200);      

	LBF_Led_ON();
        LBF_Delay_ms(100);        
	LBF_Led_OFF();
        LBF_Delay_ms(200);   

	LBF_Led_ON();
        LBF_Delay_ms(100);        
	LBF_Led_OFF();


        // Bye bye:  Power down VCC_NUM by resetting pin BUCK3V_ON
        GPIO_LOW(BUCK3V_ON_PORT, BUCK3V_ON_PIN);
        LBF_Delay_ms(3000);
        while(1);

  }



}



/***************************************************************END OF FILE****/
