/*******************************************************************************
 * Magneto-FFT-Demo.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_Global.h"

const q15_t Hamming[128];
	// Hamming-window optionally applied to captured sequence,
	// typically used in signal processing for better FFT results

void static Get_Magnetic_FieldXYZ( int16_t* pMField_X_Raw,  int16_t* pMField_Y_Raw, int16_t* pMField_Z_Raw );
void static Draw_Legend(void);

bool NextDemoRequest(void);


/* -------------------------------------------------------------------------- */


void Magneto_FFT_Demo(void)
{


/* ==   Declarations       =============================== */

#define  DIGITAL_GAIN 4
#define  BKGND_COLOR 0x102020  // dark grey
#define NUM_SAMPLES_TIME_DOMAIN  160*5/4

const uint32_t  OffsetX = (160-128)/2;  //horizontal offset (pixels) to center FFT on display 

uint8_t  ReadValue;
uint16_t i,j;
uint32_t StartTime;

int16_t	 MField_X_Raw, MField_Y_Raw, MField_Z_Raw;
int32_t  MField_X_Scaled, MField_Y_Scaled, MField_Z_Scaled ;
int32_t  MField_X_vertcoord, MField_Y_vertcoord , MField_Z_vertcoord ;
int32_t  MField_X_vertcoord_prev, MField_Y_vertcoord_prev, MField_Z_vertcoord_prev ;

int32_t  Ycoord;

int16_t  SampleZ[128];

q15_t    FFT_Z[256];
q15_t    FFT_Mag_Z[128];

arm_rfft_instance_q15  		RealFFT_Instance;




/* ==  Body     ======================================== */

    LBF_OLED_Switch_ON();

 
   /* ---     Configure Magnetometer     -------------------------- */
   /* ---     Sampling Rate is important for FFT - here 20Hz     -- */


    ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, LIS3MDL_WHOAMI);
    if (ReadValue != LIS3MDL_WHOAMI_CONTENTS)
    {
	LBF_OLED_PrintString("\n LIS3MDL Access Problem");
	LBF_Delay_ms(2000); 
    }

    // Define Full Scale: Reg. CTRL_REG2 @0x21
    // NB- earth magnetic field magnitude = 0.25 to 0.65 Gauss
    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_2_REG, 0x00);  
	// FS = 4 Gauss

    // Define XY Performance mode and ODR: Reg. CTRL_REG1 @0x20
    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_1_REG, 0x94);  // 0b10010100
	// Enable T° sensor
	// Low-power mode on X and Y
	// ODR = 20Hz - DO[2:0]=101  (was 10Hz - DO[2:0]=100)
    // Define Z Performance mode: Reg. CTRL_REG4 @0x23
    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_4_REG, 0x00);  // 0b00000000

   // Set CONTINUOUS conversion : CTRL_REG3 @0x22     
    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_3_REG, 0x00);  



    // -- Initializations --------------------------------


    //Init the FFT Structures
    arm_rfft_init_q15(&RealFFT_Instance,
                      128,
                      0,
                      1); //Bit reverse flag - 1 = normal output



   /* ---     Main Loop                     -------------------------- */

   while(1)
   {

     GUI_Clear();
     GUI_SetColor(0xFFFFFF);  // WHITE
     GUI_SetFont(&GUI_Font8_ASCII);
     GUI_DispStringAt("Magnetom'r X,Y,Z Vector (raw)", 0, 120);


     // Work by chunks of NUM_SAMPLES_TIME_DOMAIN  
     // (but will only keep 128 of them for FFT)
     for (i=0; i<NUM_SAMPLES_TIME_DOMAIN; i++)
     {

	do 
        {
	    ReadValue = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
		 LIS3MDL_STATUS_REGISTER_REG);  // Status Reg
        } while ( (ReadValue & 0x08) != 0x08);  // bit set when new XYZ data available

	// Read Results
        Get_Magnetic_FieldXYZ(  &MField_X_Raw, &MField_Y_Raw, &MField_Z_Raw );


	// Discard first 32 samples, then store 128 samples for FFT
	// + Apply Hamming Window 

	if ( (i>31) && ((i-32)<128) )
         SampleZ[i-32]  = (int16_t) (( Hamming[i-32] * (q31_t)MField_Z_Raw) >> 15);


     // ---------------------------------------------------------------------
     // First Part - Display Magnetometer samples (XYZ vector coordinates)
     // in time domain - and memorize samples to later compute FFT
     // ---------------------------------------------------------------------

	// Shift screen left
        LBF_OLED_WriteReg( 0x2E, i ); 
          // X that will correspond to first display memory address

        // --- Display Results :------------------------------------------------

         // Erase Pixels on this X coord before drawing new:
	 GUI_SetColor(0x000000);  // BLACK
	 GUI_DrawLine(i, 0, i, 119);
	    // not down to bottom to preserve scrolling text


	 GUI_SetColor(0xFF0000);  // MField_X - RED
	 MField_X_Scaled = (( (int32_t)MField_X_Raw * 128 * DIGITAL_GAIN) / 65536);
	 MField_X_vertcoord = 63 + MField_X_Scaled;

	 if (i>0)
	     GUI_DrawLine(i-1, MField_X_vertcoord_prev, i, MField_X_vertcoord);
	 else 
	     GUI_DrawPixel(0, MField_X_vertcoord);
	 MField_X_vertcoord_prev = MField_X_vertcoord;


	 GUI_SetColor(0x00FF00);  // MField_Y - GREEN
	 MField_Y_Scaled = (( (int32_t)MField_Y_Raw * 128 * DIGITAL_GAIN) / 65536);
	 MField_Y_vertcoord = 63 + MField_Y_Scaled;
	 if (i>0)
	     GUI_DrawLine(i-1, MField_Y_vertcoord_prev, i, MField_Y_vertcoord);
	 else 
	     GUI_DrawPixel(0, MField_Y_vertcoord);
	 MField_Y_vertcoord_prev = MField_Y_vertcoord;

	 GUI_SetColor(0x0000FF);  // MField_Z - BLUE
	 MField_Z_Scaled = (( (int32_t)MField_Z_Raw * 128 * DIGITAL_GAIN) / 65536);
	 MField_Z_vertcoord = 63 + MField_Z_Scaled;
	 if (i>0)
	     GUI_DrawLine(i-1, MField_Z_vertcoord_prev, i, MField_Z_vertcoord);
	 else 
	     GUI_DrawPixel(0, MField_Z_vertcoord);
	 MField_Z_vertcoord_prev = MField_Z_vertcoord;

	// Exit requested ?
        if  (NextDemoRequest())   // demo change requested
	{
	    // Stop Magnetometer: power-down
    	    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_CONTROL_REGISTER_3_REG, 0x03);  

	   // Restore normal position of 1st pixel of Display
           LBF_OLED_WriteReg( 0x2E, 0x00 ); 

	    return;
	}




     } // End For

     // Restore screen "normality": first address = first pixel
     LBF_OLED_Clear(); 
     LBF_OLED_WriteReg( 0x2E, 0 ); 


     // ---------------------------------------------------------------------
     // Second Part - Display FFT of Magnetometer Z-axis
     // ---------------------------------------------------------------------


     //Compute the FFT - 128 complex results
     arm_rfft_q15( &RealFFT_Instance, (q15_t *)SampleZ, (q15_t *)FFT_Z);

     //Scale the input before computing magnitude (input+imag parts)
     for(j=0; j<2*128; j++)
     {
          FFT_Z[j]<<=6;  
     } 

     // 128 samples from 0 to Fs = 20Hz
     // with 64 after Fs/2 = conjugates of first 64
     // Here will focus on 5Hz band = Fs/4 = first 32 samples

     //FFT function returns the real / imaginary values.   We need to compute the magnitude
     arm_cmplx_mag_q15((q15_t *)FFT_Z, (q15_t *)FFT_Mag_Z, 32);


     // Erase previous curve 
     // GUI_Clear();
     // Draw axis and legend  
     Draw_Legend();


     for (j=0; j<32; j++)  // skip sample 0 = DC-level 
     {
         // Draw new curve , 64 samples from 0 to Fs/2
	 Ycoord =  115 - (FFT_Mag_Z[j] >>6)  ;  // zero level= line 115

	 GUI_SetColor(0x0000FF); // BLUE
	 GUI_FillRect(4*j+OffsetX, Ycoord, 4*j+3+OffsetX, 115);
     }

     // Keep FFT visible for some time on screen before going back 
     // to sample capture and time-domain display
     // (monitor exit request, however)
     StartTime = HAL_GetTick();
     while( HAL_GetTick() - StartTime < 3000)
     {
	// Exit requested ?
        if  (NextDemoRequest())   // demo change requested
	{
	    // Stop Magnetometer: power-down
    	    LBF_I2CSensors_WriteSingleReg(LIS3MDL_CHIPID,
		 LIS3MDL_CONTROL_REGISTER_3_REG, 0x03);  

	   // Restore normal position of 1st pixel of Display
           LBF_OLED_WriteReg( 0x2E, 0x00 ); 

	    return;
	}
     }

   } // end while(1)
    

}



/************************************************************************/
// Private Functions
/************************************************************************/

/* --- XYZ: Read Magnetometer registers and compute magnetic field in mGauss --------- */

void static Get_Magnetic_FieldXYZ( int16_t* pMField_X_Raw,  int16_t* pMField_Y_Raw, int16_t* pMField_Z_Raw )
{
uint8_t		MField_X_LowByte, MField_X_HighByte;
uint8_t		MField_Y_LowByte, MField_Y_HighByte;
uint8_t		MField_Z_LowByte, MField_Z_HighByte;

	MField_X_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
		 LIS3MDL_MAGNETO_X_LOW_REG);
	MField_X_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID,
		 LIS3MDL_MAGNETO_X_HIGH_REG);

	MField_Y_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_MAGNETO_Y_LOW_REG);
	MField_Y_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_MAGNETO_Y_HIGH_REG);

	MField_Z_LowByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_MAGNETO_Z_LOW_REG);
	MField_Z_HighByte = LBF_I2CSensors_ReadSingleReg(LIS3MDL_CHIPID, 
		LIS3MDL_MAGNETO_Z_HIGH_REG);

        *pMField_X_Raw =  
         (int16_t)( (MField_X_HighByte <<8 ) | MField_X_LowByte ) ;
        *pMField_Y_Raw =  
         (int16_t)( (MField_Y_HighByte <<8 ) | MField_Y_LowByte ) ;
        *pMField_Z_Raw =  
         (int16_t)( (MField_Z_HighByte <<8 ) | MField_Z_LowByte ) ;

}

/************************************************************************/

void static Draw_Legend(void)
{

const uint32_t  OffsetX = (160-128)/2;  //horizontal offset (pixels) to center FFT on display 

	      GUI_SetColor(GUI_WHITE);
    	      GUI_SetFont(&GUI_Font13B_ASCII);
	      GUI_DispStringAt("FFT, Z-comp.", OffsetX+40, 10);

	      // Baseline
	      GUI_DrawLine(0+OffsetX,118,128+OffsetX,118);
	      // 1Hz-spaced graduations
	      GUI_DrawLine(0+OffsetX,115,0+OffsetX,120);
	      GUI_DrawLine(128/5+OffsetX,115,128/5+OffsetX,120);
	      GUI_DrawLine(2*128/5+OffsetX,115,2*128/5+OffsetX,120);
	      GUI_DrawLine(3*128/5+OffsetX,115,3*128/5+OffsetX,120);
	      GUI_DrawLine(4*128/5+OffsetX,115,4*128/5+OffsetX,120);
	      GUI_DrawLine(128+OffsetX,115,128+OffsetX,120);
	      // Unit
    	      GUI_SetFont(&GUI_Font8_ASCII);
	      GUI_DispStringAt("0Hz",0+OffsetX,120);
	      GUI_DispStringAt("5Hz",127+OffsetX,120);
}

/************************************************************************/
// Constant:  HAMMING WINDOW
/************************************************************************/

const q15_t Hamming[128] =
{
    0	,
    20	,
    80	,
    180	,
    320	,
    499	,
    717	,
    973	,
    1267	,
    1597	,
    1965	,
    2367	,
    2804	,
    3273	,
    3775	,
    4308	,
    4871	,
    5461	,
    6078	,
    6721	,
    7387	,
    8075	,
    8784	,
    9511	,
    10255	,
    11014	,
    11786	,
    12569	,
    13362	,
    14162	,
    14967	,
    15776	,
    16587	,
    17397	,
    18204	,
    19007	,
    19804	,
    20592	,
    21370	,
    22136	,
    22887	,
    23623	,
    24341	,
    25039	,
    25717	,
    26371	,
    27001	,
    27606	,
    28182	,
    28730	,
    29247	,
    29734	,
    30187	,
    30607	,
    30991	,
    31341	,
    31653	,
    31928	,
    32165	,
    32364	,
    32523	,
    32643	,
    32723	,
    32763	,
    32763	,
    32723	,
    32643	,
    32523	,
    32364	,
    32165	,
    31928	,
    31653	,
    31341	,
    30991	,
    30607	,
    30187	,
    29734	,
    29247	,
    28730	,
    28182	,
    27606	,
    27001	,
    26371	,
    25717	,
    25039	,
    24341	,
    23623	,
    22887	,
    22136	,
    21370	,
    20592	,
    19804	,
    19007	,
    18204	,
    17397	,
    16587	,
    15776	,
    14967	,
    14162	,
    13362	,
    12569	,
    11786	,
    11014	,
    10255	,
    9511	,
    8784	,
    8075	,
    7387	,
    6721	,
    6078	,
    5461	,
    4871	,
    4308	,
    3775	,
    3273	,
    2804	,
    2367	,
    1965	,
    1597	,
    1267	,
    973	,
    717	,
    499	,
    320	,
    180	,
    80	,
    20	,
    0
};



/***************************************************************END OF FILE****/
