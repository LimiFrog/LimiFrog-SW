/*******************************************************************************
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
        // actions partly driven by User_Configuration.h


   LBF_Led_ON();

/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT AS NEEDED:
    // (refer to INFO.txt for details on actions performed)

    /* ... To use La BlueFrog as USB Mass Storage (Full Speed)      */
    //Delay_ms(1000);
    //Success &= LBF_LaunchUSB_MassStorage();  

    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    Success &= LBF_FatFS_Init();

    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    // Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */

// NOTE: Here, as Data Flash may not be formatted yet,
//  we don't use LBF_LaunchUSB_MassStorage in the initalization phase above


/* ==  User Declarations =============================== */

    FIL MyFile;    /* FatFS File object */
    UINT bw;       /* Number of bytes written in file */


/* ==  Body     ======================================== */

     LBF_Led_ON();
    // Launch reformat only when Push Button pressed
    while ( !LBF_State_Switch1_IsOn()  );

    LBF_Led_OFF();

    /* Create FAT volume with default cluster size */
    Success &= ( f_mkfs("", 0, 0) == FR_OK); 

    /* Create a file as new */
    Success &= ( f_open(&MyFile, "FS_Formt.log", FA_CREATE_NEW | FA_WRITE) == FR_OK);

    /* Write a message */
    Success &= ( f_write(&MyFile, "Formatted by FatFS\r\n", 20, &bw)  == FR_OK);

    /* Close the file */
    f_close(&MyFile);
 
    // Launch USB
    Success &= LBF_LaunchUSB_MassStorage();  

    /* Error handler */
    LBF_Led_StopNBlinkOnFalse (Success);


  // Done !
  LBF_Led_ON();
  while (1);

    
}


/***  END OF FILE ************************************************************/
