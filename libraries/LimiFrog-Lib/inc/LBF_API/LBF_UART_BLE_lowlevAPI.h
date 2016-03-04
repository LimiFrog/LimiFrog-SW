/*******************************************************************************
 * LBF_UART_lowlevAPI.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_UART_LOWLEVAPI_H
#define __LBF_UART_LOWLEVAPI_H


/* Constants        ---------------------------------------------------------*/

// For UART software flow control
#define  XON   0x13
#define  XOFF  0x11



/* Exported functions ------------------------------------------------------- */

void LBF_UART_BLE_SendByte (uint8_t data);
uint8_t LBF_UART_BLE_ReceiveByte (void);
void LBF_UART_BLE_SendString(char* pString);
void LBF_UART_BLE_SendString_SwFlowControl(char* pString);
 
#endif  /*__LBF_UART_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
