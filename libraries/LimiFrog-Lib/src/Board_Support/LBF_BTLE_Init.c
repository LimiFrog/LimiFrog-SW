/*************************************************************************
 * LBF_BTLE_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_lowlev_API.h"
#include "User_Configuration.h"  //configuration file in user's project

#ifdef __LBF_LEGACY
  #include "LBF_UART1_Init.h"
#else
  #include "LBF_UART3_Init.h"
#endif

#include "ff_gen_drv.h" // includes ff.h (and in turn ffconf.h) and diskio.h
#include "DataFlash_diskio.h"

/*******************************************************************************
 * @brief  : Obtain BTLE boot code from storage space and download into BTLE
 * @param  : Name of .bin file containing code for PAN1740 BTLE module
 * @return : True if successful boot, else false.
 ******************************************************************************/

bool  LBF_BTLE_Init(char* FileName)
{

bool	Success = true;

uint8_t		RecvdData;
uint8_t		CodeCRC = 0x00;
uint8_t 	CodeBuffer[16384];	//16K max FOR NOW 
                //TODO support up to 32K if needed
uint32_t 	ActualCodeSize;
uint32_t 	i;
uint32_t 	StartTime_ms;

bool	    	Acquire_Code_From_File( char* FileName, 
                                     BYTE* pCodeBuffer, 
				     uint32_t BufferSize,
                                     uint32_t* pActualCodeSize);

// UART1 dedicated to BTLE module on versions earlier than LimiFrog0.1
// then UART3 from LimiFrog0.1
#ifdef __LBF_LEGACY
  #define 	UART_BLE 	UART1
#else
  #define 	UART_BLE 	UART3
#endif

   // Initialise UART used for comms with BLE,
   // first with baudrate used by BLE booting from UART
   // Baud Rate = 57600 bit/s as this is what PAN1740 uses when 
   //   attempting to boot from UART on its P0_4 and P0_5
   #ifdef __LBF_LEGACY
   LBF_UART1_Init(57600);   
   #else
   LBF_UART3_Init(57600);   
   #endif


    // Acquire Code to Download 
    Success = Acquire_Code_From_File( FileName, CodeBuffer, sizeof(CodeBuffer), &ActualCodeSize );
    if (!Success) // then stop here
    {
        return Success; 
    }

    //Compute CRC = XOR of all code bytes
    for (i=0; i<ActualCodeSize; i++)
    {
	CodeCRC = CodeCRC ^ CodeBuffer[i] ;
    }
    

    // Reset BTLE
    GPIO_HIGH(BT_RST_PORT, BT_RST_PIN); // assert BTLE reset
    LBF_Delay_ms(2); 
    GPIO_LOW(BT_RST_PORT, BT_RST_PIN);  // release BTLE reset



// See D14580 Boot-from-serial AN: leave up to 146ms (+margin here) for boot-from-serial protocol
    StartTime_ms = HAL_GetTick();
    while ( ((HAL_GetTick()- StartTime_ms) < 200) )
    {
        Success = (LBF_UART_ReceiveByte(UART_BLE)==0x02);
        if (Success)
	   break;
    }
    if (!Success)  // then stop here
    {
        return Success; 
    }

    // Boot start byte well received, 
    // respond according to DA14580 "Boot from Serial i/f" spec 
    LBF_UART_SendByte(UART_BLE, 0x01);  // SOH
    LBF_UART_SendByte(UART_BLE, (uint8_t) (ActualCodeSize &   0xFF) );       // LEN_LSB 
    LBF_UART_SendByte(UART_BLE, (uint8_t)((ActualCodeSize & 0xFF00)>>8)  );  // LEN_MSB

    // Get acknowledge from BTLE
    RecvdData = LBF_UART_ReceiveByte( UART_BLE );
    if ( RecvdData != 0x06)  // ACK=0x06,  NACK=0x15
    {
        Success = false; 
        if (RecvdData != 0x15)  //problem, not a proper NACK
        {
	    //may want to add an error handler here
        }
        return Success;
    }


    // Tx data acknowledged, so :

    // Send all bytes from file over UART 
    for (i=0; i<ActualCodeSize; i++)
    {
	LBF_UART_SendByte( UART_BLE, CodeBuffer[i] );
    }
    

    // Get CRC = XOR over code bytes from DA14580
    if (LBF_UART_ReceiveByte( UART_BLE )!= CodeCRC ) 
    {
        Success = false;
        return Success;
    }

    // Send ACK = 0x06 to DA14580
    LBF_UART_SendByte( UART_BLE, 0x06 );

    #ifdef __LBF_LEGACY
    LBF_UART1_Init( UART_BLE_BAUDRATE );   
    #else
    LBF_UART3_Init( UART_BLE_BAUDRATE );   
    #endif
    // Baud rate required by application running on PAN1740, replaces
    // baud rate required when PAN1740 boots from UART on P0_4/5 (no choice there)

    LBF_Delay_ms(6);
    // Found that 4ms (some margin here) latency was needed between code download
    // and start of Tx to DA14580 through UART,
    // else DA1480 does not advertize. 
    // Possible relationship with connection interval / advertizing interval settings ???


    return Success;  


}

/* ========================================================================== */


bool   Acquire_Code_From_File( char* FileName, 
                                     BYTE* pCodeBuffer, 
				     uint32_t BufferSize,
                                     uint32_t* pActualCodeSize)
{

/* --  FatFS Objects     ----------------------------------------  */
FATFS DataFlash_DISK_FatFs; /* File system object for User logical drive */
char DataFlash_DISK_Path[4]; /* User logical drive path */

bool FatFS_Ok = true;
FIL MyFile;
UINT rbytes_count; /* File read counts */



   /* -- Initialize FatFS and Mount DataFlash  ------------- */

    FatFS_Ok &= (FATFS_LinkDriver(&DataFlash_DISK_Driver, DataFlash_DISK_Path) == 0);
    if (FatFS_Ok)
    {
        FatFS_Ok &= 
        ( f_mount(&DataFlash_DISK_FatFs, (TCHAR const*)DataFlash_DISK_Path, 0) == FR_OK);
    }
    

    /* --- Open File and Read it        ------------------- */

    FatFS_Ok &= ( f_open(&MyFile, FileName, FA_OPEN_EXISTING|FA_READ) == FR_OK );
    FatFS_Ok &= ( f_read( &MyFile, pCodeBuffer, BufferSize, &rbytes_count ) == FR_OK);

    /* --- Close File                   ------------------- */
    FatFS_Ok  &=  (f_close(&MyFile) == FR_OK);

    /* --- DeInit                       ------------------- */
    FATFS_UnLinkDriver(DataFlash_DISK_Path);


    *pActualCodeSize = rbytes_count;

    return ( FatFS_Ok );

}




/***************************************************************END OF FILE****/
