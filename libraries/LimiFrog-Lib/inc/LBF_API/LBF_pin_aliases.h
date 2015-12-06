/*******************************************************************************
 * LBF_pin_aliases.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __LBF_PIN_ALIASES_H
#define __LBF_PIN_ALIASES_H

#include "stm32l4xx.h"  //to allow using Cortex-M register names while keeping this header self-sufficient


/**  P I N   A L I A S E S  *********************************************/


/*  ==== Power Management ============================================== */


/* --- LTC3533 PMIC ---*/

// HPWR, STM32 output
#ifdef __LBF_LEGACY  
  #define HPWR_PIN		GPIO_PIN_2
  #define HPWR_PORT		GPIOC
#else
  #define HPWR_PIN		GPIO_PIN_2
  #define HPWR_PORT		GPIOD
#endif

// BUCK_ON, STM32 output
#define	BUCK3V_ON_PIN		GPIO_PIN_6
#define BUCK3V_ON_PORT		GPIOB

// LDO_ON, STM32 output -- did not exist prior to LimiFrog0.1
#ifndef __LBF_LEGACY  
  #define LDO_ON_PIN		GPIO_PIN_2
  #define LDO_ON_PORT		GPIOC
#endif

// ONOFF_STAT (debounced On/Off push-button), STM32 input
#define	ONOFF_STAT_PIN		GPIO_PIN_13
#define ONOFF_STAT_PORT		GPIOC


/* --- TPS22929 Power Switch (DC-DC Boost Converter On/Off) ---*/

// BOOSTCONV_EN,  STM32 output
#define	VDDH_EN_PIN	GPIO_PIN_0
#define VDDH_EN_PORT	GPIOC


/*  ==== LEDs  ======================================================== */

// STM32_LED,  STM32 output
#define	STM32_LED_PIN	GPIO_PIN_3
#define STM32_LED_PORT	GPIOC


/*  ==== Selection Switches  =========================================== */

// SWITCH1,  STM32 input
#define	SWITCH1_PIN	GPIO_PIN_15
#define SWITCH1_PORT	GPIOA

// SWITCH2,  STM32 input
#define	SWITCH2_PIN	GPIO_PIN_8
#define SWITCH2_PORT	GPIOC


/*  ==== I2C1   ======================================================== */

// SCL, STM32 output, Open-Drain
// SDA, STM32 output/input, Open-Drain
#define	I2C1_SCL_PIN	GPIO_PIN_8
#define	I2C1_SDA_PIN	GPIO_PIN_9
#define	I2C1_PORT	GPIOB
// I2C1 available through extension port
// This def redundant with ext. connector definitions (PB8/8 on pos. 9/10)


/*  ==== I2C2   ======================================================== */

// SCL, STM32 output, Open-Drain
// SDA, STM32 output/input, Open-Drain
#define	I2C2_SCL_PIN	GPIO_PIN_10
#define	I2C2_SDA_PIN	GPIO_PIN_11
#define	I2C2_PORT	GPIOB


/*  ==== SPI1   ========================================================= */

// PA5 - CK, STM32 output, Std CMOS
// PA6 - MISO, STM32 input
// PA7 - MOSI, STM32 output, Std CMOS
#define	SPI1_SCK_PIN	GPIO_PIN_5
#define	SPI1_MISO_PIN	GPIO_PIN_6  // Not connected to OLED
#define	SPI1_MOSI_PIN	GPIO_PIN_7
#define	SPI1_PORT	GPIOA


/*  ==== SPI3   ========================================================= */

// PB3 - CK, STM32 output, Std CMOS
// PB4 - MISO, STM32 input
// PB5 - MOSI, STM32 output, Std CMOS
#define	SPI3_SCK_PIN	GPIO_PIN_3
#define	SPI3_MISO_PIN	GPIO_PIN_4
#define	SPI3_MOSI_PIN	GPIO_PIN_5
#define	SPI3_PORT	GPIOB


/*  ==== UART1  ======================================================= */

#ifdef __LBF_LEGACY
  #define	UART1_TX_PIN	GPIO_PIN_9
  #define	UART1_RX_PIN	GPIO_PIN_10
  #define	UART1_PORT	GPIOA
#else
  // UART1 no longer available (BLE now controlled from UART3)
#endif


/*  ==== USART 2  ======================================================= */

#ifdef __LBF_LEGACY
  #define	USART2_TX_PIN	GPIO_PIN_2
  #define	USART2_RX_PIN	GPIO_PIN_3
  #define	USART2_CK_PIN	GPIO_PIN_4
  #define	USART2_PORT	GPIOA
#else
  // USART2 available through CONN_POS2/3/4_PIN 
#endif


/*  ==== UART 3  ======================================================= */

#define	UART3_TX_PIN	GPIO_PIN_10
#define	UART3_TX_PORT	GPIOC
#define	UART3_RX_PIN	GPIO_PIN_11
#define	UART3_RX_PORT	GPIOC

#ifndef __LBF_LEGACY  // were not available previously
  #define	UART3_CTS_PIN	GPIO_PIN_14
  #define	UART3_CTS_PORT	GPIOB
  #define	UART3_RTS_PIN	GPIO_PIN_13
  #define	UART3_RTS_PORT	GPIOB
#endif


/*  ==== DATA FLASH (excl SPI)   ======================================== */
// PB7 = nCS
#define FLASH_CS_PIN	GPIO_PIN_7
#define FLASH_CS_PORT	GPIOB


/*  ==== BTLE (excl UART)       ======================================== */
// PC9 = BT_RST (active high)
#define BT_RST_PIN	GPIO_PIN_9
#define BT_RST_PORT	GPIOC


/*  ==== LSM6DS3 ACCEL/GYRO     ======================================== */

// interrupt INT1_ACC_GYR (INT2_ACC_GYR) to STM32

#ifdef __LBF_LEGACY  
  #define INT1_ACC_GYR_PIN	GPIO_PIN_15
  #define INT1_ACC_GYR_PORT	GPIOB
  #define INT2_ACC_GYR_PIN	GPIO_PIN_6
  #define INT2_ACC_GYR_PORT	GPIOC
#else 
  #define INT1_ACC_GYR_PIN	GPIO_PIN_6
  #define INT1_ACC_GYR_PORT	GPIOC
#endif


/*  ==== LIS3MDL MAGNETO        ======================================== */

// interrupt IRQ_MAG to STM32

#ifdef __LBF_LEGACY  
  #define IRQ_MAG_PIN	GPIO_PIN_14
  #define IRQ_MAG_PORT	GPIOB
#else
  #define IRQ_MAG_PIN	GPIO_PIN_15
  #define IRQ_MAG_PORT	GPIOB
#endif


/*  ==== VL6180X ALS/PROXIMITY/DISTANCE        ========================= */

// interrupt IRQ_ALS_PROX to STM32

#ifdef __LBF_LEGACY  
  #define IRQ_ALS_PROX_PIN	GPIO_PIN_0
  #define IRQ_ALS_PROX_PORT	GPIOA
#else
  #define IRQ_ALS_PROX_PIN	GPIO_PIN_2
  #define IRQ_ALS_PROX_PORT	GPIOB
#endif


/*  ==== LPS25H PRESSURE/TEMP SENSOR           ========================= */

// interrupt IRQ_PRESS to STM32

#define IRQ_PRESS_PIN	GPIO_PIN_12
#define IRQ_PRESS_PORT	GPIOB


/*  ==== BATTERY                 ======================================== */

// BAT_ADC_MEAS_ENB from STM32 to enable measurement
// BAT_ADC_MEAS to STM32 to capture (scaled) battery voltage

#define BATT_ADC_MEAS_PIN	GPIO_PIN_1
#define BATT_MEAS_ENB_PIN	GPIO_PIN_7
#define BATT_PORT		GPIOC


/*  ==== MICROPHONE              ======================================== */

// MIC_ANA, analog output from microphone to STM32

#define MIC_ANA_PIN	GPIO_PIN_0
#define MIC_ANA_PORT	GPIOB


/*  ==== OLED (excl SPI)         ======================================== */
// OLED_RS, OLED_NCS, OLED_RESET  -- STM32 outputs
#define	OLED_RS_PIN		GPIO_PIN_4
#define OLED_RS_PORT		GPIOC
#define	OLED_CS_PIN		GPIO_PIN_5
#define OLED_CS_PORT		GPIOC
#define	OLED_RESET_PIN		GPIO_PIN_1
#define OLED_RESET_PORT		GPIOB

/*  ==== USB                       ======================================== */
// DP, DM differential USB signal
// VBUS_SENSE input to sense presence of 5V on USB_PWR
// (ID defined by OTG not used here as only offering device mode)
#define	USB_DM_PIN		GPIO_PIN_11
#define	USB_DP_PIN		GPIO_PIN_12
#define	VBUS_SENSE_PIN		GPIO_PIN_9
#define	USB_PORT		GPIOA


/*  ==== EXTENSION CONNECTOR      ======================================== */

// Position 1
#ifdef __LBF_LEGACY  
  #define 	CONN_POS1_PIN		GPIO_PIN_5
  #define 	CONN_POS1_PORT		GPIOA
#else
  #define	CONN_POS1_PIN		GPIO_PIN_6
  #define 	CONN_POS1_PORT		GPIOA
#endif

// Position 2
#ifdef __LBF_LEGACY  
  #define	CONN_POS2_PIN		GPIO_PIN_6
  #define 	CONN_POS2_PORT		GPIOA
#else
  // CAUTION if using: Pos2 normally only used to monitor Mic Output
  #define	CONN_POS2_PIN		GPIO_PIN_0
  #define 	CONN_POS2_PORT		GPIOB
#endif

// Position 3
#ifdef __LBF_LEGACY  
  #define	CONN_POS3_PIN		GPIO_PIN_7
  #define 	CONN_POS3_PORT		GPIOA
#else
  #define	CONN_POS3_PIN		GPIO_PIN_4
  #define 	CONN_POS3_PORT		GPIOA
#endif

// Position 4
#ifdef __LBF_LEGACY  
  #define 	CONN_POS4_PIN		GPIO_PIN_0
  #define 	CONN_POS4_PORT		GPIOB
  #define 	MICOUT_PIN		GPIO_PIN_0  // PBO captures sound from microphone
  #define 	MICOUT_PORT		GPIOB
#else
  #define 	CONN_POS4_PIN		GPIO_PIN_3
  #define 	CONN_POS4_PORT		GPIOA
#endif

// Position 5
#ifdef __LBF_LEGACY  
  #define 	CONN_POS5_PIN		GPIO_PIN_10
  #define 	CONN_POS5_PORT		GPIOC
#else
  #define 	CONN_POS5_PIN		GPIO_PIN_2
  #define 	CONN_POS5_PORT		GPIOA
#endif

// Position 6
#ifdef __LBF_LEGACY  
  #define 	CONN_POS6_PIN		GPIO_PIN_11
  #define 	CONN_POS6_PORT		GPIOC
#else
  // Pos.6 now VCC_LDO 
#endif

// Position 7
#ifdef __LBF_LEGACY  
  #define 	CONN_POS7_PIN		GPIO_PIN_12
  #define 	CONN_POS7_PORT		GPIOC
#else
  #define 	CONN_POS7_PIN		GPIO_PIN_1
  #define 	CONN_POS7_PORT		GPIOA
#endif

// Position 8
#ifdef __LBF_LEGACY  
  // VCC (3V)
#else
  #define 	CONN_POS8_PIN		GPIO_PIN_0
  #define 	CONN_POS8_PORT		GPIOA
#endif

// Position 9
#define		CONN_POS9_PIN		GPIO_PIN_8
#define 	CONN_POS9_PORT		GPIOB

// Position 10
#define		CONN_POS10_PIN		GPIO_PIN_9
#define 	CONN_POS10_PORT		GPIOB

// Pos11: GND



#endif /*__LBF_PIN_ALIASES_H*/

/***************************************************************END OF FILE****/
