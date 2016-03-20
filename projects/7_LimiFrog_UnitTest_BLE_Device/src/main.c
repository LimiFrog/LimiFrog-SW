/*******************************************************************************
 * main.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_Global.h"

volatile bool Rx_uart3  ;
  // global variable shared with Interrupt Service Routine in stm32_it.c


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = true;

/* ================================================================ */
/* Board Initializations and Configurations except OLED             */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)                */
/* ================================================================ */

   LBF_Board_Inits();
        // actions partly driven by User_Configuration.h

   LBF_Led_ON();


/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    Success &= LBF_LaunchUSB_MassStorage();


    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    // Success &= LBF_FatFS_Init();

    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed




/* ===================================================== */
/* Application Code Below */
/* ===================================================== */

// --------------------------------------------------------
// BTLE must be enabled by #define in User_Configuration.h
// Name of the file containing code to download by STM32 
// into BTLE module also defined there -- download occurs
// during LBF_Board_Selective_Inits() phase.
// This executable must be present on FAT File System on Flash 
// (typically stored there from PC through USB).
// In this demo, code is supposed to be Serial Port Service
// snippet provided by Dialog -- this configures the BTLE
// to behave as UART cable replacement. Data sent to
// BTLE module over UART1 at 115200 baud is transitted over BTLE
// This data can be received by DSPS application running in iOS
// or Android, provided by Dialog, available on Appple/Android
// app stores
// --------------------------------------------------------


/* ==  User Declarations =============================== */

char TxString[]="\nHi there !\nThis is LimiFrog.\nHow are you ?\n";
char* pString;

char RxString[256];
uint8_t RxByte ;

uint32_t i;



/* ==  Body     ======================================== */


    LBF_OLED_Switch_ON();  // DON'T FORGET #define USE_OLED in User_Configuration.h

    LBF_OLED_PrintString("\nStarting...\n");



   // -- Inits     ----------------------------

    i=0;
    Rx_uart3 = false;

    // Initialize IT from UART3 (UART connected to BLE module)
    HAL_NVIC_SetPriority(USART3_IRQn, __USART3_IRQn_PRIO, 0 );
    HAL_NVIC_EnableIRQ(USART3_IRQn);


   // -- Send/Receive Messages ---------------


   // Enable Rx of 1 byte on UART3 in IT mode
   HAL_UART_Receive_IT(&huart3, &RxByte, 0x1 );
	    // huart3 global variable


   while(1) 
   {
       LBF_Led_ON();

        // ***  Receive section:

        if( Rx_uart3 )  
	      // if new byte received (flag set in ISR of stm32_it.c)
        {

	     RxString[i++] = RxByte;

             // Display String if carriage return received
	     if ( (RxByte == '\n') )
	     {
		// Disable UART while displaying (which will take some time)
		// Any subsequent chars received after \n during this time are ignored
		// (and therefore overrun errors on UART Rx are avoided)
		__HAL_USART_DISABLE( &huart3 );

		RxString[i] = '\0'; // Add an end-of-string character for proper string display
		LBF_OLED_PrintString("\n"); 	//skip 1 line
		LBF_OLED_PrintString(RxString);
		LBF_OLED_PrintString("\n");	//skip 1 line
		i = 0;

		//Enable back UART
		__HAL_USART_ENABLE( &huart3 );
	     }


	    // Relaunch UART3 Rx 
	    Rx_uart3 = false;
            HAL_UART_Receive_IT(&huart3, &RxByte, 0x1 );
        }


        // ***  Transmit section:

        // Check if user pushes side-switch
        if ( LBF_State_Switch1_IsOn() )
        {
          LBF_Led_OFF();

          // Send a text message from UART to BTLE for emission
          pString = TxString;
          LBF_UART_BLE_SendString_SwFlowControl( pString);

         while (  LBF_State_Switch1_IsOn() ); // wait for release

        }

   }  // end of while(1)

}


/***************************************************************END OF FILE****/// 
