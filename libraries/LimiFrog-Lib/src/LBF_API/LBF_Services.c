/*******************************************************************************
 * Services.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

#include "LBF_lowlev_API.h"




/******************
* Function :	
	void LBF_Delay_ms (uint16_t nTime) void LBF_Delay_ms (uint16_t nTime) 
* Description :	
	Loops until the delay specified in milliseconds by nTime is elapsed. LBF_Delay_ms is based on Timer3 rather than SysTick. This allows to use LBF_Delay_ms() in an interrupt service routine if wished (even though that's probably not good practice). But this also means it is safer to avoid using Timer3 for other purposes in the application (even though, technically, it is sufficient to make sure LBF_Delay_ms() is never invoked while Timer3 is running for some other purpose).
* Parameters :  
	nTime : the number of millisecond to wait – Maximum 60000ms = 1mn (greater values will be clipped)
* Return Value:  -
*******************/

void LBF_Delay_ms (uint16_t nTime)  // maximum nTime supported = 60000ms / 1mn
{

TIM_HandleTypeDef htim3; 


/**************************************************************
  Timer-based implementation WITHOUT interrupt 
  to be usable with no issue in ISR

  Based on TIMER3: a 16-bit timer, not usable on external pin.
  Used with 1ms resolution

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!  ==> This means it is safer to leave Timer3 for exclusive   !!!!
  !!!!  usage by this function and avoid using it in the           !!!!
  !!!!  application                                                !!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 **************************************************************/


    if (nTime > 60000)  // enforce 60s/1mn limit on required delay
    {
	nTime = 60000;
    }

    // Use Timer3 ( 
    LBF_Timer_Setup( &htim3, TIMER3, TIMER_UNIT_MS, 0xFFFF);  
	//so counter will not wrap around before 65.536 seconds
//    LBF_Timer_Setup( TIMER5, TIMER_UNIT_MS, 0x7FFF);  

    // Start timer3 (no IT)
    HAL_TIM_Base_Start(&htim3);

    // Keep looping while specified duration not reached
    while( __HAL_TIM_GetCounter(&htim3) < nTime);

    // because there is ample margin (over 5s) between 
    // maximum nTime (60000ms) and Timer Period (65536ms)
    // an interrupt firing during the loop will not cause
    // a risk to miss exit condition (unless ISR is more thn 5s!)
	

}



/***************************************************************END OF FILE****/
