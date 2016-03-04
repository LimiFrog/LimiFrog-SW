/*******************************************************************************
 * SplashScreen.c
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
#include "string.h"

void ApplyTilt_XY ( int8_t *pPosX, int8_t *pPosY );
bool 	Detect_VL6180X_Covered(void);
bool 	Detect_NegZ_Accel(void);
bool  	DecodeBMPFile(char* FileName);
bool 	DemoChangeRequest(void);

bool NextDemoRequest(void);


/* ----------------------------------------------------- */

void 	SplashScreen(void)
{

int16_t		OriginPoint_X = 0, OriginPoint_Y = 0;
int8_t		Delta_X = 0, Delta_Y = 0;


    // Start-up accelerometer
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x18, 0x38);  // Reg. CTRL9_XL: enable XYZ axes
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x10, 0x60);  // Reg. CTRL1_XL: 416Hz (high-perf)
    LBF_I2CSensors_WriteSingleReg(LSM6DS3_CHIPID, 0x0D, 0x01);  // Reg. INT1_CTRL: data ready on INT1


   // -----   First, display Frog + Text + Temp  ---------------

    DecodeBMPFile("SPLASH.SPE"); 
   // Decode file if present else blue screen

   // -----   Wait for user gesture before allowing to move Frog
    while ( !Detect_VL6180X_Covered() );  


    while(1) 
    {
     
    // -----   Move Frog ---------------

        ApplyTilt_XY ( &Delta_X, &Delta_Y );

        if ( Delta_X > 0 )
	{
	   if (OriginPoint_X == 159)
		OriginPoint_X = 0;
	   else if ( (OriginPoint_X < 24) || (OriginPoint_X > 139) ) 
		OriginPoint_X++;
        }

        if ( Delta_X < 0 )
	{
	   if (OriginPoint_X == 0)
		OriginPoint_X = 159;
	   else if ( (OriginPoint_X < 25) || (OriginPoint_X > 140) )  
		OriginPoint_X--;
        }

        if ( Delta_Y > 0 )
	{
	   if (OriginPoint_Y == 127)
		OriginPoint_Y = 0;
	   else if ( (OriginPoint_Y < 25) || (OriginPoint_Y > 75) )  
		OriginPoint_Y++;
        }

        if ( Delta_Y < 0 )
	{
	   if (OriginPoint_Y == 0)
		OriginPoint_Y = 127;
	   else if ( (OriginPoint_Y < 26) || (OriginPoint_Y > 76) )  
		OriginPoint_Y--;
        }


        LBF_OLED_WriteReg( 0x2E, OriginPoint_X ); 
          // X that will correspond to first display memory address
        LBF_OLED_WriteReg( 0x2F, OriginPoint_Y ); 
          // Y that will correspond to first display memory address


    // -----  Do we need to exit ?  ---------------

        if (NextDemoRequest() )
        {
           LBF_OLED_WriteReg( 0x2E, 0x00 );   // restore initial values
           LBF_OLED_WriteReg( 0x2F, 0x00 );   
	   return;
        }

    }
}






/*===============  END OF FILE ===========================================*/


