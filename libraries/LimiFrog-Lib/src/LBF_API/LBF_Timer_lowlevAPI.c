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




/*  From STM32L476 DataSheet:

TIM1, TIM8:
   Adv. Control / 16-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / 3 complementary outputs 
----------
TIM2, TIM5:
   Gal Purpose / 32-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / No complementary output

TIM3, TIM4:
   Gal Purpose / 16-bit res. / Up, Down, Up-Down / 16-bit prescale factor / 4 compare channels / No complementary output
----------
TIM15:
   Gal Purpose / 16-bit res. / Up / 16-bit prescale factor / 2 compare channels / 1 complementary output

TIM16, TIM17:
   Gal Purpose / 16-bit res. / Up / 16-bit prescale factor / 1 compare channels / 1 complementary output
----------
TIM6, TIM7:
   Basic / 16-bit res. / Up / 16-bit prescale factor / No compare channels / No complementary output
----------
LPTIM1, LPTIM2:
   Low-power / 16-bit res. / Up / 3 bit define 8 prescale factor / 1 compare channel / No complementary output

*/


/**********
* Function :	
	void LBF_Timer_Setup( TIM_HandleTypeDef* htim, LBF_TimerID_t TimerID, uint16_t Timer_TimeUnit_us, uint32_t Period_as_TimerUnits )

* Description :	
	Configures the timer identified by TimerID, with a user-specified period expressed in a user-specified time-unit (typically in micro-seconds or in millisonds). The time unit corresponds to the period of the 'prescaled clock' in the timer hardare. The timer is set to up-counting mode.

* Parameters :  
	> htim: pointer to a structure which the underlying HAL driver will fill to perform the initialization (see note below)
	> TimerID : the identity (number) of the timer to set up
	> Timer_TimeUnit_us :  the prescaled clock period to use for the target timer, expressed in micro-seconds (us). Can therefore be regarded as time unit for that timer. Aliases LBF_TIMER_UNIT_US or LBF_TIMER_UNIT_MS can conveniently be used to get the timer to use, respectively, one micro-second or one milli-second as time unit.
	> Period_as_TimerUnits : Timer period, expressed in the formerly defined time unit (i.e. in number of prescaled clock periods)

* Return Value:  -

* Note:  
	the user needs to declare a structure of type TIM_HandleTypeDef in his code prior to calling this function, passing a pointer to this structure as argument. He can then, if he so wishes, also use this handle to call other HAL functions, for example to send or receive data – he may also work at lower level if he prefers.
***********/

void LBF_Timer_Setup( TIM_HandleTypeDef* htim, TimerID_t TimerID, uint16_t Timer_TimeUnit_us, uint32_t Period_as_TimerUnits )
{

uint32_t TimerClockFqcy;

  // Select Right Timer and make sure associated handle will
  //  reflect what's done with local handle here

  switch( TimerID )
  {
    case TIMER1:
        __HAL_RCC_TIM1_CLK_ENABLE();
  	htim->Instance = TIM1;
        break;
    case TIMER2:
        __HAL_RCC_TIM2_CLK_ENABLE();
  	htim->Instance = TIM2;
        break;
    case TIMER3:
        __HAL_RCC_TIM3_CLK_ENABLE();
  	htim->Instance = TIM3;
        break;
    case TIMER4:
        __HAL_RCC_TIM4_CLK_ENABLE();
  	htim->Instance = TIM4;
        break;
    case TIMER5:	// the timer used by function LBF_Delay_ms()
        __HAL_RCC_TIM5_CLK_ENABLE();
  	htim->Instance = TIM5;
        break;
    case TIMER6:
        __HAL_RCC_TIM6_CLK_ENABLE();
  	htim->Instance = TIM6;
        break;
    case TIMER7:
        __HAL_RCC_TIM7_CLK_ENABLE();
  	htim->Instance = TIM7;
        break;
    case TIMER8:
        __HAL_RCC_TIM8_CLK_ENABLE();
  	htim->Instance = TIM8;
        break;
 
    case TIMER15:
        __HAL_RCC_TIM15_CLK_ENABLE();
  	htim->Instance = TIM15;
        break;
    case TIMER16:
        __HAL_RCC_TIM16_CLK_ENABLE();
  	htim->Instance = TIM16;
        break;
    case TIMER17:
        __HAL_RCC_TIM17_CLK_ENABLE();
  	htim->Instance = TIM17;
        break;

    default: break;

//TODO: LPTIM low-power timer

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

  htim->Init.Prescaler = ( (TimerClockFqcy/1000)*Timer_TimeUnit_us) / 1000 - 1;  
	// split calculations to preserve correct accuracy in fixed point while avoiding overflows
  htim->Init.Period = Period_as_TimerUnits -1 ;  
  htim->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 

//  HAL_TIM_Base_Init(&htim);
  HAL_TIM_Base_Init(htim);

  // !!! CAUTION: 
  // Requires Timer Clock < 65.536MHz (else overflow in htim.Init.Prescaler calculation)
  // so NOT usable if APB prescaler = 1 or 2 and Core Clock > 65.536MHz
  // (assuming Timer-TimeUnit_us takes value either TIMER_UNIT_US i.e. 1 (1us unit)
  //   or TIMER_UNIT_MS i.e. 1000 (1ms unit) )


}


/*************
* Function :	
	void LBF_Timer_Start_ITout( TIM_HandleTypeDef* htim )
* Description :	
	Starts the timer identified by htim with generation of an interrupt at the end of each period 
* Parameters :  
	htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
* Return Value:  -
* Note:
	This function sets the priorities of timer Interrupts. If parameters __TIMx_xx_IRQn_PRIO are found (typically, defined in user file IT_Priorities_UserDefinable.h) then these are used. Else a default value of 0xFF (lowest pre-emption level) is used as default.

**************/

void LBF_Timer_Start_ITout( TIM_HandleTypeDef* htim )
{
;  // handle used by TIM HAL functions 
IRQn_Type  IRQnum;
uint32_t   IRQprio;


    IRQprio = 0xFF; // default value, will be overriden below if adequate parameter found


    if (htim->Instance== TIM1)
    {
        IRQnum = TIM1_UP_TIM16_IRQn; // Caution: TIM1 update IT is combined with TIM16 (global) IT
#ifdef __TIM1_UP_TIM16_IRQn_PRIO 
        IRQprio = __TIM1_UP_TIM16_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM2)
    {
        IRQnum = TIM2_IRQn;
#ifdef __TIM2_IRQn_PRIO
        IRQprio = __TIM2_IRQn_PRIO;
#endif
    }
    // Usage of Timer3 as interrupt source by the application: discarded
    // to leave Timer3 for exclusie usage of function LBF_Delay_ms
    if (htim->Instance== TIM4)
    {
        IRQnum = TIM4_IRQn;
#ifdef __TIM4_IRQn_PRIO
        IRQprio = __TIM4_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM5)
    {
        IRQnum = TIM5_IRQn;
#ifdef __TIM5_IRQn_PRIO
        IRQprio = __TIM5_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM2)
    {
        IRQnum = TIM6_DAC_IRQn; // Caution: TIM6 (global) IT is combined with DAC underrrun IT
#ifdef __TIM6_DAC_IRQn_PRIO
        IRQprio = __TIM6_DAC_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM7)
    {
        IRQnum = TIM7_IRQn;
#ifdef __TIM7_IRQn_PRIO
        IRQprio = __TIM7_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM8)
    {
        IRQnum = TIM8_UP_IRQn;  // Timer 8 has dedicated "update" interrupt
#ifdef __TIM8_UP_IRQn_PRIO
        IRQprio = __TIM8_UP_IRQn_PRIO;
#endif
    }

    if (htim->Instance== TIM15)
    {
        IRQnum = TIM1_BRK_TIM15_IRQn; // Caution: TIM15 IT is combined with TIM1 break IT
#ifdef __TIM1_BRK_TIM15_IRQn_PRIO
        IRQprio = __TIM1_BRK_TIM15_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM16)
    {
        IRQnum = TIM1_UP_TIM16_IRQn; // Caution: TIM16 (global) IT is combined with TIM1 update IT 
#ifdef __TIM1_UP_TIM16_IRQn_PRIO
        IRQprio = __TIM1_UP_TIM16_IRQn_PRIO;
#endif
    }
    if (htim->Instance== TIM17)
    {
        IRQnum = TIM1_TRG_COM_TIM17_IRQn; // Caution: TIM17 (global) IT is combined with TIM1 trigger IT 
#ifdef __TIM1_TRG_COM_TIM17_IRQn_PRIO
        IRQprio = __TIM1_TRG_COM_TIM17_IRQn_PRIO;
#endif
    }


//TODO: LPTIM low-power timer


  // Start Time Base Generation, in interrupt mode 
//    HAL_TIM_Base_Start_IT(&htim);
    HAL_TIM_Base_Start_IT(htim);
    HAL_NVIC_SetPriority(IRQnum, IRQprio , 0); 
    HAL_NVIC_EnableIRQ(IRQnum); 

}

/**********
* Function :	
	void LBF_Timer_Stop( TIM_HandleTypeDef* htim  )
* Description :	
	Stops the timer identified by htim.
* Parameters :   
	htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
* Return Value:  -
***********/

void LBF_Timer_Stop( TIM_HandleTypeDef* htim )
{
// We disable using HAL_TIM_Base_Stop_IT 
// even when TIM was starting without IT generation
// Not a pb as this simply means we're going to disable an
// IT generation flag that was not set anyway...

//    	HAL_TIM_Base_Stop_IT(&htim);
     	HAL_TIM_Base_Stop_IT(htim);

//TODO: LPTIM low-power timer

  //  HAL_NVIC_DisableIRQ() not invoked
  //  Should be OK as means NVIC is still active, 
  //  but IT generation from Timer is no more possible

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



/*=======  PWM Specifics    ==================================*/


/***********
* Function :	
	void LBF_PWMchannel_Setup( TIM_HandleTypeDef* htim, TimChannelID_t ChannelID, uint32_t Pulse_as_TimerUnits  )
* Description :	
	Initializes the specified channel of the timer handled by htim to generate a pulse at high logic level of the specified duration when enabled (actual pulse generation does not start yet)
* Parameters : 
	> htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
	> Channel_ID : the identity (number) of the channel to use
	> Pulse_as_TimerUnits : High pulse duration, expressed in the formerly defined time unit (i.e. in number of prescaled clock periods) – typically in ms or us.
* Return Value:  -
*************/

void LBF_PWMchannel_Setup ( TIM_HandleTypeDef* htim, TimChannelID_t ChannelID, uint32_t Pulse_as_TimerUnits )
{
// Note: Timer (TIM) peripheral (i.e. time base) must have been setup first !

TIM_OC_InitTypeDef sConfigOC; 

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = Pulse_as_TimerUnits ; 
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

//  HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, (uint32_t)ChannelID );  
  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, 4*((uint32_t)ChannelID-1) );  
}


/***
* Function :	
	void LBF_Update_Pulse( TIM_HandleTypeDef* htim, TimChannelID_t ChannelID, uint32_t Pulse_as_TimerUnits  )
* Description :	
	Updates on-the-fly the pulse duration of the specified PWM channel of the timer handled by htim – allowing to modulate its duty cycle, 
* Parameters : 
	> htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
	> Channel_ID : the identity (number) of the channel to use
	> Pulse_as_TimerUnits : High pulse duration, expressed in the formerly defined time unit (i.e. in number of prescaled clock periods) – typically in ms or us.
Return Value:  -
***/

// TODO - Using a macro would probably be more efficient to describe this ? 


void LBF_PWMchannel_UpdatePulse (TIM_HandleTypeDef* htim, TimChannelID_t ChannelID, uint32_t  Pulse_as_TimerUnits)
{
  if (Pulse_as_TimerUnits==0)	    //if user wants no pulse
	Pulse_as_TimerUnits = 1;    //avoid roll-over when substracting '1' below


  __HAL_TIM_SetCompare( htim, 4*((uint32_t)ChannelID-1), Pulse_as_TimerUnits-1);  
    // Update value of Compare Registers that defines PWM pulse duration

}




/*****************
* Function :	
	void LBF_PWMchannel_Start( TIM_HandleTypeDef* htim, TimChannelID_t ChannelID  )
* Description :	
	Start the specified PWM channel of the timer handled by htim
* Parameters : 
	> htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
	> Channel_ID : the identity (number) of the channel to use
* Return Value:  -
*****************/

void LBF_PWMchannel_Start (TIM_HandleTypeDef* htim, TimChannelID_t ChannelID)
{
//         HAL_TIM_PWM_Start( &htim, (uint32_t)ChannelID );  
         HAL_TIM_PWM_Start( htim, 4*((uint32_t)ChannelID-1) );  
}




/*****************
* Function :	
	void LBF_PWMchannel_Stop( TIM_HandleTypeDef* htim, TimChannelID_t ChannelID  )
* Description :	
	Stop the specified PWM channel of the timer handled by htim
* Parameters : 
	> htim : pointer to the structure of type TIM_HandleTypeDef that contains the configuration parameters of the selected timer. Typically this  pointer is first created by the user (through the declaration of a structure of type TIM_HandleTypeDef) and then passed to functions such as this one and others to operate on this timer  (that kind of structure is central to the underlying HAL library).
	> Channel_ID : the identity (number) of the channel to use
* Return Value:  -
*****************/

void LBF_PWMchannel_Stop (TIM_HandleTypeDef* htim, TimChannelID_t ChannelID)
{
//         HAL_TIM_PWM_Stop( &htim, (uint32_t)ChannelID );  
         HAL_TIM_PWM_Stop( htim,  4*((uint32_t)ChannelID-1));  
         // Update value of Compare Registers that defines PWM pulse duration

}


/***************************************************************END OF FILE****/
