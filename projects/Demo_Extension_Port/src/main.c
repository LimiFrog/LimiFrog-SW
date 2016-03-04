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

#include "stm32l4xx_ll_dma.h"  // Low-layer driver for DMA
#include "stm32l4xx_ll_usart.h"  // Low-layer driver for USART

#include "IT_Priorities_UserDefinable.h"
 //shuold be in Global.h !!!



UART_HandleTypeDef hUart4; 
USART_HandleTypeDef hSpiUsart2; 
TIM_HandleTypeDef hTim16; 


bool volatile TxDMA_complete_UART4 = false, RxDMA_complete_UART4 = false;
bool volatile IRQ_Seen_Position10;
// Must be declared as volatile to make compiler aware this value can be modified 
// outside this file (in an Interrupt Servicing Routine --ISR). Else compiler
// may wrongly optimize as, looking at this file only, the variable is seemingly
// constant. 


static void Configure_DMA2_Ch3_Ch5_for_UART4
	(uint8_t *pUart4_Rx_Data, uint8_t* pUart4_Tx_Data, uint16_t Num_Bytes );


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
   // Includes Extension port config + Enable/Disable OLED & BlueTooth 4.x


   LBF_Led_ON();

/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    // Delay_ms(1000);
    // Success &= LBF_LaunchUSB_MassStorage();
 
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

    LBF_Led_OFF();



/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

uint8_t	Uart4_Tx_Data[256], Uart4_Rx_Data[256];
uint8_t Spi_Mosi_Data[256], Spi_Miso_Data[256];

uint32_t StartTime;
uint16_t i;

bool 	Match = true;



/* ==  Body     ======================================== */

// LBF_OLED_Switch_ON();

    LBF_Led_ON();
 
    /* User_Configuration.h has set all relevant extension port pins
       as GPIO outputs, and has enabled VCC_LDO on position 6      */


// ---   Test of Digital Functions on extension port     -------------

// Extension port configuration expected to be defined through
// User_Configuration.h
//
// POS11: EXTI
// POS10: GPIO
// POS9: GND
// POS8: UART4_TX
// POS7: UART4_RX
// POS6: VCC_LDO
// POS5: SPI_MOSI over USART2_TX
// POS4: SPI_MISO over USART2_RX
// POS3: SPI_CK over USART2_CK
// POS2: PWM out
// POS1: MIC OUT
// -----------------------------------------------------------------

    
    // ---  Use preset configurations for initializing 
    // ---   the selected peripherals to use on the extension port

    // Preset configuration for UART4 (8-bit, 1 stop bit, no parity...)
    LBF_Init_PresetConf_UART4 (&hUart4, 56000) ;  //56Kbit/s baud rate

    // Initialize the preset configuration for SPI over USART2 
    LBF_Init_PresetConf_SPIoverUSART2 (&hSpiUsart2, 1000000) ;  //1Mbit/s 

    // Setup PWM on Timer16, Ch1 (that available on Ext Port Position #2)
    LBF_Timer_Setup (&hTim16, TIMER16, TIMER_UNIT_US, 10); //10us Period i.e. 100KHz 
    LBF_PWMchannel_Setup(&hTim16, CHANNEL1, 3);  //3us pulse duration so 30% duty cycle


    // ----------------------
    // We want to use DMA with UART4: Initialize DMA
    // From Ref Manual Tables 37-39 :
    // UART4 Tx can use DMA2, Channel3 and is assigned req #2 of this channel
    // UART4 Rx can use DMA2, Channel5 and is assigned req #2 of this channel

    // Set up DMA for 256 bytes Rx and Tx on UART4
    Configure_DMA2_Ch3_Ch5_for_UART4( Uart4_Rx_Data, Uart4_Tx_Data, 256);


    // Configure NVIC for DMA transfer complete/error interrupts */
    // (parameters __DMA2_Channelxx_IRQn_PRIO expected to be defined 
    //  in e.g. IT_Priorities_UserDefinable.h)
    // Tx DMA :
    NVIC_SetPriority(DMA2_Channel3_IRQn, __DMA2_Channel3_IRQn_PRIO);  
    NVIC_EnableIRQ(DMA2_Channel3_IRQn);
    // Rx DMA :
    NVIC_SetPriority(DMA2_Channel5_IRQn, __DMA2_Channel5_IRQn_PRIO);
    NVIC_EnableIRQ(DMA2_Channel5_IRQn);


    // ----------------------

    // Initialize data buffers :
    for (i=0; i<256; i++)
    {
	Uart4_Tx_Data[i] = i;
	Spi_Mosi_Data[i] = 255-i;
    }


    // -------------------------------------------------------------------
    // Demo STEP1:  
    //        start PWM on position 1 of the extension port :
    //        PWM16 CH1, with period/duty cycle defined above

    LBF_PWMchannel_Start(&hTim16, CHANNEL1); 


    // -------------------------------------------------------------------
    // Demo STEP2:  
    //        Transmit/receive over UART4 - ext port pos. 8 (Tx) and 7 (Rx):
    //        Send 256 bytes over DMA, attempt to receive 256 bytes over DMA,
    //        if external connection between Pos 7 and 8 (loopback) then Rx=Tx

    // Enable UART4
    LL_USART_Enable(UART4);
    // Polling USART initialisation - just in case
    while((!(LL_USART_IsActiveFlag_TEACK(UART4))) || (!(LL_USART_IsActiveFlag_REACK(UART4))));

    // Enable DMA requests from UART4 
    LL_USART_EnableDMAReq_RX(UART4);
    LL_USART_EnableDMAReq_TX(UART4);

    // Enable DMA Channel Rx, then Tx 
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_5);
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_3);

    // Check DMA complete with time-out
    StartTime = HAL_GetTick();
    while( (HAL_GetTick() - StartTime) < 500 )  // 500ms time-out
    {
	if ( TxDMA_complete_UART4 && RxDMA_complete_UART4 )  // set in interrupt service routine
	    break;
    }

    // Disable Req from UART and DMA channels 
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_3);
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_5);
    LL_USART_EnableDMAReq_TX(UART4);
    LL_USART_EnableDMAReq_RX(UART4);

    // If external loopback (UART4 Rx connected to UART4 Tx) data should match
    for (i=0; i<256; i++)
    {
	    Match &= (Uart4_Tx_Data[i] == Uart4_Rx_Data[i]);
    }


    // -------------------------------------------------------------------
    // Demo STEP3:  
    //   Transmit/receive data in SPI format using USART2 
    //   (according to preset configuration enabled above),
    //   on ext port positions 5 (MOSI), 4 (MISO) and 3 (SPICK),
    //   in full duplex bidirectional mode (blocking, no DMA)
    HAL_USART_TransmitReceive( &hSpiUsart2, 
		Spi_Mosi_Data, Spi_Miso_Data, 256,  // send and receive 256 bytes
		0x1 );  // 1ms time-out
    
    // If external loopback with position 4 connected to position 5
    // (USART2 Rx=SPI MISO connected to USAR2 Tx = SPI MOSI), data should match
    for (i=0; i<256; i++)
    {
	    Match &= (Spi_Miso_Data[i] == Spi_Mosi_Data[i]);
    }


   // -------------------------------------------------------------------
    // Demo STEP4:  
    //       Generate rising edge on Extension Port position 11
    //       With Ext port position 10 set as riding-edge triggered IT...
    
    // Enable EXTI10
    LBF_Enable_EXTI_ExtPort ( CONN_POS10_PIN, RISING_TRIGGER_TRUE, FALLING_TRIGGER_FALSE);

    // Set position 11 of extension connector to Logic0
    //  (already configured as push-pull output at init, based on 
    //  User_Configuration.h)
    HAL_GPIO_WritePin( CONN_POS11_PORT, CONN_POS11_PIN, GPIO_PIN_RESET );


    // Enable NVIC for EXTI group corresponding to CONN_POS_10 (EXTI9_5)
    LBF_Enable_NVIC_EXTI_ExtPort( CONN_POS10_PIN );


    // Now Pull POS11 high and then back low
    HAL_GPIO_WritePin( CONN_POS11_PORT, CONN_POS11_PIN, GPIO_PIN_SET );
    HAL_GPIO_WritePin( CONN_POS11_PORT, CONN_POS11_PIN, GPIO_PIN_RESET );


    // If externally connecting position 11 to position 10,
    // the pulse on pos.11 should trigger an IT,
    // in the ISR we set a flag IRQ_Seen_Position10 (see stm32_it.c)
    Match &= IRQ_Seen_Position10;


    // -------------------------------------------------------------------
    // Display result : 
    // fixed LED if loopbacks OK (external connections made) else flashing

    while(1)
    {
	LBF_Delay_ms(100);
	if (!Match)
	    LBF_Led_OFF();
        LBF_Delay_ms(300);
    	LBF_Led_ON();
    }


}


/****  PRIVATE FUNCTIONS   *************************************************************/



static void Configure_DMA2_Ch3_Ch5_for_UART4
	(uint8_t *pUart4_Rx_Data, uint8_t *pUart4_Tx_Data, uint16_t Num_Bytes )
{

// This routine configures DMA2 so it can serve UART4 Rx/Tx
// When actual transfer is needed, the user still has to :
// - at UART level, enable generation of DMA requests from UART4 Tx and/or Rx 
// - at DMA level, enable channels 3 and/or 5 of DMA2 (assigned to UART4 Tx/Rx)
// If the user wishes to trigger interrupts at STM32 level based
// on DMA transfer status, he/she has to enable the relevant IT at NVIC level and write
// an adequate interrup handler (e.g. in stm32_it.c) -- either using the HAL 
// approach or a lighter solution.


    // Enable clock of DMA2:
    __DMA2_CLK_ENABLE();

    // Using Low-level drivers rather than HAL :

    // Configure transmit DMA functional parameters
    LL_DMA_ConfigTransfer(DMA2, LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH | 
                        LL_DMA_PRIORITY_MEDIUM            | 
                        LL_DMA_MODE_NORMAL                | 
                        LL_DMA_PERIPH_NOINCREMENT         | 
                        LL_DMA_MEMORY_INCREMENT           | 
                        LL_DMA_PDATAALIGN_BYTE            | 
                        LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_ConfigAddresses(DMA2, LL_DMA_CHANNEL_3,
                         (uint32_t)pUart4_Tx_Data, 
                         LL_USART_DMA_GetRegAddr(UART4, LL_USART_DMA_REG_DATA_TRANSMIT),
                         LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_3));
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_3, Num_Bytes); 
    LL_DMA_SetPeriphRequest(DMA2, LL_DMA_CHANNEL_3, LL_DMA_REQUEST_2);


    // Configure receive DMA functional parameters
    LL_DMA_ConfigTransfer(DMA2, LL_DMA_CHANNEL_5, 
                        LL_DMA_DIRECTION_PERIPH_TO_MEMORY | 
                        LL_DMA_PRIORITY_MEDIUM            | 
                        LL_DMA_MODE_NORMAL                | 
                        LL_DMA_PERIPH_NOINCREMENT         | 
                        LL_DMA_MEMORY_INCREMENT           | 
                        LL_DMA_PDATAALIGN_BYTE            | 
                        LL_DMA_MDATAALIGN_BYTE);

    LL_DMA_ConfigAddresses(DMA2, LL_DMA_CHANNEL_5,
                         LL_USART_DMA_GetRegAddr(UART4, LL_USART_DMA_REG_DATA_RECEIVE),
                         (uint32_t)pUart4_Rx_Data, // always source addr *then* dest addr 
                         LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_5));
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_5, Num_Bytes);  // 256 bytes over Rx DMA
    LL_DMA_SetPeriphRequest(DMA2, LL_DMA_CHANNEL_5, LL_DMA_REQUEST_2);

    LL_DMA_ClearFlag_GI3(DMA2);  // // global clear of all channel3 DMA2 IT flags
    LL_DMA_ClearFlag_GI5(DMA2);  // // global clear of all channel5 DMA2 IT flags

    // Enable DMA transfer complete/error interrupts  
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_3);
    LL_DMA_EnableIT_TE(DMA2, LL_DMA_CHANNEL_3);
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_5);
    LL_DMA_EnableIT_TE(DMA2, LL_DMA_CHANNEL_5);
}


/***************************************************************END OF FILE****/
