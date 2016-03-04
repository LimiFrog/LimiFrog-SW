/**************************************************************************
 * User_Configuration.h
 *************************************************************************/

/* Define to prevent recursive inclusion --------------------------------*/
#ifndef __LBF_USER_CONFIG_H
#define __LBF_USER_CONFIG_H



/* ***************************************************************************
 *  --------               USER CONFIGURATION FILE          ---------------- *
 *  This file holds board configuration parameters defined by the user.      *
 *  She/he should set the parameters listed below according to her/his needs *
 * **************************************************************************/



// ============================================================================
//    OLED presence	
// ============================================================================

// Comment out next line if no OLED or not used. Uncomment if OLED is used :

#define USE_OLED  

   // WARNING:
   // this initializes OLED but powering on/off the screen is left to user 
   // code, using e.g. functions OLED_Switch_ON() and OLED_Switch_OFF()


// ============================================================================
//    Enable/Disable BlueTooth Low-Energy Functionality
// ============================================================================

// Comment out / Uncomment next line as needed :

#define ENABLE_BTLE

// Select here the required code to download in the BTLE module 
// Must be stored on the Data Flash - Would typically be put there by USB 
// Ignored if ENABLE_BTLE is undefined
#define  BTLE_CODE_FILENAME   "BTLE_H.BIN"

// Indicate here baudrate (bits/s) for exchanges over UART between STM32 and 
// application running on PAN1740.  
//  Does NOT affect baud rate used for booting PAN1740 over UART -- which 
//  must not be changed).
// Ignored if BTLE is not enabled
#define	UART_BTLE_BAUDRATE	 115200  	



// ============================================================================
//    EXTENSION PORT
// ============================================================================



    /******************************************************************
    *  CONFIGURATION OF EACH POSITION ON THE EXTENSION PORT           *
    *								      *
    *  Specify the type of interface you want to use on each position,*	
    *  selecting one of the indicated valid values.	              *
    ******************************************************************/


    // ===========================================================
    // Extension Port Position 11  (PB9)
    // --------------------------
    #define 	EXT_PORT_POS11_Function  	NONE  
	// Valid Values = 
	//	NONE 
	//	GPIO
        //      EXTI9_5
	//	I2C1_SDA	
	//	PWM_TIM4_CH4
//TODO Also cope with CAN_TX 
    // --------------------------

    #define 	EXT_PORT_POS11_GPIOtype		NA
	// Relevant only if former parameter is GPIO or in some cases EXTI (else: ignored)
	// Valid Values = 
 	//	NA     (not applicable)
	//	IN     (standard CMOS input) 
	//	IN_PU  (input with internal pull-up) - also applies to EXTI
	//	IN_PD  (input with internal pull-down) - also applies to EXTI 
	//	OUT    (standard CMOS push-pull output)
	//	OUT_OD (open-drain output)



    // ===========================================================
    // Extension Port Position 10  (PB8)
    // --------------------------
    #define 	EXT_PORT_POS10_Function  	NONE 
	// Valid Values = 
	//	NONE 
	//	GPIO
        //      EXTI9_5
	//	I2C1_SCL
	//	PWM_TIM4_CH3
//TODO Also cope with CAN_RX 
		
    #define 	EXT_PORT_POS10_GPIOtype  	NA
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 9  -  Not configurable (GND)
    // --------------------------
    
    #define 	EXT_PORT_POS9_Function  	NONE 
	// Valid Values = 
	//	NONE 

    #define 	EXT_PORT_POS9_GPIOtype  	NA 
	// Valid values: 
	// NA

    // ===========================================================
    // Extension Port Position 8  (PA0)
    // --------------------------
    #define 	EXT_PORT_POS8_Function  	NONE
    	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI0
	//	UART2_CTS
	//	UART4_TX
	//	PWM_TIM2_CH1
	//	ADC12_IN_5
	// 	OPAMP1_VINP

    #define 	EXT_PORT_POS8_GPIOtype  	NA
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 7  (PA1)
    // --------------------------
    #define 	EXT_PORT_POS7_Function  	NONE 
	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI1
	//	UART2_RTS
	//	UART4_RX
	//	PWM_TIM2_CH2
	//	ADC12_IN_6
	//	OPAMP1_VINM

    #define 	EXT_PORT_POS7_GPIOtype  	NA 
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 6  (reserved for VCC_LDO)
    // --------------------------
    #define 	EXT_PORT_POS6_Function  	NONE
	// Valid Values = 
	//	NONE 
	//	VCC_LDO  (--> regulated 3.3V)


    // ===========================================================
    // Extension Port Position 5  (PA2)
    // --------------------------
    #define 	EXT_PORT_POS5_Function  	NONE   
	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI2
	//	UART2_TX
	//	SPI_MOSI      (over USART2 TX)
	//	PWM_TIM2_CH3
	//	ADC12_IN_7

    #define 	EXT_PORT_POS5_GPIOtype  	NA 
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 4  (PA3)
    // --------------------------
    #define 	EXT_PORT_POS4_Function  	NONE  
	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI3
	//	UART2_RX   
	//	SPI_MISO      (over USART2 RX)
	//	PWM_TIM2_CH4
	//	ADC12_IN_8
	//	OPAMP1_OUT  

	// Note - if OPAMP1 output needs to go to ADC12,
	//  select ADC12_IN_8 rather than OPAMP1_OUT

    #define 	EXT_PORT_POS4_GPIOtype  	NA
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 3  (PA4)
    // --------------------------
    #define 	EXT_PORT_POS3_Function  	NONE
	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI4
	//	SPI_CK      (over USART2 CLK)
	//	PWM_LPTIM2
	//	ADC12_IN_9
//TODO also cope with DAC1_OUT

    #define 	EXT_PORT_POS3_GPIOtype  	NA
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 2  (PA6)
    // --------------------------
    // CAUTION: Both a STM32 GPIO and a BLE GPIO are routed to this 
    //  position - One must always be kept input to avoid conflicts
    //
    #define 	EXT_PORT_POS2_Function  	NONE 
	// Valid Values = 
	//	NONE 
	//	GPIO
	//	EXTI9_5
	//	SPI_nCS   
	//	PWM_TIM16_CH1

    #define 	EXT_PORT_POS2_GPIOtype  	NA
	// Valid values (only apply to GPIO and partly to EXTI)
	// NA/IN/IN_PU/IN_PD/OUT/OUT_OD


    // ===========================================================
    // Extension Port Position 1
    // --------------------------
    // Dedicated to Mic. Out monitoring

    #define 	EXT_PORT_POS1_Function  	NONE 
	// Valid Values = 
	//	NONE 

    #define 	EXT_PORT_POS1_GPIOtype  	NA 
	// Valid values: 
	// NA

   

#endif /* __LBF_USER_CONF_H */

/***************************************************************END OF FILE****/

