/*******************************************************************************
 * LBF_UART_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include <stdint.h>


/************
* Function :	
	void LBF_UART_BLE_SendByte(uint8_t TxByte)
* Description :	
	Send a byte over the Tx pin of UART3 which connects to the BLE module. If hardware flow control has been enabled at init then UART3 CTS is taken into account to pause transmission over Tx.
* Parameters : 
	TxByte: The 8-bit value to send 
* Return Value:  -
************/

void LBF_UART_BLE_SendByte (uint8_t TxByte)
{

    HAL_UART_Transmit(&huart3, &TxByte, 0x1, 10);
    // UART blocking Tx of 1 byte with 100ms timeout
    // (huart3 is global)
}



/************
* Function :	
	uint8_t LBF_UART_BLE_ReceiveByte(void)
* Description :	
	Receives a data byte from UART3 which connects to the BLE module (with a  time out set to tbd ms). If hardware flow control has been enabled at init then UART3 RTS is managed to signal readyness to the BLE module.
* Parameters : -
* Return Value:   the data byte received
************/
// <TO DO>:  handle case of time out (no valid data received)

uint8_t LBF_UART_BLE_ReceiveByte ()
{
uint8_t RxByte = 0;
 
    HAL_UART_Receive(&huart3, &RxByte, 0x1, 10);
    // UART blocking Rx of 1 byte with 10ms timeout
    // (huart3 is global)

    return (RxByte);
    
}



/************
* Function :	
	void LBF_UART_BLE_SendString(char* pString)
* Description :	
	Send a string of characters over the Tx pin of UART3 which connects to the BLE module. If hardware flow control has been enabled at init then UART3 CTS is taken into account to pause transmission over Tx.
* Parameters : 
	pString: pointer to the first character of the string 
* Return Value:  -
************/

void LBF_UART_BLE_SendString(char* pString)
{
// Do it in a more clever way?... use HAL API DMA mode to
// send in one shot (but we need to check for end of string, so...?)
char* pStringLocal;

    pStringLocal = pString;

    while(1)   // with break on end of string
    {
        LBF_UART_BLE_SendByte(*pStringLocal);
        pStringLocal++;
        if ( *(pStringLocal++) == '\0')  {
            break; 
        }
    }


}

/************
* Function :	
	void LBF_UART_BLE_SendString_SWFlowControl(char* pString)
* Description :	
	Send a string of characters over the Tx pin of UART3 which connects to the BLE module. If hardware flow control has been enabled at init then UART3 CTS is taken into account to pause transmission over Tx.In addition, software flow control is supported : transmission is paused pon reception of XOFF, until reception of next XON.
* Parameters : 
	pString: pointer to the first character of the string 
* Return Value:  -
************/
void LBF_UART_BLE_SendString_SwFlowControl(char* pString)
{

uint8_t* pStringLocal;
uint8_t  uart_rx;



    pStringLocal = (uint8_t*)pString;

    while(1)   // but will break on end of string
    {

        //Check for XOFF without waiting for any time out
        HAL_UART_Receive(&huart3, &uart_rx, 0x1, 0);

	// Only needed in case BLE firmware implements SW flow control
	// LimiFrog0.1 supports HW flow control so could be removed
        if (uart_rx == XOFF)  // XOFF detected
        {
	     while (uart_rx != XON)   // wait for XON to resume
	     {
                 HAL_UART_Receive(&huart3, &uart_rx, 0x1, 0);
	     }
        }

        HAL_UART_Transmit(&huart3, pStringLocal, 0x1, 10);
        if ( *(pStringLocal++) == '\0')  
            break; 
     } 
}

/**************
* Function :	void LBF_UART_BLE_ReceiveStream_DMA(uint8_t* pRxBuf, uint16_t NumBytes)
* Description :	Receives a string of bytes over the Rx pin of UART3 which connects to the BLE module, using the DMA channel associated to UART3. 
* Parameters : 
>  pRxBuf: pointer to the head of the buffer where to store the received data 
>  NumBytes: the number of bytes to receive
* Return Value:  -
***************/

//void LBF_UART_BLE_ReceiveStream_DMA(uint8_t* pRxBuf, uint16_t NumBytes)
// TO DO !!!!!



/**************
* Function :	void LBF_UART_BLE_SendStream_DMA(uint8_t* pTxBuf, uint16_t NumBytes)
* Description :	Send a string of bytes over the Tx pin of UART3 which connects to the BLE module, using the DMA channel associated to UART3. If hardware flow control has been enabled at init then UART3 CTS is taken into account to pause transmission over Tx. 
* Parameters : 
	>  pTxBuf: pointer to the head of the buffer containing the data to send 
	>  NumBytes: the number of bytes to send
* Return Value:  -
***************/

// void LBF_UART_BLE_SendStream_DMA(uint8_t* pTxBuf, uint16_t NumBytes)
// TO DO !!!!!!!!




/***************************************************************END OF FILE****/
