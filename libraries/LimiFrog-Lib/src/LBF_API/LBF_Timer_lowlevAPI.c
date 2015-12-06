/*******************************************************************************
 * LBF_Timer_lowlevAPI.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "IT_Priorities_UserDefinable.h"


TIM_HandleTypeDef htim1;  //global variables declared in LBF_global_variables.h
TIM_HandleTypeDef htim2; 
TIM_HandleTypeDef htim3;     
TIM_HandleTypeDef htim4;     
TIM_HandleTypeDef htim5;   
TIM_HandleTypeDef htim6;     
TIM_HandleTypeDef htim7;     
TIM_HandleTypeDef htim8;     
TIM_HandleTypeDef htim15;    
TIM_HandleTypeDef htim16;    
TIM_HandleTypeDef htim17;    


/*  From STM32L476 DataSheet:

TIM1, TIM8:
   Adv. Control / 16-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / 3 complementary outputs 

TIM2, TIM5:
   Gal Purpose / 32-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / No complementary output

TIM3, TIM4:
   Gal Purpose / 16-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / No complementary output

TIM15:
   Gal Purpose / 16-bit res. / Up / 16-bit prescale factor / 2 compare channels / 1 complementary output

TIM16, TIM17:
   Gal Purpose / 16-bit res. / Up / 16-bit prescale factor / 1 compare channels / 1 complementary output

TIM6, TIM7:
   Basic / 16-bit res. / Up / 16-bit prescale factor / No compare channels / No complementary output

*/



/*******************************************************************************
 * @brief  : Set-up the timer indicated by caller
 * @param  : TimerID: timer to use
 * @param  : Units_in_us: Units (expressed as multiple of 1us) in which Period will be expressed (=Prescaled clock period)
 * @param  : Period_in_units: Timer Period (i.e Counter Reload Valu) expressed in above unit
 * @retval : none.
 ******************************************************************************/

void LBF_Timer_Setup( TimerID_t TimerID, uint16_t Timer_TimeUnit_us, uint32_t Period_as_TimerUnits )
{
TIM_HandleTypeDef htim;  // handle used by TIM HAL functions 
uint32_t TimerClockFqcy;

  // Select Right Timer and make sure associated handle will
  //  reflect what's done with local handle here

  switch( TimerID )
  {
    case TIMER1:
        __HAL_RCC_TIM1_CLK_ENABLE();
  	htim.Instance = TIM1;
        htim1 = htim;  // "shallow" copy i.e. pointer is copied (both point to same data)
        break;
    case TIMER2:
        __HAL_RCC_TIM2_CLK_ENABLE();
  	htim.Instance = TIM2;
        htim2 = htim;  
        break;
    case TIMER3:
        __HAL_RCC_TIM3_CLK_ENABLE();
  	htim.Instance = TIM3;
        htim3 = htim;
        break;
    case TIMER4:
        __HAL_RCC_TIM4_CLK_ENABLE();
  	htim.Instance = TIM4;	
        htim4 = htim;
        break;
    case TIMER5:	// the timer used by function LBF_Delay_ms()
        __HAL_RCC_TIM5_CLK_ENABLE();
  	htim.Instance = TIM5;	
        htim5 = htim;
        break;
    case TIMER6:
        __HAL_RCC_TIM6_CLK_ENABLE();
  	htim.Instance = TIM6;	
        htim6 = htim;
        break;
    case TIMER7:
        __HAL_RCC_TIM7_CLK_ENABLE();
  	htim.Instance = TIM7;	
        htim7 = htim;
        break;
    case TIMER8:
        __HAL_RCC_TIM8_CLK_ENABLE();
  	htim.Instance = TIM8;
        htim8 = htim;
        break;
 
    case TIMER15:
        __HAL_RCC_TIM15_CLK_ENABLE();
  	htim.Instance = TIM15;	
        htim15 = htim;
        break;
    case TIMER16:
        __HAL_RCC_TIM16_CLK_ENABLE();
  	htim.Instance = TIM16;	
        htim16 = htim;
        break;
    case TIMER17:
        __HAL_RCC_TIM17_CLK_ENABLE();
  	htim.Instance = TIM17;	
        htim17 = htim;
        break;

    default: break;
  }



  // Get Peripheral Clock Frequency
  if ( (TimerID == TIMER2) || (TimerID == TIMER3) || (TimerID == TIMER4) 
     ||(TimerID == TIMER5) || (TimerID == TIMER6) || (TimerID == TIMER7) )
  {  // then timer clock is APB1
  	TimerClockFqcy = 2*HAL_RCC_GetPCLK1Freq();
        // !!! Caution: TIMnCLK is 1x PCLK1 if APB1 prescaler=1 else is 2x -- see STM32 UserMan
	// Check APB1 clock settings in LBF_SysClkConfig.c
  }
  else
  {  // else timer clock is APB2 (so, for Timers 1, 8, 15-17)
  	TimerClockFqcy = 2*HAL_RCC_GetPCLK2Freq();
        // Caution: TIMnCLK is 1x PCLK2 if APB2 prescaler=1 else is 2x 
	// Check APB2 clock settings in LBF_SysClkConfig.c
  }
  /* ---   NOTE ON TIMER CLOCKS    ---------------------------------------------------*/
  // From STM32L476 User Manual, 8.2.14:
  // The timer clock frequencies are automatically defined by hardware. 
  // There are two cases:
  // 	1. If the APB prescaler equals 1, 
  // 	   the timer clock frequencies are set to the same frequency as that of the APB domain.
  // 	2. Otherwise, they are set to twice (×2) the frequency of the APB domain.     


  
  // Configure the TIM peripheral Time Base

  // Based on hypothesis that APB1CLK = APB2CLK = Core Clock/4 so 20MHz max
  // and therefore TIMxCLK max = 2x APBCLK = 40MHz max
  // So Prescaler value below fits on 16 bits (<65536)

  htim.Init.Prescaler = ( (TimerClockFqcy/1000)*Timer_TimeUnit_us) / 1000 - 1;  
	// split calculations to preserve correct accuracy in fixed point while avoiding overflows
  htim.Init.Period = Period_as_TimerUnits -1 ;  
  htim.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
  HAL_TIM_Base_Init(&htim);

  // !!! CAUTION: 
  // Requires Timer Clock < 65.536MHz (else overflow in htim.Init.Prescaler calculation)
  // so NOT usable if APB prescaler = 1 or 2 and Core Clock > 65.536MHz
  // (assuming Timer-TimeUnit_us takes value either TIMER_UNIT_US i.e. 1 (1us unit)
  //   or TIMER_UNIT_MS i.e. 1000 (1ms unit) )


}


/*******************************************************************************
 * @brief  : Start the timer and optionally generate an "update" interrupt when elapsed
 * @param  : TimerID: timer to use; 
 * @retval : none.
 ******************************************************************************/

void LBF_Timer_Start_ITout( TimerID_t TimerID )
{
TIM_HandleTypeDef htim;  // handle used by TIM HAL functions 
IRQn_Type  IRQnum;
uint32_t   IRQprio;

  // Select Right Timer 
  switch( TimerID )
  {
    case TIMER1:
        IRQnum = TIM1_UP_TIM16_IRQn; // Caution: TIM1 update IT is combined with TIM16 (global) IT
        IRQprio = __TIM1_UP_TIM16_IRQn_PRIO;
        htim = htim1;
        break;
    case TIMER2:
        IRQnum = TIM2_IRQn;
        IRQprio = __TIM2_IRQn_PRIO;
        htim = htim2;
        break;
    // Usage of Timer3 as interrupt source by the application: discarded
    // to leave Timer3 for exclusie usage of function LBF_Delay_ms
    /*  case TIMER3:
          IRQnum = TIM3_IRQn;
          IRQprio = __TIM3_IRQn_PRIO;
          htim = htim3;
          break;  */
    case TIMER4:
        IRQnum = TIM4_IRQn;
        IRQprio = __TIM4_IRQn_PRIO;
        htim = htim4;
        break;
    case TIMER5:
        IRQnum = TIM5_IRQn;
        IRQprio = __TIM5_IRQn_PRIO;
        htim = htim5;
        break;
    case TIMER6:
        IRQnum = TIM6_DAC_IRQn; // Caution: TIM6 (global) IT is combined with DAC underrrun IT
        IRQprio = __TIM6_DAC_IRQn_PRIO;
        htim = htim6;
        break;
    case TIMER7:
        IRQnum = TIM7_IRQn;
        IRQprio = __TIM7_IRQn_PRIO;
        htim = htim7;
        break;
    case TIMER8:
        IRQnum = TIM8_UP_IRQn;  // Timer 8 has dedicated "update" interrupt
        IRQprio = __TIM8_UP_IRQn_PRIO;
	htim = htim8;
        break;

    case TIMER15:
        IRQnum = TIM1_BRK_TIM15_IRQn; // Caution: TIM15 IT is combined with TIM1 break IT
        IRQprio = __TIM1_BRK_TIM15_IRQn_PRIO;
        htim = htim15;
        break;
    case TIMER16:
        IRQnum = TIM1_UP_TIM16_IRQn; // Caution: TIM16 (global) IT is combined with TIM1 update IT 
        IRQprio = __TIM1_UP_TIM16_IRQn_PRIO;
        htim = htim16;
        break;
    case TIMER17:
    default :  // to avoid warning "IRQnum may be used initialized in this fucntion"
        IRQnum = TIM1_TRG_COM_TIM17_IRQn; // Caution: TIM17 (global) IT is combined with TIM1 trigger IT 
        IRQprio = __TIM1_TRG_COM_TIM17_IRQn_PRIO;
        htim = htim17;
        break;
  }

  // Start Time Base Generation, in interrupt mode 
    HAL_TIM_Base_Start_IT(&htim);
    HAL_NVIC_SetPriority(IRQnum, IRQprio , 0); 
    HAL_NVIC_EnableIRQ(IRQnum); 

}


/*******************************************************************************
 * @brief  : Stop the timer (IT gets disabled)
 * @param  : TimerID: timer to use
 * @retval : none.
 ******************************************************************************/

void LBF_Timer_Stop( TimerID_t TimerID )
{
// We disable using HAL_TIM_Base_Stop_IT 
// even when TIM was starting without IT generation
// Not a pb as this simply means we're going to disable an
// IT generation flag that was not set anyway...

  switch( TimerID )
  {
    case TIMER1:
    	HAL_TIM_Base_Stop_IT(&htim1);
        break;
    case TIMER2:
    	HAL_TIM_Base_Stop_IT(&htim2);
        break;
    case TIMER3:
    	HAL_TIM_Base_Stop_IT(&htim3);
        break;
    case TIMER4:
    	HAL_TIM_Base_Stop_IT(&htim4);
        break;
    case TIMER5:
    	HAL_TIM_Base_Stop_IT(&htim5);
        break;
    case TIMER6:
    	HAL_TIM_Base_Stop_IT(&htim6);
        break;
    case TIMER7:
    	HAL_TIM_Base_Stop_IT(&htim7);
        break;
    case TIMER8:
    	HAL_TIM_Base_Stop_IT(&htim8);
        break;

    case TIMER15:
    	HAL_TIM_Base_Stop_IT(&htim15);
        break;
    case TIMER16:
    	HAL_TIM_Base_Stop_IT(&htim16);
        break;
    case TIMER17:
    	HAL_TIM_Base_Stop_IT(&htim17);
        break;

    default: break;
  }
 

}


/*
// TODO ?
void LBF_Timer_Freeze( );
void LBF_Timer_Continue( );
*/
// Caution: if trying to implement eg. a Timer_Update_Period() function that uses
// macro __HAL_TIM_SetAutoreload to directly access the reload register...
// ...if programming a smaller value than current while counter is already past that value, 
// unpredictable behavior occurs (looks like counter is directly written rather than updated at next
// roll-over



/*=======  PWM Specifics ========================================================*/

// !!!!!!!!!!!!!!!!!!!!!!!
// Here we only deal with PWM that can be made available on the extension connector
// of LimiFrog. (and ignoring complentary outputs possibilities)
// Namely:
// - TIMER2, Channel 1 (on connector position 1 = PA5)
// - TIMER3, Channels 1 and 2 (on connector position 2 = PA6 and posn 3 = PA7)
// - TIMER4, Channels 3 and 4 (on connector positions 9 = PB8 and posn 10 = PB9)
// - TIMER16, Channel 1 (on connector position 2 = PA6, also posn 9 = PB8)
// - TIMER17, Channel 1 (on connector position 3 = PA7, also posn 10 = PB9)

// !!!!!!!!!!!!!!!!!!!!!!!


/*******************************************************************************
 * @brief  : Initialise and configure a PWM channel of a timer 
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_PWMchannel_Setup ( TimerID_t TimerID, ChannelID_t ChannelID, uint32_t Pulse_as_TimerUnits )
{
// Note: Timer (TIM) peripheral (i.e. time base) must have been setup first !

TIM_OC_InitTypeDef sConfigOC; 

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = Pulse_as_TimerUnits ; 
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  if (TimerID == TIMER2)
  {
      if (ChannelID == CHANNEL1)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);  
      }
  }
  if (TimerID == TIMER3)
  {
      if (ChannelID == CHANNEL1)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);  
      }
      if (ChannelID == CHANNEL2)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);  
      }
  }
  if (TimerID == TIMER4)
  {
      if (ChannelID == CHANNEL3)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);  
      }
      if (ChannelID == CHANNEL4)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);  
      }
  }
  if (TimerID == TIMER16)
  {
      if (ChannelID == CHANNEL1)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1);  
      }
  }
  if (TimerID == TIMER17)
  {
      if (ChannelID == CHANNEL1)
      {
	  HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1);  
      }
  }
}
/*******************************************************************************
 * @brief  : Sets duty Cycle of a PWM source; Period must have been previously set
 *           using LBF_PWM_SetPeriod. ONE SINGLE PERIOD FOR ALL CHANNELS OF SAME TIMER. 
 * @param  : Pwm_ID_Chan (TIMER and CHANNEL to use), High Pulse in us.
 * @retval : none.
 ******************************************************************************/

void LBF_PWMChannel_UpdatePulse (TimerID_t TimerID, ChannelID_t ChannelID, uint32_t  Pulse_as_TimerUnits)
{
  if (Pulse_as_TimerUnits==0)	    //if user wants no pulse
	Pulse_as_TimerUnits = 1;    //avoid roll-over when substracting '1' below

  if (TimerID == TIMER2)
  {
      if (ChannelID == CHANNEL1)
      {
         __HAL_TIM_SetCompare( &htim2, TIM_CHANNEL_1, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
  }
  if (TimerID == TIMER3)
  {
      if (ChannelID == CHANNEL1)
      {
         __HAL_TIM_SetCompare( &htim3, TIM_CHANNEL_1, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
      if (ChannelID == CHANNEL2)
      {
         __HAL_TIM_SetCompare( &htim3, TIM_CHANNEL_2, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
  }
  if (TimerID == TIMER4)
  {
      if (ChannelID == CHANNEL3)
      {
         __HAL_TIM_SetCompare( &htim4, TIM_CHANNEL_3, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
      if (ChannelID == CHANNEL4)
      {
         __HAL_TIM_SetCompare( &htim4, TIM_CHANNEL_4, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
  }
  if (TimerID == TIMER16)
  {
      if (ChannelID == CHANNEL1)
      {
         __HAL_TIM_SetCompare( &htim16, TIM_CHANNEL_1, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
  }
  if (TimerID == TIMER17)
  {
      if (ChannelID == CHANNEL1)
      {
         __HAL_TIM_SetCompare( &htim17, TIM_CHANNEL_1, Pulse_as_TimerUnits-1);  
         // Update value of Compare Registers that defines PWM pulse duration
      }
  }

}

/*******************************************************************************
 * @brief  : Start a PWM source
 * @param  : TimerID, ChannelID (TIMER and CHANNEL to use)
 * @retval : none.
 ******************************************************************************/
void LBF_PWMChannel_Start (TimerID_t TimerID, ChannelID_t ChannelID)
{

  if (TimerID == TIMER2)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Start( &htim2, TIM_CHANNEL_1 );  
      }
  }
  if (TimerID == TIMER3)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Start( &htim3, TIM_CHANNEL_1 );  
      }
      if (ChannelID == CHANNEL2)
      {
         HAL_TIM_PWM_Start( &htim3, TIM_CHANNEL_2 );  
      }
  }
  if (TimerID == TIMER4)
  {
      if (ChannelID == CHANNEL4)
      {
         HAL_TIM_PWM_Start( &htim4, TIM_CHANNEL_3 );  
      }
      if (ChannelID == CHANNEL4)
      {
         HAL_TIM_PWM_Start( &htim4, TIM_CHANNEL_4 );  
      }
  }
  if (TimerID == TIMER16)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Start( &htim16, TIM_CHANNEL_1 );  
      }
  }
  if (TimerID == TIMER17)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Start( &htim17, TIM_CHANNEL_1 );  
      }
  }

}

/*******************************************************************************
 * @brief  : Stop a PWM source
 * @param  : TimerID, ChannelID (TIMER and CHANNEL to use)
 * @retval : none.
 ******************************************************************************/
void LBF_PWMChannel_Stop (TimerID_t TimerID, ChannelID_t ChannelID)
{
  if (TimerID == TIMER2)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Stop( &htim2, TIM_CHANNEL_1 );  
      }
  }
  if (TimerID == TIMER3)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Stop( &htim3, TIM_CHANNEL_1 );  
      }
      if (ChannelID == CHANNEL2)
      {
         HAL_TIM_PWM_Stop( &htim3, TIM_CHANNEL_2 );  
      }
  }
  if (TimerID == TIMER4)
  {
      if (ChannelID == CHANNEL4)
      {
         HAL_TIM_PWM_Stop( &htim4, TIM_CHANNEL_3 );  
      }
      if (ChannelID == CHANNEL4)
      {
         HAL_TIM_PWM_Stop( &htim4, TIM_CHANNEL_4 );  
      }
  }
  if (TimerID == TIMER16)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Stop( &htim16, TIM_CHANNEL_1 );  
      }
  }
  if (TimerID == TIMER17)
  {
      if (ChannelID == CHANNEL1)
      {
         HAL_TIM_PWM_Stop( &htim17, TIM_CHANNEL_1 );  
      }
  }

}


/***************************************************************END OF FILE****/
