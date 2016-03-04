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
#include "User_Configuration.h"   // typically in user's include files directory



// Local Functions internal to this file
static void LBF_ExtPortPreset_VCCLDO (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_I2C1 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_SPIoverUSART2 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_UART2 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_UART4 (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_GPIO (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_EXTI (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_PWMout (LBF_ExtPortConfig_t* pExtPortConfig);
static void LBF_ExtPortPreset_ADC (LBF_ExtPortConfig_t* pExtPortConfig);

static void LBF_ExtPortPreset_CAN (LBF_ExtPortConfig_t* pExtPortConfig); //TODO
static void LBF_ExtPortPreset_DAC (LBF_ExtPortConfig_t* pExtPortConfig); //TODO

//static void  Set_GPIO_Mode_Pull( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct);
static void  Set_GPIO_Mode( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct);
static void  Set_GPIO_Pull( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct);



void LBF_ExtPortConfig (LBF_ExtPortConfig_t* pExtPortConfig)
{

	// Retrieve user Configuration
	//LBF_User_Conf(pExtPortConfig);

	LBF_ExtPortPreset_VCCLDO( pExtPortConfig );
	    // start with VCC_LDO in case system connected to extension port
	    // should get VCC before getting a voltage on its input pins

	//  Here IOs are configured (not the perpheral itself)
	LBF_ExtPortPreset_I2C1( pExtPortConfig );
	LBF_ExtPortPreset_SPIoverUSART2( pExtPortConfig );
	LBF_ExtPortPreset_UART4( pExtPortConfig );
	LBF_ExtPortPreset_UART2( pExtPortConfig );
	LBF_ExtPortPreset_PWMout( pExtPortConfig );
	LBF_ExtPortPreset_ADC ( pExtPortConfig );
	LBF_ExtPortPreset_GPIO( pExtPortConfig ); 
	LBF_ExtPortPreset_EXTI( pExtPortConfig ); 

	//TODO
	LBF_ExtPortPreset_CAN ( pExtPortConfig );
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
    if (  (pExtPortConfig->Pos11.Function == I2C1_SDA)
	   || (pExtPortConfig->Pos10.Function == I2C1_SCL) )

    {

	// ---  IO configuration : SDA on Pos.11, SCL on Pos.10

	__I2C1_CLK_ENABLE();

	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

    	if (pExtPortConfig->Pos11.Function == I2C1_SDA)  
	{
   	    GPIO_InitStruct.Pin = CONN_POS11_PIN;
	    GPIO_InitStruct.Pull = GPIO_PULLUP; //ext pull-up still required though
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; 
    	    HAL_GPIO_Init(CONN_POS11_PORT, &GPIO_InitStruct);
	}
    	if (pExtPortConfig->Pos10.Function == I2C1_SCL)  
          //assume no multi-master,so no need for Open-drain SCL
	{
   	    GPIO_InitStruct.Pin = CONN_POS10_PIN;
	    GPIO_InitStruct.Pull = GPIO_PULLUP; 
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 
    	    HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct);
	}
    

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
	   || (pExtPortConfig->Pos2.Function == SPI_nCS) )
    {

	// ---  IO configuration : SPI implemented using a specific mode of USART2


        if (pExtPortConfig->Pos2.Function == SPI_nCS)    // Chip Select
        {
    	    GPIO_InitStruct.Pin = CONN_POS2_PIN; 
    	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    	    HAL_GPIO_Init(CONN_POS2_PORT, &GPIO_InitStruct);
    	    // Initialize nCS to inactive state
   	    GPIO_HIGH(CONN_POS2_PORT, CONN_POS2_PIN);
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
	// ---  IO configuration 

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
//bool HwFlowCtrl = false;

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
//	    HwFlowCtrl = true;
	}
        if (pExtPortConfig->Pos7.Function == UART2_RTS)   // UART2 RTS
        {
    	    GPIO_InitStruct.Pin = CONN_POS7_PIN; 
    	    HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct);
//	    HwFlowCtrl = true;
	}

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

GPIO_InitTypeDef GPIO_InitStruct;


    // GPIO Clocks already enabled...


    // Position 11 
    if (pExtPortConfig->Pos11.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos11.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos11.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS11_PIN;
	HAL_GPIO_Init(CONN_POS11_PORT, &GPIO_InitStruct); 
    }

    // Position 10 
    if (pExtPortConfig->Pos10.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos10.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos10.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS10_PIN;
	HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct); 
    }

    // Position 9 - N/A: GND

    // Position 8 
    if (pExtPortConfig->Pos8.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos8.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos8.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS8_PIN;
	HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct); 
    }

    // Position 7 
    if (pExtPortConfig->Pos7.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos7.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos7.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS7_PIN;
	HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct); 
    }

    // Position 6 
    // N/A - Reserved for VCC_LDO

    // Position 5 
    if (pExtPortConfig->Pos5.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos5.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos5.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS5_PIN;
	HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct); 
    }

    // Position 4 
    if (pExtPortConfig->Pos4.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos4.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos4.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS4_PIN;
	HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct); 
    }

    // Position 3 
    if (pExtPortConfig->Pos3.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos3.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos3.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS3_PIN;
	HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct); 
    }

    // Position 2 
    if (pExtPortConfig->Pos2.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos2.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos2.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS2_PIN;
	HAL_GPIO_Init(CONN_POS2_PORT, &GPIO_InitStruct); 
    }

    // Position 1 
    if (pExtPortConfig->Pos1.Function == GPIO)
    {
	Set_GPIO_Mode( pExtPortConfig->Pos1.GPIO_Conf, &GPIO_InitStruct );
	Set_GPIO_Pull( pExtPortConfig->Pos1.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Pin = CONN_POS1_PIN;
	HAL_GPIO_Init(CONN_POS1_PORT, &GPIO_InitStruct); 
    }

}

/*******************************************************************************
* Function: LBF_ExtPortPreset_EXTI
* Description  : Configures all IOs enabled as External Interrupts pins (EXTI)
*	on extension connector - 
*       EXTI is DISABLED at the end of the process and needs to be
*       explictly enabled in the application, also specifying the active edge
*       (rising and/or falling). NVIC must also be setup.
* Param          : pExtPortConfig, pointer on Extension Port configuration.
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_EXTI (LBF_ExtPortConfig_t* pExtPortConfig)
{

GPIO_InitTypeDef GPIO_InitStruct;


    // GPIO Clocks already enabled...


    // Position 11 (PB9)
    if (pExtPortConfig->Pos11.Function == EXTI9_5)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos11.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS11_PIN;
	HAL_GPIO_Init(CONN_POS11_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS11_PIN); // Disable the EXTI line for now
    }

    // Position 10 (PB8)
    if (pExtPortConfig->Pos10.Function == EXTI9_5)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos10.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS10_PIN;
	HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS10_PIN); // Disable the EXTI line for now
    }

    // Position 9 - N/A: GND

    // Position 8 (PA0)
    if (pExtPortConfig->Pos8.Function == EXTI0)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos8.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS8_PIN;
	HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS8_PIN); // Disable the EXTI line for now
    }

    // Position 7 (PA1)
    if (pExtPortConfig->Pos7.Function == EXTI1)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos7.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS7_PIN;
	HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS7_PIN); // Disable the EXTI line for now
    }

    // Position 6 
    // N/A - Reserved for VCC_LDO

    // Position 5 (PA2)
    if (pExtPortConfig->Pos5.Function == EXTI2)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos5.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS5_PIN;
	HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS5_PIN); // Disable the EXTI line for now
    }

    // Position 4 (PA3) 
    if (pExtPortConfig->Pos4.Function == EXTI3)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos4.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS4_PIN;
	HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS4_PIN); // Disable the EXTI line for now
    }

    // Position 3 (PA4)
    if (pExtPortConfig->Pos3.Function == EXTI4)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos3.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS3_PIN;
	HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS3_PIN); // Disable the EXTI line for now
    }

    // Position 2 (PA6)
    if (pExtPortConfig->Pos2.Function == EXTI9_5)
    {
	Set_GPIO_Pull( pExtPortConfig->Pos2.GPIO_Conf, &GPIO_InitStruct );
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  
	   // default, to be overwritten when enabling the EXTI line in application
	GPIO_InitStruct.Pin = CONN_POS2_PIN;
	HAL_GPIO_Init(CONN_POS2_PORT, &GPIO_InitStruct); 

        LBF_Disable_EXTI_ExtPort(CONN_POS2_PIN); // Disable the EXTI line for now
    }

    // Position 1 
    // N/A  (Mic Out)

}

// =============



static void  Set_GPIO_Mode( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct)
{
    switch( GPIO_Conf)
    {
      case NA:
      case IN:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		break;
      case IN_PU:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		break;
      case IN_PD:
		pGPIO_InitStruct->Mode = GPIO_MODE_INPUT;
		break;
       case OUT:
		pGPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_PP;
		pGPIO_InitStruct->Speed = GPIO_SPEED_LOW;
		break;
       case OUT_OD:
		pGPIO_InitStruct->Mode = GPIO_MODE_OUTPUT_OD;
		pGPIO_InitStruct->Speed = GPIO_SPEED_LOW;
		break;
       default:
	  ;	// Your error handler
    }

}

static void  Set_GPIO_Pull( LBF_GPIO_Conf_t GPIO_Conf,  GPIO_InitTypeDef* pGPIO_InitStruct)
{
    switch( GPIO_Conf)
    {
      case NA:
      case IN:
		pGPIO_InitStruct->Pull = GPIO_NOPULL;
		break;
      case IN_PU:
		pGPIO_InitStruct->Pull = GPIO_PULLUP;
		break;
      case IN_PD:
		pGPIO_InitStruct->Pull = GPIO_PULLDOWN;
		break;
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


    // PWM on extension positions 11 and 10 : TIMER4 CH4 and CH3
    if (    ( pExtPortConfig->Pos11.Function == PWM_TIM4_CH4)
	 || ( pExtPortConfig->Pos10.Function == PWM_TIM4_CH3 ) )
    {
	__TIM4_CLK_ENABLE();

    	GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;

    	// Position 11 
    	if (pExtPortConfig->Pos11.Function == PWM_TIM4_CH4)
    	{
	    GPIO_InitStruct.Pin = CONN_POS11_PIN;
	    HAL_GPIO_Init(CONN_POS11_PORT, &GPIO_InitStruct); 
   	 }
    	// Position 10 
    	if (pExtPortConfig->Pos10.Function == PWM_TIM4_CH3)
    	{
	    GPIO_InitStruct.Pin = CONN_POS10_PIN;
	    HAL_GPIO_Init(CONN_POS10_PORT, &GPIO_InitStruct); 
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

    // PWM on extension position 2 : TIMER16 (single channel)
    if   ( pExtPortConfig->Pos2.Function == PWM_TIM16_CH1)
    {
	__TIM16_CLK_ENABLE();
	GPIO_InitStruct.Pin = CONN_POS2_PIN;
    	GPIO_InitStruct.Alternate = GPIO_AF14_TIM16;
	HAL_GPIO_Init(CONN_POS2_PORT, &GPIO_InitStruct); 
    }

}


/*******************************************************************************
* Function: LBF_ExtPortPreset_ADC
* Description  : 
* Input          : tbd
* Return         : None.
*******************************************************************************/

void LBF_ExtPortPreset_ADC ( LBF_ExtPortConfig_t* pExtPortConfig )
{
GPIO_InitTypeDef GPIO_InitStruct;

    // Note - only the set up of GPIOs for use as ADC input is done here
    // ADC peripheral setup, including ADC clock selection and setup,
    // must be done by the application


    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL; 
	// !!!! Not just "GPIO_MODE_ANALOG" (as on L1) else wrong ADC results
    GPIO_InitStruct.Pull = GPIO_NOPULL; 

    // Position 8 
    if (pExtPortConfig->Pos8.Function == ADC12_IN_5)
    {
	GPIO_InitStruct.Pin = CONN_POS8_PIN;
	HAL_GPIO_Init(CONN_POS8_PORT, &GPIO_InitStruct); 
    }
 
    // Position 7 
    if (pExtPortConfig->Pos7.Function == ADC12_IN_6)
    {
	GPIO_InitStruct.Pin = CONN_POS7_PIN;
	HAL_GPIO_Init(CONN_POS7_PORT, &GPIO_InitStruct); 
    }

    // Position 5 
    if (pExtPortConfig->Pos5.Function == ADC12_IN_7)
    {
	GPIO_InitStruct.Pin = CONN_POS5_PIN;
	HAL_GPIO_Init(CONN_POS5_PORT, &GPIO_InitStruct); 
    }
    // Position 4 
    if (pExtPortConfig->Pos4.Function == ADC12_IN_8)
    {
	GPIO_InitStruct.Pin = CONN_POS4_PIN;
	HAL_GPIO_Init(CONN_POS4_PORT, &GPIO_InitStruct); 
    }
    // Position 3 
    if (pExtPortConfig->Pos3.Function == ADC12_IN_9)
    {
	GPIO_InitStruct.Pin = CONN_POS3_PIN;
	HAL_GPIO_Init(CONN_POS3_PORT, &GPIO_InitStruct); 
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
