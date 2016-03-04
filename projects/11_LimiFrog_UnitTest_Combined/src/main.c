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

#include "LBF_UART3_IOcfg.h"
#include "LBF_UART3_Init.h"


// --- Local "helper" function   -------------------

static bool TestBLE(void);


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
   // Caution: do not enable BLE there as in this scenario there's
   // no real BLE fw stored in Flash  

   LBF_Led_ON();
   LBF_Delay_ms(300);
   LBF_Led_OFF();


/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

// UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    // Success &= LBF_LaunchUSB_MassStorage();

    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    Success &= LBF_FatFS_Init();

    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    //Success &= LBF_emWin_Init();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

uint8_t ReadValue;

FIL MyFile;    /* FatFS File object */
uint32_t  wbytes_count;       	/* Number of bytes written in file */
uint8_t wtext[] = "Formatted by FatFS\r\n"; 	/* File write buffer */
uint32_t  rbytes_count; 	/* File read counts */
uint8_t   rtext[32]; 		/* File read buffer */

uint32_t i;


/* ==  Body     ====================================================== */



 /* ---     Activate 13V to OLED (just to check no perturbation)  ---- */

    LBF_OLED_Switch_ON();
  


 /* ---     Format Flash as Fat-FS file system                ------- */

    /* Create FAT volume with default cluster size */
    Success &= ( f_mkfs("", 0, 0) == FR_OK); 



 /* ---     Write and read back short file, check consistency   ------ */

    /* Create a file as new */
    Success &= ( f_open(&MyFile, "FS_Formt.log", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK);

    /* Write a message and close*/
    Success &= ( f_write(&MyFile, wtext, sizeof(wtext)-1, (void *)&wbytes_count)  == FR_OK);
    f_close(&MyFile);

    /* Open & Read it back */
    Success &= ( f_open(&MyFile, "FS_Formt.log", FA_READ) == FR_OK);
    Success &= (f_read(&MyFile, rtext, sizeof(wtext)-1, (void *)&rbytes_count) == FR_OK);

    /* Close the file and de-init FatFS*/
    f_close(&MyFile);
    LBF_FatFS_DeInit();

    /* Compare Result */
    if (wbytes_count != rbytes_count)  //# of bytes written and read back don't match
    {
        Success = FALSE;
    }
    else 
    {
        for (i=0; i<rbytes_count; i++) //# check actual contents
        {
            if (wtext[i]!=rtext[i])
            {
            Success = FALSE;
            }
        }
    }


  /* ---     Check access to all sensors              -------------------- */


    /* ---  ALS/Proximity Sensor : ST VL6180X  --- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, VL6180X_WHOAMI);
    Success &= (ReadValue == VL6180X_WHOAMI_CONTENTS);

    /* ---     Check access to Magnetometer :  ST LIS3MDL   ---------- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, LIS3MDL_WHOAMI);
    Success &= (ReadValue == LIS3MDL_WHOAMI_CONTENTS);

    /* ---     Check access to Accelerometer/Gyro :  ST LSM6DS3  ----- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, LSM6DS3_WHOAMI);
    Success &= (ReadValue == LSM6DS3_WHOAMI_CONTENTS);

    /* ---     Check access to Pressure/Temp Sensor : ST LPS25H  ----- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_WHOAMI);
    Success &= (ReadValue == LPS25H_WHOAMI_CONTENTS);


  /* ---     Download dummy FW into BLE module          -------------- */

    Success &= TestBLE();
    GPIO_HIGH(BT_RST_PORT, BT_RST_PIN); // put BTLE back in reset state


  /* ---     Switch off 13V to OLED             ---------------------- */

    LBF_OLED_Switch_OFF();


  /* ---     Enable USB                        ------------------------ */
    Success &= LBF_LaunchUSB_MassStorage();


  /* ---     Position all controllable GPIO to Logic1    -------------- */
  /* ---     for probing                                 -------------- */
  /* ---     User_configuration.h must have set them as outputs   ----- */

	GPIO_HIGH( CONN_POS11_PORT, CONN_POS11_PIN);
	GPIO_HIGH( CONN_POS10_PORT, CONN_POS10_PIN);

	GPIO_HIGH( CONN_POS8_PORT, CONN_POS8_PIN);
	GPIO_HIGH( CONN_POS7_PORT, CONN_POS7_PIN);

	GPIO_HIGH( CONN_POS5_PORT, CONN_POS5_PIN);
	GPIO_HIGH( CONN_POS4_PORT, CONN_POS4_PIN);
	GPIO_HIGH( CONN_POS3_PORT, CONN_POS3_PIN);
	GPIO_HIGH( CONN_POS2_PORT, CONN_POS2_PIN);


  /* ---     Report Result :               ------------------------------ */
  /* ---       fixed LED if success, quick blinking LED if failure   ---- */

    while(1)
    {
	LBF_Led_ON();
        LBF_Delay_ms(100);

        if ( !Success  )
        {
	    LBF_Led_OFF();
        }

        LBF_Delay_ms(300);
    }


}


/***** PRIVATE FUNCTIONS *****************************************************/

bool TestBLE(void)
{

GPIO_InitTypeDef GPIO_InitStruct;
uint8_t  	BLECodeBuffer[8] = {0, 1, 2, 3, 4, 5, 6, 7};	// 8 bytes dummy BLE code
const  uint32_t BLECodeSize = 8;
uint8_t		CodeCRC = 0x00;
uint32_t 	StartTime_ms;
bool		StatusOK ;
uint8_t		RecvdData;
uint32_t 	i;

  /* ---     Download dummy FW into BLE module  ---- */

   // Initialise UART3 dedicated to exchanges with BLE module,
   // first with baudrate used by BLE booting from UART
   // Baud Rate = 57600 bit/s as this is what PAN1740 uses when 
   //   attempting to boot from UART on its P0_4 and P0_5
   LBF_UART3_Init(57600);   



    //Compute CRC = XOR of all code bytes
    for (i=0; i<BLECodeSize; i++)
    {
	CodeCRC = CodeCRC ^ BLECodeBuffer[i] ;
    }

    // Initialize PC9 = BT_RST (active high)
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL; 
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;  
    GPIO_InitStruct.Pin = BT_RST_PIN;
    HAL_GPIO_Init(BT_RST_PORT, &GPIO_InitStruct);

    // Reset BTLE
    GPIO_HIGH(BT_RST_PORT, BT_RST_PIN); // assert BTLE reset
    LBF_Delay_ms(2); 
    GPIO_LOW(BT_RST_PORT, BT_RST_PIN);  // release BTLE reset


    // See D14580 Boot-from-serial AN: 
    //  try for up to 146ms (+margin here) for boot-from-serial protocol
    StartTime_ms = HAL_GetTick();
    while ( ((HAL_GetTick()- StartTime_ms) < 200) )
    {
        StatusOK = (LBF_UART_BLE_ReceiveByte()==0x02);
        if (StatusOK)
	   break;  // Got boot start byte - no need to wait further for it
    }

    if (StatusOK)  // got boot start byte
    {
	// Boot start byte well received, 
	// respond according to DA14580 "Boot from Serial i/f" spec 
	LBF_UART_BLE_SendByte(0x01);  // SOH
	LBF_UART_BLE_SendByte((uint8_t) (BLECodeSize &   0xFF) );       // LEN_LSB 
	LBF_UART_BLE_SendByte( (uint8_t)((BLECodeSize & 0xFF00)>>8)  );  // LEN_MSB

	// Get acknowledge from BTLE
	RecvdData = LBF_UART_BLE_ReceiveByte( );
	if ( RecvdData != 0x06)  // ACK=0x06,  NACK=0x15
	{
	    StatusOK = false; 
        }
	else // Tx data acknowledge, can continue
	{
	    //Send all bytes from file over UART 
	    for (i=0; i<BLECodeSize; i++)
	    {
	        LBF_UART_BLE_SendByte( BLECodeBuffer[i] );
	    }
    
	    // Get CRC = XOR over code bytes from DA14580
	    if (LBF_UART_BLE_ReceiveByte()!= CodeCRC ) 
	    {
	        StatusOK = false;
	    }
	    else
	    {
	        // Send ACK = 0x06 to DA14580
	        LBF_UART_BLE_SendByte( 0x06 );
	    }

	}   // end if(RecvdData==...)

    }  // end if(StatusOK)

    return StatusOK;

}




/***************************************************************END OF FILE****/
