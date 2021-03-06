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


// !!!! Note : Potential sources of external interrupts indicated in comments
// below are for LimiFrog-0.x.  Mapping was somewhat different in former
// versions of the board (LBF-V2.x).


/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : Handles EXT interrupts from Pin0 of ports GPIOA/B/C/D .
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - IRQ from CONN_POS8_PIN (PA0)
void EXTI0_IRQHandler(void)
{

}


/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : Handles EXT interrupts from Pin 1 of ports GPIOA/B/C/D .
* Input          : None
* Output         : None

* Return         : None
*******************************************************************************/

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - CONN_POS7_PIN  (PA1)

void EXTI1_IRQHandler(void)
{

}

/*******************************************************************************

* Function Name  : EXTI2_IRQHandler
* Description    : Handles EXT interrupts from Pin 2 of ports GPIOA/B/C/D .
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - IRQ_ALS_PROX_PIN  (PB2)
//  - CONN_POS1_PIN  (PA2)
// Caution: if enabling multiple sources for same EXTIxx_IRQn,
//   need to discriminate sources in IRQ handler

void EXTI2_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : Handles EXT interrupts from Pin 3 of ports GPIOA/B/C/D .
* Input          : None

* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - CONN_POS4_PIN (PA3)

{

}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : Handles EXT interrupts from Pin 4 of ports GPIOA/B/C/D .
* Input          : None
* Output         : None

* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - CONN_POS3_PIN  (PA4)

{

}

/*******************************************************************************

* Function Name  : EXTI9_5_IRQHandler
* Description    : Handles EXT interrupts from Pins 5 to 9 of ports GPIOA/B/C/D 
* Input          : None
* Output         : None
* Return         : None

*******************************************************************************/

// On LimiFrog-0.x, possible external interrupts expected here would be :
//  - INT1_ACC_GYR_PIN, Interrupt from LSM6DS3 (PC6)
//  - CONN_POS1_PIN (PA6)
//  - Mechanical Switch #2 if configured by user as IT source, through PC8
//    (caution: this switch is not debounced)

void EXTI9_5_IRQHandler(void)
{

}

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
* Function Name  : WWDG_IRQHandler
* Description    : Window Watchdog interrupt
*******************************************************************************/
void WWDG_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : PVD_PVM_IRQHandler
* Description    : PVD/PVM1/PVM2/PVM3/PVM4 through EXTI lines 16/35/36/37/38 
*******************************************************************************/
void PVD_PVM_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TAMP_STAMP_IRQHandler
* Description    : RTC Tamper or TimeStamp /CSS on LSE thru EXTI line 19 IT
*******************************************************************************/
void TAMP_STAMP_IRQHandler(void)
{
  
}

/*******************************************************************************
* Function Name  : RTC_WKUP_IRQHandler
* Description    : RTC Wakeup timer through EXTI line 20 interrupt
*******************************************************************************/
void RTC_WKUP_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : Flash global interrupt
*******************************************************************************/
void FLASH_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : RCC global interrupt
*******************************************************************************/
void RCC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : DMA1 channel 1 interrupt
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : DMA1 channel 2 interrupt
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : DMA1 channel 3 interrupt
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : DMA1 channel 4 interrupt
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : DMA1 channel 5 interrupt
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : DMA1 channel 6 interrupt
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : DMA1 channel 7 interrupt
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : ADC1 and ADC2 global interrupt
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : CAN1_TX_IRQHandler
* Description    : CAN1_TX interrupts
*******************************************************************************/
void CAN1_TX_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : CAN1_RX0_IRQHandler
* Description    : CAN1_RX0 interrupts
*******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : CAN1_RX1_IRQHandler
* Description    : CAN1_RX1 interrupt
*******************************************************************************/
void CAN1_RX1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : CAN1_SCE_IRQHandler
* Description    : CAN1_SCE interrupt
*******************************************************************************/
void CAN1_SCE_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM1_BRK_TIM15_IRQHandler
* Description    : TIM1 Break/TIM15 global interrupts
*******************************************************************************/
void TIM1_BRK_TIM15_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM1_UP_TIM16_IRQHandler
* Description    : TIM1 Update/TIM16 global interrupts
*******************************************************************************/
void TIM1_UP_TIM16_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM1_TRG_COM_TIM17_IRQHandler
* Description    : TIM1 trigger and commutation/TIM17 interrupts
*******************************************************************************/
void TIM1_TRG_COM_TIM17_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : TIM1 capture compare interrupt
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : TIM2 global interrupt
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : TIM3 global interrupt
*******************************************************************************/
void TIM3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : TIM4 global interrupt
*******************************************************************************/
void TIM4_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : I2C1 event interrupt
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : I2C1 error interrupt
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : I2C2 event interrupt
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : I2C2 error interrupt
*******************************************************************************/
void I2C2_ER_IRQHandlervoid)
{
  
}

/******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : SPI1 global interrupt
*******************************************************************************/
void SPI1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : SPI2 global interrupt
*******************************************************************************/
void SPI2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : USART1 global interrupt
*******************************************************************************/
void USART1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : USART2 global interrupt
*******************************************************************************/
void USART2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : USART3 global interrupt
*******************************************************************************/
void USART3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : RTC_Alarm_IRQHandler
* Description    : RTC alarms through EXTI line 18 interrupts
*******************************************************************************/
void RTC_Alarm_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DFSDM3_IRQHandler
* Description    : DFSDM3 global interrupt
*******************************************************************************/
void DFSDM3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : TIM8 Break interrupt
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : TIM8 Update interrupt
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : TIM8 capture compare interrupt
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM8_CC_IRQHandler  (error in STM32L4 ref Manual? says TIM1CC)
* Description    : TIM8 capture compare interrupt
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : ADC3 global interrupt
*******************************************************************************/
void ADC3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : FMC_IRQHandler
* Description    : FMC global interrupt
*******************************************************************************/
void FMC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : SDMMC1_IRQHandler
* Description    : SDMMC1 global interrupt
*******************************************************************************/
void SDMMC1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : TIM5 global interrupt
*******************************************************************************/
void TIM5_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : SPI3 global interrupt
*******************************************************************************/
void SPI3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : UART4 global interrupt
*******************************************************************************/
void UART4_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : UART5 global interrupt
*******************************************************************************/
void UART5_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM6_DAC_IRQHandler
* Description    : TIM6 global and DAC12 underrun interrupts
*******************************************************************************/
void TIM6_DAC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : TIM7 global interrupt
*******************************************************************************/
void TIM7_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : DMA2 channel 1 interrupt
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : DMA2 channel 2 interrupt
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : DMA2 channel 3 interrupt
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA2_Channel4_IRQHandler
* Description    : DMA2 channel 4 interrupt
*******************************************************************************/
void DMA2_Channel4_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  : DMA2_Channel5_IRQHandler
* Description    : DMA2 channel 5 interrupt
*******************************************************************************/
void DMA2_Channel5_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :DFSDM0_IRQHandler
* Description    : DFSDM0 global interrupt
*******************************************************************************/
void DFSDM0_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :DFSDM1_IRQHandler
* Description    : DFSDM1 global interrupt
*******************************************************************************/
void DFSDM1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :DFSDM2_IRQHandler
* Description    : DFSDM2 global interrupt
*******************************************************************************/
void DFSDM2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :COMP_IRQHandler
* Description    : COMP1/COMP2 through EXTI lines 21/22
interrupts
*******************************************************************************/
void COMP_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :LPTIM1_IRQHandler
* Description    : LPTIM1 global interrupt
*******************************************************************************/
void LPTIM1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :LPTIM2_IRQHandler
* Description    : LPTIM2 global interrupt
*******************************************************************************/
void LPTIM2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :OTG_FS_IRQHandler
* Description    : OTG_FS global interrupt
*******************************************************************************/
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}

/******************************************************************************
* Function Name  :DMA2_Channel6_IRQHandler
* Description    : DMA2 channel 6 interrupt
*******************************************************************************/
void DMA2_Channel6_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :DMA2_Channel7_IRQHandler
* Description    : DMA2 channel 7 interrupt
*******************************************************************************/
void DMA2_Channel7_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :LPUART1_IRQHandler
* Description    : LPUART1 global interrupt
*******************************************************************************/
void LPUART1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :QUADSPI_IRQHandler
* Description    : QUADSPI global interrupt
*******************************************************************************/
void QUADSPI_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :I2C3_EV_IRQHandler
* Description    : I2C3 event interrupt
*******************************************************************************/
void I2C3_EV_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :I2C3_ER_IRQHandler
* Description    : I2C3 error interrupt
*******************************************************************************/
void I2C3_ER_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :SAI1_IRQHandler
* Description    : SAI1 global interrupt
*******************************************************************************/
void SAI1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :SAI2_IRQHandler
* Description    : SAI2 global interrupt
*******************************************************************************/
void SAI2_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :SWPMI1_IRQHandler
* Description    : SWPMI1 global interrupt
*******************************************************************************/
void SWPMI1_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :TSC_IRQHandler
* Description    : TSC global interrupt
*******************************************************************************/
void TSC_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :LCD_IRQHandler
* Description    : LCD global interrupt
*******************************************************************************/
void LCD_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :AES_IRQHandler
* Description    : AES global interrupt
*******************************************************************************/
void AES_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :RNG_IRQHandler
* Description    : RNG global interrupt
*******************************************************************************/
void RNG_IRQHandler(void)
{
  
}

/******************************************************************************
* Function Name  :FPU_IRQHandler
* Description    : Floating point interrupt
*******************************************************************************/
void FPU_IRQHandler(void)
{
  
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
