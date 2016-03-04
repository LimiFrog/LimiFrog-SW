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


// For each timer used, need to declare a handle of type TIM_HandleTYpeDef
// Global variable to use them in e.g. IRQ handlers 
TIM_HandleTypeDef htim2; 
TIM_HandleTypeDef htim4; 


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


uint32_t	CurrentTime ;
uint8_t		i;
uint8_t		Pulse_Index = 0 ;

uint32_t const	PWM_Period_ms =  100; 
uint32_t const	Pulse_Duration_ms[3] =
		{	PWM_Period_ms /4,
			PWM_Period_ms /2,		
			PWM_Period_ms *3 /4  };


/* ==  Body     ======================================== */


    LBF_Led_OFF();
    LBF_Delay_ms(1000);
    

    // *** Free running timer demo section *************************
    // ==>
    //     Flash LED every 0.5s with duration detected by 
    //     polling free running timer


    // ==  First, using a 1ms resolution  ==========================

    // Use Timer2 (a 32-bit timer) with 1ms resolution- 
    LBF_Timer_Setup( &htim2, TIMER2, TIMER_UNIT_MS, 10000);  
	//Counter wraps around after say 10s - not important in this example

    // Start timer2 (no IT)
    HAL_TIM_Base_Start(&htim2);

    i = 0;
    do 
    {
        // Read counter value
        CurrentTime =  __HAL_TIM_GetCounter(&htim2);
    
        if ( CurrentTime % 500 == 0)  	//Every 0.5s (500ms)...
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
    LBF_Timer_Setup( &htim2, TIMER2, TIMER_UNIT_US, 10000000);  
	//Counter to wrap around after say 10s - not important in this example

    // Start timer2 (no IT)
    HAL_TIM_Base_Start(&htim2);

    i = 0;
    do 
    {
        // Read counter value
        CurrentTime =  __HAL_TIM_GetCounter(&htim2);
    
        if ( CurrentTime % 500000 == 0)  	//Every 0.5s (500000us)...
        {
	     i++;
             LBF_Led_ON();		// ...Flash LED
	     LBF_Delay_ms(100);
             LBF_Led_OFF();
        }
    }  while (i!=8);  // to get 8 flashes

    HAL_TIM_Base_Stop(&htim2);

    //End Of Free Running Timer Demo


    // ===  Pause       =============================================
    HAL_TIM_Base_Stop(&htim2);
    LBF_Delay_ms(1000);



    // *** Timer-based interrupt generation demo section ************

    LBF_Timer_Setup( &htim4, TIMER4, TIMER_UNIT_MS, 100);  //Configure Timer4 for 0.1s period


   // Set timer4 to fire IT when elapsed (so, every 0.1s)
   // Then wait for 5sec.
   // Series of IT fire while waiting, in IT handler (cf stm32_it.c) LED gets toggled
   // => Should see LED blinking at 20Hz during these 4 seconds (so 20 flashes +-1)
   //
    LBF_Timer_Start_ITout( &htim4 );  //Start Timer4 with IT generation
    LBF_Delay_ms(4000);  // ITs are firing during this time

    LBF_Timer_Stop( &htim4 );  //Now stop Timer4 

 

    // *** PWM demo section  (PWM on Timer4, Channel 4)  *******************

    // Set-up Timer 4 and specify period 
    LBF_Timer_Setup( &htim4, TIMER4, TIMER_UNIT_MS, PWM_Period_ms );  // PWM_Period = constant specified above


    // Set-up Channel 4 of Timer 4 and specify high pulse duration (duty cycle = pulse / period)
    LBF_PWMchannel_Setup( &htim4, CHANNEL4, Pulse_Duration_ms[0]);  //100ms pulse  --> 20% duty cycle   

    // Launch PWM
    LBF_PWMchannel_Start( &htim4, CHANNEL4 );  
    // available on Ext. Conn. Position 11 if enabled in User_Configuration.h

 
    while(1)
    {	
        // Now we will also get LED to follow state of PWM 
        // by checking value present on position 10 of Connector 
        // (this requires the #define POS11_IS_PWM_TIM4_CH4  in User_Configuration.h )
        if ( IS_GPIO_SET( CONN_POS11_PORT, CONN_POS11_PIN ) )
        {
           LBF_Led_ON();
        }
        else
        {
            LBF_Led_OFF();
        }


        // ...and we will changethe duty cycle when user presses the side-push button 
        if (LBF_State_Switch1_IsOn() )
        {   
            while (LBF_State_Switch1_IsOn()); // wait for release
            if ( ++Pulse_Index == 3)
	       Pulse_Index = 0;
            LBF_PWMchannel_UpdatePulse (&htim4, CHANNEL4, Pulse_Duration_ms[Pulse_Index]);
        }


    }  // end while(1)



}




/***************************************************************END OF FILE****/
