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

// ---  Global variables  ----------------------------------------

// Handles for HAL-controlled peripherals
ADC_HandleTypeDef    hAdc2;
TIM_HandleTypeDef    htim6;


#define NOISE_THRESHOLD_PCT  30    //Noise detection threshold in % of ADC saturation level



// ---  Private "helper" functions  ----------------------------------------

static void  Get_Pressure_Temp( int32_t* pPressure_mb, float* pTemp_celsius);
static void  SetUp_Mic_ADC2_TIM6(void);
static void  Draw_Background( uint8_t Back_Color_Sel );
static void Update_Pressure_Temp( int32_t Pressure_mbar, float Temp_celsius, int32_t* pPrev_Pressure_mbar, float* pPrev_Temp_celsius);



/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = TRUE;

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
    // Delay_ms(1000);
    Success &= LBF_LaunchUSB_MassStorage();
 
    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    // Success &= LBF_FatFS_Init();

    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();



/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

// Variables
uint8_t	 	ReadValue;
int32_t		Pressure_mbar, Prev_Pressure_mbar;
float		Temp_celsius, Prev_Temp_celsius;

uint8_t		Back_Color_Sel;



/* ==  Body     ====================================================== */


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

 /* ---     Prepare ADC Microphone    ------------------------ */

  SetUp_Mic_ADC2_TIM6();

  //Launch ADC conversion 
  if ( HAL_ADC_Start(&hAdc2) != HAL_OK)
  {
      /* Possible Error Handler here */
  }


 /* ---     Prepare Display of Results    ----------------------- */

   LBF_OLED_Switch_ON();
   // Provide power (13V) to OLED panel, enable display

   // Draw background: 
   //rounded rectangle filled with yellow to red vertical gradient 
   Back_Color_Sel = 0;
   Draw_Background( Back_Color_Sel);

   GUI_SetTextMode( GUI_TM_TRANS );  // overlay chars (transparent background)
   GUI_SetColor(GUI_BLACK);


  /* ---     Track  Pressure            ------------------------- */

  while(1)
  {

	// The Analog WDog sets an IT flag but NVIC is not programmed to take it into account
	// So IT does not actually fire	
	// Instead we poll the flag in this loop and act if it's set

	if ( __HAL_ADC_GET_FLAG( &hAdc2, ADC_FLAG_AWD1 ) )  // Flag AWD1 was set by Analog Watchdog 
	{
   	    // Toggle color of background 
   	    // (rounded rectangle filled with gradient)
	    Back_Color_Sel = (Back_Color_Sel+1)%2;
	    Draw_Background( Back_Color_Sel);
	    Update_Pressure_Temp( Pressure_mbar, Temp_celsius, &Prev_Pressure_mbar, &Prev_Temp_celsius);

	    // Clear AWD1 flag
	    __HAL_ADC_CLEAR_FLAG( &hAdc2, ADC_FLAG_AWD1 );
	}

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

static void  SetUp_Mic_ADC2_TIM6(void)
{

ADC_ChannelConfTypeDef   sConfigAdcChannel;
TIM_MasterConfigTypeDef  sMasterConfig;
ADC_AnalogWDGConfTypeDef AnalogWDGConfig;

    // ----------------------------------------------------------------
    // --- ADC Setup --------------------------------------------------

    // Configure ADC clocking
     __HAL_RCC_ADC_CLK_ENABLE();  // ADC clock enable
     __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);  // select clock source
  

    // === Init ADC  ================
    hAdc2.Instance = ADC2;

    hAdc2.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV64;  
	// from DIV1 to DIV256
    hAdc2.Init.Resolution            = ADC_RESOLUTION_12B;    
	// 6, 8, 10 or 12bits
    hAdc2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hAdc2.Init.ScanConvMode          = DISABLE;  
	//ADC conversion on only 1 channel (set on rank 1)
    hAdc2.Init.EOCSelection          = EOC_SEQ_CONV;   
	// alternative: EOC_SINGLE_CONV
        // !!! ATTENTION - with Wdog need to select SEQ_CONV ?
    hAdc2.Init.LowPowerAutoWait      = DISABLE;
    hAdc2.Init.ContinuousConvMode    = DISABLE; 
	// only 1 conversion at each conversion trigger
    hAdc2.Init.NbrOfConversion       = 1;                        
    hAdc2.Init.DiscontinuousConvMode = DISABLE;
    hAdc2.Init.NbrOfDiscConversion   = 1; 
	// don't care as discontinous mode off
    hAdc2.Init.ExternalTrigConv      = ADC_EXTERNALTRIG_T6_TRGO;  
	// !!!!!  TRIGGERED BY TIMER 6 ("Basic" Timer of STM32L4)
    hAdc2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;  
	// N/A with sw trigger
    hAdc2.Init.DMAContinuousRequests = DISABLE;  
	// don't care in single shot mode 
    hAdc2.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      
	// overwrite previous if overrun -- shouldn't happen with sw triggered start !*/
    hAdc2.Init.OversamplingMode      = DISABLE; 


    if (HAL_ADC_Init(&hAdc2) != HAL_OK)
    {
      /* ADC initialization error */
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }



    // === ADC Regular Channel Setup ====
    sConfigAdcChannel.Channel      = ADC_CHANNEL_15;  
	//MIC_ANA on PB0: ADC12_IN15
    sConfigAdcChannel.Rank         = ADC_REGULAR_RANK_1;  
	//This channel will be first (and only!) sampled in the sequence
    sConfigAdcChannel.SamplingTime = ADC_SAMPLETIME_6CYCLES_5;  
	//valid values: 2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5 and 640.5 ADC clock cycles
	//comes on top of ADC intrinsic processing time. Larger time= more averaged result
  
    // The following are probably default settings anyway
    sConfigAdcChannel.SingleDiff   = ADC_SINGLE_ENDED;            
	/* Single-ended input channel */
    sConfigAdcChannel.OffsetNumber = ADC_OFFSET_NONE;             
	/* No offset subtraction */ 
    sConfigAdcChannel.Offset = 0;                                 

    if (HAL_ADC_ConfigChannel(&hAdc2, &sConfigAdcChannel) != HAL_OK)
    {
      /* Channel Configuration Error */
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }


    // ===  (Optional) Calibrate ADC and start conversion process  ====
    if (HAL_ADCEx_Calibration_Start(&hAdc2, ADC_SINGLE_ENDED) !=  HAL_OK)
    {
       // ADC Calibration Error 
       LBF_Led_StopNBlinkOnFalse (FALSE);
     }

     // ===   Set analog watchdog  =====         
     // Mic output is DC-centered on VCC/2
     // Set High Threshold at 0.75xVCC and Low Threshold at 0.25xVCC     
 
     /* Analog watchdog configuration */
     AnalogWDGConfig.WatchdogNumber = ADC_ANALOGWATCHDOG_1;  // Use Watchdog 1
     AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_SINGLE_REG; //Analog watchdog applied to a regular group single channel
     AnalogWDGConfig.Channel = ADC_CHANNEL_15; 	// the channel associated to the microphone
     AnalogWDGConfig.ITMode = DISABLE;
     AnalogWDGConfig.HighThreshold = (4096/2 + NOISE_THRESHOLD_PCT *2048/100);
     AnalogWDGConfig.LowThreshold =  (4096/2 - NOISE_THRESHOLD_PCT*2048/100);
     HAL_ADC_AnalogWDGConfig(&hAdc2, &AnalogWDGConfig);

     // Enable IT on ADC Watchdog (thru AnalogWDGConfig.ITMode)
     //  at NVIC level 
     // To be serviced by ADC1_2_IRQHandler in e.g. stm32_it.c
/*
     HAL_NVIC_SetPriority(ADC1_2_IRQn, __ADC1_2_IRQn_PRIO , 0); 
	// priority defined in IT_Priorities_UserDefinable.h
     HAL_NVIC_EnableIRQ(ADC1_2_IRQn); 
*/


    // ----------------------------------------------------------------
    // --- Timer6 Setup ("Basic" Timer used as trigger for ADC @20KHz  


   //Timer6 Init 
    LBF_Timer_Setup( &htim6, TIMER6, TIMER_UNIT_US, 500 );  // Set Timer Period=50 us i.e. fqcy = 2KHz

    /* Timer TRGO selection */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
      /* Timer TRGO selection Error */
         // LBF_OLED_PrintString("\nMaster Config FAIL\n");
         LBF_Led_StopNBlinkOnFalse (FALSE);
    }

    if (HAL_TIM_Base_Start(&htim6) != HAL_OK)
    {
      /* Counter Enable Error */
        // LBF_OLED_PrintString("\nTime Base Start FAIL\n");
        LBF_Led_StopNBlinkOnFalse (FALSE);
    }

}

/* ===================================================================== */

static void 	Draw_Background( uint8_t Back_Color_Sel )
{

#define		GRAD_COLOR_START_1	0xFF0000
#define		GRAD_COLOR_STOP_1	0xFFFF00
#define		GRAD_COLOR_START_2	0x0000FF
#define		GRAD_COLOR_STOP_2	0x00FFFF

    if (Back_Color_Sel == 0 )
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

/***************************************************************END OF FILE****/
