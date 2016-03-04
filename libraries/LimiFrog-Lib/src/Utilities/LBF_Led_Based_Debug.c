/*******************************************************************************
 * LBF_Led_Based_Debug.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"



/*************
* Function :	
	void LBF_Led_BlinkOnFalse_FixedOnTrue( bool Status )
* Description :	
	Enters infinite loop, with flashing LED is Status is false, or with fixed LED on if Status is true.  For debug an diagnosis.
* Parameters :  
	Status :  the boolean that will cause LED to flash if false and to stay fixed if true.
* Return Value:  -
**************/

void LBF_Led_BlinkOnFalse_FixedOnTrue( bool Status )
{
  while(1)
  {
    LBF_Led_ON();
    LBF_Delay_ms(100);
    if (Status != false)
    {
	LBF_Led_OFF();
    }
    LBF_Delay_ms(300);
  }
}


/***********
* Function :	
	void LBF_Led_StopNBlinkOnFalse( bool Status )
* Description :	
	Enters infinite loop with flashing LED is Status is false, else continue. Mostly for debug an diagnosis.
* Parameters :  Status -  the boolean that will (if false) make LED to flash and program to enter infinite loop or(if true) let it continue
* Return Value:  -
***********/

void LBF_Led_StopNBlinkOnFalse( bool Status )
{
  if (Status == false)
  {
    while(1)
    {
      LBF_Led_ON();
      LBF_Delay_ms(100);
      LBF_Led_OFF();
      LBF_Delay_ms(300);
    }
  }
}





/***************************************************************END OF FILE****/
