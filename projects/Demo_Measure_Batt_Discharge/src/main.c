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

static void LBF_Battery_Setup_ADC3(void);
static uint32_t LBF_Battery_GetVoltage_mV(void);

#define BATT_MEASUREMENT_PERIODICITY  (60*1000)  // in ms  -->  1 per minute


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = true;

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


    // If USB cable is plugged in, don't do anything,
    //  just allow access to internal files from PC in "USB stick" mode.
    // Will have to power off and back on without USB cable plugged in
    //  to run in "active" mode 
    if ( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_9 )== GPIO_PIN_SET )   
		// GPIO A Pin 9 = VBUS_SENSE input on STM32, bears 5V if USB plugged in, else Gnd
    {
        Success &= LBF_LaunchUSB_MassStorage(); // ... Use LimiFrog as USB Mass Storage (FS)
        LBF_Led_StopNBlinkOnFalse (Success);
        while(1); 
    }


    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
    Success &= LBF_FatFS_Init();

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


uint16_t color_table[8] = {BLACK, YELLOW, RED, WHITE, GREEN, BLUE, ORANGE, CYAN} ;
uint32_t counter = 0;

uint32_t  Time= 0, Hours = 0, Minutes = 0;
uint32_t  Voltage_mV;

FIL MyFile;
bool FatFS_OK = true;
uint32_t wbytes_count; /* File write counts */
char wtext[128]; /* File write buffer */
const char FileName[] = "BATLOG.TXT";

char Str_Time[8], Str_Voltage[8]; 



/* ==  Body     ======================================== */



    LBF_OLED_Switch_ON();
    // Provide power (13V) to OLED panel, enable display

    // Initialize a few GUI characteristics
    GUI_SetTextMode( GUI_TM_TRANS );  // overlay chars (transparent background)
    GUI_SetFont(&GUI_Font24B_ASCII);

    LBF_Led_ON();
    
    LBF_Battery_Setup_ADC3();
      // Initialize ADC3 Ch2 for subsequent use for battery monitoring

    // Initialize Timer to fire every x sec
    LBF_Timer_Setup( &hTim4, TIMER4, TIMER_UNIT_MS, BATT_MEASUREMENT_PERIODICITY);  
    LBF_Timer_Start_ITout( &hTim4 );  //Start Timer4 with IT generation


    // Write header in text file
    strcpy( wtext, "Time \tBattery Level in mV \r\n");
    FatFS_OK  &= ( f_open(&MyFile, FileName, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK);
    FatFS_OK  &= ( f_write(&MyFile, wtext, strlen(wtext), (void *)&wbytes_count) == FR_OK);
    FatFS_OK  &= ( f_close(&MyFile) == FR_OK );
    LBF_Led_StopNBlinkOnFalse( FatFS_OK  );  


    while(1)
    {

	LBF_Led_TOGGLE();

	// Handle pattern shift on OLED display :
        if ( !LBF_State_Switch1_IsOn() )  // keep current pattern if button pressed
        {  
            counter++;

            // Fill the 160x128 screens with 8 colors organized as 2 rows of 4 blocks
            // Arguments: Xstart, Ystart, Width, Height, Color in RGB565 format 
            LBF_OLED_Fill(0, 0, 40, 64, color_table[(0+counter)%8] );  
            LBF_OLED_Fill(40, 0,40, 64, color_table[(1+counter)%8]);
            LBF_OLED_Fill(80, 0, 40, 64, color_table[(2+counter)%8]);
            LBF_OLED_Fill(120, 0, 40, 64, color_table[(3+counter)%8]);
            LBF_OLED_Fill(0, 64, 40, 64, color_table[(4+counter)%8]);
            LBF_OLED_Fill(40, 64, 40, 64, color_table[(5+counter)%8]);
            LBF_OLED_Fill(80, 64, 40, 64, color_table[(6+counter)%8]);
            LBF_OLED_Fill(120, 64, 40, 64, color_table[(7+counter)%8]);
         }


	// Capture and log battery level if time to do so :
	if ( Timer4_Elapsed)
	{

	    Time = Time + BATT_MEASUREMENT_PERIODICITY/1000;  // in seconds
	    Hours = Time / 3600;
	    Minutes = (Time % 3600)/60;
	    sprintf( Str_Time, "%2d:%2d\t", (int)Hours, (int)Minutes );  

            Voltage_mV = LBF_Battery_GetVoltage_mV();
	    sprintf( Str_Voltage, "%d\r\n", (int)Voltage_mV );  

	    FatFS_OK &= (f_open(&MyFile, FileName, FA_WRITE) == FR_OK);
	    FatFS_OK &= (f_lseek(&MyFile, f_size(&MyFile)) == FR_OK);
	    	  // f_lseek to append (go to end of file)
		  // Could use mode FA_APPEND instead with more recent release of FatFS

	    FatFS_OK &= ( 
		    f_write(&MyFile, Str_Time, strlen(Str_Time), (void *)&wbytes_count) == FR_OK);
	    FatFS_OK &= ( 
		    f_write(&MyFile, Str_Voltage, strlen(Str_Voltage), (void *)&wbytes_count) == FR_OK);

	    FatFS_OK &= ( f_close(&MyFile) == FR_OK );
	    LBF_Led_StopNBlinkOnFalse( FatFS_OK );  // stop in case of error

	    Timer4_Elapsed = FALSE;

            // Display measured battery voltage for a short time
	    GUI_Clear();
            GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
            GUI_DispDecAt( Voltage_mV,  X_FULL_SCREEN/2, Y_FULL_SCREEN/4, 4);  
            			// display 4 digits, centered on specified position
            GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
            GUI_DispStringAt( "mV",  X_FULL_SCREEN/2, Y_FULL_SCREEN/2);  

	    LBF_Delay_ms(500);  // short freeze
	}
     }



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
