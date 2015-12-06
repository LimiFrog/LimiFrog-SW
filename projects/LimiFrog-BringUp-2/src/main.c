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
#include "User_Configuration.h"


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

   LBF_Board_Fixed_Inits();
   LBF_Board_Selective_Inits(); 
             // actions driven by User_Configuration.h

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


uint16_t color_table[8] = {BLACK, YELLOW, RED, WHITE, GREEN, BLUE, ORANGE, CYAN} ;
uint32_t counter = 0;



/* ==  Body     ======================================== */



    LBF_OLED_Switch_ON();
    // Provide power (13V) to OLED panel, enable display

    LBF_OLED_Fill(0, 0, 160, 128, BLUE);      

    while(1)
    {
          if ( LBF_State_Switch1_IsOn() )
          {  
             LBF_OLED_Fill(0, 0, 160, 128, CYAN);  
          }
          if ( LBF_State_Switch2_IsOn() )
          {  
             counter++;

             // Fill the 160x128 screens with 8 colors organized as 2 rows of 4 blocks
             // Arguments: Xstart, Ystart, Width, Height, Color in RGB565 format 
             LBF_OLED_Fill(0, 0, 40, 64, color_table[(0+counter)%8] );  
             LBF_OLED_Fill(40, 0,40, 64, color_table[(1+counter)%8]);
             LBF_OLED_Fill(80, 0, 40, 64, color_table[(2+counter)%8]);
             LBF_OLED_Fill(120, 0, 40, 64, color_table[(3+counter)%8]);
             LBF_OLED_Fill(0, 64, 40, 64, color_table[(4+counter)%8]);
             LBF_OLED_Fill(40, 64, 40, 64, color_table[(5+counter)%8]);
             LBF_OLED_Fill(80, 64, 40, 64, color_table[(6+counter)%8]);
             LBF_OLED_Fill(120, 64, 40, 64, color_table[(7+counter)%8]);
          }

     }



    return 0;
}
 

/***************************************************************END OF FILE****/
