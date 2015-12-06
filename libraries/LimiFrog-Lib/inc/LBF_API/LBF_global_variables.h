/*******************************************************************************
 * LBF_global_variables.h
 ******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GLOBAL_VARIABLES_H
#define __LBF_GLOBAL_VARIABLES_H


/**** Declarations of Global Variables accessed from different code modules  **/


/*   ------- Handles for Structures used by HAL API Functions   ------------- */

extern UART_HandleTypeDef huart1;   // initialized in LBF_UART1_Init.c

extern UART_HandleTypeDef huart3; // initialized in LBF_USART3_Init.c

extern I2C_HandleTypeDef hi2c1;     // initialized in LBF_I2C1_Init.c
extern I2C_HandleTypeDef hi2c2;     // initialized in LBF_I2C2_Init.c

extern SPI_HandleTypeDef hspi1;     // initialized in LBF_SPI1_Init.c
extern SPI_HandleTypeDef hspi3;     // initialized in LBF_SPI3_Init.c


extern TIM_HandleTypeDef htim1;     // initialized in LBF_Timer_lowlevAPI.c
extern TIM_HandleTypeDef htim2;     // initialized in LBF_Timer_lowlevAPI.c
extern TIM_HandleTypeDef htim3;     // ditto
extern TIM_HandleTypeDef htim4;     // ditto
extern TIM_HandleTypeDef htim5;     // ditto
extern TIM_HandleTypeDef htim6;     // ditto
extern TIM_HandleTypeDef htim7;     // ditto
extern TIM_HandleTypeDef htim8;     // ditto
extern TIM_HandleTypeDef htim15;    // ditto
extern TIM_HandleTypeDef htim16;    // ditto
extern TIM_HandleTypeDef htim17;    // ditto

extern USART_HandleTypeDef husart2; 	// initialized in LBF_ExtPort_Presets.c
extern UART_HandleTypeDef huart2; 	// initialized in LBF_ExtPort_Presets.c
extern UART_HandleTypeDef huart4; 	// initialized in LBF_ExtPort_Presets.c



#endif  /*__LBF_GLOBAL_VARIABLES_H*/

/***************************************************************END OF FILE****/
