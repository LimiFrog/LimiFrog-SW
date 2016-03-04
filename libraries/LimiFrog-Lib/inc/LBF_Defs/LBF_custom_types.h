/*******************************************************************************
 * LBF_custom_types.h
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_CUSTOM_TYPES_H
#define __LBF_CUSTOM_TYPES_H


#include <stdint.h>
 // to allow using uint32_t etc. below while keeping this header self-sufficient


/* Exported types ------------------------------------------------------- */


// RETURN STATUS type:  ReturnStatus_t :
typedef enum {
  NOK = 0,
  OK = 1
}    
ReturnStatus_t;


// -- Structures for holding extension port configuration parameters :

typedef enum
{
    NONE	,
    GPIO	,
    EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI9_5, EXTI15_10,
    PWM_TIM4_CH4, PWM_TIM4_CH3,
    PWM_TIM2_CH4, PWM_TIM2_CH3, PWM_TIM2_CH2, PWM_TIM2_CH1,
    PWM_LPTIM2,
    PWM_TIM16_CH1,
    I2C1_SDA, I2C1_SCL,
    SPI_CK, SPI_MISO, SPI_MOSI, SPI_nCS,
    UART2_TX, UART2_RX, UART2_RTS, UART2_CTS,
    UART4_TX, UART4_RX,
    ADC12_IN_5, ADC12_IN_6, ADC12_IN_7, ADC12_IN_8, ADC12_IN_9,
    OPAMP1_VINP, OPAMP1_VINM, OPAMP1_VOUT,
    VCC_LDO	
} LBF_Function_t;

typedef enum {
  NA     = 0,	// not applicable
  IN     = 1,	// standard input
  IN_PU  = 2,	// input with weak pull-up
  IN_PD  = 3,	// input with weak pull-down
  OUT    = 4,	// standard CMOS push-pull output
  OUT_OD = 5	// open-drain output
/*
  IT_RISING = 6,   // external interrupt, rising-edge triggered
  IT_FALLING = 7   // external interrupt, falling-edge triggered
*/
}    
LBF_GPIO_Conf_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos11_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos10_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos9_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos8_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos7_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos6_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos5_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos4_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos3_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos2_t;

typedef struct
{
    LBF_Function_t	Function ;
    LBF_GPIO_Conf_t	GPIO_Conf;
} Pos1_t;


typedef struct
{
    uint32_t	UART2_SPI_Baudrate ;  // relevant only if USART2/SPI used
    uint32_t	UART4_Baudrate ;      // relevant only if UART4 used

    Pos11_t	Pos11;
    Pos10_t	Pos10;
    Pos9_t	Pos9;
    Pos8_t	Pos8;
    Pos7_t	Pos7;
    Pos6_t	Pos6;
    Pos5_t	Pos5;
    Pos4_t	Pos4;
    Pos3_t	Pos3;
    Pos2_t	Pos2;
    Pos1_t	Pos1;
} LBF_ExtPortConfig_t;



// -- Structure for holding BTLE module initialization control parameters :

typedef struct
{
    bool        Enable ;  
    char *  	FW_Filename;
    uint32_t	UART_BaudRate;
} BTLE_Init_t;





#endif  /*__LBF_CUSTOM_TYPES_H*/

/***************************************************************END OF FILE****/
