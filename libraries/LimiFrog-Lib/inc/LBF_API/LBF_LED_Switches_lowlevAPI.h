/*******************************************************************************
 * LBF_LED_Switches_lowlevAPI.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_LED_SW_LOWLEVAPI_H
#define __LBF_LED_SW_LOWLEVAPI_H


#include <stdbool.h>   //to be able to use boolean type in function prototype below and keep this header seld-sufficient

#include "LBF_GPIO_lowlevAPI.h"  //to use GPIO_HIGH etc. below and keep this header seld-sufficient




/* Exported functions ------------------------------------------------------- */

/* Switches */
bool LBF_State_Switch1_IsOn(void);
bool LBF_State_Switch2_IsOn(void);


/* Exported in-lined functions ------------------------------------------------------- */

/* LEDs */

/****************
* Function :	
	void LBF_Led_ON(void)
* Description :	
	Turns on the STM32-controlled LED located at the edge of the board
* Parameters :  -
* Return Value:  -
****************/

__STATIC_INLINE  void LBF_Led_ON(void)
{
    GPIO_HIGH(STM32_LED_PORT, STM32_LED_PIN);
}

/****************
* Function :	
	void LBF_Led_OFF(void)
* Description :	
	Turns off the STM32-controlled LED located at the edge of the board
* Parameters :  -
* Return Value:  -
****************/
__STATIC_INLINE  void LBF_Led_OFF(void)
{
    GPIO_LOW(STM32_LED_PORT, STM32_LED_PIN);
}


/****************
* Function :	
	void LBF_Led_TOGGLE(void)
* Description :	
	Toggles the STM32-controlled LED located at the edge of the board
* Parameters :  -
* Return Value:  -
****************/

__STATIC_INLINE  void LBF_Led_TOGGLE(void)
{
    GPIO_TOGGLE(STM32_LED_PORT, STM32_LED_PIN);
}


#endif  /*__LBF_LED_SW_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
