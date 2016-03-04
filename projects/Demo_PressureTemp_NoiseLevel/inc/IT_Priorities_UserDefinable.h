/******************************************************************************
 * IT_Priorities_UserDefinable.h
 * 
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IT_PRIO_USERDEFINABLE_H
#define __IT_PRIO_USERDEFINABLE_H



/* ============  Interrupt Priorities for NVIC  ============================= *
 *                                                                            *
 * Refer to ../../LimiFrog_PROJECT_TEMPLATE/inc/IT_Priorities_UserDefinable.h *
 *                                                                            *
 * for a list of interrupt priorities that can be defined at NVIC level.      *
 * ( NVIC is the Nested Vector Interrupt Controller that handles all          *
 * interrupt requests at ARM Cortex core level )                              *
 *                                                                            *
 * ========================================================================= */



/* Priority levels can be set between 0x0 and 0xF                 */
/* !!!  LOWER NUMERICAL VALUE MEANS HIGHER PRE-EMPTION LEVEL  !!! */


// Note: 
// #define  TICK_INT_PRIORITY  ...  
// in stm32l4xx_hal_conf.h defines the SysTick interrupt priority (0xFF). 
// This parameter is used in calls to HAL_InitTick(TICK_INT_PRIORITY), 
// in files stm32l4xx_hal.c and stm32l4xx_hal_rcc.c.


#define __OTG_FS_IRQn_PRIO	0x7
// was originally hard-coded to 0x7 by ST in reference usbd_conf.c

#define  __ADC1_2_IRQn_PRIO	0xA
// Used by Analog Watchdog in this demo

// External Interrupts 
#define	__EXTI0_IRQn_PRIO	0xA	
#define	__EXTI1_IRQn_PRIO	0xA	
#define	__EXTI2_IRQn_PRIO	0xA	
#define	__EXTI3_IRQn_PRIO	0xA	
#define	__EXTI4_IRQn_PRIO	0xA	
#define	__EXTI9_5_IRQn_PRIO   	0xA	// includes ONOFF_STAT pin from PMIC, triggers power-on/-off
#define	__EXTI15_10_IRQn_PRIO	0xA	

// Timer Interrupts,
// Some combined with IT from other peripherals
#define __TIM1_UP_TIM16_IRQn_PRIO	0xA
#define __TIM2_IRQn_PRIO	0xA
#define __TIM3_IRQn_PRIO	0xA
#define __TIM4_IRQn_PRIO	0xA
#define __TIM5_IRQn_PRIO	0xA
#define __TIM6_DAC_IRQn_PRIO	0xA
#define __TIM7_IRQn_PRIO	0xA
#define __TIM8_UP_IRQn_PRIO	0xA
#define __TIM1_BRK_TIM15_IRQn_PRIO	0xA
#define __TIM1_UP_TIM16_IRQn_PRIO	0xA
#define __TIM1_TRG_COM_TIM17_IRQn_PRIO	0xA


#endif  /*__IT_PRIO_USERDEFINABLE_H */

/***************************************************************END OF FILE****/
