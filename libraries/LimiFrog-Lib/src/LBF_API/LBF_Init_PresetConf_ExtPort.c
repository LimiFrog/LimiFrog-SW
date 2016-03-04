/*************************************************************************
 * LBF_Init_PresetConf_ExtPort.c
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
//void LBF_ExtPortConfig (void)


/* -------------------------------------------------------------- */



/***********
* Function :	
	void LBF_Init_PresetConf_I2C1 (I2C_HandleTypeDef* hi2c )
* Description :	
	Puts I2C1 into the following preset configuration :  400kHz SCL clock, 7-bit I2C target adress (ChipID), dual addressing mode disabled, general call disabled. The peripheral clock APB1 is assumed to be 20MHz (else SCL clock will be different).
* Parameters :  
	hi2c : pointer to a structure which the underlying HAL driver will fill to perform the initialization (see note below)
Return Value:  -
* Note:  
	the user needs to declare a structure of type I2C_HandleTypeDef in his code prior to calling this function, passing a pointer to this structure as argument. He can then, if he so wishes, also use this handle to call otherhAL functions, for example to send or receive data – he may also work at lower level if he prefers.
************/

void LBF_Init_PresetConf_I2C1 ( I2C_HandleTypeDef* hi2c)
{

        // ---  Peripheral initialization : 

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


	hi2c->Instance = I2C1;
	hi2c->Init.Timing = ((uint32_t)I2C1_PRESC ) << 28
		    | ((uint32_t)I2C1_SCLDEL ) << 20
		    | ((uint32_t)I2C1_SDADEL ) << 16
		    | ((uint32_t)I2C1_SCLH ) << 8
		    | ((uint32_t)I2C1_SCLL )  ;
      	// = Contents of the I2C_TIMINGR_register value
	hi2c->Init.OwnAddress1 = 0;
	hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	hi2c->Init.OwnAddress2 = 0;
	hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLED; 
	HAL_I2C_Init(hi2c);

}

void LBF_DeInit_PresetConf_I2C1 ( I2C_HandleTypeDef* hi2c)
{
	HAL_I2C_DeInit(hi2c);
}




/*******************
* Function :	
	void LBF_Init_PresetConf_SPIoverUSART2 (USART_HandleTypeDef* hSpiUsart, uint32_t  User_Configured_BaudRate )
* Description :	
	Puts USART2 into an SPI master emulation mode, at 8-bit per frame, full-duplex, MSB first (as required by the SPI protocol), with the following pin correspondance : SPI MOSI = USART2 Tx, SPI MISO = USART2_Rx, SPI CK = USART2_CK. Chip select must be handled through a GPIO.
* Parameters :  
	> hSpiUsart : pointer to a structure which the underlying HAL driver will fill to perform the initialization (see note below)
	> User_Configured_BaudRate: required baud rate  i.e. clock frequency (in Hertz) for the SPI transmission. Maximum supported value is Fsystem_clock / 16. 
* Return Value:  -
* Note:  
	the user needs to declare a structure of type USART_HandleTypeDef in his code prior to calling this function, passing a pointer to this structure as argument. He can then, if he so wishes, also use this handle to call otherhAL functions, for example to send or receive data – he may also work at lower level if he prefers.
*******************/

void LBF_Init_PresetConf_SPIoverUSART2 (USART_HandleTypeDef* hSpiUsart, uint32_t  User_Configured_BaudRate )
{
        // ---  Peripheral initialization : 

        hSpiUsart->Instance = USART2;
        hSpiUsart->Init.BaudRate = User_Configured_BaudRate;    
        hSpiUsart->Init.WordLength = USART_WORDLENGTH_8B;  
        hSpiUsart->Init.StopBits = USART_STOPBITS_1;
        hSpiUsart->Init.Parity = USART_PARITY_NONE;
        hSpiUsart->Init.Mode = USART_MODE_TX_RX;
        hSpiUsart->Init.CLKPolarity = USART_POLARITY_LOW;
        hSpiUsart->Init.CLKPhase = USART_PHASE_1EDGE;
        hSpiUsart->Init.CLKLastBit = USART_LASTBIT_ENABLE;
        HAL_USART_Init(hSpiUsart);

        // SPI transmission is MSB first
        // MSBfirst option available from STM32-L4 ...but not offered in 
        //   HAL USART API (only with UART API!) ...so do it directly at register level
        hSpiUsart->Instance->CR1 &= 0xFFFFFFFE;  
		// disable USART2 = clear bit[0] (UE) in Control Reg. 1
        hSpiUsart->Instance->CR2 |= 0x00080000;  
		//  MSB first = set bit [19] (MSBFIRST)in Control Reg. 2
        hSpiUsart->Instance->CR1 |= 0x00000001;  
		// enable back USART2 = set bit[0] (UE) in Control Reg. 1
}


void LBF_DeInit_PresetConf_SPIoverUSART2 (USART_HandleTypeDef* hSpiUsart )
{
        HAL_USART_DeInit(hSpiUsart);
}



/*******************
* Function :	
	void LBF_Init_PresetConf_UART4 (UART_HandleTypeDef* huart,  uint32_t  User_Configured_BaudRate )
* Description :	
	Puts UART4 into the following preset configuration :  8-bit word length, 1 stop bit, no parity, x16 oversampling, full duplex(Rx and Tx enabled), no hardware flow control
* Parameters :  
	> huart : pointer to a structure which the underlying HAL driver will fill to perform the initialization (see note below)
	> User_Configured_BaudRate: required baud rate  i.e. clock frequency (in Hertz) for the SPI transmission. Maximum supported value is Fsystem_clock / 16. 
* Return Value:  -
* Note:  
	the user needs to declare a structure of type USART_HandleTypeDef in his code prior to calling this function, passing a pointer to this structure as argument. He can then, if he so wishes, also use this handle to call otherhAL functions, for example to send or receive data – he may also work at lower level if he prefers.
*******************/

void LBF_Init_PresetConf_UART4 (UART_HandleTypeDef* huart,  uint32_t  User_Configured_BaudRate )
{
        // ---  Peripheral initialization : 

        huart->Instance = UART4;
        huart->Init.BaudRate = User_Configured_BaudRate;    
        huart->Init.WordLength = UART_WORDLENGTH_8B;  
        huart->Init.StopBits = UART_STOPBITS_1;
        huart->Init.Parity = UART_PARITY_NONE;
        huart->Init.Mode = UART_MODE_TX_RX;
        huart->Init.HwFlowCtl = UART_HWCONTROL_NONE; 
        huart->Init.OverSampling = UART_OVERSAMPLING_16;
        HAL_UART_Init(huart);
}


void LBF_DeInit_PresetConf_UART4 (UART_HandleTypeDef* huart)
{
        HAL_UART_DeInit(huart);
}



/*******************
* Function :	
	void LBF_Init_Presetconf_UART2 (UART_HandleTypeDef* huart, bool cts_flowcontrol, bool rts_flowcontrol, uint32_t  User_Configured_BaudRate)
* Description :	
	Puts UART2 into the following preset configuration :  8-bit word length, 1 stop bit, no parity, x16 oversampling, full duplex(Rx and Tx enabled). Hardware flow control on CTS and/or RTS is possible.
* Parameters :  
	> huart : pointer to a structure which the underlying HAL driver will fill to perform the initialization (see note below)
	> cts_flowcontrol: if true, hardware flow control is enabled on the UART4_CTS pin
	> rts_flowcontrol: if true, hardware flow control is enabled on the UART4_RTS pin
	> User_Configured_BaudRate: required baud rate  i.e. clock frequency (in Hertz) for the SPI transmission. Maximum supported value is Fsystem_clock / 16. 
* Return Value:  -
* Note:  
	the user needs to declare a structure of type USART_HandleTypeDef in his code prior to calling this function, passing a pointer to this structure as argument. He can then, if he so wishes, also use this handle to call otherhAL functions, for example to send or receive data – he may also work at lower level if he prefers.
*******************/

void LBF_Init_Presetconf_UART2 (UART_HandleTypeDef* huart, bool cts_flowcontrol, bool rts_flowcontrol, uint32_t  User_Configured_BaudRate)
{
        // ---  Peripheral initialization : 

        huart->Instance = USART2;
        huart->Init.BaudRate = User_Configured_BaudRate;    
        huart->Init.WordLength = UART_WORDLENGTH_8B;  
        huart->Init.StopBits = UART_STOPBITS_1;
        huart->Init.Parity = UART_PARITY_NONE;
        huart->Init.Mode = UART_MODE_TX_RX;
        huart->Init.OverSampling = UART_OVERSAMPLING_16;
    	if (cts_flowcontrol && rts_flowcontrol)
   	{
            huart->Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS; 
   	}
	else if (cts_flowcontrol)
   	{
            huart->Init.HwFlowCtl = UART_HWCONTROL_CTS; 
   	}
	else if (rts_flowcontrol)
   	{
            huart->Init.HwFlowCtl = UART_HWCONTROL_RTS; 
   	}
	else 
   	{
            huart->Init.HwFlowCtl = UART_HWCONTROL_NONE; 
   	}
        HAL_UART_Init(huart);

}


void LBF_DeInit_Presetconf_UART2 (UART_HandleTypeDef* huart)
{
        HAL_UART_DeInit(huart);
}





/***************************************************************END OF FILE****/
