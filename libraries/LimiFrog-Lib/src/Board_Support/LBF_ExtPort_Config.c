/*************************************************************************
 * LBF_ExtPort_Presets.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"
#include "LBF_ExtPort_Config.h"
#include "LBF_User_Conf.h"   // in user's source files directory

// global variable used by USART HAL functions 
I2C_HandleTypeDef 	hi2c1; 	 
USART_HandleTypeDef 	husart2;  	
UART_HandleTypeDef 	huart4;  	
UART_HandleTypeDef 	huart2;  	


// Local Functions internal to this file
static void LBF_ExtPortPreset_VCCLDO (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_I2C1 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_SPIoverUSART2 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_UART2 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_UART4 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_GPIO (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_PWMout (LBF_ExtPortConfig_t* pExtPortConfig);

static void LBF_ExtPortPreset_CAN (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_ADC (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_DAC (LBF_ExtPortConfig_t* pExtPortConfig);


//void LBF_ExtPortConfig (void)
void LBF_ExtPortConfig (LBF_ExtPortConfig_t* pExtPortConfig)
{
/*
LBF_ExtPortConfig_t   ExtPortConfig ;
LBF_ExtPortConfig_t* pExtPortConfig = &ExtPortConfig;
*/

	// Retrieve user Configuration
	//LBF_User_Conf(pExtPortConfig);

	LBF_ExtPortPreset_VCCLDO( pExtPortConfig );
	    // start with VCC_LDO in case system connected to extension port
	    // should get VCC before getting a voltage on its input pins

	LBF_ExtPortPreset_I2C1( pExtPortConfig );
	LBF_ExtPortPreset_SPIoverUSART2( pExtPortConfig );
	LBF_ExtPortPreset_UART4( pExtPortConfig );
	LBF_ExtPortPreset_UART2( pExtPortConfig );
	LBF_ExtPortPreset_GPIO( pExtPortConfig );
	LBF_ExtPortPreset_PWMout( pExtPortConfig );

	LBF_ExtPortPreset_CAN ( pExtPortConfig );
	LBF_ExtPortPreset_ADC ( pExtPortConfig );
	LBF_ExtPortPreset_DAC ( pExtPortConfig );

}


/*******************************************************************************
* Function: LBF_ExtPortPreset_VCCLDO
* Description  : Enable the LDO if required to provide VCC_LDO (3.3V regulated
		  voltage) on pin position 6
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_VCCLDO (LBF_ExtPortConfig_t* pExtPortConfig)
{
    // Is VCC_LDO enabled on extension port?
    if ( pExtPortConfig->Pos6.Function == VCC_LDO)
    {
 	GPIO_HIGH( LDO_ON_PORT, LDO_ON_PIN);
    }
}


/*******************************************************************************
* Function: LBF_ExtPortPreset_I2C1
* Description  : Configures IOs enabled as I2C pins on extension connector 
* 		 and initializes I2C1 
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_I2C1 (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;


    // Is I2C enabled on extension port?
    if (  (pExtPortConfig->Pos10.Function == I2C1_SDA)
	   || (pExtPortConfig->Pos9.Function == I2C1_SCL) )

    {

	// ---  IO configuration : SCL on Pos.9, SDA on Pos.10

	__I2C1_CLK_ENABLE();

	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    	if (pExtPortConfig->Pos10.Function == I2C1_SDA)  
	{
   	    GPIO_InitStruct.Pin = CONN_POS10_PIN;
	    GPIO_InitStruct.Pull = GPIO_PULLUP; //ext pull-up still required though
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 
    	    HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct);
	}
    	if (pExtPortConfig->Pos9.Function == I2C1_SCL)  
          //multi-master not supported, no need for Open-drain SCL
	{
   	    GPIO_InitStruct.Pin |= CONN_POS9_PIN;
	    GPIO_InitStruct.Pull = GPIO_NOPULL; 
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; 
    	    HAL_GPIO_Init(CONN_POS9_PORT, &GPIO_InitStruct);
	}
    

        // ---  Peripheral initialization : ------

        // Following settings assume I2C2 core clock (=APB1 clock in Default LimiFrog setting)
        // is 20MHz and target I2C2 speed is 400KHz
        // TODO Find a way to ensure I2C2 clock remains 8MHz if STM32L4 core clock modified
        // TODO Check vs MXCube recommended settings

        #define I2C1_PRESC	0x1   // tPRESC = (PRESC+1) x tI2C2CLK  -- 0.1us (10MHz)
        #define I2C1_SCLL  	0xB   // tSCLL = (SCLL+1) x tPRESC  --  1.2us
        #define I2C1_SCLH 	0x4   // tSCLH = (SCLH+1) x tPRESC  --  0.5us
        #define I2C1_SDADEL 	0x2   // tSDADEL = SDADEL x tPRESC  -- 0.2us 
        #define I2C1_SCLDEL	0x4   // tSCLDEL = (SCLDEL+1) x tPRESC  -- 0.5us
        // I2C speed: 400KHz,
        //    defined by tSCL = tSCLL + tSCLH + tSYNC1 + tSYNC2 ~ 2.5us  (400KHz)
        //     where tSYNC1 and tSYNC2 are delays introduced by the analog and/or 
        //     digital noise filters and resync mechasinsms 
        //     -- refer to Ref Manual I2C section     (I2C master mode)
        // SCLDEL defines setup time: SDA stable before SCL rising edge
        // SDADEL defines hold time: SDA stable after SCL *falling* edge (as per I2C spec?)


	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = ((uint32_t)I2C1_PRESC ) << 28
		    | ((uint32_t)I2C1_SCLDEL ) << 20
		    | ((uint32_t)I2C1_SDADEL ) << 16
		    | ((uint32_t)I2C1_SCLH ) << 8
		    | ((uint32_t)I2C1_SCLL )  ;
      	// = Contents of the I2C_TIMINGR_register value
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED; 
	HAL_I2C_Init(&hi2c1);

    } // end if *pExtPortConfig....

}



/*******************************************************************************
* Function: LBF_ExtPortPreset_SPIoverUSART2
* Description  : Configures IOs enabled as SPI pins on extension connector 
* 		 and initializes USART2 for use as SPI interface
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_SPIoverUSART2 (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;


    // Is SPI enabled on extension port?
    if (  (pExtPortConfig->Pos5.Function == SPI_MOSI)
	   || (pExtPortConfig->Pos4.Function == SPI_MISO) 
	   || (pExtPortConfig->Pos3.Function == SPI_CK) 
	   || (pExtPortConfig->Pos1.Function == SPI_nCS) )
    {

	// ---  IO configuration : SPI implemented using a specific mode of USART2


        if (pExtPortConfig->Pos1.Function == SPI_nCS)    // Chip Select
        {
    	    GPIO_InitStruct.Pin = CONN_POS1_PIN; 
    	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    	    HAL_GPIO_Init(CONN_POS1_PORT, &GPIO_InitStruct);
    	    // Initialize nCS to inactive state
   	    GPIO_HIGH(CONN_POS1_PORT, CONN_POS1_PIN);
	}

	__USART2_CLK_ENABLE();

        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL; 
        GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

        if (pExtPortConfig->Pos5.Function == SPI_MOSI)   // MOSI / USART2_TX
        {
    	    GPIO_InitStruct.Pin = CONN_POS5_PIN; 
    	    HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct);
	}
        if (pExtPortConfig->Pos4.Function == SPI_MISO)   // MISO / USART2_RX
        {
    	    GPIO_InitStruct.Pin = CONN_POS4_PIN; 
    	    HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct);
	}
        if (pExtPortConfig->Pos3.Function == SPI_CK)     // SCK / USART2_CLK
        {
    	    GPIO_InitStruct.Pin = CONN_POS3_PIN; 
    	    HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct);
	}

 
        // ---  Peripheral initialization : ------

        husart2.Instance = USART2;
        husart2.Init.BaudRate = pExtPortConfig->UART2_SPI_Baudrate;    
        husart2.Init.WordLength = USART_WORDLENGTH_8B;  
        husart2.Init.StopBits = USART_STOPBITS_1;
        husart2.Init.Parity = USART_PARITY_NONE;
        husart2.Init.Mode = USART_MODE_TX_RX;
        husart2.Init.CLKPolarity = USART_POLARITY_LOW;
        husart2.Init.CLKPhase = USART_PHASE_1EDGE;
        husart2.Init.CLKLastBit = USART_LASTBIT_ENABLE;
        HAL_USART_Init(&husart2);

        // SPI transmission is MSB first
        // MSBfirst option available from STM32-L4 ...but not offered in 
        //   HAL USART API (only with UART API! ...so do it directly at register level
        husart2.Instance->CR1 &= 0xFFFFFFFE;  
		// disable USART2 = clear bit[0] (UE) in Control Reg. 1
        husart2.Instance->CR2 |= 0x00080000;  
		//  MSB first = set bit [19] (MSBFIRST)in Control Reg. 2
        husart2.Instance->CR1 |= 0x00000001;  
		// enable back USART2 = set bit[0] (UE) in Control Reg. 1

    }  // end if *pExtPortConfig......
}



/*******************************************************************************
* Function: LBF_ExtPortPreset_UART4
* Description  : Configures IOs enabled as UART4 pins on extension connector 
* 		 and initializes UART4 for use as SPI interface
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_UART4 (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;


    // Is UART4 enabled on extension port?
    if (  (pExtPortConfig->Pos7.Function == UART4_RX)
	   || (pExtPortConfig->Pos8.Function == UART4_TX) )
    {
	// ---  IO configuration : SPI implemented using a specific mode of USART2

	__UART4_CLK_ENABLE();

        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP; 
        GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;

        if (pExtPortConfig->Pos7.Function == UART4_RX)   // UART4 RX
        {
    	    GPIO_InitStruct.Pin = CONN_POS7_PIN; 
    	    HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct);
	}
        if (pExtPortConfig->Pos8.Function == UART4_TX)   // UART4 TX
        {
    	    GPIO_InitStruct.Pin = CONN_POS8_PIN; 
    	    HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct);
	}

 
        // ---  Peripheral initialization : ------

        huart4.Instance = UART4;
        huart4.Init.BaudRate = pExtPortConfig-> UART4_Baudrate;    
        huart4.Init.WordLength = UART_WORDLENGTH_8B;  
        huart4.Init.StopBits = UART_STOPBITS_1;
        huart4.Init.Parity = UART_PARITY_NONE;
        huart4.Init.Mode = UART_MODE_TX_RX;
        huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE; 
        huart4.Init.OverSampling = UART_OVERSAMPLING_16;
        HAL_UART_Init(&huart4);

    }  // end if *pExtPortConfig......
}


/*******************************************************************************
* Function: LBF_ExtPortPreset_UART2
* Description  : Configures IOs enabled as UART2 pins on extension connector 
* 		 and initializes UART2 for use as SPI interface
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_UART2 (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;
bool HwFlowCtrl = false;

    // Is UART2 enabled on extension port?
    if (  (pExtPortConfig->Pos5.Function == UART2_TX)	// TX
	   || (pExtPortConfig->Pos4.Function == UART2_RX) // RX
	   || (pExtPortConfig->Pos8.Function == UART2_CTS) // optional CTS
	   || (pExtPortConfig->Pos7.Function == UART2_RTS) )  // optional RTS
    {

	// ---  IO configuration 

	__USART2_CLK_ENABLE();

        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL; 
        GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

        if (pExtPortConfig->Pos5.Function == UART2_TX)   // UART2_TX
        {
    	    GPIO_InitStruct.Pin = CONN_POS5_PIN; 
    	    HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct);
	}
        if (pExtPortConfig->Pos4.Function == UART2_RX)   // UART2_RX
        {
    	    GPIO_InitStruct.Pin = CONN_POS4_PIN; 
    	    HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct);
	}
        if (pExtPortConfig->Pos8.Function == UART2_CTS)   // UART2 CTS
        {
    	    GPIO_InitStruct.Pin = CONN_POS8_PIN; 
    	    HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct);
	    HwFlowCtrl = true;
	}
        if (pExtPortConfig->Pos7.Function == UART2_RTS)   // UART2 RTS
        {
    	    GPIO_InitStruct.Pin = CONN_POS7_PIN; 
    	    HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct);
	    HwFlowCtrl = true;
	}

 
        // ---  Peripheral initialization : ------

        huart2.Instance = USART2;
        huart2.Init.BaudRate = pExtPortConfig-> UART2_SPI_Baudrate;    
        huart2.Init.WordLength = UART_WORDLENGTH_8B;  
        huart2.Init.StopBits = UART_STOPBITS_1;
        huart2.Init.Parity = UART_PARITY_NONE;
        huart2.Init.Mode = UART_MODE_TX_RX;
    	if (HwFlowCtrl)
   	{
            huart2.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS; 
   	}
	else
   	{
            huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; 
   	}
        huart2.Init.OverSampling = UART_OVERSAMPLING_16;
        HAL_UART_Init(&huart2);


    }  // end if *pExtPortConfig......
}


/*******************************************************************************
* Function: LBF_ExtPortPreset_GPIO
* Description  : Configures all IOs enabled as GPIO pins on extension connector 
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_GPIO (LBF_ExtPortConfig_t* pExtPortConfig)
{

void  Set_GPIO_Mode_Pull( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct);

GPIO_InitTypeDef GPIO_InitStruct;


    // GPIO Clocks already enabled...

    // Position 11 - N/A: GND

    // Position 10 
    if (pExtPortConfig->Pos10.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos10.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS10_PIN;
	HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct); 
    }

    // Position 9 
    if (pExtPortConfig->Pos9.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos9.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS9_PIN;
	HAL_GPIO_Init(CONN_POS9_PORT, &GPIO_InitStruct); 
    }

    // Position 8 
    if (pExtPortConfig->Pos8.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos8.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS8_PIN;
	HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct); 
    }

    // Position 7 
    if (pExtPortConfig->Pos7.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos7.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS7_PIN;
	HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct); 
    }

    // Position 6 
    // N/A - Reserved for VCC_LDO

    // Position 5 
    if (pExtPortConfig->Pos5.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos5.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS5_PIN;
	HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct); 
    }

    // Position 4 
    if (pExtPortConfig->Pos4.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos4.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS4_PIN;
	HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct); 
    }

    // Position 3 
    if (pExtPortConfig->Pos3.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos3.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS3_PIN;
	HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct); 
    }

    // Position 2 
    if (pExtPortConfig->Pos2.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos2.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS2_PIN;
	HAL_GPIO_Init(CONN_POS2_PORT, &GPIO_InitStruct); 
    }

    // Position 1 
    if (pExtPortConfig->Pos1.Function == GPIO)
    {
	Set_GPIO_Mode_Pull( pExtPortConfig->Pos1.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS1_PIN;
	HAL_GPIO_Init(CONN_POS1_PORT, &GPIO_InitStruct); 
    }

}

// =============

void  Set_GPIO_Mode_Pull( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct)
{
    switch( GPIO_Conf)
    {
      case NA:
      case IN:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		pGPIO_InitStruct->Pull = GPIO_NOPULL;
		break;
      case IN_PU:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		pGPIO_InitStruct->Pull = GPIO_PULLUP;
		break;
      case IN_PD:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		pGPIO_InitStruct->Pull = GPIO_PULLDOWN;
		break;
       case OUT:
		pGPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
		pGPIO_InitStruct->Speed = GPIO_SPEED_LOW;
		break;
       case OUT_OD:
		pGPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_OD;
		pGPIO_InitStruct->Speed = GPIO_SPEED_LOW;
		break;
       case IT_RISING:
		pGPIO_InitStruct->Mode = GPIO_MODE_IT_RISING;
		pGPIO_InitStruct->Pull = GPIO_PULLDOWN; // to avoid IT if input not driven
		break;
		//Note Ext IT still needs to be enabled at NVIC level
       case IT_FALLING:
		pGPIO_InitStruct->Mode = GPIO_MODE_IT_FALLING;
		pGPIO_InitStruct->Pull = GPIO_PULLUP; // to avoid IT if input not driven
		break;
		//Note Ext IT still needs to be enabled at NVIC level
       default:
	  ;	// Your error handler
    }

}

/*******************************************************************************
* Function: LBF_ExtPortPreset_PWMout
* Description  : Configures all IOs enabled as PWM outputs on extension connector 
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

/********************************************************
*  This sets up a PWM output over selected 
*  position of the external connector.
*  The Timer/Channel used are as follows :
*   > POS1 :  TIMER16
*   > POS2 :  n/a
*   > POS3 :  LPTIMER2
*   > POS4 :  TIMER2 CH4
*   > POS5 :  TIMER2 CH3
*   > POS6 :  n/a (vcc_ldo)
*   > POS7 :  TIMER2 CH2
*   > POS8 :  TIMER2 CH1
*   > POS9 :  TIMER4 CH3
*   > POS10:  TIMER4 CH4
*   > POS11:  n/a (gnd)
*
*  PWM signals from the same timer will all use the same 
*  period, but the duty cycle can be different for each channel
*
*  PWM mode used:
*    edge-aligned, up-counting timer, positive pulse
*    Drive Strength: "Speed Low" (limited slew rate)
**********************************************************/

void LBF_ExtPortPreset_PWMout (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;

    // settings common to all PWM outputs
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;


    // PWM on extension positions 10 and 9 : TIMER4 CH4 and CH3
    if (    ( pExtPortConfig->Pos10.Function == PWM_TIM4_CH4)
	 || ( pExtPortConfig->Pos9.Function == PWM_TIM4_CH3 ) )
    {
	__TIM4_CLK_ENABLE();

    	GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;

    	// Position 10 
    	if (pExtPortConfig->Pos10.Function == PWM_TIM4_CH4)
    	{
	    GPIO_InitStruct.Pin = CONN_POS10_PIN;
	    HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct); 
   	 }
    	// Position 9 
    	if (pExtPortConfig->Pos9.Function == PWM_TIM4_CH3)
    	{
	    GPIO_InitStruct.Pin = CONN_POS9_PIN;
	    HAL_GPIO_Init(CONN_POS9_PORT, &GPIO_InitStruct); 
   	 }
    }

    // PWM on extension positions 8,7,5,4 : TIMER2 CH1-CH4
    if (    ( pExtPortConfig->Pos8.Function == PWM_TIM2_CH1 )
	 || ( pExtPortConfig->Pos7.Function == PWM_TIM2_CH2 ) 
	 || ( pExtPortConfig->Pos5.Function == PWM_TIM2_CH3 ) 
	 || ( pExtPortConfig->Pos4.Function == PWM_TIM2_CH4 ) )
    {
	__TIM2_CLK_ENABLE();

    	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;

    	// Position 8 
    	if (pExtPortConfig->Pos8.Function == PWM_TIM2_CH1)
    	{
	    GPIO_InitStruct.Pin = CONN_POS8_PIN;
	    HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct); 
   	 }
    	// Position 7 
    	if (pExtPortConfig->Pos7.Function == PWM_TIM2_CH2)
    	{
	    GPIO_InitStruct.Pin = CONN_POS7_PIN;
	    HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct); 
   	 }
    	// Position 5 
    	if (pExtPortConfig->Pos5.Function == PWM_TIM2_CH3)
    	{
	    GPIO_InitStruct.Pin = CONN_POS5_PIN;
	    HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct); 
   	 }
    	// Position 4 
    	if (pExtPortConfig->Pos4.Function == PWM_TIM2_CH4)
    	{
	    GPIO_InitStruct.Pin = CONN_POS4_PIN;
	    HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct); 
   	 }
    }

    // PWM on extension position 3 : LPTIM2  (single channel)
    if   ( pExtPortConfig->Pos3.Function == PWM_LPTIM2)
    {
	__LPTIM2_CLK_ENABLE();
    	GPIO_InitStruct.Alternate = GPIO_AF14_LPTIM2;
	GPIO_InitStruct.Pin = CONN_POS3_PIN;
	HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct); 
    }

    // PWM on extension position 1 : TIMER16 (single channel)
    if   ( pExtPortConfig->Pos3.Function == PWM_TIM16_CH1)
    {
	__TIM16_CLK_ENABLE();
	GPIO_InitStruct.Pin = CONN_POS1_PIN;
    	GPIO_InitStruct.Alternate = GPIO_AF14_TIM16;
	HAL_GPIO_Init(CONN_POS1_PORT, &GPIO_InitStruct); 
    }

}


/*******************************************************************************
* Function: LBF_ExtPortPreset_CAN
* Description  : Configures relevant GPIOs to be used as CAN bus on Extension Port
* 		  and initializes CAN in a pre-defined configuration
* Input          : tbd
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_CAN (LBF_ExtPortConfig_t* pExtPortConfig )
{
	//TODO
}




/*******************************************************************************
* Function: LBF_ExtPortPreset_ADC
* Description  : 
* Input          : tbd
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_ADC ( LBF_ExtPortConfig_t* pExtPortConfig )
{
	//TODO
}



/*******************************************************************************
* Function: LBF_ExtPortPreset_DAC
* Description  : 
* Input          : tbd
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_DAC ( LBF_ExtPortConfig_t* pExtPortConfig )
{
	//TODO
}



/***************************************************************END OF FILE****/
