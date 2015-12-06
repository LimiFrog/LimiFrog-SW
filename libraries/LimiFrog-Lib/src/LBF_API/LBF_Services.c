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


/****************
 * @brief  : idle loop for a delay expressed in ms.
 * @param  : nTime - required delay in ms.
 * @return : none.
 ****************/


void LBF_Delay_ms (uint16_t nTime)  // maximum nTime supported = 60000ms / 1mn


/**************************************************************
  Timer-based implementation WITHOUT interrupt 
  to be usable with no issue in ISR

  Based on TIMER3: a 16-bit timer, not usable on external pin.
  Used with 1ms resolution

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!  ==> This means it is safer to leave Timer3 for exclusive   !!!!
  !!!!  usage bu this function and avoid using it in the           !!!!
  !!!!  application                                                !!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


 **************************************************************/
{

    if (nTime > 60000)  // enforce 60s/1mn limit on required delay
    {
	nTime = 60000;
    }


    // Use Timer3 ( 
    LBF_Timer_Setup( TIMER3, TIMER_UNIT_MS, 0xFFFF);  
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
