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

static void  Setup_ADC2_TIM6_AWD(void);

ADC_HandleTypeDef    hAdc2;

#define NOISE_THRESHOLD_PCT  30    //Noise detection threshold in % of ADC saturation level


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


bool	Bkgnd_is_cyan;


/* ==  Body     ======================================== */


    LBF_OLED_Switch_ON();
      // Provide power (13V) to OLED panel, enable display

    LBF_Led_ON();
    

    LBF_OLED_Fill(0, 0, 160, 128, CYAN);
    Bkgnd_is_cyan = TRUE;
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_DispStringAt( "Noise Threshold=  ", 5, Y_FULL_SCREEN*1/2 );
    GUI_DispDecMin( (int32_t)NOISE_THRESHOLD_PCT );
    GUI_DispString( " %" );

    // Configure ADC2 as Analog Watchdog with sampling continuously  
    // triggered by TIM6  (at 20KHz)
    Setup_ADC2_TIM6_AWD();


    //Launch ADC conversion 
    if ( HAL_ADC_Start(&hAdc2) != HAL_OK)
    {
      /* Possible Error Handler here */
    }


    // Below we're using a HAL macro in polling mode to detect if analog watchdog
    // has fired.
    // Alternatively, could enable IT from analog watchdog when setting up
    // ADC2 and work on IT

    while(1)
    {
	if ( __HAL_ADC_GET_FLAG( &hAdc2, ADC_FLAG_AWD1 ) )  // Flag AWD1 was set by Analog Watchdog 
	{
	    LBF_Led_ON();

 	    if (Bkgnd_is_cyan)
	    {
		LBF_OLED_Fill(0, 0, 160, 128, RED);
		Bkgnd_is_cyan = FALSE;
	    }
	    else
	    {
		LBF_OLED_Fill(0, 0, 160, 128, CYAN);
		Bkgnd_is_cyan = TRUE;
	    }

	    __HAL_ADC_CLEAR_FLAG( &hAdc2, ADC_FLAG_AWD1 );
	    LBF_Led_OFF();
	}

    } 

return 0;
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

static void Setup_ADC2_TIM6_AWD(void)
{

TIM_HandleTypeDef    hTim6;

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

     // Caution - if enabling IT on ADC Watchdog (thru AnalogWDGConfig.ITMode)
     // ..don't forget to also enable IT at NVIC level !!!!!!
     // HAL_NVIC_SetPriority(ADC1_2_IRQn, __ADC1_2_IRQn_PRIO , 0); // priority defined in User_Configuration.h
     // HAL_NVIC_EnableIRQ(ADC1_2_IRQn); 



    // ----------------------------------------------------------------
    // --- Timer6 Setup ("Basic" Timer used as trigger for ADC @20KHz  


   //Timer6 Init 
    LBF_Timer_Setup( &hTim6, TIMER6, TIMER_UNIT_US, 50 );  // Set Timer Period=50 us i.e. fqcy = 20KHz

    /* Timer TRGO selection */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(&hTim6, &sMasterConfig) != HAL_OK)
    {
      /* Timer TRGO selection Error */
         // LBF_OLED_PrintString("\nMaster Config FAIL\n");
         LBF_Led_StopNBlinkOnFalse (FALSE);
    }

    if (HAL_TIM_Base_Start(&hTim6) != HAL_OK)
    {
      /* Counter Enable Error */
        // LBF_OLED_PrintString("\nTime Base Start FAIL\n");
        LBF_Led_StopNBlinkOnFalse (FALSE);
    }

}



/***************************************************************END OF FILE****/
