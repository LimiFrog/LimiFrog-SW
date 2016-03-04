/*******************************************************************************
 * Pressure-Mic.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/


#include "LBF_Global.h"


// ADC_HandleTypeDef    hAdc3;


// Private functions
static void  Get_Pressure_Temp( int32_t* pPressure_mb, float* pTemp_celsius);
//static void  SetUp_Mic_ADC2_TIM6(void);
static void  Draw_Background( uint8_t Back_Color_Sel );
static void Update_Pressure_Temp( int32_t Pressure_mbar, float Temp_celsius, int32_t* pPrev_Pressure_mbar, float* pPrev_Temp_celsius);

//static void LBF_Battery_Setup_ADC3(void);
//static uint32_t LBF_Battery_GetVoltage_mV(void);

bool NextDemoRequest(void);


/* ----------------------------------------------------------- */

void Pressure_Voltage(void)
{

uint8_t	 	ReadValue;
int32_t		Pressure_mbar, Prev_Pressure_mbar;
float		Temp_celsius, Prev_Temp_celsius;

uint8_t		Back_Color_Sel;

//uint32_t  Voltage_mV;



 /* ---     Measure battery voltage    ----------------------- */
/*
    LBF_Battery_Setup_ADC3();
      // Initialize ADC3 Ch2 for subsequent use for battery monitoring

    Voltage_mV = LBF_Battery_GetVoltage_mV();
*/

 /* ---     Check I2C access to Pressure Sensor :  ST LPS25H  -------- */

    ReadValue = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_WHOAMI);
    LBF_Led_StopNBlinkOnFalse ( ReadValue == LPS25H_WHOAMI_CONTENTS ); 
		// to stop here and blink LED if failure
  
 
 /* ---     Prepare Pressure Sensor    ------------------------ */

  // Enable single shot mode with internal IT generated when data ready
  LBF_I2CSensors_WriteSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG1_ADDR, 0x84);

  Pressure_mbar = 0;
  Temp_celsius = 0;
  Prev_Pressure_mbar = 0;
  Prev_Temp_celsius = 0;


 /* ---     Prepare Display of Results    ----------------------- */

   LBF_OLED_Switch_ON();
   // Provide power (13V) to OLED panel, enable display

   // Draw background: 
   //rounded rectangle filled with yellow to red vertical gradient 
   Back_Color_Sel = 0;
   Draw_Background( Back_Color_Sel);

   GUI_SetTextMode( GUI_TM_TRANS );  // overlay chars (transparent background)
   GUI_SetColor(GUI_BLACK);
   GUI_Clear();


  /* ---     Track  Pressure            ------------------------- */

  while(1)
  {
        // --- Perform actual measurements  --------------------------------

	Get_Pressure_Temp( &Pressure_mbar, &Temp_celsius);
	// returns pressure in mbar 
	// and 10x temperature in Celsius (allows 1/10°C resolution on int.)


        // --- Display Result if new ---------------------------------------


	if ( (Pressure_mbar != Prev_Pressure_mbar) ||  
		((Temp_celsius - Prev_Temp_celsius) > 0.1 ) || ((Prev_Temp_celsius - Temp_celsius) > 0.1 ) )
	{

	// --- Erase screen and redraw background
	  Draw_Background( Back_Color_Sel);

	// --- Update data displayed
	  Update_Pressure_Temp( Pressure_mbar, Temp_celsius, &Prev_Pressure_mbar, &Prev_Temp_celsius);

	}

   
        LBF_Delay_ms(100);

       // --- Should we exit ?     --------------------------------------
       if  (NextDemoRequest() )   // demo change requested
       {
	 return;
       }


  }  //  end while(1)


}


/* ==  PRIVATE FUNCTIONS             ========================================= */


static void  Get_Pressure_Temp( int32_t* pPressure_mb, float* pTemp_celsius)
{

uint8_t		Pressure_Bytes[4]; 
int32_t		Pressure_Signed;

uint8_t		Temp_Bytes[2]; 
int16_t		Temp_Signed;


        // Launch Single Shot Measurement, bit will auto-cleared when data ready
         LBF_I2CSensors_WriteSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG2_ADDR, 0x01);  

	// Wait until data available from Sensor
        while ( LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_CTRL_REG2_ADDR) != 0x00);  


	// Read Pressure Results on 3 Bytes (24 bits)
        Pressure_Bytes[0] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_XL_ADDR);
        Pressure_Bytes[1] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_L_ADDR);
        Pressure_Bytes[2] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_PRESS_OUT_H_ADDR);
        // Expand to 4th MSByte according to sign of result on 24 bits
        ( (Pressure_Bytes[2]&0x80) == 0x80) ?  (Pressure_Bytes[3] = 0xFF) :  (Pressure_Bytes[3] = 0x00) ;

        Pressure_Signed = (int32_t)( (uint32_t)Pressure_Bytes[3]<<24
                                   | (uint32_t)Pressure_Bytes[2]<<16
                                   | (uint32_t)Pressure_Bytes[1]<<8
                                   | (uint32_t)Pressure_Bytes[0]      );

        *pPressure_mb = Pressure_Signed / 4096 ;  //in mbar, as per LPS25H datasheet


	// Read Temperature Results on 2 Bytes (16 bits)
        Temp_Bytes[0] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_TEMP_OUT_L_ADDR);
        Temp_Bytes[1] = LBF_I2CSensors_ReadSingleReg(LPS25H_CHIPID, LPS25H_TEMP_OUT_H_ADDR);

        Temp_Signed = (int16_t)(   Temp_Bytes[1]<<8
                                 | Temp_Bytes[0]   );  // result in 2's compl format


	// Temperature = 42.5°C + Value From Sensor / 480 , according to LPS25H datasheet
        *pTemp_celsius = 42.5 +  (float)Temp_Signed / 480 ;  

}


/* ===================================================================== */

static void 	Draw_Background( uint8_t Back_Color_Sel )
{

#define		GRAD_COLOR_START_1	0xFF0000
#define		GRAD_COLOR_STOP_1	0xFFFF00
#define		GRAD_COLOR_START_2	0x0000FF
#define		GRAD_COLOR_STOP_2	0x00FFFF

    if (Back_Color_Sel == 1 )
    {
	GUI_DrawGradientRoundedV(10, 10, X_FULL_SCREEN-10, Y_FULL_SCREEN-10, 10,
				GRAD_COLOR_START_1, GRAD_COLOR_STOP_1);
    }
    else
    {
	GUI_DrawGradientRoundedV(10, 10, X_FULL_SCREEN-10, Y_FULL_SCREEN-10, 10,
				GRAD_COLOR_START_2, GRAD_COLOR_STOP_2);
    }

}

/* ===================================================================== */

static void Update_Pressure_Temp( int32_t Pressure_mbar, float Temp_celsius, int32_t* pPrev_Pressure_mbar, float* pPrev_Temp_celsius)
{
	// --- Pressure
          GUI_SetFont(&GUI_Font24B_ASCII);
          GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
          GUI_DispDecAt( Pressure_mbar,  X_FULL_SCREEN/2, Y_FULL_SCREEN/4, 4);  
          // Display pressure with 4 digits, centered on specified position

          GUI_SetFont(&GUI_Font16B_ASCII);
          GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
          GUI_DispStringAt( "mbar\n", X_FULL_SCREEN/2, Y_FULL_SCREEN/2 );
          // Display units, centered on specified position


	// --- Temperature
          GUI_DispStringAt("", X_FULL_SCREEN*1/4, Y_FULL_SCREEN*3/4 ); // Set new position
          GUI_DispFloatMin( Temp_celsius, 1);  // 1 digit after decimal point  
          GUI_DispString("  deg. C\n");

	  *pPrev_Pressure_mbar = Pressure_mbar;
	  *pPrev_Temp_celsius = Temp_celsius;
}

/* ===================================================================== */

/*
static uint32_t LBF_Battery_GetVoltage_mV(void)
{

__IO uint32_t  ADC_ConvertedValue;
uint32_t Vbat_mV;


    // Enable Battery measurement (active low)
    GPIO_LOW(BATT_PORT, BATT_MEAS_ENB_PIN);


    // ===  Perform Measurement   ===========

    //Launch ADC conversion (sw triggered mode)
    if ( HAL_ADC_Start(&hAdc3) != HAL_OK)
    {
      // Possible Error Handler here 
    }
  
    // Wait for the ADC conversion to be completed (timeout unit: ms) 
    if ( HAL_ADC_PollForConversion(&hAdc3, 10) != HAL_OK)
    {
      // Possible Error Handler here 
    }

    // ST's examples also check here that continous conversion of 
    // regular channel is finished (checking HAL_ADC_STATE_REG_EOC
    // with HAL_ADC_GetState() ) -- but that looks redundant !
    // while ((HAL_ADC_GetState(&hAdc3) & HAL_ADC_STATE_REG_EOC) != HAL_ADC_STATE_REG_EOC);
 

    // Read ADC Conversion result
    ADC_ConvertedValue = HAL_ADC_GetValue(&hAdc3);
  


    // --- Return Result  ---------------------------------------------
    
    Vbat_mV = (ADC_ConvertedValue * 293 * 14) / 1024;
    // as Vbat goes to ADC through 10K/(4+10K) divider with 2.93V nominal reference voltage
    // assuming ADC set for 10-bit resolution (1024 = 2**10)


    // Disable Battery measurement (save power)
    GPIO_HIGH(BATT_PORT, BATT_MEAS_ENB_PIN);

    return( Vbat_mV );

}

*/

/* ===================================================================== */

/*

static void LBF_Battery_Setup_ADC3(void)
{

ADC_ChannelConfTypeDef   sConfigAdcChannel;

    // Configure ADC clocking
     __HAL_RCC_ADC_CLK_ENABLE();  // ADC clock enable
     __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);  // select clock source
  

    // === Init ADC  ================
    hAdc3.Instance = ADC3;

    hAdc3.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV64;  
	// from DIV1 to DIV256
    hAdc3.Init.Resolution            = ADC_RESOLUTION_10B;    
	// 6, 8, 10 or 12bits
    hAdc3.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hAdc3.Init.ScanConvMode          = DISABLE;  
	//ADC conversion on only 1 channel (set on rank 1)
    hAdc3.Init.EOCSelection          = EOC_SINGLE_CONV;   
	// alternative: EOC_SEQ_CONV
    hAdc3.Init.LowPowerAutoWait 	    = DISABLE;
    hAdc3.Init.ContinuousConvMode    = DISABLE;  
	// only 1 conversion at each conversion trigger
    hAdc3.Init.NbrOfConversion       = 1;                        
    hAdc3.Init.DiscontinuousConvMode = DISABLE;
    hAdc3.Init.NbrOfDiscConversion   = 1; 
	// don't care as discontinous mode off
    hAdc3.Init.ExternalTrigConv      = ADC_SOFTWARE_START;  
	// soft triggering of conversion 
    hAdc3.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;  
	// N/A with sw trigger
    hAdc3.Init.DMAContinuousRequests = DISABLE;  
	// don't care in single shot mode 
    hAdc3.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      
	// overwrite previous if overrun -- shouldn't happen with sw triggered start !
    hAdc3.Init.OversamplingMode      = DISABLE; 


    if (HAL_ADC_Init(&hAdc3) != HAL_OK)
    {
      // ADC initialization error 
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }



    // === ADC Regular Channel Setup ====
    sConfigAdcChannel.Channel      = ADC_CHANNEL_2;  
	//BAT_ADC_MEAS on PC1: ADC123_IN2
    sConfigAdcChannel.Rank         = ADC_REGULAR_RANK_1;  
	//This channel will be first (and only!) sampled in the sequence
    sConfigAdcChannel.SamplingTime = ADC_SAMPLETIME_6CYCLES_5;  
	//valid values: 2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5 and 640.5 ADC clock cycles
	//comes on top of ADC intrinsic processing time. Larger time= more averaged result
  
    // The following are probably default settings anyway
    sConfigAdcChannel.SingleDiff   = ADC_SINGLE_ENDED;            

	// Single-ended input channel 
    sConfigAdcChannel.OffsetNumber = ADC_OFFSET_NONE;             
	// No offset subtraction  
    sConfigAdcChannel.Offset = 0;                                 

    if (HAL_ADC_ConfigChannel(&hAdc3, &sConfigAdcChannel) != HAL_OK)
    {
      // Channel Configuration Error 
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }


    // ===  (Optional) Calibrate ADC and start conversion process  ====
    if (HAL_ADCEx_Calibration_Start(&hAdc3, ADC_SINGLE_ENDED) !=  HAL_OK)
    {
       // ADC Calibration Error 
       LBF_Led_StopNBlinkOnFalse (FALSE);
     }


    // --- End of ADC Setup ---------------------------------------------


}

*/

/***************************************************************END OF FILE****/
