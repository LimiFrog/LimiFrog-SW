/*******************************************************************************
 * LBF_ExtPort_lowlevAPI.h
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_EXTPORT_LOWLEVAPI_H
#define __LBF_EXTPORT_LOWLEVAPI_H


/* Exported functions ------------------------------------------------------- */

void LBF_Enable_LDO();
void LBF_Disable_LDO();

uint8_t LBF_SPIoverUSART2_TransferByte(uint8_t TxByte);

void	LBF_I2C1_WriteSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegVal);
void  	LBF_I2C1_WriteMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToWrite );
uint8_t LBF_I2C1_ReadSingleReg (uint8_t ChipID, uint16_t RegAdd);
void 	LBF_I2C1_ReadMultipleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t* pVal, uint16_t NumByteToRead );
void 	LBF_I2C1_RmodWSingleReg (uint8_t ChipID, uint16_t RegAdd, uint8_t RegMask, uint8_t RegUpdateVal);

void LBF_UART4_ReceiveBuffer(uint8_t* pRxBuffer,  uint16_t size);
void LBF_UART4_SendBuffer(uint8_t* pTxBuffer,  uint16_t size);


#endif  /* __LBF_EXTPORT_LOWLEVAPI_H */

/***************************************************************END OF FILE****/
