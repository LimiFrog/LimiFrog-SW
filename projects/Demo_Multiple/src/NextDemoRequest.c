/*******************************************************************************
 * NextDemoRequest.c
 * 
  * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

// Next Demo is requested by tapping LimiFrog or clapping hands or ...
// This is detected by the microphone 


#include "LBF_Global.h"

ADC_HandleTypeDef    hAdc2;
TIM_HandleTypeDef    htim6;

/* -------------------------------------------------------------------- */


bool NextDemoRequest(void)
{
	if ( __HAL_ADC_GET_FLAG( &hAdc2, ADC_FLAG_AWD1 ) )  
	    // Flag AWD1 was set by Analog Watchdog 
	{
	
	   LBF_Led_TOGGLE();
	   LBF_Delay_ms(300);
	   LBF_Led_TOGGLE();
	    // Clear AWD1 flag
	    __HAL_ADC_CLEAR_FLAG( &hAdc2, ADC_FLAG_AWD1 );
	   return true;
	}

        else if  (LBF_State_Switch1_IsOn())   // demo change by PB
	{
	   LBF_Led_TOGGLE();
	   while(LBF_State_Switch1_IsOn()); // wait until released
	   LBF_Led_TOGGLE();
	   return true;
	}

	else
	   return false;
}


/***********************************************************************************************/


void NextDemoRequest_Init(void)
{

ADC_ChannelConfTypeDef   sConfigAdcChannel;
TIM_MasterConfigTypeDef  sMasterConfig;
ADC_AnalogWDGConfTypeDef AnalogWDGConfig;

#define NOISE_THRESHOLD_PCT  30    //Noise detection threshold in % of ADC saturation level

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
    LBF_Timer_Setup( &htim6, TIMER6, TIMER_UNIT_US, 1000 );  // Set Timer Period=1ms i.e. fqcy = 1KHz

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

    // ----------------------------------------------------------------
    // ---    Launch ADC conversion 
    if ( HAL_ADC_Start(&hAdc2) != HAL_OK)
    {
        /* Possible Error Handler here */
    }
  

}



/***************************************************************END OF FILE****/// 
