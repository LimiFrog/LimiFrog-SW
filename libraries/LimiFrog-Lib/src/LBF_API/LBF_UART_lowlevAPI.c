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



/*******************************************************************************
 * @brief  : Send specified data byte over specified UART (with a default time out set to 100ms).
 * @param  : Uart_ID : specifies target UART, can take value UART1 or UART3 (UART #2 not used in LimiFrog) 
 *	     data : the data byte to send.
 * @retval : none.
 ******************************************************************************/
void LBF_UART_SendByte (UartID_t Uart_ID, uint8_t data)
{

    if (Uart_ID == UART1)
    {
         HAL_UART_Transmit(&huart1, &data, 0x1, 100);
    }
    else if (Uart_ID == UART3)
    {
         HAL_UART_Transmit(&huart3, &data, 0x1, 100);
    }
        // UART blocking Tx of 1 byte with 100ms timeout
        // (huart(x) is global)
    }

/*******************************************************************************
 * @brief  : Receives a data byte from specified UART (with a default time out set to 100ms). 
 * @param  : Uart_ID : specifies target UART, can take value UART1 or UART3 (UART #2 not used in LimiFrog) 
 *	     data : the data byte received.
 * @retval : Rien.
 ******************************************************************************/
uint8_t LBF_UART_ReceiveByte (UartID_t Uart_ID)
{
uint8_t RxByte = 0;
 
    if (Uart_ID == UART1)
    {
        HAL_UART_Receive(&huart1, &RxByte, 0x1, 100);
    }
    else if (Uart_ID == UART3)
    {
        HAL_UART_Receive(&huart3, &RxByte, 0x1, 100);
    }
        // UART blocking Rx of 1 byte with 100ms timeout
        // (huart(x) is global)
    
    return (RxByte);
    
}

/*******************************************************************************
 * @brief  : Sends a string of characters over specified UART without any flow control (with a default time out set to 100ms on UART reception) 
 * @param  : Uart_ID : specifies target UART, can take value UART1 or UART3 (UART #2 not used in LimiFrog) 
 * 	     pString: pointer to the first character of the string
 * @retval : Rien.
 ******************************************************************************/
void LBF_UART_SendString(UartID_t Uart_ID, char* pString)
{
// Do it in a more clever way?... use HAL API DMA mode to
// send in one shot (but we need to check for end of string, so...?)
char* pStringLocal;

    pStringLocal = pString;
    // while((*pStringLocal)!='\0')
    while(1)   // with break on end of string
    {
        LBF_UART_SendByte(Uart_ID, *pStringLocal);
        pStringLocal++;
        if ( *(pStringLocal++) == '\0')  {
            break; 
        }
    }


}

/*******************************************************************************
 * @brief  : Send string with XON/XOFF based flow control (with default timeout)
 * @param  : Uart_ID : specifies target UART, can take value UART1 or UART3 (UART #2 not used in LimiFrog) 
 * 	     pString: pointer to the first character of the string
 * @retval : Rien.
 ******************************************************************************/
void LBF_UART_SendString_SwFlowControl(UartID_t Uart_ID, char* pString)
{

uint8_t* pStringLocal;
uint8_t  uart_rx;
UART_HandleTypeDef huart;  // handle used by UART HAL functions 


    if (Uart_ID == UART1)
    {
        huart = huart1;
    }
    else if (Uart_ID == UART3)
    {
        huart = huart3;
    }
    

    pStringLocal = (uint8_t*)pString;

    while(1)   // but will break on end of string
    {

        //Check for XOFF without waiting for any time out
        HAL_UART_Receive(&huart, &uart_rx, 0x1, 0);

	// Only needed in case BLE firmware implements SW flow control
	// LimiFrog0.1 supports HW flow control so could be removed
        if (uart_rx == XOFF)  // XOFF detected
        {
	     while (uart_rx != XON)   // wait for XON to resume
	     {
                 HAL_UART_Receive(&huart, &uart_rx, 0x1, 0);
	     }
        }

        HAL_UART_Transmit(&huart, pStringLocal, 0x1, 100);
        if ( *(pStringLocal++) == '\0')  
            break; 
     } 
}



/***************************************************************END OF FILE****/
