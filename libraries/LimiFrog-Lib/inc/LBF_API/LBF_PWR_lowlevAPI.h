/*******************************************************************************
 * LBF_PWR_lowlevAPI.h
 ******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_PWR_LOWLEVAPI_H
#define __LBF_PWR_LOWLEVAPI_H

#include <stdbool.h>  //to use type bool in below prototype and keep this header file self-sufficient
#include <stdint.h>        //same rationale, to use uint8_t below


// OLED VCC Control (13V)

void LBF_Turn_VDDH_On(void);
void LBF_Turn_VDDH_Off(void);
bool LBF_Check_VDDH_On(void);


// LDO VCC Control (3.3V) --  available through extension port

void LBF_Enable_LDO(void);
void LBF_Disable_LDO(void);


#endif  /*__LBF_PWR_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
