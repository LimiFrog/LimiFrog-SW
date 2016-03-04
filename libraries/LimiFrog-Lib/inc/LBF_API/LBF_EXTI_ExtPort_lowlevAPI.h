/*******************************************************************************
 * LBF_EXTI_ExtPort_lowlevAPI.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_EXTI_EXTPORT_LOWLEVAPI_H
#define __LBF_EXTI_EXTPORT_LOWLEVAPI_H


/* Custom Types      ---------------------------------------------------------*/
typedef enum {
  RISING_TRIGGER_FALSE = 0,
  RISING_TRIGGER_TRUE = 1
}    
IT_RisingTrigger_t;

typedef enum {
  FALLING_TRIGGER_FALSE = 0,
  FALLING_TRIGGER_TRUE = 1
}    
IT_FallingTrigger_t;



/* Exported functions ------------------------------------------------------- */

void LBF_Enable_EXTI_ExtPort ( uint16_t  GPIO_Pin, IT_RisingTrigger_t  IT_RisingTrigger, IT_FallingTrigger_t IT_FallingTrigger);
void LBF_Disable_EXTI_ExtPort( uint16_t  GPIO_Pin);
void LBF_SoftIT_EXTI_ExtPort( uint16_t  GPIO_Pin);
bool LBF_IsPending_EXTI_ExtPort( uint16_t  GPIO_Pin);
void LBF_Clear_EXTI_ExtPort( uint16_t  GPIO_Pin);

void LBF_Enable_NVIC_EXTI_ExtPort( uint16_t  GPIO_Pin );
void LBF_Disable_NVIC_EXTI_ExtPort( uint16_t  GPIO_Pin );

#endif  /*__LBF_EXTI_EXTPORT_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
