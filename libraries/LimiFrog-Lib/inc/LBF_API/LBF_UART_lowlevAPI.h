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

/* Custom Types      ---------------------------------------------------------*/
typedef enum {
  UART1 = 1,
  UART3 = 3
}    
UartID_t;


/* Exported functions ------------------------------------------------------- */

void LBF_UART_SendByte (UartID_t Uart_ID, uint8_t data);
uint8_t LBF_UART_ReceiveByte (UartID_t Uart_ID);
void LBF_UART_SendString(UartID_t Uart_ID, char* pString);
void LBF_UART_SendString_SwFlowControl(UartID_t Uart_ID, char* pString);
 
#endif  /*__LBF_UART_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
