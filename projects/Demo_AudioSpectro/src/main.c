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

/* *****************************************
 * Largely inspired by the 
 * "MonkeyListen" project by Eli Hughes
 * https://github.com/ehughes/MonkeyListen 
* *****************************************/


// =================================================================
// IMPORTANT NOTES:
//
// 1) In this demo,the user is expected to provide an EXTERNAL 
// CONNECTION between the microphone output on Extension Port
// Position 1 and the PGA (Programmable Gain Amplifier) input
// on Extension Port Position 8
//
// 2) This demo amplifies the microphone output with PGA, as the 
// microphone signal is weak.
// Microphone output is biased at VCC/2 ~ 1.5V, keeping it at that
// level leads to ADC saturation (ADC range = 0-3V)
// Therefore it is required to lower the mic output DC biasing,
// which can be done by CONNECTING AN EXTERNAL RESISTOR between
// mic output on Extension Port Position 1 and GND (e.g. on
// Extension Port Position 9).
// As the biasing is done on the board by a 47K+47K resistor bridge,
// connecting e.g. an external 1K resistor brings the biasing voltage
// down to ~ 60mV. With the audio signal less than 120mV peak-to-peak 
// in most situations this is OK. Pick a larger resistor for higher
// DC bias
//
// =================================================================




#include "LBF_Global.h"

#include "IT_Priorities_UserDefinable.h"


// ---  Global variables  ----------------------------------------

// Handles for HAL-controlled peripherals
ADC_HandleTypeDef    hAdc2;
DMA_HandleTypeDef    hDma1;
OPAMP_HandleTypeDef  hOpamp1;
TIM_HandleTypeDef    htim6;

#define  USE_HAMMING_WINDOW
const q15_t Hamming[128];   
	// Hamming-window optionally applied to captured sequence,
	// typically used in signal processing for better FFT results

#define  MIC_DIG_SCALE_FACTOR 1


// Flags from Interrupt Service Routines (ISR)
volatile bool ConversionComplete;  // set by ADC IRQ handler


// ---  Helper functions  ----------------------------------------

static void LBF_Setup_ADC2Ch8_TIM6_DMA(void);



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
    // Success &= LBF_LaunchUSB_MassStorage();
 
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


uint32_t  Mic_128Samples_Ping[128], Mic_128Samples_Pong[128];
uint32_t  *pMic_128Samples_CaptureBuffer, *pMic_128Samples_DisplayBuffer;
int16_t   Sample[128];
uint32_t  DC_level;

uint8_t	  IterationParity = 0;
int32_t  Ycoord;
int32_t  Previous_Ycoord[128];

q15_t MicFFT[256];
q15_t MicFFT_Mag[128];

arm_rfft_instance_q15  		RealFFT_Instance;
    
bool Mode_FFT = false;	// use FFT mode if true, else use time-domain mode

const uint32_t  OffsetX = (160-128)/2;  //horizontal offset (pixels) to center FFT on display 

uint32_t  Start;
GPIO_InitTypeDef GPIO_InitStruct;
uint32_t  i;


/* ==  Body     ======================================== */


    LBF_OLED_Switch_ON();
      // Provide power (13V) to OLED panel, enable display

    // Enable VCC_LDO (to make divider for audio DC bias)
    // LBF_Enable_LDO();

    // Set-up OPAMP1 in PGA mode, VIN- not connected, gain=2

    __HAL_RCC_OPAMP_CLK_ENABLE();


    // --------------------------------------------------------------
    //  -- The following is an alternative to having the IO for
    //  -- for PGA and ADC automatically configured at init
    //  -- based on user file User_Configuration.h 

/*
    // Using OPAMP in single-ended input PGA mode :
    // PA0 --> OPAMP1_VINP;  PA3 --> OPAMP1_VOUT     
    // (PA1 --> OPAMP1_VINM not used)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    // PA3 = OPAMP output is also a possible ADC input
    // provided PA3 is configured as such, which is done
    // as follows with HAL 
    // * notice the Mode is not just "GPIO_MODE_ANALOG" *
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL; 
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
*/
    // --------------------------------------------------------------



    // Configure OPAMP Peripheral as PGA, single-ended input
    hOpamp1.Instance = OPAMP1;
    hOpamp1.Init.PowerSupplyRange = OPAMP_POWERSUPPLY_HIGH;
    hOpamp1.Init.Mode = OPAMP_PGA_MODE;
    hOpamp1.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO0;
    hOpamp1.Init.InvertingInput = OPAMP_INVERTINGINPUT_CONNECT_NO;
    hOpamp1.Init.PgaGain = OPAMP_PGA_GAIN_16;   

    hOpamp1.Init.PowerMode = OPAMP_POWERMODE_NORMAL;
    hOpamp1.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
    LBF_Led_StopNBlinkOnFalse ( HAL_OPAMP_Init(&hOpamp1) == HAL_OK );

    // Now actually start OPAMP1 
    LBF_Led_StopNBlinkOnFalse ( HAL_OPAMP_Start(&hOpamp1) == HAL_OK );


    // To capture PGA output,
    // Configure ADC2 Ch.8 triggered by TIM6  
    // with DMA storage
    LBF_Setup_ADC2Ch8_TIM6_DMA();

  

    // -- DC level estimation ----------------------------

    // temporarily set ADC to oversampling mode
    hAdc2.Init.ExternalTrigConv   = ADC_SOFTWARE_START;  
    hAdc2.Init.OversamplingMode  = ENABLE;  
    hAdc2.Init.Oversampling.Ratio  = ADC_OVERSAMPLING_RATIO_256;  
    hAdc2.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_8; 
    hAdc2.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;  
	// A single trigger for all channel oversampled conversions 
    hAdc2.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE; 
	// Oversampling buffer maintained during injection sequence 
    LBF_Led_StopNBlinkOnFalse ( HAL_ADC_Init(&hAdc2) == HAL_OK) ;


   // Launch the ADC for single shot (so N sub-samples)
    LBF_Led_StopNBlinkOnFalse ( HAL_ADC_Start(&hAdc2) == HAL_OK) ;
    LBF_Led_StopNBlinkOnFalse ( HAL_ADC_PollForConversion(&hAdc2, 10) == HAL_OK);
	  // 10ms time-out
 
    /* Read the converted value  */
    DC_level = HAL_ADC_GetValue(&hAdc2);



LBF_OLED_PrintString("\nDC level at ADC (0-4095) = ");
LBF_OLED_PrintDec((int32_t)DC_level);
LBF_OLED_PrintString("\n");

    // Stop ADC and set back to non-oversampling mode, timer-triggered
    LBF_Led_StopNBlinkOnFalse ( HAL_ADC_Stop(&hAdc2) == HAL_OK) ;
    hAdc2.Init.OversamplingMode  = DISABLE;  
    hAdc2.Init.ExternalTrigConv   = ADC_EXTERNALTRIG_T6_TRGO;  
    LBF_Led_StopNBlinkOnFalse( HAL_ADC_Init(&hAdc2) == HAL_OK) ;


    // -- Initializations --------------------------------
    ConversionComplete = false;

    pMic_128Samples_CaptureBuffer = Mic_128Samples_Ping;
    pMic_128Samples_DisplayBuffer = Mic_128Samples_Pong;
    for (i=0; i<128; i++)
    {
	*(pMic_128Samples_DisplayBuffer + i) = DC_level;
	Previous_Ycoord[i] = 0;
    }

    //Init the FFT Structures
    arm_rfft_init_q15(&RealFFT_Instance,
                      //&MyComplexFFT_Instance,
                      128,
                      0,
                      1); //Bit reverse flag - 1 = normal output


    // ---------------------------------------------------


    if (Mode_FFT)
    {
        LBF_OLED_PrintString("\n\n FFT Mode");
    }
    else
    {
        LBF_OLED_PrintString("\n\n Time Domain Mode");
    }
    LBF_OLED_PrintString("\n\n Press button now to toggle\n FFT/Time Domain");
    Start = HAL_GetTick();
    while ( (HAL_GetTick() - Start) < 2500)
    {
    if (LBF_State_Switch1_IsOn())
	{
	    Mode_FFT = !Mode_FFT;
	    while(LBF_State_Switch1_IsOn() ); // wait until release
	    LBF_Delay_ms(10);  // to skip any bounce
	}
    }

    GUI_Clear();
 
    LBF_Led_ON();


    while(1)
    {

        // ===   Start conversion of 128 samples in DMA mode.      === 
        // ===   DMA triggers IT, corresponding handler must be    ===
        // ===   dealt with in stm32_it.c                          ===       
	Success = 
	   (HAL_ADC_Start_DMA(&hAdc2, pMic_128Samples_CaptureBuffer, 128) == HAL_OK);

	LBF_Led_StopNBlinkOnFalse (Success);  // stop here in case of error
	

        // ===   While conversion is ongoing                       === 
	// ===   display samples from previous conversion          === 


	// Condition converted signal: center on 0 + hamming window if enabled
	for (i=0; i<128; i++)
	{
	    Sample[i]  =  (int16_t) (*(pMic_128Samples_DisplayBuffer + i) - DC_level)
					* MIC_DIG_SCALE_FACTOR;
#ifdef USE_HAMMING_WINDOW
	    Sample[i]  = (int16_t) (( Hamming[i] * (q31_t)Sample[i]) >> 15);
#endif
	}



	if ( ! Mode_FFT) // use TIME-DOMAIN mode
	{


	  for (i=0; i<128; i++)
	  {
	      // Erase previous points
	      GUI_SetColor(GUI_BLACK);
	      GUI_DrawPoint(i+OffsetX, Previous_Ycoord[i]);

	      // Draw new points:

	      Ycoord = 			// bring this outside display loop ?
  		  Sample[i] // 0-centered  
	      	* 127 / 4096    // scale
	        +  63 ;  //center vertically on middle of screen
  
	      GUI_SetColor(0xFF0000); //RED
	      GUI_DrawPoint(i+OffsetX, Ycoord);

	      Previous_Ycoord[i] = Ycoord;
	  }

	}
	else
	{

  	  //Compute the FFT
	  arm_rfft_q15( &RealFFT_Instance, (q15_t *)Sample, (q15_t *)MicFFT);

	  //Scale the input before computing magnitude
	  for(i=0; i<256; i++)
	  {
	      MicFFT[i]<<=6;  
	  } 

	  //FFT function returns the real / imaginary values.   We need to compute the magnitude
          arm_cmplx_mag_q15((q15_t *)MicFFT, (q15_t *)MicFFT_Mag, 128);



	  for (i=0; i<64; i++)
	  {
	      // Erase previous points
	      GUI_SetColor(GUI_BLACK);
	      GUI_FillRect(2*i+OffsetX, 0, 2*i+1+OffsetX, 127);

	      // Draw new points (1st 64 magnitude values as last 64 are just conjugates)

	      Ycoord =  127 - (MicFFT_Mag[i] >>6)  ;  // zero level= bottom of screen

	      GUI_SetColor(0x0000FF); // BLUE
	      GUI_FillRect(2*i+OffsetX, Ycoord, 2*i+1+OffsetX, 127);

	      Previous_Ycoord[i] = Ycoord;
	  }


	}  // end if(!Mode_FFT)



	// Allow freezing picture by pushing user button
	 while ( LBF_State_Switch1_IsOn() ) 
	 {
	    LBF_Led_OFF();  //loop until PB released
	 }
	 LBF_Led_ON();



        // ===   Normally conversion has finished quicker than time
        // ===   needed to display (ConverSionComplete is set)
        // ===   If not then wait till all samples are acquired.      
	while (!ConversionComplete)
	{
	    LBF_Led_OFF(); // DEBUG
	}
	LBF_Led_ON();


	// Swap Capture Buffer and Display Buffer at each iteration
	if (IterationParity == 0)	
	{
	    pMic_128Samples_CaptureBuffer = Mic_128Samples_Ping;
	    pMic_128Samples_DisplayBuffer = Mic_128Samples_Pong;
	}
	else
	{
	    pMic_128Samples_CaptureBuffer = Mic_128Samples_Pong;
	    pMic_128Samples_DisplayBuffer = Mic_128Samples_Ping;
	}
	IterationParity = (IterationParity+1) %2;     

        ConversionComplete = false;


    } // end while(1)


}




/************************************************************************/
// PRIVATE FUNCTIONS
/************************************************************************/



/*******************************************************************************
 * @brief  : Sets up ADC2 for subsequent mic output voltage measurement: 
 *           Timer Triggered @20KHz, 12bit res
 * @param  : None.
 * @return : None
 ******************************************************************************/

static void LBF_Setup_ADC2Ch8_TIM6_DMA(void)
{

ADC_ChannelConfTypeDef   sConfigAdcChannel;
TIM_MasterConfigTypeDef  sMasterConfig;



    // ----------------------------------------------------------------
    // --- DMA1 Setup for use by ADC2

    // === Setup DMA channel assigned to ADC2 ====
    // === (which is DMA1 Channel2, see Ref Man. 


    __HAL_RCC_DMA1_CLK_ENABLE();

    hDma1.Instance = DMA1_Channel2;	
	// Ch.2 of DMA1 is the channel assigned to ADC2 (and other periphs)	
    hDma1.Init.Request = DMA_REQUEST_0;	
	// Select ADC2 amongst all potential sources on DMA1 Channel 2 
        // See Table 39 of User Man (ADC2 drives req.0 of its assigned channel)
	// or desc of Reg.DMA1_CSELR
    hDma1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hDma1.Init.PeriphInc = DMA_PINC_DISABLE;  // no automatic address increment on Periph (ADC2)
    hDma1.Init.MemInc = DMA_MINC_ENABLE;  // automatic addess increment on Memory
    hDma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;  // read 32-bit data from Periph
    hDma1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;  // write 32-bit data to Memory
    hDma1.Init.Mode = DMA_NORMAL;  // Normal of Circular
    hDma1.Init.Priority = DMA_PRIORITY_LOW;
    //HAL_DMA_Init(&hDma1);
    if (HAL_DMA_Init(&hDma1) != HAL_OK)
    {
      /* ADC initialization error */
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }

    __HAL_LINKDMA( &hAdc2, DMA_Handle, hDma1);



    // ----------------------------------------------------------------
    // --- ADC2 Setup --------------------------------------------------

    // Configure ADC clocking
     __HAL_RCC_ADC_CLK_ENABLE();  // ADC clock enable
     __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);  // select clock source
  

    // === Init ADC  ================
    hAdc2.Instance = ADC2;

    hAdc2.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV32;  //so 2+MHz
	// from DIV1 to DIV256
    hAdc2.Init.Resolution            = ADC_RESOLUTION_12B;    
	// 6, 8, 10 or 12bits
    hAdc2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hAdc2.Init.ScanConvMode          = DISABLE;  // ADC_SCAN_DISABLE;  
	//ADC conversion on only 1 channel (set on rank 1)
    hAdc2.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;   // *
	// alternative: EOC_SEQ_CONV
    hAdc2.Init.LowPowerAutoWait      = DISABLE;
    hAdc2.Init.ContinuousConvMode    = DISABLE; //ENABLE; // *
	// automatic conversion restart after each single conversion
    hAdc2.Init.NbrOfConversion       = 1; 
	// don't care as sequencer is off(not scanning multiple channels)                       
    hAdc2.Init.DiscontinuousConvMode = DISABLE;
	// don't care as sequencer is off(not scanning multiple channels)                       
    hAdc2.Init.NbrOfDiscConversion   = 1; 
	// don't care as discontinous mode off
    hAdc2.Init.ExternalTrigConv      = ADC_EXTERNALTRIG_T6_TRGO;  
	// !!!!!  TRIGGERED BY TIMER 6 ("Basic" Timer of STM32L4)
    hAdc2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;  
	// N/A with sw trigger
    hAdc2.Init.DMAContinuousRequests = DISABLE; // ENABLE;//msut be consistent with DMA mode (normal/circular) 
    hAdc2.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      
	// overwrite previous if overrun 
    hAdc2.Init.OversamplingMode      = DISABLE; 


    if (HAL_ADC_Init(&hAdc2) != HAL_OK)
    {
      /* ADC initialization error */
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }


    // === ADC Regular Channel Setup ====
    sConfigAdcChannel.Channel      = ADC_CHANNEL_8;  
	//ADC2 Channel8 can take OPAMP1 Vout as input
    sConfigAdcChannel.Rank         = ADC_REGULAR_RANK_1;  
	//This channel will be first (and only!) sampled in the sequence
    sConfigAdcChannel.SamplingTime = ADC_SAMPLETIME_6CYCLES_5;  
	//valid values: 2.5, 6.5, 12.5, 24.5, 47.5, 92.5, 247.5 and 640.5 ADC clock cycles
	//comes on top of ADC intrinsic processing time. Larger time= more averaged result
    sConfigAdcChannel.SingleDiff   = ADC_SINGLE_ENDED;            
	// Single-ended input channel */
    sConfigAdcChannel.OffsetNumber = ADC_OFFSET_NONE;             
	// Offset subtraction */ 
    sConfigAdcChannel.Offset = 0;              
       // CAUTION: when substracing an offset, the ADC returns a signed rather 
       //           than unsigned value, with sign extension on 16 bits - see Ref.Manual

    if (HAL_ADC_ConfigChannel(&hAdc2, &sConfigAdcChannel) != HAL_OK)
    {
      /* Channel Configuration Error */
       LBF_Led_StopNBlinkOnFalse (FALSE);
    }


/*
    // ===  (Optional) Calibrate ADC and start conversion process  ====
    if (HAL_ADCEx_Calibration_Start(&hAdc2, ADC_SINGLE_ENDED) !=  HAL_OK)
    {
       // ADC Calibration Error 
       LBF_Led_StopNBlinkOnFalse (FALSE);
     }
*/

    // ----------------------------------------------------------------
    // --- Timer6 Setup ("Basic" Timer used as trigger for ADC @20KHz  


   //Timer6 Init 
    LBF_Timer_Setup( &htim6, TIMER6, TIMER_UNIT_US, 125 );  // Set Timer Fqcy = 8KHz 

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


    
    // ADC has been set in DMA mode, so enable IRQ for DMA
    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, __DMA1_CHANNEL2_IRQn_PRIO, 0);   
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);


}


/************************************************************************/
// Constant:  HAMMING WINDOW
/************************************************************************/

#ifdef USE_HAMMING_WINDOW
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
#endif


/***************************************************************END OF FILE****/
