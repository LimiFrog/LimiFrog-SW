/*******************************************************************************
 * LBF_Init_PresetConf_ExtPort.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_INIT_PRESETCONF_EXTPORT_H
#define __LBF_INIT_PRESETCONF_EXTPORT_H


/* Exported functions ------------------------------------------------------- */

void LBF_Init_PresetConf_I2C1 ( I2C_HandleTypeDef* hi2c);
void LBF_DeInit_PresetConf_I2C1 ( I2C_HandleTypeDef* hi2c);

void LBF_Init_PresetConf_SPIoverUSART2 (USART_HandleTypeDef* hSpiUsart, uint32_t User_Configured_BaudRate );
void LBF_DeInit_PresetConf_SPIoverUSART2 (USART_HandleTypeDef* hSpiUsart );

void LBF_Init_PresetConf_UART4 (UART_HandleTypeDef* husart,  uint32_t User_Configured_BaudRate );
void LBF_DeInit_PresetConf_UART4 (UART_HandleTypeDef* husart);

void LBF_Init_Presetconf_UART2 (UART_HandleTypeDef* huart, bool cts_flowcontrol, bool rts_flowcontrol, uint32_t  User_Configured_BaudRate);
void LBF_DeInit_Presetconf_UART2 (UART_HandleTypeDef* huart);


#endif  /*__LBF_INIT_PRESETCONF_EXTPORT_H*/


/***************************************************************END OF FILE****/
