/*******************************************************************************
 * DemoChangeRequest.c
 * 
  * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_Global.h"


bool DemoChangeRequest(void)
{
//int8_t  X_Accel_HighByte;
int8_t  Z_Accel_HighByte;
bool  ChangeRequested ;


    while ( (LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x1E) & 0x01) == 0x00);
            // Status Reg
            // Wait for XLDA bit to be set
 //   X_Accel_HighByte =  (int8_t) LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x29);   
    Z_Accel_HighByte =  (int8_t) LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2D);   

//    ChangeRequested = ( (X_Accel_HighByte < -64) || (X_Accel_HighByte > 64) ); //significant tilt on X
    ChangeRequested = ( Z_Accel_HighByte < 0 ); //or Z<0 (shake or upside down)
    if (ChangeRequested)
    {
        LBF_Led_ON();

/*
        // if previous change was requested less than 1s ago, ignore this one
        CurrentTime = HAL_GetTick();
        if ( (CurrentTime - PreviousTime) < 1000)
	    ChangeRequested = false;
        PreviousTime = CurrentTime;
*/
        LBF_Delay_ms(100);

        LBF_Led_OFF();
     }


     return ChangeRequested ;
}  




/***************************************************************END OF FILE****/// 
