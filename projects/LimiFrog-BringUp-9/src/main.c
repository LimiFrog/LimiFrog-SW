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
#include "User_Configuration.h"

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

    LBF_Board_Fixed_Inits();
    LBF_Board_Selective_Inits(); 
             // actions driven by User_Configuration.h

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
    // Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();




/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

uint32_t	CurrentTime_ms, CurrentTime_us ;
uint8_t		i;

/*
const uint16_t  Period = 200; //200ms pwm period
uint16_t	Pulse_Selection[4] = {20, 40, 80, 160};  // 0.2, 0.4, 0.8 or 1.6ms high pulse
uint8_t		PulseIndex = 0;
*/

/* ==  Body     ======================================== */


    LBF_Led_OFF();
    LBF_Delay_ms(1000);
    

    // *** Free running timer demo section *************************
    // ==>
    //     Flash LED every 0.5s with duration detected by 
    //     polling free running timer


    // ==  First, using a 1ms resolution  ==========================

    // Use Timer2 (a 32-bit timer) with 1ms resolution- 
    LBF_Timer_Setup( TIMER2, TIMER_UNIT_MS, 10000);  
	//Counter wraps around after say 10s - not important in this example

    // Start timer2 (no IT)
    HAL_TIM_Base_Start(&htim2);

    i = 0;
    do 
    {
        // Read counter value
        CurrentTime_ms =  __HAL_TIM_GetCounter(&htim2);
    
        if ( CurrentTime_ms % 500 == 0)  	//Every 0.5s (500ms)...
        {
	     i++;
             LBF_Led_ON();		// ...Flash LED
	     LBF_Delay_ms(100);
             LBF_Led_OFF();
        }
    }  while (i!=8);  // to get 8 flashes
 


    // ===  Pause       =============================================
    HAL_TIM_Base_Stop(&htim2);
    LBF_Delay_ms(1000);


    // ==  Exact same demo using a 1us resolution this time  ========

    // This time set Timer2 for 1us resolution- 
    LBF_Timer_Setup( TIMER2, TIMER_UNIT_US, 10000000);  
	//Counter to wrap around after say 10s - not important in this example

    // Start timer2 (no IT)
    HAL_TIM_Base_Start(&htim2);

    i = 0;
    do 
    {
        // Read counter value
        CurrentTime_us =  __HAL_TIM_GetCounter(&htim2);
    
        if ( CurrentTime_us % 500000 == 0)  	//Every 0.5s (500000us)...
        {
	     i++;
             LBF_Led_ON();		// ...Flash LED
	     LBF_Delay_ms(100);
             LBF_Led_OFF();
        }
    }  while (i!=8);  // to get 8 flashes

    HAL_TIM_Base_Stop(&htim2);

    //End Of Free Running Timer Demo




    // *** Timer-based interrupt generation demo section ************

    LBF_Timer_Setup( TIMER4, TIMER_UNIT_MS, 30);  //Configure Timer4 for 1ms prescaled clock, 30ms period


   // Set timer4 to fire IT when elapsed (so, every 30ms)
   // Then wait for 2sec.
   // Series of IT fire while waiting, in IT handler (cf stm32_it.c) LED gets toggled
   // => Should see LED blinking fast during these 2 seconds
   //
    LBF_Timer_Start_ITout( TIMER4 );  //Start Timer4 with IT generation
    LBF_Delay_ms(2000);  // ITs are firing during this time

    LBF_Timer_Stop( TIMER4 );  //Now stop Timer4 

 

    // *** PWM demo section  (PWM on Timer4, Channel 4)  *******************
/*
    // Set-up Timer 4 and specify period 
    LBF_Timer_Setup( TIMER4, TIMER_UNIT_MS, Period );  


    // Set-up Channel 4 of Timer 4 and specify high pulse duration (duty cycle = pulse / period)
    LBF_PWMchannel_Setup( TIMER4, CHANNEL4, Pulse_Selection[PulseIndex]);   

    // Launch PWM
    LBF_PWMChannel_Start( TIMER4, CHANNEL4 );  
    // available on Ext. Conn; Position 10 - cf User_Configuration.h


    while(1)
    {	
        // Now we will get LED to follow state of PWM 
        // by checking value present on position 10 of Connector 
        // (this requires the #define POS10_IS_PWM_TIM4_CH4  in User_Configuration.h )
        if ( IS_GPIO_SET( CONN_POS10_PORT, CONN_POS10_PIN ) )
        {
           Stm32_Led_ON();
        }
        else
        {
            Stm32_Led_OFF();
        }

        // ...and we will increase or decrease the duty cycle when user presses side-push buttons 
        if (State_Switch1_IsOn() )
        {   
            while (State_Switch1_IsOn()); // wait for release
            if ( PulseIndex-- == 0)
	       PulseIndex = 3;
            LBF_PWMChannel_UpdatePulse (TIMER4, CHANNEL4, Pulse_Selection[PulseIndex]);
        }
        if (State_Switch2_IsOn() )
        {
            while (State_Switch2_IsOn()); // wait for release
            if ( ++PulseIndex == 4)
	       PulseIndex = 0;
            LBF_PWMChannel_UpdatePulse (TIMER4, CHANNEL4, Pulse_Selection[PulseIndex]);
        }

    }  // end while(1)
*/

return 0;
}




/***************************************************************END OF FILE****/
