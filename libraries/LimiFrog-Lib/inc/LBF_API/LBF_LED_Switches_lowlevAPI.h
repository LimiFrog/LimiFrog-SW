/*******************************************************************************
 * LBF_LED_Switches_lowlevAPI.h
 ******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_LED_SW_LOWLEVAPI_H
#define __LBF_LED_SW_LOWLEVAPI_H

#include <stdbool.h>   //to be able to use boolean type in function prototype below and keep this header seld-sufficient

/* Exported Macros ------------------------------------------------------- */



/* Exported functions ------------------------------------------------------- */

/* LEDs */
void LBF_Led_ON(void);
void LBF_Led_OFF(void);
void LBF_Led_TOGGLE(void);

/* Switches */
bool LBF_State_Switch1_IsOn(void);
bool LBF_State_Switch2_IsOn(void);

#endif  /*__LBF_LED_SW_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
