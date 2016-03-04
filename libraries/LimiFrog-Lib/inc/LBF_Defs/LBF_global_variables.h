/*******************************************************************************
 * LBF_global_variables.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GLOBAL_VARIABLES_H
#define __LBF_GLOBAL_VARIABLES_H


/**** Declarations of Global Variables accessed from different code modules  **/



/*   ------- Handles for Structures used by HAL API Functions   ------------- */


/*******************************************************************************
*                                                                              *
*  The HAL library uses structures to store the parameters used to initialize  *
*   the STM32 on-chip peripherals.  These structures are pointed by "handles". *
*  It may be necessary to access these structures from different locations     *
*  in the overall code, so declaring them as global is handy.                  *
*                                                                              *
*  Some peripherals are almost always used in the LimiFrog board setup.        *
*  Therefore the declaration of the handles pertaining to these peripherals    *
*  is done in this header file that can get included in all source code files, *
*  thus sparing the need to redeclare these variables every time.              *
*                                                                              *
*  Handles to other peripherals (e.g. Timer etc.) must be declared on a case   *
*  by case basis.                                                              *
*                                                                              *
*******************************************************************************/


// I2C2: used on LimiFrog for access to all sensors
extern I2C_HandleTypeDef hi2c2;     // defined in LBF_I2C2_Init.c

// SPI1: used on LimiFrog for access to the OLED display 
extern SPI_HandleTypeDef hspi1;     // defined in LBF_SPI1_Init.c

// SPI3: used on LimiFrog for access to the Data Flash
extern SPI_HandleTypeDef hspi3;     // defined in LBF_SPI3_Init.c

// UART3: used on LimiFrog for access to the BlueTooth4.1 (BLE) module
extern UART_HandleTypeDef huart3;   // defined in LBF_USART3_Init.c

// PCD for access to USB in device mode 
extern PCD_HandleTypeDef hpcd;      // defined in usbd_conf.c



#endif  /*__LBF_GLOBAL_VARIABLES_H*/

/***************************************************************END OF FILE****/
