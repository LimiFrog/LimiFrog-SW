/*******************************************************************************
 * LBF_GPIO_lowlevAPI.h
 ******************************************************************************/





/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GPIO_LOWLEVAPI_H
#define __LBF_GPIO_LOWLEVAPI_H

#include "stm32l4xx.h"  //to allow access to STM32 registers in macros below while keeping header self-sufficient


/* Exported Macros ------------------------------------------------------- */

#define GPIO_HIGH(PORT,PIN)             HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_SET)
#define GPIO_LOW(PORT,PIN)              HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_RESET)
#define GPIO_TOGGLE(PORT,PIN)           HAL_GPIO_TogglePin(PORT, PIN)

#define	IS_GPIO_SET(PORT, PIN)		(bool)(HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_SET)
#define	IS_GPIO_RESET(PORT, PIN)	(bool)(HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_RESET)

/* Exported functions ------------------------------------------------------- */




#endif  /*__LBF_GPIO_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
