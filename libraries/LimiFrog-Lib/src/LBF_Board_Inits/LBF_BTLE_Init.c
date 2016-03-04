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


#include "User_Configuration.h"

#include "LBF_lowlev_API.h"
#include "LBF_UART3_Init.h"

#include "ff_gen_drv.h" // includes ff.h (and in turn ffconf.h) and diskio.h
#include "DataFlash_diskio.h"

static bool  Acquire_Code_From_File( char* FileName, 
                                     BYTE* pCodeBuffer, 
				     uint32_t BufferSize,
                                     uint32_t* pActualCodeSize);

static void 	LBF_UART3_SendByte (uint8_t data);
static uint8_t 	LBF_UART3_ReceiveByte (void);


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
uint8_t 	CodeBuffer[20*1024];	//20K max FOR NOW 
                //TODO Make that configurable ?
		//TODO "Chop" firmware downoad to use (several times)
		// a smaller buffer and limit RAM consumption
uint32_t 	ActualCodeSize;
uint32_t 	i;
uint32_t 	StartTime_ms;

   // UART3 dedicated to BTLE module from LimiFrog0.1 onwards
   // Initialise UART used for comms with BLE,
   // first with baudrate used by BLE booting from UART
   // Baud Rate = 57600 bit/s as this is what PAN1740 uses when 
   //   attempting to boot from UART on its P0_4 and P0_5
   LBF_UART3_Init(57600);   



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
        Success = (LBF_UART3_ReceiveByte()==0x02);
        if (Success)
	   break;
    }
    if (!Success)  // then stop here
    {
        return Success; 
    }

    // Boot start byte well received, 
    // respond according to DA14580 "Boot from Serial i/f" spec 
    LBF_UART3_SendByte(0x01);  // SOH
    LBF_UART3_SendByte((uint8_t) (ActualCodeSize &   0xFF) );       // LEN_LSB 
    LBF_UART3_SendByte((uint8_t)((ActualCodeSize & 0xFF00)>>8)  );  // LEN_MSB

    // Get acknowledge from BTLE
    RecvdData = LBF_UART3_ReceiveByte();
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
	LBF_UART3_SendByte( CodeBuffer[i] );
    }
    

    // Get CRC = XOR over code bytes from DA14580
    if (LBF_UART3_ReceiveByte(  )!= CodeCRC ) 
    {
        Success = false;
        return Success;
    }

    // Send ACK = 0x06 to DA14580
    LBF_UART3_SendByte( 0x06 );

 
    // Now switch to Baud rate required by application running on PAN1740, 
    // to replace rate required when PAN1740 boots from UART on P0_4/5 
    // (no choice there)
    LBF_UART3_Init( UART_BTLE_BAUDRATE );   


    LBF_Delay_ms(6);
    // Found that 4ms (some margin here) latency was needed between code download
    // and start of Tx to DA14580 through UART,
    // else DA1480 does not advertize. 
    // Possible relationship with connection interval / advertizing interval settings ???


    return Success;  


}

/***   PRIVATE FUNCTIONS       ************************************************/


static bool   Acquire_Code_From_File( char* FileName, 
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

/* ========================================================================== */

/*******************************************************************************
 * @brief  : Send specified data byte over UART3 (with a time out set to 100ms).
 * @param  : the data byte to send.
 * @retval : none.
 ******************************************************************************/

static void LBF_UART3_SendByte (uint8_t data)
{
         HAL_UART_Transmit(&huart3, &data, 0x1, 100);

        // UART blocking Tx of 1 byte with 100ms timeout
        // (huart3 is global)
}


/* ========================================================================== */

/*******************************************************************************
 * @brief  : Receives a data byte from UART3 (with a time out set to 100ms). 
 * @param  : None.
 * @retval : the byte received.
 ******************************************************************************/

static uint8_t LBF_UART3_ReceiveByte (void)
{
uint8_t RxByte = 0;
 
        HAL_UART_Receive(&huart3, &RxByte, 0x1, 100);
    
        // UART blocking Rx of 1 byte with 100ms timeout
        // (huart3 is global)
    
        return (RxByte);
}

/***************************************************************END OF FILE****/
