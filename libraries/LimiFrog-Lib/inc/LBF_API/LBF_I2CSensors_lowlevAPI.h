/*******************************************************************************
 * LBF_I2CSensors_lowlevAPI.h
 ******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_I2CSENSORS_LOWLEVAPI_H
#define __LBF_I2CSENSORS_LOWLEVAPI_H

#include <stdint.h>        //same rationale, to use uint8_t below


//#include "pin_aliases.h"

/* Exported constants --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */


void LBF_I2CSensors_WriteSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegVal);
void  LBF_I2CSensors_WriteMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToWrite );

uint8_t LBF_I2CSensors_ReadSingleReg (uint8_t ChipID, uint16_t RegAdd);
void LBF_I2CSensors_ReadMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToRead );

void LBF_I2CSensors_RmodWSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegMask, uint8_t RegUpdateVal);


#endif  /*__LBF_I2CSENSORS_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
