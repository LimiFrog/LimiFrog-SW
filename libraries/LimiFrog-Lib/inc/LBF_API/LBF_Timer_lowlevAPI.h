/*******************************************************************************
 * LBF_Timer_lowlevAPI.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_TIMER_LOWLEVAPI_H
#define __LBF_TIMER_LOWLEVAPI_H


/* Constants        ---------------------------------------------------------*/

#define TIMER_UNIT_US	1
#define TIMER_UNIT_MS	1000



/* Custom Types      ---------------------------------------------------------*/
typedef enum {
  TIMER1 = 1,
  TIMER2 = 2,
  TIMER3 = 3,
  TIMER4 = 4,
  TIMER5 = 5,
  TIMER6 = 6,
  TIMER7 = 7,
  TIMER8 = 8,
  TIMER15 = 15,
  TIMER16 = 16,
  TIMER17 = 17
}    
TimerID_t;


typedef enum {
  CHANNEL1 = 1,
  CHANNEL2 = 2,
  CHANNEL3 = 3,
  CHANNEL4 = 4
}    
ChannelID_t;


/* Exported functions ------------------------------------------------------- */

void LBF_Timer_Setup( TimerID_t TimerID, uint16_t Timer_TimeUnit_us, uint32_t Period_as_TimerUnits );
void LBF_Timer_Start_ITout( TimerID_t TimerID );
void LBF_Timer_Stop( TimerID_t TimerID );

void LBF_PWMchannel_Setup ( TimerID_t TimerID, ChannelID_t ChannelID, uint32_t Pulse_as_TimerUnits );
void LBF_PWMChannel_UpdatePulse (TimerID_t TimerID, ChannelID_t ChannelID, uint32_t  Pulse_as_TimerUnits);
void LBF_PWMChannel_Start (TimerID_t TimerID, ChannelID_t ChannelID);
void LBF_PWMChannel_Stop (TimerID_t TimerID, ChannelID_t ChannelID);



#endif  /*__LBF_TIMER_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
