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


ADC_HandleTypeDef    hAdc3;
TIM_HandleTypeDef    hTim4;

volatile bool 	Timer4_Elapsed = FALSE;  // global variable shared with stm32_it.c
   // Declared as volatile because is set in IRQ service routine and exploited outside it.
   // Without this keywork, risk of unexpected behavior with compiler optimizations turned on.
   // See e.g. :
   // http://www.embedded.com/electronics-blogs/beginner-s-corner/4023801/Introduction-to-the-Volatile-Keyword



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

uint16_t  Ycoord;
uint32_t  Voltage_mV;

void LBF_Battery_Setup_ADC3(void);
uint32_t LBF_Battery_GetVoltage_mV(void);

uint16_t  i = 0;



/* ==  Body     ======================================== */


    LBF_OLED_Switch_ON();
      // Provide power (13V) to OLED panel, enable display

    LBF_OLED_PrintString("\nBatt. Monitor (5V full scale)\n");

    LBF_Led_ON();
    
    LBF_Battery_Setup_ADC3();
      // Initialize ADC3 Ch2 for subsequent use for battery monitoring

    // Initialize Timer to fire every x sec
    LBF_Timer_Setup( &hTim4, TIMER4, TIMER_UNIT_MS, 1000);  // 1 sec period
    LBF_Timer_Start_ITout( &hTim4 );  //Start Timer4 with IT generation

    // Prepare Display: Font Size
    GUI_SetFont(&GUI_Font16B_ASCII);

    while(1)
    {
	if ( Timer4_Elapsed)
	{
	    if (++i == 160)
	    {
		i =0;
		LBF_OLED_Clear();
	    }

            Voltage_mV = LBF_Battery_GetVoltage_mV();

	    // Draw point
	    Ycoord = 127 - (Voltage_mV*128 / 5000);
	    GUI_DrawPoint( i, Ycoord);

            // Display value
            GUI_DispStringAt( "Vbat (mV) = ", X_FULL_SCREEN/16, Y_FULL_SCREEN*3/4 );
            GUI_DispDecAt( Voltage_mV,  X_FULL_SCREEN/2, Y_FULL_SCREEN*3/4, 4);  
           // Display voltage with 4 digits, at specified position

	    Timer4_Elapsed = FALSE;
	}

    } // end while(1)


return 0;
}


/*************************************************************************/
// PRIVATE FUNCTIONS
/************************************************************************/


/*******************************************************************************
 * @brief  : Measures voltage provided by LimiFrog LiPo battery (using ADC3 Ch.2)
 * @param  : None.
 * @return : Measured voltage in mV.
 ******************************************************************************/

uint32_t LBF_Battery_GetVoltage_mV(void)
{

__IO uint32_t  ADC_ConvertedValue;
uint32_t Vbat_mV;


    // Enable Battery measurement (active low)
    GPIO_LOW(BATT_PORT, BATT_MEAS_ENB_PIN);


    // ===  Perform Measurement   ===========

    //Launch ADC conversion (sw triggered mode)
    if ( HAL_ADC_Start(&hAdc3) != HAL_OK)
    {
      /* Possible Error Handler here */
    }
  
    // Wait for the ADC conversion to be completed (timeout unit: ms) */
    if ( HAL_ADC_PollForConversion(&hAdc3, 10) != HAL_OK)
    {
      /* Possible Error Handler here */
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

/***************************/

/*******************************************************************************
 * @brief  : Sets up ADC3 in configuration suitable for subsequent battery 
 *	      voltage measurement: Single Shot, 10bit res, slow clock
 * @param  : None.
 * @return : None
 ******************************************************************************/

void LBF_Battery_Setup_ADC3(void)
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
	// overwrite previous if overrun -- shouldn't happen with sw triggered start !*/
    hAdc3.Init.OversamplingMode      = DISABLE; 


    if (HAL_ADC_Init(&hAdc3) != HAL_OK)
    {
      /* ADC initialization error */
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

	/* Single-ended input channel */
    sConfigAdcChannel.OffsetNumber = ADC_OFFSET_NONE;             
	/* No offset subtraction */ 
    sConfigAdcChannel.Offset = 0;                                 

    if (HAL_ADC_ConfigChannel(&hAdc3, &sConfigAdcChannel) != HAL_OK)
    {
      /* Channel Configuration Error */
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




/***************************************************************END OF FILE****/
