/*******************************************************************************
 * IT_Priorities_UserDefinable.h
 * 
 ******************************************************************************/


/****************************************************************************
*                                                                           *
* Enabling interrupts at STM32 (Cortex core) level is done by programming   *
* the NVIC (Nested Vector Interrupt Controller) of the ARM Cortex core.     *
* This involves defining a priority or preemption level for the different   *
* interrupt sources supported by the core.                                  *
*                                                                           *
* In the libs and example code provided with LimiFrog, the priority level is*
* defined by a constant that can handily be defined in this file.           *
* (and the sub-priority level is always set to zero)                        *
*                                                                           *
* Adapt the priority levels for your own project.                           *
* You may remove those associated to IT you don't use in your application   *
*                                                                           *
****************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IT_PRIO_USERDEFINABLE_H
#define __IT_PRIO_USERDEFINABLE_H



/* ---------------  Interrupt Priorities for NVIC  ---------------------- */


/* Priority levels can be set between 0x0 and 0xF                 */
/* !!!  LOWER NUMERICAL VALUE MEANS HIGHER PRE-EMPTION LEVEL  !!! */


// Note: 
// #define  TICK_INT_PRIORITY  ...  
// in stm32l4xx_hal_conf.h defines the SysTick interrupt priority (0xFF). 
// This parameter is used in calls to HAL_InitTick(TICK_INT_PRIORITY), 
// in files stm32l4xx_hal.c and stm32l4xx_hal_rcc.c.


#define  __WWDG_IRQn_PRIO		0xA
#define  __PVD_PVM_IRQn_PRIO		0xA
#define  __TAMP_STAMP_IRQn_PRIO		0xA
#define  __RTC_WKUP_IRQn_PRIO		0xA
#define  __FLASH_IRQn_PRIO		0xA
#define  __RCC_IRQn_PRIO		0xA

#define  __EXTI0_IRQn_PRIO		0xC
#define  __EXTI1_IRQn_PRIO		0xC
#define  __EXTI2_IRQn_PRIO		0xC
#define  __EXTI3_IRQn_PRIO		0xC
#define  __EXTI4_IRQn_PRIO		0xC
#define  __EXTI9_5_IRQn_PRIO		0xC
#define  __EXTI15_10_IRQn_PRIO		0xA  
	// IT from ON/OFF button is EXTI13 (pin PC13) on LimiFrog

#define  __DMA1_Channel1_IRQn_PRIO	0x9	
#define  __DMA1_Channel2_IRQn_PRIO	0x9
#define  __DMA1_Channel3_IRQn_PRIO	0x9
#define  __DMA1_Channel4_IRQn_PRIO	0x9
#define  __DMA1_Channel5_IRQn_PRIO	0x9
#define  __DMA1_Channel6_IRQn_PRIO	0x9
#define  __DMA1_Channel7_IRQn_PRIO	0x9

#define  __DMA2_Channel1_IRQn_PRIO	0x9
#define  __DMA2_Channel2_IRQn_PRIO	0x9
#define  __DMA2_Channel3_IRQn_PRIO	0x9
#define  __DMA2_Channel4_IRQn_PRIO	0x9
#define  __DMA2_Channel5_IRQn_PRIO	0x9
#define  __DMA2_Channel6_IRQn_PRIO	0x9
#define  __DMA2_Channel7_IRQn_PRIO	0x9

#define  __ADC1_2_IRQn_PRIO		0x9
#define  __ADC3_IRQn_PRIO		0x9

#define  __CAN1_TX_IRQn_PRIO		0x9
#define  __CAN1_RX0_IRQn_PRIO		0x9
#define  __CAN1_RX1_IRQn_PRIO		0x9
#define  __CAN1_SCE_IRQn_PRIO		0x9

// Note - in many occurences, IT from timer
// is combined with IT from another peripheral
#define  __TIM1_BRK_TIM15_IRQn_PRIO	0xA
#define  __TIM1_UP_TIM16_IRQn_PRIO	0xA
#define  __TIM1_TRG_COM_TIM17_IRQn_PRIO	0xA
#define  __TIM1_CC_IRQn_PRIO		0xA
#define  __TIM2_IRQn_PRIO		0xA
#define  __TIM3_IRQn_PRIO		0xA
#define  __TIM4_IRQn_PRIO		0xA
#define  __TIM5_IRQn_PRIO		0xA
#define  __TIM6_DAC_IRQn_PRIO		0xA
#define  __TIM7_IRQn_PRIO		0xA
#define  __TIM8_BRK_IRQn_PRIO		0xA
#define  __TIM8_UP_IRQn_PRIO		0xA
#define  __TIM8_TRG_COM_IRQn_PRIO	0xA
#define  __TIM8_CC_IRQn_PRIO		0xA

#define  __LPTIM1_IRQn_PRIO		0xA
#define  __LPTIM2_IRQn_PRIO		0xA

#define  __I2C1_EV_IRQn_PRIO		0x9
#define  __I2C1_ER_IRQn_PRIO		0x9
#define  __I2C2_EV_IRQn_PRIO		0x9
#define  __I2C2_ER_IRQn_PRIO		0x9
#define  __I2C3_EV_IRQn_PRIO		0x9
#define  __I2C3_ER_IRQn_PRIO		0x9

#define  __SPI1_IRQn_PRIO		0x9
#define  __SPI2_IRQn_PRIO		0x9
#define  __SPI3_IRQn_PRIO		0x9

#define  __USART1_IRQn_PRIO		0x9
#define  __USART2_IRQn_PRIO		0x9
#define  __USART3_IRQn_PRIO		0x9

#define  __UART4_IRQn_PRIO		0x9
#define  __UART5_IRQn_PRIO		0x9
#define  __LPUART1_IRQn_PRIO		0x9

#define  __RTC_Alarm_IRQn_PRIO		0x5

#define  __FMC_IRQn_PRIO		0x9

#define  __SDMMC1_IRQn_PRIO		0x9

#define  __DFSDM0_IRQn_PRIO		0x9
#define  __DFSDM1_IRQn_PRIO		0x9
#define  __DFSDM2_IRQn_PRIO		0x9
#define  __DFSDM3_IRQn_PRIO		0x9

#define  __COMP_IRQn_PRIO		0x9



#endif  /*__IT_PRIO_USERDEFINABLE_H */

/***************************************************************END OF FILE****/
