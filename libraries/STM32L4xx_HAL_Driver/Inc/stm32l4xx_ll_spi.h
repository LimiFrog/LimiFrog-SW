/**
  ******************************************************************************
  * @file    stm32l4xx_ll_spi.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    16-September-2015
  * @brief   Header file of SPI LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L4xx_LL_SPI_H
#define __STM32L4xx_LL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"

/** @addtogroup STM32L4xx_LL_Driver
  * @{
  */

#if defined (SPI1) || defined (SPI2) || defined (SPI3)

/** @defgroup SPI_LL SPI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Constants SPI Exported Constants
  * @{
  */

/** @defgroup SPI_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_SPI_ReadReg function
  * @{
  */
#define LL_SPI_SR_RXNE                     SPI_SR_RXNE               /*!< Rx buffer not empty flag         */
#define LL_SPI_SR_TXE                      SPI_SR_TXE                /*!< Tx buffer empty flag             */
#define LL_SPI_SR_BSY                      SPI_SR_BSY                /*!< Busy flag                        */
#define LL_SPI_SR_UDR                      SPI_SR_UDR                /*!< Underrun flag                    */
#define LL_SPI_SR_CRCERR                   SPI_SR_CRCERR             /*!< CRC error flag                   */
#define LL_SPI_SR_MODF                     SPI_SR_MODF               /*!< Mode fault flag                  */
#define LL_SPI_SR_OVR                      SPI_SR_OVR                /*!< Overrun flag                     */
#define LL_SPI_SR_FRE                      SPI_SR_FRE                /*!< TI mode frame format error flag  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_SPI_ReadReg and  LL_SPI_WriteReg functions
  * @{
  */
#define LL_SPI_CR2_RXNEIE                  SPI_CR2_RXNEIE            /*!< Rx buffer not empty interrupt enable */
#define LL_SPI_CR2_TXEIE                   SPI_CR2_TXEIE             /*!< Tx buffer empty interrupt enable     */
#define LL_SPI_CR2_ERRIE                   SPI_CR2_ERRIE             /*!< Error interrupt enable               */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_MODE MODE
  * @{
  */
#define LL_SPI_MODE_MASTER                 ((uint32_t)0x00000104)    /*!< Master configuration  */
#define LL_SPI_MODE_SLAVE                  ((uint32_t)0x00000000)    /*!< Slave configuration   */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PROTOCOL PROTOCOL
  * @{
  */
#define LL_SPI_PROTOCOL_MOTOROLA           ((uint32_t)0x00000000)    /*!< Motorola mode. Used as default value */
#define LL_SPI_PROTOCOL_TI                 (SPI_CR2_FRF)             /*!< TI mode                              */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_PHASE PHASE
  * @{
  */
#define LL_SPI_PHASE_1EDGE                 ((uint32_t)0x00000000)    /*!< First clock transition is the first data capture edge  */
#define LL_SPI_PHASE_2EDGE                 (SPI_CR1_CPHA)            /*!< Second clock transition is the first data capture edge */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_POLARITY POLARITY
  * @{
  */
#define LL_SPI_POLARITY_LOW                ((uint32_t)0x00000000)    /*!< Clock to 0 when idle */
#define LL_SPI_POLARITY_HIGH               (SPI_CR1_CPOL)            /*!< Clock to 1 when idle */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BAUDRATEPRESCALER BAUDRATEPRESCALER
  * @{
  */
#define LL_SPI_BAUDRATEPRESCALER_DIV2      ((uint32_t)0x00000000)                         /*!< Baudrate control equal to fPCLK/2   */
#define LL_SPI_BAUDRATEPRESCALER_DIV4      (SPI_CR1_BR_0)                                 /*!< Baudrate control equal to fPCLK/4   */
#define LL_SPI_BAUDRATEPRESCALER_DIV8      (SPI_CR1_BR_1)                                 /*!< Baudrate control equal to fPCLK/8   */
#define LL_SPI_BAUDRATEPRESCALER_DIV16     (SPI_CR1_BR_1 | SPI_CR1_BR_0)                  /*!< Baudrate control equal to fPCLK/16  */
#define LL_SPI_BAUDRATEPRESCALER_DIV32     (SPI_CR1_BR_2)                                 /*!< Baudrate control equal to fPCLK/32  */
#define LL_SPI_BAUDRATEPRESCALER_DIV64     (SPI_CR1_BR_2 | SPI_CR1_BR_0)                  /*!< Baudrate control equal to fPCLK/64  */
#define LL_SPI_BAUDRATEPRESCALER_DIV128    (SPI_CR1_BR_2 | SPI_CR1_BR_1)                  /*!< Baudrate control equal to fPCLK/128 */
#define LL_SPI_BAUDRATEPRESCALER_DIV256    (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)   /*!< Baudrate control equal to fPCLK/256 */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_BIT_ORDER TRANSMISSION BIT ORDER
  * @{
  */
#define LL_SPI_LSB_FIRST                   (SPI_CR1_LSBFIRST)        /*!< Data is transmitted/received withthe LSB first */
#define LL_SPI_MSB_FIRST                   ((uint32_t)0x00000000)    /*!< Data is transmitted/received withthe MSB first */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TRANSFER_MODE TRANSFER MODE
  * @{
  */
#define LL_SPI_FULL_DUPLEX                 ((uint32_t)0x00000000)    /*!< Full-Duplex mode. Rx and Tx transfer on 2 lines */
#define LL_SPI_SIMPLEX_RX                  (SPI_CR1_RXONLY)          /*!< Simplex Rx mode.  Rx transfer only on 1 line    */
#define LL_SPI_HALF_DUPLEX                 (SPI_CR1_BIDIMODE)        /*!< Half-Duplex mode. Rx or Tx transfer on 1 line   */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_DIRECTION_HALF_DUPLEX DIRECTION HALF DUPLEX
  * @{
  */
#define LL_SPI_DIRECTION_HALF_DUPLEX_TX    (SPI_CR1_BIDIOE)          /*!< Tx transfer selection for Half-Duplex mode */
#define LL_SPI_DIRECTION_HALF_DUPLEX_RX    (0x00000000)              /*!< Rx transfer selection for Half-Duplex mode */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_DATAWIDTH DATAWIDTH
  * @{
  */
#define LL_SPI_DATAWIDTH_4BIT              (SPI_CR2_DS_0 | SPI_CR2_DS_1)                               /*!< Data length for SPI transfer:  4 bits */
#define LL_SPI_DATAWIDTH_5BIT              (SPI_CR2_DS_2)                                              /*!< Data length for SPI transfer:  5 bits */
#define LL_SPI_DATAWIDTH_6BIT              (SPI_CR2_DS_2 | SPI_CR2_DS_0)                               /*!< Data length for SPI transfer:  6 bits */
#define LL_SPI_DATAWIDTH_7BIT              (SPI_CR2_DS_2 | SPI_CR2_DS_1)                               /*!< Data length for SPI transfer:  7 bits */
#define LL_SPI_DATAWIDTH_8BIT              (SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0)                /*!< Data length for SPI transfer:  8 bits */
#define LL_SPI_DATAWIDTH_9BIT              (SPI_CR2_DS_3)                                              /*!< Data length for SPI transfer:  9 bits */
#define LL_SPI_DATAWIDTH_10BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_0)                               /*!< Data length for SPI transfer: 10 bits */
#define LL_SPI_DATAWIDTH_11BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_1)                               /*!< Data length for SPI transfer: 11 bits */
#define LL_SPI_DATAWIDTH_12BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_1 | SPI_CR2_DS_0)                /*!< Data length for SPI transfer: 12 bits */
#define LL_SPI_DATAWIDTH_13BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_2)                               /*!< Data length for SPI transfer: 13 bits */
#define LL_SPI_DATAWIDTH_14BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_0)                /*!< Data length for SPI transfer: 14 bits */
#define LL_SPI_DATAWIDTH_15BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1)                /*!< Data length for SPI transfer: 15 bits */
#define LL_SPI_DATAWIDTH_16BIT             (SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0) /*!< Data length for SPI transfer: 16 bits */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RX_FIFO_TH RX FIFO THRESHOLD
  * @{
  */
#define LL_SPI_RX_FIFO_TH_HALF             ((uint32_t)0x00000000)    /*!< RXNE event is generated if FIFO level is greater than or equel to 1/2 (16-bit) */
#define LL_SPI_RX_FIFO_TH_QUARTER          (SPI_CR2_FRXTH)           /*!< RXNE event is generated if FIFO level is greater than or equel to 1/4 (8-bit)  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_CRC_LENGTH CRC LENGTH
  * @{
  */
#define LL_SPI_CRC_8BIT                    ((uint32_t)0x00000000)    /*!<  8-bit CRC length */
#define LL_SPI_CRC_16BIT                   (SPI_CR1_CRCL)            /*!< 16-bit CRC length */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_NSS_MODE NSS MODE
  * @{
  */
#define LL_SPI_NSS_SOFT                    (SPI_CR1_SSM)                     /*!< NSS managed internally. NSS pin not used and free              */
#define LL_SPI_NSS_HARD_INPUT              ((uint32_t)0x00000000)            /*!< NSS pin used in Input. Only used in Master mode                */
#define LL_SPI_NSS_HARD_OUTPUT             (((uint32_t)SPI_CR2_SSOE << 16))  /*!< NSS pin used in Output. Only used in Slave mode as chip select */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_RX_FIFO RX FIFO LEVEL
  * @{
  */
#define LL_SPI_RX_FIFO_EMPTY               ((uint32_t)0x00000000)            /*!< FIFO reception empty */
#define LL_SPI_RX_FIFO_QUARTER_FULL        (SPI_SR_FRLVL_0)                  /*!< FIFO reception 1/4   */
#define LL_SPI_RX_FIFO_HALF_FULL           (SPI_SR_FRLVL_1)                  /*!< FIFO reception 1/2   */
#define LL_SPI_RX_FIFO_FULL                (SPI_SR_FRLVL_1 | SPI_SR_FRLVL_0) /*!< FIFO reception full  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_TX_FIFO TX FIFO LEVEL
  * @{
  */
#define LL_SPI_TX_FIFO_EMPTY               ((uint32_t)0x00000000)            /*!< FIFO transmission empty */
#define LL_SPI_TX_FIFO_QUARTER_FULL        (SPI_SR_FTLVL_0)                  /*!< FIFO transmission 1/4   */
#define LL_SPI_TX_FIFO_HALF_FULL           (SPI_SR_FTLVL_1)                  /*!< FIFO transmission 1/2   */
#define LL_SPI_TX_FIFO_FULL                (SPI_SR_FTLVL_1 | SPI_SR_FTLVL_0) /*!< FIFO transmission full  */
/**
  * @}
  */

/** @defgroup SPI_LL_EC_DMA_PARITY DMA PARITY
  * @{
  */
#define LL_SPI_DMA_PARITY_EVEN             ((uint32_t)0x00000000)    /*!< Select DMA parity Even */
#define LL_SPI_DMA_PARITY_ODD              ((uint32_t)0x00000001)    /*!< Select DMA parity Odd  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Macros SPI Exported Macros
  * @{
  */

/** @defgroup SPI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_SPI_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in SPI register
  * @param  __INSTANCE__ SPI Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_SPI_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable SPI peripheral
  * @rmtoll CR1          SPE           LL_SPI_Enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Enable(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Disable SPI peripheral
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  * @rmtoll CR1          SPE           LL_SPI_Disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_Disable(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Check if SPI peripheral is enabled
  * @rmtoll CR1          SPE           LL_SPI_IsEnabled
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_IsEnabled(SPI_TypeDef *SPIx)
{
}

/**
  * @brief  Set SPI Mode to Master or Slave
  * @note   This bit should not be changed when communication is ongoing.
  * @rmtoll CR1          MSTR          LL_SPI_SetMode\n
  *         CR1          SSI           LL_SPI_SetMode
  * @param  SPIx SPI Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetMode(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, Mode);
}

/**
  * @brief  Get SPI Mode (Master or Slave)
  * @rmtoll CR1          MSTR          LL_SPI_GetMode\n
  *         CR1          SSI           LL_SPI_GetMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_MODE_MASTER
  *         @arg @ref LL_SPI_MODE_SLAVE
  */
__STATIC_INLINE uint32_t LL_SPI_GetMode(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI));
}

/**
  * @brief  Set Serial protocol used
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @rmtoll CR2          FRF           LL_SPI_SetStandard
  * @param  SPIx SPI Instance
  * @param  Standard This parameter can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetStandard(SPI_TypeDef *SPIx, uint32_t Standard)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_FRF, Standard);
}

/**
  * @brief  Set Serial protocol used
  * @rmtoll CR2          FRF           LL_SPI_GetStandard
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_PROTOCOL_MOTOROLA
  *         @arg @ref LL_SPI_PROTOCOL_TI
  */
__STATIC_INLINE uint32_t LL_SPI_GetStandard(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_FRF));
}

/**
  * @brief  Set Clock phase
  * @note   This bit should not be changed when communication is ongoing.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CR1          CPHA          LL_SPI_SetClockPhase
  * @param  SPIx SPI Instance
  * @param  ClockPhase This parameter can be one of the following values:
  *         @arg @ref LL_SPI_PHASE_1EDGE
  *         @arg @ref LL_SPI_PHASE_2EDGE
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t ClockPhase)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA, ClockPhase);
}

/**
  * @brief  Get Clock phase
  * @rmtoll CR1          CPHA          LL_SPI_GetClockPhase
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_PHASE_1EDGE
  *         @arg @ref LL_SPI_PHASE_2EDGE
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPhase(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA));
}

/**
  * @brief  Set Clock polarity
  * @note   This bit should not be changed when communication is ongoing.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CR1          CPOL          LL_SPI_SetClockPolarity
  * @param  SPIx SPI Instance
  * @param  ClockPolarity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_POLARITY_LOW
  *         @arg @ref LL_SPI_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL, ClockPolarity);
}

/**
  * @brief  Get Clock polarity
  * @rmtoll CR1          CPOL          LL_SPI_GetClockPolarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_POLARITY_LOW
  *         @arg @ref LL_SPI_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_SPI_GetClockPolarity(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL));
}

/**
  * @brief  Set Baudrate Prescaler
  * @note   These bits should not be changed when communication is ongoing. SPI BaudRate = fPCLK/Pescaler.
  * @rmtoll CR1          BR            LL_SPI_SetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @param  Baudrate This parameter can be one of the following values:
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV256
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetBaudRatePrescaler(SPI_TypeDef *SPIx, uint32_t Baudrate)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_BR, Baudrate);
}

/**
  * @brief  Get Baudrate Prescaler
  * @rmtoll CR1          BR            LL_SPI_GetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref LL_SPI_BAUDRATEPRESCALER_DIV256
  */
__STATIC_INLINE uint32_t LL_SPI_GetBaudRatePrescaler(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BR));
}

/**
  * @brief  Set Transfer Bit Order
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @rmtoll CR1          LSBFIRST      LL_SPI_SetTransferBitOrder
  * @param  SPIx SPI Instance
  * @param  BitOrder This parameter can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t BitOrder)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_LSBFIRST, BitOrder);
}

/**
  * @brief  Get Transfer Bit Order
  * @rmtoll CR1          LSBFIRST      LL_SPI_GetTransferBitOrder
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_LSB_FIRST
  *         @arg @ref LL_SPI_MSB_FIRST
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferBitOrder(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_LSBFIRST));
}

/**
  * @brief  Set Transfer Direction Mode
  * @note   For Half-Duplex mode, Rx Direction is set by default.
  *         In master mode, the MOSI pin is used and in slave mode, the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          RXONLY        LL_SPI_SetTransferDirection\n
  *         CR1          BIDIMODE      LL_SPI_SetTransferDirection
  * @param  SPIx SPI Instance
  * @param  TransferDirection This parameter can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t TransferDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE, TransferDirection);
}

/**
  * @brief  Get Transfer Direction Mode
  * @rmtoll CR1          RXONLY        LL_SPI_GetTransferDirection\n
  *         CR1          BIDIMODE      LL_SPI_GetTransferDirection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_FULL_DUPLEX
  *         @arg @ref LL_SPI_SIMPLEX_RX
  *         @arg @ref LL_SPI_HALF_DUPLEX
  */
__STATIC_INLINE uint32_t LL_SPI_GetTransferDirection(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE));
}

/**
  * @brief  Set direction for Half-Duplex Mode
  * @note   In master mode, the MOSI pin is used and in slave mode, the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          BIDIOE        LL_SPI_SetHalfDuplexDirection
  * @param  SPIx SPI Instance
  * @param  HalfDuplexDirection This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DIRECTION_HALF_DUPLEX_TX
  *         @arg @ref LL_SPI_DIRECTION_HALF_DUPLEX_RX
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetHalfDuplexDirection(SPI_TypeDef *SPIx, uint32_t HalfDuplexDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_BIDIOE, HalfDuplexDirection);
}

/**
  * @brief  Get direction for Half-Duplex Mode
  * @note   In master mode, the MOSI pin is used and in slave mode, the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          BIDIOE        LL_SPI_GetHalfDuplexDirection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DIRECTION_HALF_DUPLEX_TX
  *         @arg @ref LL_SPI_DIRECTION_HALF_DUPLEX_RX
  */
__STATIC_INLINE uint32_t LL_SPI_GetHalfDuplexDirection(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BIDIOE));
}

/**
  * @brief  Set Frame Data Size
  * @rmtoll CR2          DS            LL_SPI_SetDataWidth
  * @param  SPIx SPI Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DATAWIDTH_4BIT
  *         @arg @ref LL_SPI_DATAWIDTH_5BIT
  *         @arg @ref LL_SPI_DATAWIDTH_6BIT
  *         @arg @ref LL_SPI_DATAWIDTH_7BIT
  *         @arg @ref LL_SPI_DATAWIDTH_8BIT
  *         @arg @ref LL_SPI_DATAWIDTH_9BIT
  *         @arg @ref LL_SPI_DATAWIDTH_10BIT
  *         @arg @ref LL_SPI_DATAWIDTH_11BIT
  *         @arg @ref LL_SPI_DATAWIDTH_12BIT
  *         @arg @ref LL_SPI_DATAWIDTH_13BIT
  *         @arg @ref LL_SPI_DATAWIDTH_14BIT
  *         @arg @ref LL_SPI_DATAWIDTH_15BIT
  *         @arg @ref LL_SPI_DATAWIDTH_16BIT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t DataWidth)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_DS, DataWidth);
}

/**
  * @brief  Get Frame Data Size
  * @rmtoll CR2          DS            LL_SPI_GetDataWidth
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DATAWIDTH_4BIT
  *         @arg @ref LL_SPI_DATAWIDTH_5BIT
  *         @arg @ref LL_SPI_DATAWIDTH_6BIT
  *         @arg @ref LL_SPI_DATAWIDTH_7BIT
  *         @arg @ref LL_SPI_DATAWIDTH_8BIT
  *         @arg @ref LL_SPI_DATAWIDTH_9BIT
  *         @arg @ref LL_SPI_DATAWIDTH_10BIT
  *         @arg @ref LL_SPI_DATAWIDTH_11BIT
  *         @arg @ref LL_SPI_DATAWIDTH_12BIT
  *         @arg @ref LL_SPI_DATAWIDTH_13BIT
  *         @arg @ref LL_SPI_DATAWIDTH_14BIT
  *         @arg @ref LL_SPI_DATAWIDTH_15BIT
  *         @arg @ref LL_SPI_DATAWIDTH_16BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetDataWidth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_DS));
}

/**
  * @brief  Set threshold of RXFIFO that triggers an RXNE event
  * @rmtoll CR2          FRXTH         LL_SPI_SetRxFIFOThreshold
  * @param  SPIx SPI Instance
  * @param  Threshold This parameter can be one of the following values:
  *         @arg @ref LL_SPI_RX_FIFO_TH_HALF
  *         @arg @ref LL_SPI_RX_FIFO_TH_QUARTER
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetRxFIFOThreshold(SPI_TypeDef *SPIx, uint32_t Threshold)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_FRXTH, Threshold);
}

/**
  * @brief  Get threshold of RXFIFO that triggers an RXNE event
  * @rmtoll CR2          FRXTH         LL_SPI_GetRxFIFOThreshold
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_RX_FIFO_TH_HALF
  *         @arg @ref LL_SPI_RX_FIFO_TH_QUARTER
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOThreshold(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_FRXTH));
}

/**
  * @}
  */

/** @defgroup SPI_EF_CRC_Management CRC_Management
  * @{
  */

/**
  * @brief  Enable CRC
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @rmtoll CR1          CRCEN         LL_SPI_EnableCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableCRC(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CRCEN);
}

/**
  * @brief  Disable CRC
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @rmtoll CR1          CRCEN         LL_SPI_DisableCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableCRC(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_CRCEN);
}

/**
  * @brief  Check if CRC is enabled
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @rmtoll CR1          CRCEN         LL_SPI_IsEnabledCRC
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_IsEnabledCRC(SPI_TypeDef *SPIx)
{
}

/**
  * @brief  Set CRC Length
  * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
  * @rmtoll CR1          CRCL          LL_SPI_SetCRCWidth
  * @param  SPIx SPI Instance
  * @param  CRCLength This parameter can be one of the following values:
  *         @arg @ref LL_SPI_CRC_8BIT
  *         @arg @ref LL_SPI_CRC_16BIT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetCRCWidth(SPI_TypeDef *SPIx, uint32_t CRCLength)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CRCL, CRCLength);
}

/**
  * @brief  Get CRC Length
  * @rmtoll CR1          CRCL          LL_SPI_GetCRCWidth
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_CRC_8BIT
  *         @arg @ref LL_SPI_CRC_16BIT
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCWidth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CRCL));
}

/**
  * @brief  Set CRCNext to transfer CRC on the line
  * @note   This bit has to be written as soon as the last data is written in the SPIx_DR register.
  * @rmtoll CR1          CRCNEXT       LL_SPI_SetCRCNext
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetCRCNext(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CRCNEXT);
}

/**
  * @brief  Set polynomial for CRC calculation
  * @rmtoll CRCPR        CRCPOLY       LL_SPI_SetCRCPolynomial
  * @param  SPIx SPI Instance
  * @param  CRCPoly 0..0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetCRCPolynomial(SPI_TypeDef *SPIx, uint32_t CRCPoly)
{
  MODIFY_REG(SPIx->CRCPR, SPI_CRCPR_CRCPOLY, CRCPoly);
}

/**
  * @brief  Get polynomial for CRC calculation
  * @rmtoll CRCPR        CRCPOLY       LL_SPI_GetCRCPolynomial
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetCRCPolynomial(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CRCPR));
}

/**
  * @brief  Get Rx CRC
  * @rmtoll RXCRCR       RXCRC         LL_SPI_GetRxCRC
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->RXCRCR));
}

/**
  * @brief  Get Tx CRC
  * @rmtoll TXCRCR       TXCRC         LL_SPI_GetTxCRC
  * @param  SPIx SPI Instance
  * @retval 0..0xFFFF
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->TXCRCR));
}

/**
  * @}
  */

/** @defgroup SPI_EF_NSS_Management NSS_Management
  * @{
  */

/**
  * @brief  Set NSS Mode
  * @note   LL_SPI_NSS_SOFT Mode is not used in SPI TI mode.
  * @rmtoll CR1          SSM           LL_SPI_SetNSSMode\n
  * @rmtoll CR2          SSOE          LL_SPI_SetNSSMode
  * @param  SPIx SPI Instance
  * @param  NSS This parameter can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t NSS)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_SSM,  NSS);
  MODIFY_REG(SPIx->CR2, SPI_CR2_SSOE, ((uint32_t)(NSS >> 16)));
}

/**
  * @brief  Get NSS Mode
  * @rmtoll CR1          SSM           LL_SPI_GetNSSMode\n
  * @rmtoll CR2          SSOE          LL_SPI_GetNSSMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_NSS_SOFT
  *         @arg @ref LL_SPI_NSS_HARD_INPUT
  *         @arg @ref LL_SPI_NSS_HARD_OUTPUT
  */
__STATIC_INLINE uint32_t LL_SPI_GetNSSMode(SPI_TypeDef *SPIx)
{
  register uint32_t Ssm  = (READ_BIT(SPIx->CR1, SPI_CR1_SSM));
  register uint32_t Ssoe = (READ_BIT(SPIx->CR2,  SPI_CR2_SSOE) << 16);
  return (Ssm | Ssoe);
}

/**
  * @brief  Enable NSS pulse mgt
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @rmtoll CR2          NSSP          LL_SPI_EnableNSSPulseMgt
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableNSSPulseMgt(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_NSSP);
}

/**
  * @brief  Disable NSS pulse mgt
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @rmtoll CR2          NSSP          LL_SPI_DisableNSSPulseMgt
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableNSSPulseMgt(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_NSSP);
}

/**
  * @brief  Check if NSS pulse is enabled
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @rmtoll CR2          NSSP          LL_SPI_IsEnabledNSSPulse
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_IsEnabledNSSPulse(SPI_TypeDef *SPIx)
{
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check if Rx buffer is not empty
  * @rmtoll SR           RXNE          LL_SPI_IsActiveFlag_RXNE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXNE(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_RXNE) == (SPI_SR_RXNE));
}

/**
  * @brief  Check if Tx buffer is empty
  * @rmtoll SR           TXE           LL_SPI_IsActiveFlag_TXE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXE(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_TXE) == (SPI_SR_TXE));
}

/**
  * @brief  Get Underrun error flag
  * @rmtoll SR           UDR           LL_SPI_IsActiveFlag_UDR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_UDR(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_UDR) == (SPI_SR_UDR));
}

/**
  * @brief  Get CRC error flag
  * @rmtoll SR           CRCERR        LL_SPI_IsActiveFlag_CRCERR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_CRCERR(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_CRCERR) == (SPI_SR_CRCERR));
}

/**
  * @brief  Get  Mode fault error flag
  * @rmtoll SR           MODF          LL_SPI_IsActiveFlag_MODF
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_MODF(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_MODF) == (SPI_SR_MODF));
}

/**
  * @brief  Get Overrun error flag
  * @rmtoll SR           OVR           LL_SPI_IsActiveFlag_OVR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_OVR(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_OVR) == (SPI_SR_OVR));
}

/**
  * @brief  Get Busy flag
  * @note   The BSY flag is cleared under any one of the following conditions:
  * -When the SPI is correctly disabled
  * -When a fault is detected in Master mode (MODF bit set to 1)
  * -In Master mode, when it finishes a data transmission and no new data is ready to be
  * sent
  * -In Slave mode, when the BSY flag is set to '0' for at least one SPI clock cycle between
  * each data transfer.
  * @rmtoll SR           BSY           LL_SPI_IsActiveFlag_BSY
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_BSY(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_BSY) == (SPI_SR_BSY));
}

/**
  * @brief  Get Frame format error flag
  * @rmtoll SR           FRE           LL_SPI_IsActiveFlag_FRE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_FRE(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->SR, SPI_SR_FRE) == (SPI_SR_FRE));
}

/**
  * @brief  Get FIFO reception Level
  * @rmtoll SR           FRLVL         LL_SPI_GetRxFIFOLevel
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_RX_FIFO_EMPTY
  *         @arg @ref LL_SPI_RX_FIFO_QUARTER_FULL
  *         @arg @ref LL_SPI_RX_FIFO_HALF_FULL
  *         @arg @ref LL_SPI_RX_FIFO_FULL
  */
__STATIC_INLINE uint32_t LL_SPI_GetRxFIFOLevel(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->SR, SPI_SR_FRLVL));
}

/**
  * @brief  Get FIFO Transmission Level
  * @rmtoll SR           FTLVL         LL_SPI_GetTxFIFOLevel
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_TX_FIFO_EMPTY
  *         @arg @ref LL_SPI_TX_FIFO_QUARTER_FULL
  *         @arg @ref LL_SPI_TX_FIFO_HALF_FULL
  *         @arg @ref LL_SPI_TX_FIFO_FULL
  */
__STATIC_INLINE uint32_t LL_SPI_GetTxFIFOLevel(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->SR, SPI_SR_FTLVL));
}

/**
  * @brief  Clear Underrun error flag
  * @rmtoll SR           UDR           LL_SPI_ClearFlag_UDR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_UDR(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

/**
  * @brief  Clear CRC error flag
  * @rmtoll SR           CRCERR        LL_SPI_ClearFlag_CRCERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_CRCERR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->SR, SPI_SR_CRCERR);
}

/**
  * @brief  Clear  Mode fault error flag
  * @rmtoll SR           MODF          LL_SPI_ClearFlag_MODF
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_MODF(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
  tmpreg = CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
  (void) tmpreg;
}

/**
  * @brief  Clear Overrun error flag
  * @rmtoll SR           OVR           LL_SPI_ClearFlag_OVR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_OVR(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->DR;
  (void) tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

/**
  * @brief  Clear Frame format error flag
  * @rmtoll SR           FRE           LL_SPI_ClearFlag_FRE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_ClearFlag_FRE(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Error IT
  * @note   This bit controls the generation of an interrupt when an error condition occurs (CRCERR,OVR, MODF in SPI mode, FRE at TI mode).
  * @rmtoll CR2          ERRIE         LL_SPI_EnableIT_ERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_ERR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_ERRIE);
}

/**
  * @brief  Enable Rx buffer not empty IT
  * @rmtoll CR2          RXNEIE        LL_SPI_EnableIT_RXNE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_RXNE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_RXNEIE);
}

/**
  * @brief  Enable Tx buffer empty IT
  * @rmtoll CR2          TXEIE         LL_SPI_EnableIT_TXE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableIT_TXE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_TXEIE);
}

/**
  * @brief  Disable Error IT
  * @note   This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode, FRE at TI mode).
  * @rmtoll CR2          ERRIE         LL_SPI_DisableIT_ERR
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_ERR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_ERRIE);
}

/**
  * @brief  Disable Rx buffer not empty IT
  * @rmtoll CR2          RXNEIE        LL_SPI_DisableIT_RXNE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_RXNE(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_RXNEIE);
}

/**
  * @brief  Disable Tx buffer empty IT
  * @rmtoll CR2          TXEIE         LL_SPI_DisableIT_TXE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableIT_TXE(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_TXEIE);
}

/**
  * @brief  Check if ERR IT is enabled
  * @rmtoll CR2          ERRIE         LL_SPI_IsEnabledIT_ERR
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_ERR(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CR2, SPI_CR2_ERRIE) == (SPI_CR2_ERRIE));
}

/**
  * @brief  Check if RXNE IT is enabled
  * @rmtoll CR2          RXNEIE        LL_SPI_IsEnabledIT_RXNE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXNE(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CR2, SPI_CR2_RXNEIE) == (SPI_CR2_RXNEIE));
}

/**
  * @brief  Check if TXE IT is enabled
  * @rmtoll CR2          TXEIE         LL_SPI_IsEnabledIT_TXE
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXE(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CR2, SPI_CR2_TXEIE) == (SPI_CR2_TXEIE));
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_DMA_Management DMA_Management
  * @{
  */

/**
  * @brief  Enable DMA Rx
  * @rmtoll CR2          RXDMAEN       LL_SPI_EnableDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_RX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_RXDMAEN);
}

/**
  * @brief  Disable DMA Rx
  * @rmtoll CR2          RXDMAEN       LL_SPI_DisableDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_RX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_RXDMAEN);
}

/**
  * @brief  Check if DMA Rx is enabled
  * @rmtoll CR2          RXDMAEN       LL_SPI_IsEnabledDMAReq_RX
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_RX(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CR2, SPI_CR2_RXDMAEN) == (SPI_CR2_RXDMAEN));
}

/**
  * @brief  Enable DMA Tx
  * @rmtoll CR2          TXDMAEN       LL_SPI_EnableDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_EnableDMAReq_TX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_TXDMAEN);
}

/**
  * @brief  Disable DMA Tx
  * @rmtoll CR2          TXDMAEN       LL_SPI_DisableDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void LL_SPI_DisableDMAReq_TX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_TXDMAEN);
}

/**
  * @brief  Check if DMA Tx is enabled
  * @rmtoll CR2          TXDMAEN       LL_SPI_IsEnabledDMAReq_TX
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_TX(SPI_TypeDef *SPIx)
{
  return (READ_BIT(SPIx->CR2, SPI_CR2_TXDMAEN) == (SPI_CR2_TXDMAEN));
}

/**
  * @brief  Set parity of  Last DMA reception
  * @rmtoll CR2          LDMARX        LL_SPI_SetDMAParity_RX
  * @param  SPIx SPI Instance
  * @param  Parity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DMA_PARITY_ODD
  *         @arg @ref LL_SPI_DMA_PARITY_EVEN
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetDMAParity_RX(SPI_TypeDef *SPIx, uint32_t Parity)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_LDMARX, (Parity << POSITION_VAL(SPI_CR2_LDMARX)));
}

/**
  * @brief  Get parity configuration for  Last DMA reception
  * @rmtoll CR2          LDMARX        LL_SPI_GetDMAParity_RX
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DMA_PARITY_ODD
  *         @arg @ref LL_SPI_DMA_PARITY_EVEN
  */
__STATIC_INLINE uint32_t LL_SPI_GetDMAParity_RX(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_LDMARX) >> POSITION_VAL(SPI_CR2_LDMARX));
}

/**
  * @brief  Set parity of  Last DMA transmission
  * @rmtoll CR2          LDMATX        LL_SPI_SetDMAParity_TX
  * @param  SPIx SPI Instance
  * @param  Parity This parameter can be one of the following values:
  *         @arg @ref LL_SPI_DMA_PARITY_ODD
  *         @arg @ref LL_SPI_DMA_PARITY_EVEN
  * @retval None
  */
__STATIC_INLINE void LL_SPI_SetDMAParity_TX(SPI_TypeDef *SPIx, uint32_t Parity)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_LDMATX, (Parity << POSITION_VAL(SPI_CR2_LDMATX)));
}

/**
  * @brief  Get parity configuration for Last DMA transmission
  * @rmtoll CR2          LDMATX        LL_SPI_GetDMAParity_TX
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SPI_DMA_PARITY_ODD
  *         @arg @ref LL_SPI_DMA_PARITY_EVEN
  */
__STATIC_INLINE uint32_t LL_SPI_GetDMAParity_TX(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_LDMATX) >> POSITION_VAL(SPI_CR2_LDMATX));
}

/**
  * @brief  Get the data register address used for DMA transfer
  * @rmtoll DR           DR            LL_SPI_DMA_GetRegAddr
  * @param  SPIx SPI Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t LL_SPI_DMA_GetRegAddr(SPI_TypeDef *SPIx)
{
  return (uint32_t)&(SPIx->DR);
}

/**
  * @}
  */

/** @defgroup SPI_LL_EF_DATA_Management DATA_Management
  * @{
  */

/**
  * @brief  Read  8-Bits in the Data Register
  * @rmtoll DR           DR            LL_SPI_ReceiveData8
  * @param  SPIx SPI Instance
  * @retval RxData 0..0xFF
  */
__STATIC_INLINE uint8_t LL_SPI_ReceiveData8(SPI_TypeDef *SPIx)
{
  return (uint8_t)(READ_REG(SPIx->DR));
}

/**
  * @brief  Read  16-Bits in the Data Register
  * @rmtoll DR           DR            LL_SPI_ReceiveData16
  * @param  SPIx SPI Instance
  * @retval RxData 0..0xFFFF
  */
__STATIC_INLINE uint16_t LL_SPI_ReceiveData16(SPI_TypeDef *SPIx)
{
  return (uint16_t)(READ_REG(SPIx->DR));
}

/**
  * @brief  Write  8-Bits in the Data Register
  * @rmtoll DR           DR            LL_SPI_TransmitData8
  * @param  SPIx SPI Instance
  * @param  TxData 0..0xFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_TransmitData8(SPI_TypeDef *SPIx, uint8_t TxData)
{
  *((__IO uint8_t*)&SPIx->DR) = TxData;
}

/**
  * @brief  Write 16-Bits in the Data Register
  * @rmtoll DR           DR            LL_SPI_TransmitData16
  * @param  SPIx SPI Instance
  * @param  TxData 0..0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SPI_TransmitData16(SPI_TypeDef *SPIx, uint16_t TxData)
{
  *((__IO uint16_t*)&SPIx->DR) = TxData;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (SPI1) || defined (SPI2) || defined (SPI3) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L4xx_LL_SPI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
