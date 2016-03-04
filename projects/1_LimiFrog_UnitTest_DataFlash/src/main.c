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
      // includes actions driven by User_Configuration.h

   LBF_Led_ON();


/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    // LBF_Delay_ms(1000);
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

bool TestFlash (void);
bool Flash_Ok;


/* ==  Body     ======================================== */

    // Test reads and writes from/to Flash
    Flash_Ok = TestFlash();

    //Get LED to blink if success
    while(1)
    {
          if (Flash_Ok==TRUE)
          {
              LBF_Led_OFF();
          }
          LBF_Delay_ms(700);
          LBF_Led_ON();
          LBF_Delay_ms(300);        
    }

    
}



/*******************************************************************************
* Function Name  : TestFlash.

* Description    : Short test to write and read from data flash.
* Input          : None.
* Output         : None.
* Return         : TRUE if success, else FALSE.

*******************************************************************************/
bool TestFlash(void) 
{
// Size of Flash= LBF_FLASH_NUMBER_OF_PAGES * LBF_FLASH_PAGE_LENGTH

int rand();  //returns a value between 0 and RAND_MAX (defined by the compiler, often 32767)

uint8_t WriteDataBuff[4096]; 
uint8_t ReadDataBuff[4096];
uint8_t random[4096];
uint32_t i;
bool Success = true;



/* First, Check Manufacturer ID of ADESTO Flash*/

  if ( (LBF_FLASH_ReadID()>>16 & 0xFF) == 0x1F )  //check manufacturer ID
  {
         Success=TRUE;
  }
  else
  {
         Success=FALSE;
  }


/* Now, Check Read/Write Functionality */

    // Generate random numbers and write into Flash 
    for (i=0; i< 4095; i++)
    {
         random[i] = (i+rand())%256;
         WriteDataBuff[i] = random[i];
    }
    LBF_FLASH_WriteBuffer(WriteDataBuff, 0x00, 4095);


   // Read back  
    LBF_FLASH_ReadBuffer(ReadDataBuff, 0x00, 4095);


    // Write complement 
    for (i=0; i<4095; i++)
    {
         WriteDataBuff[i] = ((uint8_t)~ReadDataBuff[i]);
    }
    LBF_FLASH_WriteBuffer(WriteDataBuff, 0x00, 4095);


    // Read and check if success (results consistent with full sequence)
    LBF_FLASH_ReadBuffer(ReadDataBuff, 0x00, 4095);
    for (i=0; i<4095; i++)
    {
         if (ReadDataBuff[i] != ((uint8_t)~random[i]) )
         {
             Success=FALSE;
         }
    } 


    // Also check unaligned start address (0x01 used here) and smaller than 1 page (222 bytes here)
    for (i=0; i< 222; i++)
    {
         WriteDataBuff[i] = random[i];
    }
    LBF_FLASH_WriteBuffer(WriteDataBuff, 0x01, 222);

    LBF_FLASH_ReadBuffer(ReadDataBuff, 0x01, 222);
    for (i=0; i<222; i++)
    {
         if (ReadDataBuff[i] != random[i] )
         {
             Success=FALSE;
         }
    } 


  return  Success ;
}


