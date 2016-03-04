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
    // Success &= LBF_emWin_Init();


    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */



/* ==  Body     ======================================== */



    while (1)
    {

    //  Led ON if D+ pulled to Logic1 (USB device signalling FS)

	if ( IS_GPIO_SET( USB_PORT, USB_DP_PIN) )
	{
	    LBF_Led_ON();
	}
	else 
	{
	    LBF_Led_OFF();
        }	


    //  Whatever the result, toggle while push-button switch #1 is pressed

	if ( LBF_State_Switch1_IsOn() )
	{

		LBF_Led_TOGGLE();

		while ( LBF_State_Switch1_IsOn() ) ; 
		    // wait until button released to continue

		LBF_Led_TOGGLE();
		   // back to initial value
	}

    }
    

}

/***  END OF FILE ************************************************************/
