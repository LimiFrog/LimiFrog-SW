/*******************************************************************************
 * LBF_ExtIT_lowlevAPI.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_EXTIT_LOWLEVAPI_H
#define __LBF_EXTIT_LOWLEVAPI_H


/* Custom Types      ---------------------------------------------------------*/
typedef enum {
  FALLING = 0,
  RISING = 1
}    
IT_Polarity_t;

/* Exported functions ------------------------------------------------------- */

void LBF_Enable_ExtIT( GPIO_TypeDef* GPIO_Port, uint16_t  GPIO_Pin, IT_Polarity_t  IT_Polarity );
void LBF_Disable_ExtIT( GPIO_TypeDef* GPIO_Port, uint16_t  GPIO_Pin );


#endif  /*__LBF_EXTIT_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
