/*******************************************************************************
 * LBF_GPIO_lowlevAPI.h
 ******************************************************************************/





/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GPIO_LOWLEVAPI_H
#define __LBF_GPIO_LOWLEVAPI_H

#include "stm32l4xx.h"  //to allow access to STM32 registers in macros below while keeping header self-sufficient

#include <stdbool.h>   //to be able to use boolean type in function prototype below and keep this header seld-sufficient



/* Exported functions (in-lined)      --------------------------------------- */
/*
#define GPIO_HIGH(PORT,PIN)             HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_SET)
#define GPIO_LOW(PORT,PIN)              HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_RESET)
#define GPIO_TOGGLE(PORT,PIN)           HAL_GPIO_TogglePin(PORT, PIN)

#define	IS_GPIO_SET(PORT, PIN)		(bool)(HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_SET)
#define	IS_GPIO_RESET(PORT, PIN)	(bool)(HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_RESET)
*/

// Rather use short inline functions :

/*********
* Function :	
	void GPIO_HIGH ( GPIO_TypeDef* GPIO_Port_Name, uint16_t GPIO_Pin_Number )
* Description :	
	Sets to Logic_1  pin  GPIO_Pin_Number of port GPIO_Port_Name.  
* Parameters : 
 	> GPIO_Port_Name (In):  can be GPIOA to GPIOC (or alias) 
	> GPIO_Pin_Number (In):  can be 0 to 15 (or alias) 
* Return Value:  -
* Note : See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
***********/

__STATIC_INLINE void  GPIO_HIGH(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
   GPIOx->BSRR = (uint32_t)GPIO_Pin;
}



/*********
* Function :	
	void GPIO_LOW ( GPIO_TypeDef* GPIO_Port_Name, uint16_t GPIO_Pin_Number )
* Description :	
	Sets to Logic_0  pin  GPIO_Pin_Number of port GPIO_Port_Name.  
* Parameters : 
 	> GPIO_Port_Name (In):  can be GPIOA to GPIOC (or alias) 
	> GPIO_Pin_Number (In):  can be 0 to 15 (or alias) 
* Return Value:  -
* Note : See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
***********/

__STATIC_INLINE void  GPIO_LOW(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
   GPIOx->BRR = (uint32_t)GPIO_Pin;
}



/*********
* Function :	
	void GPIO_TOGGLE ( GPIO_TypeDef* GPIO_Port_Name, uint16_t GPIO_Pin_Number )
* Description :	
	Toggles the logic level of pin  GPIO_Pin_Number of port GPIO_Port_Name.  
* Parameters : 
 	> GPIO_Port_Name (In):  can be GPIOA to GPIOC (or alias) 
	> GPIO_Pin_Number (In):  can be 0 to 15 (or alias) 
* Return Value:  -
* Note : See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases.
***********/

__STATIC_INLINE void  GPIO_TOGGLE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}



/*******
* Function :	
	bool IS_GPIO_SET ( GPIO_TypeDef* GPIO_Port_Name, uint16_t GPIO_Pin_Number )
* Description :	
	Evaluates the logic level on pin  GPIO_Pin_Number of port GPIO_Port_Name.  
* Parameters : 
 	> GPIO_Port_Name (In):  can be GPIOA to GPIOC (or alias) 
	> GPIO_Pin_Number (In):  can be 0 to 15 (or alias) 
* Return Value:  true if level detected is Logic_1,  else false
* Note : See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases. 
********/

__STATIC_INLINE bool  IS_GPIO_SET(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
GPIO_PinState bitstatus;
  if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return (bool)(bitstatus==GPIO_PIN_SET);
}



/*******
* Function :	
	bool IS_GPIO_RESET ( GPIO_TypeDef* GPIO_Port_Name, uint16_t GPIO_Pin_Number )
* Description :	
	Evaluates the logic level on pin  GPIO_Pin_Number of port GPIO_Port_Name.  
* Parameters : 
 	> GPIO_Port_Name (In):  can be GPIOA to GPIOC (or alias) 
	> GPIO_Pin_Number (In):  can be 0 to 15 (or alias) 
* Return Value:  true if level detected is Logic_0,  else false
* Note : See file LBF_pin_aliases.h for a proposal list of meaningful port name and pin number aliases. 
********/

__STATIC_INLINE bool  IS_GPIO_RESET(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
GPIO_PinState bitstatus;
  if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return (bool)(bitstatus==GPIO_PIN_RESET);
}





#endif  /*__LBF_GPIO_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
