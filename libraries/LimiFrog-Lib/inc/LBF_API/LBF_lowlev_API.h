/*******************************************************************************
 * LBF_lowlev_API.h
 ******************************************************************************/


/* Define to prevent recursive inclusion --------------*/
#ifndef __LBF_LOWLEV_API_H
#define __LBF_LOWLEV_API_H 


// --- Support Boolean type          ------------
#include <stdbool.h>
//allow using TRUE and FALSE in capital letters (LimiFrog legacy)
#define TRUE  true  
#define FALSE  false  


#include "stm32l4xx_hal.h"  //STM32 HAL Drivers 
 // pulls stm32l4xx_hal_conf.h --> stm32l4xx_hal_<ppp>.h --> .stm32l4xx_hal_def.h --> stm32l4xx.h

#include "LBF_lsm6ds3.h"

#include "LBF_global_variables.h"
#include "LBF_custom_types.h"
#include "LBF_pin_aliases.h"
#include "LBF_OnBoard_chip_aliases.h"
#include "LBF_Services.h"
#include "LBF_FLASH_lowlevAPI.h"
#include "LBF_GPIO_lowlevAPI.h"
#include "LBF_LED_Switches_lowlevAPI.h"
#include "LBF_OLED_lowlevAPI.h"
#include "LBF_PWR_lowlevAPI.h"
#include "LBF_I2CSensors_lowlevAPI.h"
#include "LBF_UART_lowlevAPI.h"
#include "LBF_Timer_lowlevAPI.h"
#include "LBF_ExtIT_lowlevAPI.h"
#include "LBF_ADC_lowlevAPI.h"
#include "LBF_Battery_lowlevAPI.h"

#include "LBF_ExtPort_lowlevAPI.h"

#endif /* __LBF_LOWLEV_API_H */

/*********************************END OF FILE****/

