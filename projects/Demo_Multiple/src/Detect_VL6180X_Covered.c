/*******************************************************************************
 * Detect_VL6180X_Covered.c
 * 
 * Author: La BlueFrog, 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 *************************************************************************/


#include "LBF_Global.h"



#define DETECT_MAX_DIST  50  // maximum 50mm distance for positive detection
#define DETECT_MIN_DIST  10  

bool Detect_VL6180X_Covered(void)
{

uint8_t    Distance_mm;
bool  Covered = false;
uint32_t   StartTime;


    // Set bits [2:0] of Reg.0x14 to 0b100: enable internal IT on sample ready
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0014, 0x4);
    //TODO! MOVE to main init (also for DistEval() )

    // Wait until device ready to start ranging
    while ( ( LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, 0x004D) & 0x01) != 0x01);

    // Start cont. range measurements: write 0x03 to 0x18
    LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0018, 0x3);
    StartTime = HAL_GetTick();
    
    while ( !Covered )
    {
        // Wait until bits [2:0] of Reg.0x4F are 0b100 (measurement complete)
        while( (LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, 0x004F) & 0x07) != 0x4 );

        // Read distance ("range value") in mm from Reg.0x0062  
        Distance_mm = LBF_I2CSensors_ReadSingleReg(VL6180X_CHIPID, 0x0062);

        // Set bits [2:0] of Reg.0x15 to 0b111  (clear all interrupts)
        LBF_I2CSensors_WriteSingleReg (VL6180X_CHIPID, 0x0015, 0x7);

        // So, is there something close-by ?
        Covered=  (Distance_mm < DETECT_MAX_DIST ) && (Distance_mm > DETECT_MIN_DIST );

        if ( (HAL_GetTick()-StartTime) > 50 )   // Time out
	{
             if ( LBF_State_Switch1_IsOn()  )
		 Covered = true;   // allow switch to replace gesture
             break; 
        }
     }

     // Stop Ranging
     LBF_I2CSensors_WriteSingleReg(VL6180X_CHIPID, 0x18, 0x01); 

     return Covered ;  
}  




/***************************************************************END OF FILE****/
