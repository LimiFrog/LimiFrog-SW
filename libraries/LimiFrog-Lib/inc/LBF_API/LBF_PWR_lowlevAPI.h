/*******************************************************************************
 * LBF_PWR_lowlevAPI.h
 ******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_PWR_LOWLEVAPI_H
#define __LBF_PWR_LOWLEVAPI_H

#include <stdbool.h>  //to use type bool in below prototype and keep this header file self-sufficient
#include <stdint.h>        //same rationale, to use uint8_t below


//#include "pin_aliases.h"

/* Exported constants --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */

void Turn_VDDH_On(void);
void Turn_VDDH_Off(void);
bool Check_VDDH_On(void);



#endif  /*__LBF_PWR_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
