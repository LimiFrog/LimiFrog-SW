/**
  ******************************************************************************
  * @file    stm32l4xx_ll_adc.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    16-September-2015
  * @brief   Header file of ADC LL module.
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
#ifndef __STM32L4xx_LL_ADC_H
#define __STM32L4xx_LL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx.h"

/** @addtogroup STM32L4xx_LL_Driver
  * @{
  */

#if defined (ADC1) || defined (ADC2) || defined (ADC3)

/** @defgroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Constants ADC Private Constants
  * @{
  */

/* Internal mask for ADC group regular sequencer:                             */
/* To select into literal LL_ADC_REG_RANK_x the relevant bits for:            */
/* - sequencer register offset                                                */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group regular sequencer configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SQR1_REGOFFSET                 ((uint32_t)0x00000000)
#define ADC_SQR2_REGOFFSET                 ((uint32_t)0x00000100)
#define ADC_SQR3_REGOFFSET                 ((uint32_t)0x00000200)
#define ADC_SQR4_REGOFFSET                 ((uint32_t)0x00000300)

#define ADC_REG_SQRX_REGOFFSET_MASK        (ADC_SQR1_REGOFFSET | ADC_SQR2_REGOFFSET | ADC_SQR3_REGOFFSET | ADC_SQR4_REGOFFSET)
#define ADC_REG_RANK_ID_SQRX_MASK          (ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0)

/* Definition of ADC group regular sequencer bits information to be inserted  */
/* into ADC group regular sequencer ranks literals definition.                */
#define ADC_REG_RANK_1_SQRX_BITOFFSET_POS  ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_SQR1_SQ1) */
#define ADC_REG_RANK_2_SQRX_BITOFFSET_POS  ((uint32_t)12) /* Value equivalent to POSITION_VAL(ADC_SQR1_SQ2) */
#define ADC_REG_RANK_3_SQRX_BITOFFSET_POS  ((uint32_t)18) /* Value equivalent to POSITION_VAL(ADC_SQR1_SQ3) */
#define ADC_REG_RANK_4_SQRX_BITOFFSET_POS  ((uint32_t)24) /* Value equivalent to POSITION_VAL(ADC_SQR1_SQ4) */
#define ADC_REG_RANK_5_SQRX_BITOFFSET_POS  ((uint32_t) 0) /* Value equivalent to POSITION_VAL(ADC_SQR2_SQ5) */
#define ADC_REG_RANK_6_SQRX_BITOFFSET_POS  ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_SQR2_SQ6) */
#define ADC_REG_RANK_7_SQRX_BITOFFSET_POS  ((uint32_t)12) /* Value equivalent to POSITION_VAL(ADC_SQR2_SQ7) */
#define ADC_REG_RANK_8_SQRX_BITOFFSET_POS  ((uint32_t)18) /* Value equivalent to POSITION_VAL(ADC_SQR2_SQ8) */
#define ADC_REG_RANK_9_SQRX_BITOFFSET_POS  ((uint32_t)24) /* Value equivalent to POSITION_VAL(ADC_SQR2_SQ9) */
#define ADC_REG_RANK_10_SQRX_BITOFFSET_POS ((uint32_t) 0) /* Value equivalent to POSITION_VAL(ADC_SQR3_SQ10) */
#define ADC_REG_RANK_11_SQRX_BITOFFSET_POS ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_SQR3_SQ11) */
#define ADC_REG_RANK_12_SQRX_BITOFFSET_POS ((uint32_t)12) /* Value equivalent to POSITION_VAL(ADC_SQR3_SQ12) */
#define ADC_REG_RANK_13_SQRX_BITOFFSET_POS ((uint32_t)18) /* Value equivalent to POSITION_VAL(ADC_SQR3_SQ13) */
#define ADC_REG_RANK_14_SQRX_BITOFFSET_POS ((uint32_t)24) /* Value equivalent to POSITION_VAL(ADC_SQR3_SQ14) */
#define ADC_REG_RANK_15_SQRX_BITOFFSET_POS ((uint32_t) 0) /* Value equivalent to POSITION_VAL(ADC_SQR4_SQ15) */
#define ADC_REG_RANK_16_SQRX_BITOFFSET_POS ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_SQR4_SQ16) */



/* Internal mask for ADC group injected sequencer:                            */
/* To select into literal LL_ADC_INJ_RANK_x the relevant bits for:            */
/* - data register offset                                                     */
/* - sequencer rank bits position into the selected register                  */

/* Internal register offset for ADC group injected data register */
/* (offset placed into a spare area of literal definition) */
#define ADC_JDR1_REGOFFSET                 ((uint32_t)0x00000000)
#define ADC_JDR2_REGOFFSET                 ((uint32_t)0x00000100)
#define ADC_JDR3_REGOFFSET                 ((uint32_t)0x00000200)
#define ADC_JDR4_REGOFFSET                 ((uint32_t)0x00000300)

#define ADC_INJ_JDRX_REGOFFSET_MASK        (ADC_JDR1_REGOFFSET | ADC_JDR2_REGOFFSET | ADC_JDR3_REGOFFSET | ADC_JDR4_REGOFFSET)
#define ADC_INJ_RANK_ID_JSQR_MASK          (ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0)

/* Definition of ADC group injected sequencer bits information to be inserted */
/* into ADC group injected sequencer ranks literals definition.               */
#define ADC_INJ_RANK_1_JSQR_BITOFFSET_POS  ((uint32_t) 8) /* Value equivalent to POSITION_VAL(ADC_JSQR_JSQ1) */
#define ADC_INJ_RANK_2_JSQR_BITOFFSET_POS  ((uint32_t)14) /* Value equivalent to POSITION_VAL(ADC_JSQR_JSQ2) */
#define ADC_INJ_RANK_3_JSQR_BITOFFSET_POS  ((uint32_t)20) /* Value equivalent to POSITION_VAL(ADC_JSQR_JSQ3) */
#define ADC_INJ_RANK_4_JSQR_BITOFFSET_POS  ((uint32_t)26) /* Value equivalent to POSITION_VAL(ADC_JSQR_JSQ4) */



/* Internal mask for ADC group regular trigger:                               */
/* To select into literal LL_ADC_REG_TRIG_x the relevant bits for:            */
/* - regular trigger source                                                   */
/* - regular trigger edge                                                     */
#define ADC_REG_TRIG_EXT_EDGE_DEFAULT       (ADC_CFGR_EXTEN_0) /* Trigger edge set to rising edge (default setting for compatibility with some ADC on other STM32 families having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_SOURCE_MASK            (((LL_ADC_REG_TRIG_SW_START & ADC_CFGR_EXTSEL) << (4 * 0)) | \
                                             ((ADC_CFGR_EXTSEL)                            << (4 * 1)) | \
                                             ((ADC_CFGR_EXTSEL)                            << (4 * 2)) | \
                                             ((ADC_CFGR_EXTSEL)                            << (4 * 3))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_REG_TRIG_EDGE_MASK              (((LL_ADC_REG_TRIG_SW_START & ADC_CFGR_EXTEN) << (4 * 0)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4 * 1)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4 * 2)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT)             << (4 * 3))  )

/* Definition of ADC group regular trigger bits information.                  */
#define ADC_REG_TRIG_EXTSEL_BITOFFSET_POS  ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_CFGR_EXTSEL) */
#define ADC_REG_TRIG_EXTEN_BITOFFSET_POS   ((uint32_t)10) /* Value equivalent to POSITION_VAL(ADC_CFGR_EXTEN) */



/* Internal mask for ADC group injected trigger:                              */
/* To select into literal LL_ADC_INJ_TRIG_x the relevant bits for:            */
/* - injected trigger source                                                  */
/* - injected trigger edge                                                    */
#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT      (ADC_JSQR_JEXTEN_0) /* Trigger edge set to rising edge (default setting for compatibility with some ADC on other STM32 families having this setting set by HW default value) */

/* Mask containing trigger source masks for each of possible                  */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_SOURCE_MASK            (((LL_ADC_INJ_TRIG_SW_START & ADC_JSQR_JEXTSEL) << (4 * 0)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4 * 1)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4 * 2)) | \
                                            ((ADC_JSQR_JEXTSEL)                             << (4 * 3))  )

/* Mask containing trigger edge masks for each of possible                    */
/* trigger edge selection duplicated with shifts [0; 4; 8; 12]                */
/* corresponding to {SW start; ext trigger; ext trigger; ext trigger}.        */
#define ADC_INJ_TRIG_EDGE_MASK              (((LL_ADC_INJ_TRIG_SW_START & ADC_JSQR_JEXTEN) << (4 * 0)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4 * 1)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4 * 2)) | \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT)              << (4 * 3))  )

/* Definition of ADC group injected trigger bits information.                 */
#define ADC_INJ_TRIG_EXTSEL_BITOFFSET_POS  ((uint32_t) 2) /* Value equivalent to POSITION_VAL(ADC_JSQR_JEXTSEL) */
#define ADC_INJ_TRIG_EXTEN_BITOFFSET_POS   ((uint32_t) 6) /* Value equivalent to POSITION_VAL(ADC_JSQR_JEXTEN) */



/* Internal register offset for ADC group regular sequencer configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SQR1_REGOFFSET                 ((uint32_t)0x00000000)
#define ADC_SQR2_REGOFFSET                 ((uint32_t)0x00000100)
#define ADC_SQR3_REGOFFSET                 ((uint32_t)0x00000200)
#define ADC_SQR4_REGOFFSET                 ((uint32_t)0x00000300)

#define ADC_REG_SQRX_REGOFFSET_MASK        (ADC_SQR1_REGOFFSET | ADC_SQR2_REGOFFSET | ADC_SQR3_REGOFFSET | ADC_SQR4_REGOFFSET)
#define ADC_REG_RANK_ID_SQRX_MASK          (ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0)



/* Internal mask for ADC channel:                                             */
/* To select into literal LL_ADC_CHANNEL_x the relevant bits for:             */
/* - channel identifier defined by number                                     */
/* - channel identifier defined by bitfield                                   */
/* - channel differentiation between external channels (connected to          */
/*   GPIO pins) and internal channels (connected to internal paths)           */
/* - channel sampling time defined by SMPRx register offset                   */
/*   and SMPx bits positions into SMPRx register                              */
#define ADC_CHANNEL_ID_NUMBER_MASK         (ADC_CFGR_AWD1CH)
#define ADC_CHANNEL_ID_BITFIELD_MASK       (ADC_AWD2CR_AWD2CH)
#define ADC_CHANNEL_ID_MASK                (ADC_CHANNEL_ID_NUMBER_MASK | ADC_CHANNEL_ID_BITFIELD_MASK | ADC_CHANNEL_ID_INTERNAL_CH_MASK)
/* Equivalent mask of ADC_CHANNEL_NUMBER_MASK aligned on register LSB (bit 0) */
#define ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 (ADC_SQR2_SQ5) /* Equivalent to shift: (ADC_CHANNEL_NUMBER_MASK >> POSITION_VAL(ADC_CHANNEL_NUMBER_MASK)) */

/* Channel differentiation between external and internal channels */
#define ADC_CHANNEL_ID_INTERNAL_CH         ((uint32_t)0x80000000) /* Marker of internal channel */
#define ADC_CHANNEL_ID_INTERNAL_CH_2       ((uint32_t)0x02000000) /* Marker of internal channel for other ADC instances, in case of different ADC internal channels mapped on same channel number on different ADC instances */
#define ADC_CHANNEL_ID_INTERNAL_CH_MASK    (ADC_CHANNEL_ID_INTERNAL_CH | ADC_CHANNEL_ID_INTERNAL_CH_2)

/* Internal register offset for ADC channel sampling time configuration */
/* (offset placed into a spare area of literal definition) */
#define ADC_SMPR1_REGOFFSET                ((uint32_t)0x00000000)
#define ADC_SMPR2_REGOFFSET                ((uint32_t)0x01000000)
#define ADC_CHANNEL_SMPRX_REGOFFSET_MASK   (ADC_SMPR1_REGOFFSET | ADC_SMPR2_REGOFFSET)

#define ADC_CHANNEL_SMPx_BITOFFSET_MASK    ((uint32_t)0x00F80000)
#define ADC_CHANNEL_SMPx_BITOFFSET_POS     ((uint32_t)19)           /* Value equivalent to POSITION_VAL(ADC_CHANNEL_SMPx_BITOFFSET_MASK) */

/* Definition of channels ID number information to be inserted into           */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_NUMBER               ((uint32_t)0x00000000)
#define ADC_CHANNEL_1_NUMBER               (                                                                                ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_2_NUMBER               (                                                            ADC_CFGR_AWD1CH_1                    )
#define ADC_CHANNEL_3_NUMBER               (                                                            ADC_CFGR_AWD1CH_1 | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_4_NUMBER               (                                        ADC_CFGR_AWD1CH_2                                        )
#define ADC_CHANNEL_5_NUMBER               (                                        ADC_CFGR_AWD1CH_2                     | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_6_NUMBER               (                                        ADC_CFGR_AWD1CH_2 | ADC_CFGR_AWD1CH_1                    )
#define ADC_CHANNEL_7_NUMBER               (                                        ADC_CFGR_AWD1CH_2 | ADC_CFGR_AWD1CH_1 | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_8_NUMBER               (                    ADC_CFGR_AWD1CH_3                                                            )
#define ADC_CHANNEL_9_NUMBER               (                    ADC_CFGR_AWD1CH_3                                         | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_10_NUMBER              (                    ADC_CFGR_AWD1CH_3                     | ADC_CFGR_AWD1CH_1                    )
#define ADC_CHANNEL_11_NUMBER              (                    ADC_CFGR_AWD1CH_3                     | ADC_CFGR_AWD1CH_1 | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_12_NUMBER              (                    ADC_CFGR_AWD1CH_3 | ADC_CFGR_AWD1CH_2                                        )
#define ADC_CHANNEL_13_NUMBER              (                    ADC_CFGR_AWD1CH_3 | ADC_CFGR_AWD1CH_2                     | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_14_NUMBER              (                    ADC_CFGR_AWD1CH_3 | ADC_CFGR_AWD1CH_2 | ADC_CFGR_AWD1CH_1                    )
#define ADC_CHANNEL_15_NUMBER              (                    ADC_CFGR_AWD1CH_3 | ADC_CFGR_AWD1CH_2 | ADC_CFGR_AWD1CH_1 | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_16_NUMBER              (ADC_CFGR_AWD1CH_4                                                                                )
#define ADC_CHANNEL_17_NUMBER              (ADC_CFGR_AWD1CH_4                                                             | ADC_CFGR_AWD1CH_0)
#define ADC_CHANNEL_18_NUMBER              (ADC_CFGR_AWD1CH_4                                         | ADC_CFGR_AWD1CH_1                    )

/* Definition of channels ID bitfield information to be inserted into         */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_BITFIELD             (ADC_AWD2CR_AWD2CH_0)
#define ADC_CHANNEL_1_BITFIELD             (ADC_AWD2CR_AWD2CH_1)
#define ADC_CHANNEL_2_BITFIELD             (ADC_AWD2CR_AWD2CH_2)
#define ADC_CHANNEL_3_BITFIELD             (ADC_AWD2CR_AWD2CH_3)
#define ADC_CHANNEL_4_BITFIELD             (ADC_AWD2CR_AWD2CH_4)
#define ADC_CHANNEL_5_BITFIELD             (ADC_AWD2CR_AWD2CH_5)
#define ADC_CHANNEL_6_BITFIELD             (ADC_AWD2CR_AWD2CH_6)
#define ADC_CHANNEL_7_BITFIELD             (ADC_AWD2CR_AWD2CH_7)
#define ADC_CHANNEL_8_BITFIELD             (ADC_AWD2CR_AWD2CH_8)
#define ADC_CHANNEL_9_BITFIELD             (ADC_AWD2CR_AWD2CH_9)
#define ADC_CHANNEL_10_BITFIELD            (ADC_AWD2CR_AWD2CH_10)
#define ADC_CHANNEL_11_BITFIELD            (ADC_AWD2CR_AWD2CH_11)
#define ADC_CHANNEL_12_BITFIELD            (ADC_AWD2CR_AWD2CH_12)
#define ADC_CHANNEL_13_BITFIELD            (ADC_AWD2CR_AWD2CH_13)
#define ADC_CHANNEL_14_BITFIELD            (ADC_AWD2CR_AWD2CH_14)
#define ADC_CHANNEL_15_BITFIELD            (ADC_AWD2CR_AWD2CH_15)
#define ADC_CHANNEL_16_BITFIELD            (ADC_AWD2CR_AWD2CH_16)
#define ADC_CHANNEL_17_BITFIELD            (ADC_AWD2CR_AWD2CH_17)
#define ADC_CHANNEL_18_BITFIELD            (ADC_AWD2CR_AWD2CH_18)

/* Definition of channels sampling time information to be inserted into       */
/* channels literals definition.                                              */
#define ADC_CHANNEL_0_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t) 0) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP0) */
#define ADC_CHANNEL_1_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t) 3) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP1) */
#define ADC_CHANNEL_2_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t) 6) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP2) */
#define ADC_CHANNEL_3_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t) 9) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP3) */
#define ADC_CHANNEL_4_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)12) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP4) */
#define ADC_CHANNEL_5_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)15) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP5) */
#define ADC_CHANNEL_6_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)18) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP6) */
#define ADC_CHANNEL_7_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)21) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP7) */
#define ADC_CHANNEL_8_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)24) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP8) */
#define ADC_CHANNEL_9_SMP                  (ADC_SMPR1_REGOFFSET | (((uint32_t)27) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR1_SMP9) */
#define ADC_CHANNEL_10_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t) 0) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP10) */
#define ADC_CHANNEL_11_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t) 3) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP11) */
#define ADC_CHANNEL_12_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t) 6) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP12) */
#define ADC_CHANNEL_13_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t) 9) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP13) */
#define ADC_CHANNEL_14_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t)12) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP14) */
#define ADC_CHANNEL_15_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t)15) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP15) */
#define ADC_CHANNEL_16_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t)18) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP16) */
#define ADC_CHANNEL_17_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t)21) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP17) */
#define ADC_CHANNEL_18_SMP                 (ADC_SMPR2_REGOFFSET | (((uint32_t)24) << ADC_CHANNEL_SMPx_BITOFFSET_POS)) /* Value shifted is equivalent to POSITION_VAL(ADC_SMPR2_SMP18) */


/* Internal mask for ADC mode single or differential ended:                   */
/* To select into literals LL_ADC_SINGLE_ENDED or LL_ADC_SINGLE_DIFFERENTIAL  */
/* the relevant bits for:                                                     */
/* (concatenation of multiple bits used in different registers)               */
/* - ADC calibration: calibration start, calibration factor get or set        */
/* - ADC channels: set each ADC channel ending mode                           */
#define ADC_SINGLEDIFF_CALIB_START_MASK    (ADC_CR_ADCALDIF)
#define ADC_SINGLEDIFF_CALIB_FACTOR_MASK   (ADC_CALFACT_CALFACT_D | ADC_CALFACT_CALFACT_S)
#define ADC_SINGLEDIFF_CHANNEL_MASK        (ADC_CHANNEL_ID_BITFIELD_MASK) /* Equivalent to ADC_DIFSEL_DIFSEL */
#define ADC_SINGLEDIFF_CHANNEL_SHIFT_MASK  (ADC_CALFACT_CALFACT_S_5) /* Bit chosen to perform of shift when single mode is selected, shift value out of channels bits range. */


/* Internal mask for ADC analog watchdog:                                     */
/* To select into literals LL_ADC_AWD_CHANNELx_xxx the relevant bits for:     */
/* (concatenation of multiple bits used in different analog watchdogs,        */
/* (feature of several watchdogs not available on all STM32 families)).       */
/* - analog watchdog 1: monitored channel defined by number,                  */
/*   selection of ADC group (ADC groups regular and-or injected).             */
/* - analog watchdog 2 and 3: monitored channel defined by bitfield, no       */
/*   selection on groups.                                                     */

/* Internal register offset for ADC analog watchdog channel configuration */
#define ADC_AWD_CR1_REGOFFSET              ((uint32_t)0x00000000)
#define ADC_AWD_CR2_REGOFFSET              ((uint32_t)0x00080000)
#define ADC_AWD_CR3_REGOFFSET              ((uint32_t)0x00100000)

/* Register offset gap between AWD1 and AWD2-AWD3 configuration registers */
/* (Set separately as ADC_AWD_CRX_REGOFFSET to spare 32 bits space */
#define ADC_AWD_CR12_REGOFFSETGAP_MASK     (ADC_AWD2CR_AWD2CH_0)
#define ADC_AWD_CR12_REGOFFSETGAP_VAL      ((uint32_t)0x00000024)

#define ADC_AWD_CRX_REGOFFSET_MASK         (ADC_AWD_CR1_REGOFFSET | ADC_AWD_CR2_REGOFFSET | ADC_AWD_CR3_REGOFFSET)

#define ADC_AWD_CR1_CHANNEL_MASK           (ADC_CFGR_AWD1CH | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL)
#define ADC_AWD_CR23_CHANNEL_MASK          (ADC_AWD2CR_AWD2CH)
#define ADC_AWD_CR_ALL_CHANNEL_MASK        (ADC_AWD_CR1_CHANNEL_MASK | ADC_AWD_CR23_CHANNEL_MASK)

/* Internal register offset for ADC analog watchdog threshold configuration */
#define ADC_AWD_TR1_REGOFFSET              (ADC_AWD_CR1_REGOFFSET)
#define ADC_AWD_TR2_REGOFFSET              (ADC_AWD_CR2_REGOFFSET)
#define ADC_AWD_TR3_REGOFFSET              (ADC_AWD_CR3_REGOFFSET)
#define ADC_AWD_TRX_REGOFFSET_MASK         (ADC_AWD_TR1_REGOFFSET | ADC_AWD_TR2_REGOFFSET | ADC_AWD_TR3_REGOFFSET)


/* Internal mask for ADC offset:                                              */
/* Internal register offset for ADC offset number configuration */
#define ADC_OFR1_REGOFFSET                 ((uint32_t)0x00000000)
#define ADC_OFR2_REGOFFSET                 ((uint32_t)0x00000001)
#define ADC_OFR3_REGOFFSET                 ((uint32_t)0x00000002)
#define ADC_OFR4_REGOFFSET                 ((uint32_t)0x00000003)
#define ADC_OFRx_REGOFFSET_MASK            (ADC_OFR1_REGOFFSET | ADC_OFR2_REGOFFSET | ADC_OFR3_REGOFFSET | ADC_OFR4_REGOFFSET)


/* ADC registers bits positions */
#define ADC_CFGR_RES_BITOFFSET_POS         ((uint32_t) 3) /* Value equivalent to POSITION_VAL(ADC_CFGR_RES) */
#define ADC_TR1_HT1_BITOFFSET_POS          ((uint32_t)16) /* Value equivalent to POSITION_VAL(ADC_TR1_HT1) */


/* ADC registers bits groups */
#define ADC_CR_BITS_PROPERTY_RS            (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART | ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN) /* ADC register CR bits with HW property "rs": Software can read as well as set this bit. Writing '0' has no effect on the bit value. */


/* ADC internal channels related definitions */
/* Internal voltage reference VrefInt */
#define VREFINT_CAL_ADDR                   ((uint16_t*) ((uint32_t)0x1FFF75AA)) /* Internal voltage reference, address of parameter VREFINT_CAL: VrefInt ADC raw data acquired at temperature 30 DegC (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
#define VREFINT_CAL_VREF                   ((uint32_t) 3000)                    /* Analog voltage reference (Vref+) value with which temperature sensor has been calibrated in production (tolerance: +-10 mV) (unit: mV). */
/* Temperature sensor */
#define TEMPSENSOR_CAL1_ADDR               ((uint16_t*) ((uint32_t)0x1FFF75A8)) /* Internal temperature sensor, address of parameter TS_CAL1: On STM32L4, temperature sensor ADC raw data acquired at temperature  30 DegC (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
#define TEMPSENSOR_CAL2_ADDR               ((uint16_t*) ((uint32_t)0x1FFF75CA)) /* Internal temperature sensor, address of parameter TS_CAL2: On STM32L4, temperature sensor ADC raw data acquired at temperature 110 DegC (tolerance: +-5 DegC), Vref+ = 3.0 V (tolerance: +-10 mV). */
#define TEMPSENSOR_CAL1_TEMP               (( int32_t)   30)                    /* Internal temperature sensor, temperature at which temperature sensor has been calibrated in production for data into TEMPSENSOR_CAL1_ADDR (tolerance: +-5 DegC) (unit: DegC). */
#define TEMPSENSOR_CAL2_TEMP               (( int32_t)  110)                    /* Internal temperature sensor, temperature at which temperature sensor has been calibrated in production for data into TEMPSENSOR_CAL2_ADDR (tolerance: +-5 DegC) (unit: DegC). */
#define TEMPSENSOR_CAL_VREFANALOG          ((uint32_t) 3000)                    /* Analog voltage reference (Vref+) voltage with which temperature sensor has been calibrated in production (+-10 mV) (unit: mV). */


/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: isolate bits with the
  *         selected mask and shift them to the register LSB
  *         (shift mask on register position bit 0).
  * @param  __BITS__ Bits in register 32 bits
  * @param  __MASK__ Mask in register 32 bits
  * @retval Bits in register 32 bits
*/
#define __ADC_MASK_SHIFT(__BITS__, __MASK__)                                   \
  (((__BITS__) & (__MASK__)) >> POSITION_VAL((__MASK__)))

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
*/
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
 ((uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2))))

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_LL_EC_GET_FLAG ADC flags
  * @brief    Flags defines which can be used with LL_ADC_ReadReg function
  * @{
  */
#define LL_ADC_ISR_ADRDY                   ADC_ISR_ADRDY      /*!< ADC flag ADC instance ready */
#define LL_ADC_ISR_EOC                     ADC_ISR_EOC        /*!< ADC flag ADC group regular end of unitary conversion */
#define LL_ADC_ISR_EOS                     ADC_ISR_EOS        /*!< ADC flag ADC group regular end of sequence conversions */
#define LL_ADC_ISR_OVR                     ADC_ISR_OVR        /*!< ADC flag ADC group regular overrun */
#define LL_ADC_ISR_EOSMP                   ADC_ISR_EOSMP      /*!< ADC flag ADC group regular end of sampling phase */
#define LL_ADC_ISR_JEOC                    ADC_ISR_JEOC       /*!< ADC flag ADC group injected end of unitary conversion */
#define LL_ADC_ISR_JEOS                    ADC_ISR_JEOS       /*!< ADC flag ADC group injected end of sequence conversions */
#define LL_ADC_ISR_JQOVF                   ADC_ISR_JQOVF      /*!< ADC flag ADC group injected contexts queue overflow */
#define LL_ADC_ISR_AWD1                    ADC_ISR_AWD1       /*!< ADC flag ADC analog watchdog 1 */
#define LL_ADC_ISR_AWD2                    ADC_ISR_AWD2       /*!< ADC flag ADC analog watchdog 2 */
#define LL_ADC_ISR_AWD3                    ADC_ISR_AWD3       /*!< ADC flag ADC analog watchdog 3 */
#define LL_ADC_CSR_ADRDY_MST               ADC_CSR_ADRDY_MST  /*!< ADC flag ADC instance ready of the ADC master */
#define LL_ADC_CSR_ADRDY_SLV               ADC_CSR_ADRDY_SLV  /*!< ADC flag ADC instance ready of the ADC slave */
#if defined(ADC2)
#define LL_ADC_CSR_EOC_MST                 ADC_CSR_EOC_MST    /*!< ADC flag multimode ADC group regular end of unitary conversion of the ADC master */
#define LL_ADC_CSR_EOC_SLV                 ADC_CSR_EOC_SLV    /*!< ADC flag multimode ADC group regular end of unitary conversion of the ADC slave */
#define LL_ADC_CSR_EOS_MST                 ADC_CSR_EOS_MST    /*!< ADC flag multimode ADC group regular end of sequence conversions of the ADC master */
#define LL_ADC_CSR_EOS_SLV                 ADC_CSR_EOS_SLV    /*!< ADC flag multimode ADC group regular end of sequence conversions of the ADC slave */
#define LL_ADC_CSR_OVR_MST                 ADC_CSR_OVR_MST    /*!< ADC flag multimode ADC group regular overrun of the ADC master */
#define LL_ADC_CSR_OVR_SLV                 ADC_CSR_OVR_SLV    /*!< ADC flag multimode ADC group regular overrun of the ADC slave */
#define LL_ADC_CSR_EOSMP_MST               ADC_CSR_EOSMP_MST  /*!< ADC flag multimode ADC group regular end of sampling phase of the ADC master */
#define LL_ADC_CSR_EOSMP_SLV               ADC_CSR_EOSMP_SLV  /*!< ADC flag multimode ADC group regular end of sampling phase of the ADC slave */
#define LL_ADC_CSR_JEOC_MST                ADC_CSR_JEOC_MST   /*!< ADC flag multimode ADC group injected end of unitary conversion of the ADC master */
#define LL_ADC_CSR_JEOC_SLV                ADC_CSR_JEOC_SLV   /*!< ADC flag multimode ADC group injected end of unitary conversion of the ADC slave */
#define LL_ADC_CSR_JEOS_MST                ADC_CSR_JEOS_MST   /*!< ADC flag multimode ADC group injected end of sequence conversions of the ADC master */
#define LL_ADC_CSR_JEOS_SLV                ADC_CSR_JEOS_SLV   /*!< ADC flag multimode ADC group injected end of sequence conversions of the ADC slave */
#define LL_ADC_CSR_JQOVF_MST               ADC_CSR_JQOVF_MST  /*!< ADC flag multimode ADC group injected contexts queue overflow of the ADC master */
#define LL_ADC_CSR_JQOVF_SLV               ADC_CSR_JQOVF_SLV  /*!< ADC flag multimode ADC group injected contexts queue overflow of the ADC slave */
#define LL_ADC_CSR_AWD1_MST                ADC_CSR_AWD1_MST   /*!< ADC flag multimode ADC analog watchdog 1 of the ADC master */
#define LL_ADC_CSR_AWD1_SLV                ADC_CSR_AWD1_SLV   /*!< ADC flag multimode ADC analog watchdog 1 of the ADC slave */
#define LL_ADC_CSR_AWD2_MST                ADC_CSR_AWD2_MST   /*!< ADC flag multimode ADC analog watchdog 2 of the ADC master */
#define LL_ADC_CSR_AWD2_SLV                ADC_CSR_AWD2_SLV   /*!< ADC flag multimode ADC analog watchdog 2 of the ADC slave */
#define LL_ADC_CSR_AWD3_MST                ADC_CSR_AWD3_MST   /*!< ADC flag multimode ADC analog watchdog 3 of the ADC master */
#define LL_ADC_CSR_AWD3_SLV                ADC_CSR_AWD3_SLV   /*!< ADC flag multimode ADC analog watchdog 3 of the ADC slave */
#endif
/**
  * @}
  */

/** @defgroup ADC_LL_EC_IT ADC interruptions
  * @brief    IT defines which can be used with LL_ADC_ReadReg and  LL_ADC_WriteReg functions
  * @{
  */
#define LL_ADC_IER_ADRDY                   ADC_IER_ADRDY  /*!< ADC interruption ADC instance ready */
#define LL_ADC_IER_EOC                     ADC_IER_EOC    /*!< ADC interruption ADC group regular end of unitary conversion */
#define LL_ADC_IER_EOS                     ADC_IER_EOS    /*!< ADC interruption ADC group regular end of sequence conversions */
#define LL_ADC_IER_OVR                     ADC_IER_OVR    /*!< ADC interruption ADC group regular overrun */
#define LL_ADC_IER_EOSMP                   ADC_IER_EOSMP  /*!< ADC interruption ADC group regular end of sampling phase */
#define LL_ADC_IER_JEOC                    ADC_IER_JEOC   /*!< ADC interruption ADC group injected end of unitary conversion */
#define LL_ADC_IER_JEOS                    ADC_IER_JEOS   /*!< ADC interruption ADC group injected end of sequence conversions */
#define LL_ADC_IER_JQOVF                   ADC_IER_JQOVF  /*!< ADC interruption ADC group injected contexts queue overflow */
#define LL_ADC_IER_AWD1                    ADC_IER_AWD1   /*!< ADC interruption ADC analog watchdog 1 */
#define LL_ADC_IER_AWD2                    ADC_IER_AWD2   /*!< ADC interruption ADC analog watchdog 2 */
#define LL_ADC_IER_AWD3                    ADC_IER_AWD3   /*!< ADC interruption ADC analog watchdog 3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REGISTERS  ADC instance - Registers compliant with specific purpose
  * @{
  */
/* List of ADC registers intended to be used (most commonly) with             */
/* DMA transfer.                                                              */
/* Refer to function @ref LL_ADC_DMA_GetRegAddr().                            */
#define LL_ADC_DMA_REG_REGULAR_DATA          ((uint32_t)0x00000000) /* ADC group regular conversion data register (corresponding to register DR) to be used with ADC configured in independent mode. Without DMA transfer, register accessed by LL function @ref LL_ADC_REG_ReadConversionData32() and other functions @ref LL_ADC_REG_ReadConversionDatax() */
#if defined(ADC2)
#define LL_ADC_DMA_REG_REGULAR_DATA_MULTI    ((uint32_t)0x00000001) /* ADC group regular conversion data register (corresponding to register CDR) to be used with ADC configured in multimode (available on STM32 devices with several ADC instances). Without DMA transfer, register accessed by LL function @ref LL_ADC_REG_ReadMultiConversionData32() */
#endif
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_CLOCK_SOURCE  ADC common - Clock source
  * @{
  */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV1        (ADC_CCR_CKMODE_0)                                    /*!< ADC synchronous clock derived from AHB clock not divided  */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV2        (ADC_CCR_CKMODE_1                   )                 /*!< ADC synchronous clock derived from AHB clock divided by 2 */
#define LL_ADC_CLOCK_SYNC_PCLK_DIV4        (ADC_CCR_CKMODE_1 | ADC_CCR_CKMODE_0)                 /*!< ADC synchronous clock derived from AHB clock divided by 4 */
#define LL_ADC_CLOCK_ASYNC_DIV1            ((uint32_t)0x00000000)                                /*!< ADC asynchronous clock not divided    */
#define LL_ADC_CLOCK_ASYNC_DIV2            (ADC_CCR_PRESC_0)                                     /*!< ADC asynchronous clock divided by 2   */
#define LL_ADC_CLOCK_ASYNC_DIV4            (ADC_CCR_PRESC_1                  )                   /*!< ADC asynchronous clock divided by 4   */
#define LL_ADC_CLOCK_ASYNC_DIV6            (ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock divided by 6   */
#define LL_ADC_CLOCK_ASYNC_DIV8            (ADC_CCR_PRESC_2                                    ) /*!< ADC asynchronous clock divided by 8   */
#define LL_ADC_CLOCK_ASYNC_DIV10           (ADC_CCR_PRESC_2                   | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock divided by 10  */
#define LL_ADC_CLOCK_ASYNC_DIV12           (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1                  ) /*!< ADC asynchronous clock divided by 12  */
#define LL_ADC_CLOCK_ASYNC_DIV16           (ADC_CCR_PRESC_2 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock divided by 16  */
#define LL_ADC_CLOCK_ASYNC_DIV32           (ADC_CCR_PRESC_3)                                     /*!< ADC asynchronous clock divided by 32  */
#define LL_ADC_CLOCK_ASYNC_DIV64           (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_0)                   /*!< ADC asynchronous clock divided by 64  */
#define LL_ADC_CLOCK_ASYNC_DIV128          (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1)                   /*!< ADC asynchronous clock divided by 128 */
#define LL_ADC_CLOCK_ASYNC_DIV256          (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1 | ADC_CCR_PRESC_0) /*!< ADC asynchronous clock divided by 256 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_COMMON_PATH_INTERNAL  ADC common - Measurement path to internal channels
  * @{
  */
/* Note: Other measurement paths to internal channels may be available        */
/*       (connections to other peripherals).                                  */
/*       If they are not listed below, they do not require any specific       */
/*       path enable. In this case, Access to measurement path is done        */
/*       only by selecting the corresponding ADC internal channel.            */
#define LL_ADC_PATH_INTERNAL_NONE          ((uint32_t)0x00000000) /*!< ADC measurement pathes all disabled */
#define LL_ADC_PATH_INTERNAL_VREFINT       (ADC_CCR_VREFEN)       /*!< ADC measurement path to internal channel VrefInt */
#define LL_ADC_PATH_INTERNAL_TEMPSENSOR    (ADC_CCR_TSEN)         /*!< ADC measurement path to internal channel temperature sensor */
#define LL_ADC_PATH_INTERNAL_VBAT          (ADC_CCR_VBATEN)       /*!< ADC measurement path to internal channel Vbat */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_RESOLUTION  ADC instance - Resolution
  * @{
  */
#define LL_ADC_RESOLUTION_12B              ((uint32_t)0x00000000)              /*!< ADC resolution 12 bits */
#define LL_ADC_RESOLUTION_10B              (                 ADC_CFGR_RES_0)   /*!< ADC resolution 10 bits */
#define LL_ADC_RESOLUTION_8B               (ADC_CFGR_RES_1                 )   /*!< ADC resolution  8 bits */
#define LL_ADC_RESOLUTION_6B               (ADC_CFGR_RES_1 | ADC_CFGR_RES_0)   /*!< ADC resolution  6 bits */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_DATA_ALIGN  ADC instance - Data alignment
  * @{
  */
#define LL_ADC_DATA_ALIGN_RIGHT            ((uint32_t)0x00000000) /*!< ADC conversion data alignment: right aligned (alignment on data register LSB bit 0)*/
#define LL_ADC_DATA_ALIGN_LEFT             (ADC_CFGR_ALIGN)       /*!< ADC conversion data alignment: left aligned (aligment on data register MSB bit 15)*/
/**
  * @}
  */

/** @defgroup ADC_LL_EC_LP_MODE  ADC instance - Low power mode
  * @{
  */
#define LL_ADC_LP_MODE_NONE                ((uint32_t)0x00000000) /*!< No ADC low power mode activated */
#define LL_ADC_LP_AUTOWAIT                 (ADC_CFGR_AUTDLY)      /*!< ADC low power mode auto delay: Dynamic low power mode, ADC conversions are performed only when necessary. See description with function @ref LL_ADC_SetLowPowerMode(). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_NB  ADC instance - Offset number
  * @{
  */
#define LL_ADC_OFFSET_1                    ADC_OFR1_REGOFFSET /*!< ADC offset number 1: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_2                    ADC_OFR2_REGOFFSET /*!< ADC offset number 2: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_3                    ADC_OFR3_REGOFFSET /*!< ADC offset number 3: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define LL_ADC_OFFSET_4                    ADC_OFR4_REGOFFSET /*!< ADC offset number 4: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OFFSET_STATE ADC instance - Offset state
  * @{
  */
#define LL_ADC_OFFSET_DISABLE              ((uint32_t)0x00000000) /*!< ADC offset disabled (among ADC selected offset number 1, 2, 3 or 4) */
#define LL_ADC_OFFSET_ENABLE               (ADC_OFR1_OFFSET1_EN)  /*!< ADC offset enabled (among ADC selected offset number 1, 2, 3 or 4) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define LL_ADC_GROUP_REGULAR               ((uint32_t)0x00000001) /*!< ADC group regular (available on all STM32 devices) */
#define LL_ADC_GROUP_INJECTED              ((uint32_t)0x00000002) /*!< ADC group injected (not available on all STM32 devices)*/
#define LL_ADC_GROUP_REGULAR_INJECTED      ((uint32_t)0x00000003) /*!< ADC both groups regular and injected */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_CHANNEL  ADC instance - Channel number
  * @{
  */
#define LL_ADC_CHANNEL_0                   (ADC_CHANNEL_0_NUMBER  | ADC_CHANNEL_0_SMP  | ADC_CHANNEL_0_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN0  */
#define LL_ADC_CHANNEL_1                   (ADC_CHANNEL_1_NUMBER  | ADC_CHANNEL_1_SMP  | ADC_CHANNEL_1_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN1  */
#define LL_ADC_CHANNEL_2                   (ADC_CHANNEL_2_NUMBER  | ADC_CHANNEL_2_SMP  | ADC_CHANNEL_2_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN2  */
#define LL_ADC_CHANNEL_3                   (ADC_CHANNEL_3_NUMBER  | ADC_CHANNEL_3_SMP  | ADC_CHANNEL_3_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN3  */
#define LL_ADC_CHANNEL_4                   (ADC_CHANNEL_4_NUMBER  | ADC_CHANNEL_4_SMP  | ADC_CHANNEL_4_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN4  */
#define LL_ADC_CHANNEL_5                   (ADC_CHANNEL_5_NUMBER  | ADC_CHANNEL_5_SMP  | ADC_CHANNEL_5_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN5  */
#define LL_ADC_CHANNEL_6                   (ADC_CHANNEL_6_NUMBER  | ADC_CHANNEL_6_SMP  | ADC_CHANNEL_6_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN6  */
#define LL_ADC_CHANNEL_7                   (ADC_CHANNEL_7_NUMBER  | ADC_CHANNEL_7_SMP  | ADC_CHANNEL_7_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN7  */
#define LL_ADC_CHANNEL_8                   (ADC_CHANNEL_8_NUMBER  | ADC_CHANNEL_8_SMP  | ADC_CHANNEL_8_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN8  */
#define LL_ADC_CHANNEL_9                   (ADC_CHANNEL_9_NUMBER  | ADC_CHANNEL_9_SMP  | ADC_CHANNEL_9_BITFIELD ) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN9  */
#define LL_ADC_CHANNEL_10                  (ADC_CHANNEL_10_NUMBER | ADC_CHANNEL_10_SMP | ADC_CHANNEL_10_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN10 */
#define LL_ADC_CHANNEL_11                  (ADC_CHANNEL_11_NUMBER | ADC_CHANNEL_11_SMP | ADC_CHANNEL_11_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN11 */
#define LL_ADC_CHANNEL_12                  (ADC_CHANNEL_12_NUMBER | ADC_CHANNEL_12_SMP | ADC_CHANNEL_12_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN12 */
#define LL_ADC_CHANNEL_13                  (ADC_CHANNEL_13_NUMBER | ADC_CHANNEL_13_SMP | ADC_CHANNEL_13_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN13 */
#define LL_ADC_CHANNEL_14                  (ADC_CHANNEL_14_NUMBER | ADC_CHANNEL_14_SMP | ADC_CHANNEL_14_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN14 */
#define LL_ADC_CHANNEL_15                  (ADC_CHANNEL_15_NUMBER | ADC_CHANNEL_15_SMP | ADC_CHANNEL_15_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN15 */
#define LL_ADC_CHANNEL_16                  (ADC_CHANNEL_16_NUMBER | ADC_CHANNEL_16_SMP | ADC_CHANNEL_16_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN16 */
#define LL_ADC_CHANNEL_17                  (ADC_CHANNEL_17_NUMBER | ADC_CHANNEL_17_SMP | ADC_CHANNEL_17_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN17 */
#define LL_ADC_CHANNEL_18                  (ADC_CHANNEL_18_NUMBER | ADC_CHANNEL_18_SMP | ADC_CHANNEL_18_BITFIELD) /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN18 */
#define LL_ADC_CHANNEL_VREFINT             (LL_ADC_CHANNEL_0  | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to VrefInt: Internal voltage reference. On STM32L4, ADC channel available only on ADC instance: ADC1. */
#define LL_ADC_CHANNEL_TEMPSENSOR          (LL_ADC_CHANNEL_17 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Temperature sensor. On STM32L4, ADC channel available only on ADC instances: ADC1, ADC3. */
#define LL_ADC_CHANNEL_VBAT                (LL_ADC_CHANNEL_18 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to Vbat/3: Vbat voltage through an dividor ladder of factor 1/3 to have Vbat always below Vdda. On STM32L4, ADC channel available only on ADC instances: ADC1, ADC3. */
#define LL_ADC_CHANNEL_DAC1CH1_ADC2        (LL_ADC_CHANNEL_17 | ADC_CHANNEL_ID_INTERNAL_CH | ADC_CHANNEL_ID_INTERNAL_CH_2) /*!< ADC internal channel connected to DAC1 channel 1, channel specific to ADC2 */
#define LL_ADC_CHANNEL_DAC1CH2_ADC2        (LL_ADC_CHANNEL_18 | ADC_CHANNEL_ID_INTERNAL_CH | ADC_CHANNEL_ID_INTERNAL_CH_2) /*!< ADC internal channel connected to DAC1 channel 2, channel specific to ADC2 */
#define LL_ADC_CHANNEL_DAC1CH1_ADC3        (LL_ADC_CHANNEL_14 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to DAC1 channel 1, channel specific to ADC3 */
#define LL_ADC_CHANNEL_DAC1CH2_ADC3        (LL_ADC_CHANNEL_15 | ADC_CHANNEL_ID_INTERNAL_CH) /*!< ADC internal channel connected to DAC1 channel 2, channel specific to ADC3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIG_SOURCE  ADC group regular - Trigger source
  * @{
  */
#define LL_ADC_REG_TRIG_SW_START           ((uint32_t)0x00000000)                                                                                          /*!< ADC group regular conversion trigger internal (SW start) */
#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO      (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from TIM1 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_TRGO2     (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from TIM1 TRGO2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CC1       (ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                                                 /*!< ADC group regular conversion trigger external from TIM1 CC1. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CC2       (ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                             /*!< ADC group regular conversion trigger external from TIM1 CC2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM1_CC3       (ADC_CFGR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                             /*!< ADC group regular conversion trigger external from TIM1 CC3. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM2_TRGO      (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                     /*!< ADC group regular conversion trigger external from TIM2 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM2_CC2       (ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from TIM2 CC2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM3_TRGO      (ADC_CFGR_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                             /*!< ADC group regular conversion trigger external from TIM3 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM3_CC4       (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT) /*!< ADC group regular conversion trigger external from TIM3 CC4. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM4_TRGO      (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from TIM4 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM4_CC4       (ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from TIM4 CC4. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM6_TRGO      (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                     /*!< ADC group regular conversion trigger external from TIM6 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM8_TRGO      (ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                     /*!< ADC group regular conversion trigger external from TIM8 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM8_TRGO2     (ADC_CFGR_EXTSEL_3 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                                             /*!< ADC group regular conversion trigger external from TIM8 TRGO2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_TIM15_TRGO     (ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                     /*!< ADC group regular conversion trigger external from TIM15 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_REG_TRIG_EXT_EXTI_LINE11    (ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT)                                         /*!< ADC group regular conversion trigger external from external interrupt line 11. Trigger edge set to rising edge (default setting). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_TRIG_EDGE  ADC group regular - Trigger edge
  * @{
  */
#define LL_ADC_REG_TRIG_EXT_RISING         (                   ADC_CFGR_EXTEN_0)   /*!< ADC group regular conversion trigger polarity set to rising edge */
#define LL_ADC_REG_TRIG_EXT_FALLING        (ADC_CFGR_EXTEN_1                   )   /*!< ADC group regular conversion trigger polarity set to falling edge */
#define LL_ADC_REG_TRIG_EXT_RISINGFALLING  (ADC_CFGR_EXTEN_1 | ADC_CFGR_EXTEN_0)   /*!< ADC group regular conversion trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_CONV  ADC group regular - Continuous mode
* @{
*/
#define LL_ADC_REG_CONV_SINGLE             ((uint32_t)0x00000000) /*!< ADC conversions are performed in single mode: one conversion per trigger */
#define LL_ADC_REG_CONV_CONTINUOUS         (ADC_CFGR_CONT)        /*!< ADC conversions are performed in continuous mode: after the first trigger, following conversions launched successively automatically */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_DMA_TRANSFER  ADC group regular - DMA transfer
  * @{
  */
#define LL_ADC_REG_DMA_TRANSFER_NONE       ((uint32_t)0x00000000)               /*!< ADC conversions are not transferred by DMA */
#define LL_ADC_REG_DMA_TRANSFER_LIMITED    (                  ADC_CFGR_DMAEN)   /*!< ADC conversions are transferred by DMA, in limited mode (one shot mode): DMA transfer requests are stopped when number of DMA data transfers (number of ADC conversions) is reached. This ADC mode is intended to be used with DMA mode non-circular. */
#define LL_ADC_REG_DMA_TRANSFER_UNLIMITED  (ADC_CFGR_DMACFG | ADC_CFGR_DMAEN)   /*!< ADC conversions are transferred by DMA, in unlimited mode: DMA transfer requests are unlimited, whatever number of DMA data transferred (number of ADC conversions). This ADC mode is intended to be used with DMA mode circular. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_OVR  ADC group regular - Overrun
* @{
*/
#define LL_ADC_REG_OVR_DATA_PRESERVED      ((uint32_t)0x00000000) /*!< ADC group regular behaviour in case of overrun: data preserved */
#define LL_ADC_REG_OVR_DATA_OVERWRITTEN    (ADC_CFGR_OVRMOD)      /*!< ADC group regular behaviour in case of overrun: data overwritten */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_LENGTH  ADC group regular - Sequencer length
  * @{
  */
#define LL_ADC_REG_SEQ_SCAN_DISABLE        ((uint32_t)0x00000000)                                      /*!< ADC group regular sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS  (                                             ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 2 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS  (                              ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 3 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS  (                              ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 4 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS  (               ADC_SQR1_L_2                              ) /*!< ADC group regular sequencer enable with 5 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS  (               ADC_SQR1_L_2                | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 6 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS  (               ADC_SQR1_L_2 | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 7 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS  (               ADC_SQR1_L_2 | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 8 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS  (ADC_SQR1_L_3                                             ) /*!< ADC group regular sequencer enable with 9 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS (ADC_SQR1_L_3                               | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 10 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS (ADC_SQR1_L_3                | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 11 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS (ADC_SQR1_L_3                | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 12 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2                              ) /*!< ADC group regular sequencer enable with 13 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2                | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 14 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 | ADC_SQR1_L_1               ) /*!< ADC group regular sequencer enable with 15 ranks in the sequence */
#define LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS (ADC_SQR1_L_3 | ADC_SQR1_L_2 | ADC_SQR1_L_1 | ADC_SQR1_L_0) /*!< ADC group regular sequencer enable with 16 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_SEQ_DISCONT  ADC group regular - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_REG_SEQ_DISCONT_DISABLE     ((uint32_t)0x00000000)                                                           /*!< ADC group regular sequencer discontinuous mode disable */
#define LL_ADC_REG_SEQ_DISCONT_1RANK       (                                                               ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every rank */
#define LL_ADC_REG_SEQ_DISCONT_2RANKS      (                                          ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enabled with sequence interruption every 2 ranks */
#define LL_ADC_REG_SEQ_DISCONT_3RANKS      (                     ADC_CFGR_DISCNUM_1                      | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 3 ranks */
#define LL_ADC_REG_SEQ_DISCONT_4RANKS      (                     ADC_CFGR_DISCNUM_1 | ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 4 ranks */
#define LL_ADC_REG_SEQ_DISCONT_5RANKS      (ADC_CFGR_DISCNUM_2                                           | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 5 ranks */
#define LL_ADC_REG_SEQ_DISCONT_6RANKS      (ADC_CFGR_DISCNUM_2                      | ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 6 ranks */
#define LL_ADC_REG_SEQ_DISCONT_7RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCNUM_1                      | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 7 ranks */
#define LL_ADC_REG_SEQ_DISCONT_8RANKS      (ADC_CFGR_DISCNUM_2 | ADC_CFGR_DISCNUM_1 | ADC_CFGR_DISCNUM_0 | ADC_CFGR_DISCEN) /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 8 ranks */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_REG_RANKS  ADC group regular - Sequencer ranks
  * @{
  */
#define LL_ADC_REG_RANK_1                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_1_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 1 */
#define LL_ADC_REG_RANK_2                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_2_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 2 */
#define LL_ADC_REG_RANK_3                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_3_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 3 */
#define LL_ADC_REG_RANK_4                  (ADC_SQR1_REGOFFSET | ADC_REG_RANK_4_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 4 */
#define LL_ADC_REG_RANK_5                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_5_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 5 */
#define LL_ADC_REG_RANK_6                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_6_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 6 */
#define LL_ADC_REG_RANK_7                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_7_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 7 */
#define LL_ADC_REG_RANK_8                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_8_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 8 */
#define LL_ADC_REG_RANK_9                  (ADC_SQR2_REGOFFSET | ADC_REG_RANK_9_SQRX_BITOFFSET_POS)  /*!< ADC group regular sequencer rank 9 */
#define LL_ADC_REG_RANK_10                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_10_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 10 */
#define LL_ADC_REG_RANK_11                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_11_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 11 */
#define LL_ADC_REG_RANK_12                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_12_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 12 */
#define LL_ADC_REG_RANK_13                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_13_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 13 */
#define LL_ADC_REG_RANK_14                 (ADC_SQR3_REGOFFSET | ADC_REG_RANK_14_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 14 */
#define LL_ADC_REG_RANK_15                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_15_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 15 */
#define LL_ADC_REG_RANK_16                 (ADC_SQR4_REGOFFSET | ADC_REG_RANK_16_SQRX_BITOFFSET_POS) /*!< ADC group regular sequencer rank 16 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_SOURCE  ADC group injected - Trigger source
  * @{
  */
#define LL_ADC_INJ_TRIG_SW_START           ((uint32_t)0x00000000)                                                                                              /*!< ADC group injected conversion trigger internal (SW start). Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO      (ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                                     /*!< ADC group injected conversion trigger external from TIM1 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2     (ADC_JSQR_JEXTSEL_3 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group injected conversion trigger external from TIM1 TRGO2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM1_CC4       (ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group injected conversion trigger external from TIM1 CC4. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM2_TRGO      (ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group injected conversion trigger external from TIM2 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM2_CC1       (ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from TIM2 CC1. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from TIM3 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CC1       (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                      /*!< ADC group injected conversion trigger external from TIM3 CC1. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CC3       (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                      /*!< ADC group injected conversion trigger external from TIM3 CC3. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM3_CC4       (ADC_JSQR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                                                /*!< ADC group injected conversion trigger external from TIM3 CC4. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM4_TRGO      (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from TIM4 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM6_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                      /*!< ADC group injected conversion trigger external from TIM6 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_CC4       (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                      /*!< ADC group injected conversion trigger external from TIM8 CC4. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_TRGO      (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from TIM8 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2     (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from TIM8 TRGO2. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_TIM15_TRGO     (ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT) /*!< ADC group injected conversion trigger external from TIM15 TRGO. Trigger edge set to rising edge (default setting). */
#define LL_ADC_INJ_TRIG_EXT_EXTI_LINE15    (ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT)                                           /*!< ADC group injected conversion trigger external from external interrupt line 15. Trigger edge set to rising edge (default setting). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_EDGE  ADC group injected - Trigger edge
  * @{
  */
#define LL_ADC_INJ_TRIG_EXT_RISING         (                    ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion trigger polarity set to rising edge */
#define LL_ADC_INJ_TRIG_EXT_FALLING        (ADC_JSQR_JEXTEN_1                    ) /*!< ADC group injected conversion trigger polarity set to falling edge */
#define LL_ADC_INJ_TRIG_EXT_RISINGFALLING  (ADC_JSQR_JEXTEN_1 | ADC_JSQR_JEXTEN_0) /*!< ADC group injected conversion trigger polarity set to both rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_TRIG_AUTO  ADC group injected - Trigger automatic mode
* @{
*/
#define LL_ADC_INJ_TRIG_INDEPENDENT        ((uint32_t)0x00000000) /*!< ADC group injected conversion trigger independent */
#define LL_ADC_INJ_TRIG_FROM_GRP_REGULAR   (ADC_CFGR_JAUTO)       /*!< ADC group injected conversion trigger from ADC group regular */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_CONTEXT_QUEUE  ADC group injected - Context queue mode
  * @{
  */
#define LL_ADC_INJ_QUEUE_2CONTEXTS_LAST_ACTIVE ((uint32_t)0x00000000) /* Group injected sequence context queue is enabled and can contain up to 2 contexts. When all contexts have been processed, the queue maintains the last context active perpetually. */
#define LL_ADC_INJ_QUEUE_2CONTEXTS_END_EMPTY   (ADC_CFGR_JQM)         /* Group injected sequence context queue is enabled and can contain up to 2 contexts. When all contexts have been processed, the queue is empty and injected group triggers are disabled. */
#define LL_ADC_INJ_QUEUE_DISABLE               (ADC_CFGR_JQDIS)       /* Group injected sequence context queue is disabled: only 1 sequence can be configured and is active perpetually. */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_LENGTH  ADC group injected - Sequencer length
  * @{
  */
#define LL_ADC_INJ_SEQ_SCAN_DISABLE        ((uint32_t)0x00000000)          /*!< ADC group injected sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS  (                ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable with 2 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS  (ADC_JSQR_JL_1                ) /*!< ADC group injected sequencer enable with 3 ranks in the sequence */
#define LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS  (ADC_JSQR_JL_1 | ADC_JSQR_JL_0) /*!< ADC group injected sequencer enable with 4 ranks in the sequence */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_SEQ_DISCONT  ADC group injected - Sequencer discontinuous mode
  * @{
  */
#define LL_ADC_INJ_SEQ_DISCONT_DISABLE     ((uint32_t)0x00000000) /*!< ADC group injected sequencer discontinuous mode disable */
#define LL_ADC_INJ_SEQ_DISCONT_1RANK       (ADC_CFGR_JDISCEN)     /*!< ADC group injected sequencer discontinuous mode enable with sequence interruption every rank */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_INJ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define LL_ADC_INJ_RANK_1                  (ADC_JDR1_REGOFFSET | ADC_INJ_RANK_1_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 1 */
#define LL_ADC_INJ_RANK_2                  (ADC_JDR2_REGOFFSET | ADC_INJ_RANK_2_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 2 */
#define LL_ADC_INJ_RANK_3                  (ADC_JDR3_REGOFFSET | ADC_INJ_RANK_3_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 3 */
#define LL_ADC_INJ_RANK_4                  (ADC_JDR4_REGOFFSET | ADC_INJ_RANK_4_JSQR_BITOFFSET_POS) /*!< ADC group injected sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_SAMPLINGTIME  Channel - Sampling time
  * @{
  */
#define LL_ADC_SAMPLINGTIME_2CYCLES_5      (0x00000000)                                                /*!< Sampling time 2.5 ADC clock cycle */
#define LL_ADC_SAMPLINGTIME_6CYCLES_5      (                                        ADC_SMPR2_SMP10_0) /*!< Sampling time 6.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_12CYCLES_5     (                    ADC_SMPR2_SMP10_1                    ) /*!< Sampling time 12.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_24CYCLES_5     (                    ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0) /*!< Sampling time 24.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_47CYCLES_5     (ADC_SMPR2_SMP10_2                                        ) /*!< Sampling time 47.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_92CYCLES_5     (ADC_SMPR2_SMP10_2                     | ADC_SMPR2_SMP10_0) /*!< Sampling time 92.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_247CYCLES_5    (ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1                    ) /*!< Sampling time 247.5 ADC clock cycles */
#define LL_ADC_SAMPLINGTIME_640CYCLES_5    (ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0) /*!< Sampling time 640.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_SINGLE_DIFF_ENDING  Channel - Single or differential ending
  * @{
  */
#define LL_ADC_SINGLE_ENDED                (                  ADC_CALFACT_CALFACT_S)         /*!< ADC channel ending set to single ended (literal also used to set calibration mode) */
#define LL_ADC_DIFFERENTIAL_ENDED          (ADC_CR_ADCALDIF | ADC_CALFACT_CALFACT_D)         /*!< ADC channel ending set to differential (literal also used to set calibration mode) */
#define LL_ADC_BOTH_SINGLE_DIFF_ENDED      (LL_ADC_SINGLE_ENDED | LL_ADC_DIFFERENTIAL_ENDED) /*!< ADC channel ending set to both single ended and differential (literal used only to set calibration factors) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD Analog watchdog - Analog watchdog number
  * @{
  */
#define LL_ADC_AWD1                        (ADC_AWD_CR1_CHANNEL_MASK  | ADC_AWD_CR1_REGOFFSET) /*!< ADC analog watchdog number 1 */
#define LL_ADC_AWD2                        (ADC_AWD_CR23_CHANNEL_MASK | ADC_AWD_CR2_REGOFFSET) /*!< ADC analog watchdog number 2 */
#define LL_ADC_AWD3                        (ADC_AWD_CR23_CHANNEL_MASK | ADC_AWD_CR3_REGOFFSET) /*!< ADC analog watchdog number 3 */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_CHANNELS  Analog watchdog - Monitored channels
  * @{
  */
#define LL_ADC_AWD_DISABLE                 ((uint32_t)0x00000000)
#define LL_ADC_AWD_ALL_CHANNELS_REG        (ADC_AWD_CR23_CHANNEL_MASK                                    | ADC_CFGR_AWD1EN                   ) /*!< ADC analog watchdog monitoring of all channels, converted by group regular only */
#define LL_ADC_AWD_ALL_CHANNELS_INJ        (ADC_AWD_CR23_CHANNEL_MASK                 | ADC_CFGR_JAWD1EN                                     ) /*!< ADC analog watchdog monitoring of all channels, converted by group injected only */
#define LL_ADC_AWD_ALL_CHANNELS_REG_INJ    (ADC_AWD_CR23_CHANNEL_MASK                 | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN                   ) /*!< ADC analog watchdog monitoring of all channels, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_0_REG           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_0_INJ           ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_0_REG_INJ       ((LL_ADC_CHANNEL_0  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_1_REG           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_1_INJ           ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_1_REG_INJ       ((LL_ADC_CHANNEL_1  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_2_REG           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_2_INJ           ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_2_REG_INJ       ((LL_ADC_CHANNEL_2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_3_REG           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_3_INJ           ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_3_REG_INJ       ((LL_ADC_CHANNEL_3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_4_REG           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_4_INJ           ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_4_REG_INJ       ((LL_ADC_CHANNEL_4  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_5_REG           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_5_INJ           ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_5_REG_INJ       ((LL_ADC_CHANNEL_5  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_6_REG           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_6_INJ           ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_6_REG_INJ       ((LL_ADC_CHANNEL_6  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_7_REG           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_7_INJ           ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_7_REG_INJ       ((LL_ADC_CHANNEL_7  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_8_REG           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_8_INJ           ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_8_REG_INJ       ((LL_ADC_CHANNEL_8  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_9_REG           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_9_INJ           ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_9_REG_INJ       ((LL_ADC_CHANNEL_9  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_10_REG          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_10_INJ          ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_10_REG_INJ      ((LL_ADC_CHANNEL_10 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_11_REG          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_11_INJ          ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_11_REG_INJ      ((LL_ADC_CHANNEL_11 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_12_REG          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_12_INJ          ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_12_REG_INJ      ((LL_ADC_CHANNEL_12 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN12, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_13_REG          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_13_INJ          ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_13_REG_INJ      ((LL_ADC_CHANNEL_13 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN13, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_14_REG          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_14_INJ          ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_14_REG_INJ      ((LL_ADC_CHANNEL_14 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN14, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_15_REG          ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_15_INJ          ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_15_REG_INJ      ((LL_ADC_CHANNEL_15 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN15, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_16_REG          ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_16_INJ          ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_16_REG_INJ      ((LL_ADC_CHANNEL_16 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN16, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_17_REG          ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_17_INJ          ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_17_REG_INJ      ((LL_ADC_CHANNEL_17 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN17, converted by either group regular or injected */
#define LL_ADC_AWD_CHANNEL_18_REG          ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by group regular only */
#define LL_ADC_AWD_CHANNEL_18_INJ          ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by group injected only */
#define LL_ADC_AWD_CHANNEL_18_REG_INJ      ((LL_ADC_CHANNEL_18 & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN18, converted by either group regular or injected */
#define LL_ADC_AWD_CH_VREFINT_REG          ((LL_ADC_CHANNEL_VREFINT       & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group regular only */
#define LL_ADC_AWD_CH_VREFINT_INJ          ((LL_ADC_CHANNEL_VREFINT       & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by group injected only */
#define LL_ADC_AWD_CH_VREFINT_REG_INJ      ((LL_ADC_CHANNEL_VREFINT       & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to VrefInt: Internal voltage reference, converted by either group regular or injected */
#define LL_ADC_AWD_CH_TEMPSENSOR_REG       ((LL_ADC_CHANNEL_TEMPSENSOR    & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by group regular only */
#define LL_ADC_AWD_CH_TEMPSENSOR_INJ       ((LL_ADC_CHANNEL_TEMPSENSOR    & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by group injected only */
#define LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ   ((LL_ADC_CHANNEL_TEMPSENSOR    & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Temperature sensor, converted by either group regular or injected */
#define LL_ADC_AWD_CH_VBAT_REG             ((LL_ADC_CHANNEL_VBAT          & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/3: Vbat voltage through an dividor ladder of factor 1/3 to have Vbat always below Vdda, converted by group regular only */
#define LL_ADC_AWD_CH_VBAT_INJ             ((LL_ADC_CHANNEL_VBAT          & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/3: Vbat voltage through an dividor ladder of factor 1/3 to have Vbat always below Vdda, converted by group injected only */
#define LL_ADC_AWD_CH_VBAT_REG_INJ         ((LL_ADC_CHANNEL_VBAT          & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to Vbat/3: Vbat voltage through an dividor ladder of factor 1/3 to have Vbat always below Vdda */
#define LL_ADC_AWD_CH_DAC1CH1_ADC2_REG     ((LL_ADC_CHANNEL_DAC1CH1_ADC2  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by group regular only */
#define LL_ADC_AWD_CH_DAC1CH1_ADC2_INJ     ((LL_ADC_CHANNEL_DAC1CH1_ADC2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by group injected only */
#define LL_ADC_AWD_CH_DAC1CH1_ADC2_REG_INJ ((LL_ADC_CHANNEL_DAC1CH1_ADC2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by either group regular or injected */
#define LL_ADC_AWD_CH_DAC1CH2_ADC2_REG     ((LL_ADC_CHANNEL_DAC1CH2_ADC2  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by group regular only */
#define LL_ADC_AWD_CH_DAC1CH2_ADC2_INJ     ((LL_ADC_CHANNEL_DAC1CH2_ADC2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by group injected only */
#define LL_ADC_AWD_CH_DAC1CH2_ADC2_REG_INJ ((LL_ADC_CHANNEL_DAC1CH2_ADC2  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC2, converted by either group regular or injected */
#define LL_ADC_AWD_CH_DAC1CH1_ADC3_REG     ((LL_ADC_CHANNEL_DAC1CH1_ADC3  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by group regular only */
#define LL_ADC_AWD_CH_DAC1CH1_ADC3_INJ     ((LL_ADC_CHANNEL_DAC1CH1_ADC3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by group injected only */
#define LL_ADC_AWD_CH_DAC1CH1_ADC3_REG_INJ ((LL_ADC_CHANNEL_DAC1CH1_ADC3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by either group regular or injected */
#define LL_ADC_AWD_CH_DAC1CH2_ADC3_REG     ((LL_ADC_CHANNEL_DAC1CH2_ADC3  & ADC_CHANNEL_ID_MASK)                    | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by group regular only */
#define LL_ADC_AWD_CH_DAC1CH2_ADC3_INJ     ((LL_ADC_CHANNEL_DAC1CH2_ADC3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN                   | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by group injected only */
#define LL_ADC_AWD_CH_DAC1CH2_ADC3_REG_INJ ((LL_ADC_CHANNEL_DAC1CH2_ADC3  & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL) /*!< ADC analog watchdog monitoring of ADC internal channel connected to DAC1 channel 1, channel specific to ADC3, converted by either group regular or injected */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_AWD_THRESHOLDS  Analog watchdog - Thresholds
  * @{
  */
#define LL_ADC_AWD_THRESHOLD_HIGH          (ADC_TR1_HT1              ) /*!< ADC analog watchdog threshold high */
#define LL_ADC_AWD_THRESHOLD_LOW           (              ADC_TR1_LT1) /*!< ADC analog watchdog threshold low */
#define LL_ADC_AWD_THRESHOLDS_HIGH_LOW     (ADC_TR1_HT1 | ADC_TR1_LT1) /*!< ADC analog watchdog both thresholds high and low concatenated into the same data */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS  Oversampling - Oversampling scope
  * @{
  */
#define LL_ADC_OVS_DISABLE                 ((uint32_t)0x00000000)
#define LL_ADC_OVS_GRP_REGULAR_CONTINUED   (                                    ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular: when ADC group injected is triggered, the oversampling on ADC group regular is temporary stopped and continued. */
#define LL_ADC_OVS_GRP_REGULAR_RESUMED     (ADC_CFGR2_ROVSM |                   ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular: when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
#define LL_ADC_OVS_GRP_INJECTED            (                  ADC_CFGR2_JOVSE                  ) /*!< ADC oversampling on conversions of ADC group injected */
#define LL_ADC_OVS_GRP_INJ_REG_RESUMED     (                  ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSE) /*!< ADC oversampling on conversions of both ADC groups regular and injected. If group injected interrupting group regular: when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_DISCONT  Oversampling - Discontinuous mode
  * @{
  */
#define LL_ADC_OVS_REG_CONT                ((uint32_t)0x00000000) /*!< ADC oversampling discontinuous mode: continuous mode (all conversions of oversampling ratio are done from 1 trigger) */
#define LL_ADC_OVS_REG_DISCONT             (ADC_CFGR2_TROVS)      /*!< ADC oversampling discontinuous mode: discontinuous mode (each conversion of oversampling ratio needs a trigger) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_RATIO  Oversampling - Ratio
  * @{
  */
#define LL_ADC_OVS_RATIO_2                 ((uint32_t)0x00000000)                                   /*!< ADC oversampling ratio of 2 (2 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_4                 (                                      ADC_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 4 (4 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_8                 (                   ADC_CFGR2_OVSR_1                   ) /*!< ADC oversampling ratio of 8 (8 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_16                (                   ADC_CFGR2_OVSR_1 | ADC_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 16 (16 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_32                (ADC_CFGR2_OVSR_2                                      ) /*!< ADC oversampling ratio of 32 (32 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_64                (ADC_CFGR2_OVSR_2                    | ADC_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 64 (64 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_128               (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1                   ) /*!< ADC oversampling ratio of 128 (128 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
#define LL_ADC_OVS_RATIO_256               (ADC_CFGR2_OVSR_2 | ADC_CFGR2_OVSR_1 | ADC_CFGR2_OVSR_0) /*!< ADC oversampling ratio of 256 (256 ADC conversions are performed, sum of these conversions data is computed to result as the ADC oversampling conversion data (before potential shift) */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_OVS_RIGHTBITSHIFT  Oversampling - Data right shift
  * @{
  */
#define LL_ADC_OVS_DATA_SHIFT_NONE         ((uint32_t)0x00000000)                                                      /*!< ADC oversampling no shift (sum of the ADC conversions data is not divided to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_1            (                                                         ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 1 (sum of the ADC conversions data is divided by 2 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_2            (                                      ADC_CFGR2_OVSS_1                   ) /*!< ADC oversampling shift of 2 (sum of the ADC conversions data is divided by 4 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_3            (                                      ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 3 (sum of the ADC conversions data is divided by 8 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_4            (                   ADC_CFGR2_OVSS_2                                      ) /*!< ADC oversampling shift of 4 (sum of the ADC conversions data is divided by 16 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_5            (                   ADC_CFGR2_OVSS_2                    | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 5 (sum of the ADC conversions data is divided by 32 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_6            (                   ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1                   ) /*!< ADC oversampling shift of 6 (sum of the ADC conversions data is divided by 64 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_7            (                   ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0) /*!< ADC oversampling shift of 7 (sum of the ADC conversions data is divided by 128 to result as the ADC oversampling conversion data) */
#define LL_ADC_OVS_DATA_SHIFT_8            (ADC_CFGR2_OVSS_3                                                         ) /*!< ADC oversampling shift of 8 (sum of the ADC conversions data is divided by 256 to result as the ADC oversampling conversion data) */
/**
  * @}
  */

#if defined(ADC2)
/** @defgroup ADC_LL_EC_MULTI  Multimode - Mode
  * @{
  */
#define LL_ADC_MULTI_INDEPENDENT           ((uint32_t)0x00000000)                                              /*!< ADC dual mode disabled (ADC independent mode) */
#define LL_ADC_MULTI_DUAL_REG_SIMULT       (                 ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1                 ) /*!< ADC dual mode enabled: group regular simultaneous */
#define LL_ADC_MULTI_DUAL_REG_INTERL       (                 ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular interleaved */
#define LL_ADC_MULTI_DUAL_INJ_SIMULT       (                 ADC_CCR_DUAL_2                  | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected simultaneous */
#define LL_ADC_MULTI_DUAL_INJ_ALTERN       (ADC_CCR_DUAL_3                                   | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: group injected alternate trigger. Works only with external triggers (not internal SW start) */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM  (                                                   ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected simultaneous */
#define LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT  (                                  ADC_CCR_DUAL_1                 ) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected alternate trigger */
#define LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM  (                                  ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0) /*!< ADC dual mode enabled: Combined group regular interleaved + group injected simultaneous */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_DMA_TRANSFER  Multimode - DMA transfer
  * @{
  */
#define LL_ADC_MULTI_REG_DMA_EACH_ADC        ((uint32_t)0x00000000)                             /*!< ADC multimode group regular conversions are transferred by DMA: each ADC uses its own DMA channel, with its individual DMA transfer settings */
#define LL_ADC_MULTI_REG_DMA_LIMIT_RES12_10B (                 ADC_CCR_MDMA_1                 ) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master), in limited mode (one shot mode): DMA transfer requests are stopped when number of DMA data transfers (number of ADC conversions) is reached. This ADC mode is intended to be used with DMA mode non-circular. Setting for ADC resolution of 12 and 10 bits */
#define LL_ADC_MULTI_REG_DMA_LIMIT_RES8_6B   (                 ADC_CCR_MDMA_1 | ADC_CCR_MDMA_0) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master), in limited mode (one shot mode): DMA transfer requests are stopped when number of DMA data transfers (number of ADC conversions) is reached. This ADC mode is intended to be used with DMA mode non-circular. Setting for ADC resolution of 8 and 6 bits */
#define LL_ADC_MULTI_REG_DMA_UNLMT_RES12_10B (ADC_CCR_DMACFG | ADC_CCR_MDMA_1                 ) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master), in unlimited mode: DMA transfer requests are unlimited, whatever number of DMA data transferred (number of ADC conversions). This ADC mode is intended to be used with DMA mode circular. Setting for ADC resolution of 12 and 10 bits */
#define LL_ADC_MULTI_REG_DMA_UNLMT_RES8_6B   (ADC_CCR_DMACFG | ADC_CCR_MDMA_1 | ADC_CCR_MDMA_0) /*!< ADC multimode group regular conversions are transferred by DMA, one DMA channel for both ADC (DMA of ADC master), in unlimited mode: DMA transfer requests are unlimited, whatever number of DMA data transferred (number of ADC conversions). This ADC mode is intended to be used with DMA mode circular. Setting for ADC resolution of 8 and 6 bits */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_TWOSMP_DELAY  Multimode - Delay between two sampling phases
  * @{
  */
#define LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE   ((uint32_t)0x00000000)                                                  /*!< ADC multimode delay between two sampling phases: 1 ADC clock cycle */
#define LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES  (                                                      ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 2 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES  (                                    ADC_CCR_DELAY_1                  ) /*!< ADC multimode delay between two sampling phases: 3 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES  (                                    ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 4 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES  (                  ADC_CCR_DELAY_2                                    ) /*!< ADC multimode delay between two sampling phases: 5 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES  (                  ADC_CCR_DELAY_2                   | ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 6 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES  (                  ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1                  ) /*!< ADC multimode delay between two sampling phases: 7 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES  (                  ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 8 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES  (ADC_CCR_DELAY_3                                                      ) /*!< ADC multimode delay between two sampling phases: 9 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES (ADC_CCR_DELAY_3                                     | ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 10 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES (ADC_CCR_DELAY_3                   | ADC_CCR_DELAY_1                  ) /*!< ADC multimode delay between two sampling phases: 11 ADC clock cycles */
#define LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES (ADC_CCR_DELAY_3                   | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0) /*!< ADC multimode delay between two sampling phases: 12 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADC_LL_EC_MULTI_CONV_DATA  Multimode - ADC master or slave
  * @{
  */
#define LL_ADC_MULTI_MASTER                (                    ADC_CDR_RDATA_MST) /*!< In multimode, selection among several ADC instances: ADC master */
#define LL_ADC_MULTI_SLAVE                 (ADC_CDR_RDATA_SLV                    ) /*!< In multimode, selection among several ADC instances: ADC slave */
#define LL_ADC_MULTI_MASTER_SLAVE          (ADC_CDR_RDATA_SLV | ADC_CDR_RDATA_MST) /*!< In multimode, selection among several ADC instances: both ADC master and ADC slave */
/**
  * @}
  */

#endif /* ADC2 */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC Exported Macros
  * @{
  */

/** @defgroup ADC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_ADC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in ADC register
  * @param  __INSTANCE__ ADC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_ADC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup ADC_LL_EM_HELPER_MACRO ADC helper macro
  * @{
  */

/**
  * @brief  Helper macro to get ADC channel number in decimal format
  *         from literals LL_ADC_CHANNEL_x.
  * @note   Example:
  *            __LL_ADC_CHANNEL_TO_DECIMAL_NB(LL_ADC_CHANNEL_4)
  *            will return decimal number "4".
  * @note   The input can be a value from functions where a channel
  *         number is returned, either defined with number
  *         or with bitfield (only one bit must be set).
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval 0...18
  */
#define __LL_ADC_CHANNEL_TO_DECIMAL_NB(__CHANNEL__)                                             \
  ((((__CHANNEL__) & ADC_CHANNEL_ID_BITFIELD_MASK) != 0)                                        \
    ? (                                                                                         \
       POSITION_VAL((__CHANNEL__))                                                              \
      )                                                                                         \
      :                                                                                         \
      (                                                                                         \
       ((__CHANNEL__) & ADC_CHANNEL_ID_NUMBER_MASK) >> POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) \
      )                                                                                         \
  )

/**
  * @brief  Helper macro to get ADC channel in literal format LL_ADC_CHANNEL_x
  *         from number in decimal format.
  * @note   Example:
  *           __LL_ADC_DECIMAL_NB_TO_CHANNEL(4)
  *           will return a data equivalent to "LL_ADC_CHANNEL_4".
  * @param  __DECIMAL_NB__: 0...18
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  *         (1, 2, 3, 4) For ADC channel read back from ADC register,
  *                      comparison with internal channel parameter to be done
  *                      using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
#define __LL_ADC_DECIMAL_NB_TO_CHANNEL(__DECIMAL_NB__)                                                          \
  (((__DECIMAL_NB__) <= 9)                                                                                      \
    ? (                                                                                                         \
       ((__DECIMAL_NB__) << POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK))                                  |        \
       (ADC_AWD2CR_AWD2CH_0 << (__DECIMAL_NB__))                                                       |        \
       (ADC_SMPR1_REGOFFSET | (((uint32_t) (3 * (__DECIMAL_NB__))) << ADC_CHANNEL_SMPx_BITOFFSET_POS))          \
      )                                                                                                         \
      :                                                                                                         \
      (                                                                                                         \
       ((__DECIMAL_NB__) << POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK))                                         | \
       (ADC_AWD2CR_AWD2CH_0 << (__DECIMAL_NB__))                                                              | \
       (ADC_SMPR2_REGOFFSET | (((uint32_t) (3 * ((__DECIMAL_NB__) - 10))) << ADC_CHANNEL_SMPx_BITOFFSET_POS))   \
      )                                                                                                         \
  )

/**
  * @brief  Helper macro to determine whether the channel corresponds to
  *         parameters definitions of driver:
  *          * Parameter definition of a ADC internal channel
  *            (LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...)
  *          * Parameter definition of a ADC external channel (channel connected
  *            to a GPIO pin) (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  * @note   The channel parameter must be a value defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...),
  *         must not be a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval 0 if the channel corresponds to a parameter definition of a ADC external channel (channel connected to a GPIO pin)
  *         1 if the channel corresponds to a parameter definition of a ADC internal channel
  */
#define __LL_ADC_IS_CHANNEL_INTERNAL(__CHANNEL__)                              \
  (((__CHANNEL__) & ADC_CHANNEL_ID_INTERNAL_CH_MASK) != 0)

/**
  * @brief  Helper macro to convert a channel defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         to its equivalent parameter definition of a ADC external channel
  *         (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  * @note   The channel parameter can be, additionally to a value 
  *         defined from parameter definition of a ADC internal channel
  *         (LL_ADC_CHANNEL_VREFINT, LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is returned
  *         from ADC registers.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  */
#define __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL(__CHANNEL__)                     \
  ((__CHANNEL__) & ~ADC_CHANNEL_ID_INTERNAL_CH_MASK)

/**
  * @brief  Helper macro to determine whether the internal channel
  *         selected is available on the ADC instance selected.
  * @note   The channel parameter must be a value defined from parameter
  *         definition of a ADC internal channel (LL_ADC_CHANNEL_VREFINT,
  *         LL_ADC_CHANNEL_TEMPSENSOR, ...),
  *         must not be a value defined from parameter definition of
  *         ADC external channel (LL_ADC_CHANNEL_1, LL_ADC_CHANNEL_2, ...)
  *         or a value from functions where a channel number is
  *         returned from ADC registers,
  *         because internal and external channels share the same channel
  *         number in ADC registers. The differentiation is made only with
  *         parameters definitions of driver.
  * @param  __ADC_INSTANCE__ ADC instance
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  * @retval 0 if the internal channel selected is not available on the ADC instance selected.
  *         1 if the internal channel selected is available on the ADC instance selected.
  */
#if defined (ADC1) && defined (ADC2) && defined (ADC3)
#define __LL_ADC_IS_CHANNEL_INTERNAL_AVAILABLE(__ADC_INSTANCE__, __CHANNEL__)  \
  (((__ADC_INSTANCE__) == ADC1)                                                \
    ? (                                                                        \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)    ||                         \
       ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR) ||                         \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)                                  \
      )                                                                        \
      :                                                                        \
      ((__ADC_INSTANCE__) == ADC2)                                             \
      ? (                                                                      \
         ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)      ||                     \
         ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH1_ADC2) ||                     \
         ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH2_ADC2)                        \
        )                                                                      \
        :                                                                      \
        ((__ADC_INSTANCE__) == ADC3)                                           \
        ? (                                                                    \
           ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)      ||                   \
           ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR)   ||                   \
           ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)         ||                   \
           ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH1_ADC3) ||                   \
           ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH2_ADC3)                      \
          )                                                                    \
          :                                                                    \
          (0)                                                                  \
  )
#elif defined (ADC1) && defined (ADC2)
#define __LL_ADC_IS_CHANNEL_INTERNAL_AVAILABLE(__ADC_INSTANCE__, __CHANNEL__)  \
  (((__ADC_INSTANCE__) == ADC1)                                                \
    ? (                                                                        \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)    ||                         \
       ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR) ||                         \
       ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)                                  \
      )                                                                        \
      :                                                                        \
      ((__ADC_INSTANCE__) == ADC2)                                             \
      ? (                                                                      \
         ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)      ||                     \
         ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH1_ADC2) ||                     \
         ((__CHANNEL__) == LL_ADC_CHANNEL_DAC1CH2_ADC2)                        \
        )                                                                      \
        :                                                                      \
        (0)                                                                    \
  )
#elif defined (ADC1)
#define __LL_ADC_IS_CHANNEL_INTERNAL_AVAILABLE(__ADC_INSTANCE__, __CHANNEL__)  \
  (                                                                            \
    ((__CHANNEL__) == LL_ADC_CHANNEL_VREFINT)    ||                            \
    ((__CHANNEL__) == LL_ADC_CHANNEL_TEMPSENSOR) ||                            \
    ((__CHANNEL__) == LL_ADC_CHANNEL_VBAT)                                     \
  )
#endif

/**
  * @brief  Helper macro to define ADC analog watchdog parameter:
  *         define a single channel to monitor with analog watchdog
  *         from sequencer channel and groups definition.
  * @note   To be used with function @ref LL_ADC_SetAnalogWDMonitChannels().
  *         Example:
  *           LL_ADC_SetAnalogWDMonitChannels(
  *             ADC1, LL_ADC_AWD1,
  *             __LL_ADC_ANALOGWD_CHANNEL_GROUP(LL_ADC_CHANNEL4, LL_ADC_REGULAR_GROUP))
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  *         (1, 2, 3, 4) For ADC channel read back from ADC register,
  *                      comparison with internal channel parameter to be done
  *                      using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  * @param  __GROUP__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_GROUP_REGULAR
  *         @arg @ref LL_ADC_GROUP_INJECTED
  *         @arg @ref LL_ADC_GROUP_REGULAR_INJECTED
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ         (1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG       (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ       (4)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ      (4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_INJ             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG_INJ            (4)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG_INJ    (3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG_INJ    (3)
  *         (0) On STM32L4, parameter available only on analog watchdog number: AWD1.
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  */
#define __LL_ADC_ANALOGWD_CHANNEL_GROUP(__CHANNEL__, __GROUP__)                                           \
  (((__GROUP__) == LL_ADC_GROUP_REGULAR)                                                                  \
    ? (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL)                        \
      :                                                                                                   \
      ((__GROUP__) == LL_ADC_GROUP_INJECTED)                                                              \
       ? (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1SGL)                    \
         :                                                                                                \
         (((__CHANNEL__) & ADC_CHANNEL_ID_MASK) | ADC_CFGR_JAWD1EN | ADC_CFGR_AWD1EN | ADC_CFGR_AWD1SGL)  \
  )

/**
  * @brief  Helper macro to get the ADC analog watchdog threshold high
  *         or low from raw value with both thresholds concatenated.
  * @note   To be used with function @ref LL_ADC_GetAnalogWDThresholds().
  *         Example, to get analog watchdog threshold high from the register raw value:
  *           __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW(LL_ADC_AWD_THRESHOLD_HIGH, <raw_value_with_both_thresholds>);
  * @param  __AWD_THRESHOLD_TYPE__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  __AWD_THRESHOLDS__ For AWD1: 0x000...0xFFF, for AWD2, AWD3: 0x00...0xFF
  * @retval 0x00000000...0xFFFFFFFF
  */
#define __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW(__AWD_THRESHOLD_TYPE__, __AWD_THRESHOLDS__)       \
  (((__AWD_THRESHOLDS__) >> POSITION_VAL((__AWD_THRESHOLD_TYPE__))) & LL_ADC_AWD_THRESHOLD_LOW)

/**
  * @brief  Helper macro to set the ADC calibration value with both single ended
  *         and differential modes calibration factors concatenated.
  * @note   To be used with function @ref LL_ADC_SetCalibrationFactor().
  *         Example, to set calibration factors single ended to 0x55
  *         and differential ended to 0x2A:
  *           LL_ADC_SetCalibrationFactor(
  *             ADC1,
  *             __LL_ADC_CALIB_FACTOR_SINGLE_DIFF(0x55, 0x2A))
  * @param  __CALIB_FACTOR_SINGLE_ENDED__ 0x00...0x7F
  * @param  __CALIB_FACTOR_DIFFERENTIAL__ 0x00...0x7F
  * @retval 0x00000000...0xFFFFFFFF
  */
#define __LL_ADC_CALIB_FACTOR_SINGLE_DIFF(__CALIB_FACTOR_SINGLE_ENDED__, __CALIB_FACTOR_DIFFERENTIAL__)        \
  (((__CALIB_FACTOR_DIFFERENTIAL__) << POSITION_VAL(ADC_CALFACT_CALFACT_D)) | (__CALIB_FACTOR_SINGLE_ENDED__))

#if defined(ADC2)
/**
  * @brief  Helper macro to get the ADC multimode conversion data of ADC master
  *         or ADC slave from raw value with both ADC conversion data concatenated.
  * @note   This macro is intended to be used when multimode transfer by DMA
  *         is enabled: refer to function @ref LL_ADC_SetMultiDMATransfer().
  *         In this case the transferred data need to processed with this macro
  *         to separate the conversion data of ADC master and ADC slave.
  * @param  __ADC_MULTI_MASTER_SLAVE__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER
  *         @arg @ref LL_ADC_MULTI_SLAVE
  * @param  __ADC_MULTI_CONV_DATA__ 0x000...0xFFF
  * @retval 0x000...0xFFF
  */
#define __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE(__ADC_MULTI_MASTER_SLAVE__, __ADC_MULTI_CONV_DATA__)  \
  (((__ADC_MULTI_CONV_DATA__) >> POSITION_VAL((__ADC_MULTI_MASTER_SLAVE__))) & ADC_CDR_RDATA_MST)
#endif

/**
  * @brief  Helper macro to select the ADC common instance
  *         to which is belonging the selected ADC instance.
  * @note   ADC common register instance can be used for:
  *          * Set parameters common to several ADC instances
  *          * Multimode (for devices with several ADC instances)
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @param  __ADCx__ ADC instance
  * @retval ADC common register instance
  */
#if defined(ADC1) && defined(ADC2) && defined(ADC3)
#define __LL_ADC_COMMON_INSTANCE(__ADCx__)                                     \
  (ADC123_COMMON)
#elif defined(ADC1) && defined(ADC2)
#define __LL_ADC_COMMON_INSTANCE(__ADCx__)                                     \
  (ADC12_COMMON)
#else
#define __LL_ADC_COMMON_INSTANCE(__ADCx__)                                     \
  (ADC1_COMMON)
#endif

/**
  * @brief  Helper macro to check if all ADC instances sharing the same
  *         ADC common instance are disabled.
  * @note   This check is required by functions with setting conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         Refer to functions having argument "ADCxy_COMMON" as parameter.
  * @retval 0: All ADC instances sharing the same ADC common instance
  *            are disabled.
  *         1: At least one ADC instance sharing the same ADC common instance
  *            is enabled
  */
#if defined(ADC1) && defined(ADC2) && defined(ADC3)
#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE()                              \
  (LL_ADC_IsEnabled(ADC1) |                                                    \
   LL_ADC_IsEnabled(ADC2) |                                                    \
   LL_ADC_IsEnabled(ADC3)  )
#elif defined(ADC1) && defined(ADC2)
#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE()                              \
  (LL_ADC_IsEnabled(ADC1) |                                                    \
   LL_ADC_IsEnabled(ADC2)  )
#else
#define __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE()                              \
  LL_ADC_IsEnabled(ADC1)
#endif

/**
  * @brief  Helper macro to define the ADC conversion data full-scale digital
  *         value corresponding to the selected ADC resolution.
  * @note   ADC conversion data full-scale corresponds to voltage range 
  *         determined by analog voltage references Vref+ and Vref-,
  *         refer to reference manual)
  * @param  __RESOLUTION__ This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_DIGITAL_SCALE(__RESOLUTION__)                                 \
  (((uint32_t)0xFFF) >> ((__RESOLUTION__) >> (ADC_CFGR_RES_BITOFFSET_POS - 1 )))

/**
  * @brief  Helper macro to calculate the voltage (unit: mVolt)
  *         corresponding to a ADC conversion data (unit: digital value).
  * @note   ADC measurement data must correspond to a resolution of 12bits
  *         (full scale digital value 4095). If not the case, the data must be
  *         preliminarily rescaled to an equivalent resolution of 12 bits.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __ADC_DATA__ ADC conversion data (resolution 12 bits)
  *                       (unit: digital value).
  * @retval ADC conversion data equivalent voltage value (unit: mVolt)
  */
#define __LL_ADC_CALC_DATA_VOLTAGE(__VREFANALOG_VOLTAGE__, __ADC_DATA__)       \
  ((__ADC_DATA__) * (__VREFANALOG_VOLTAGE__) / __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B))

/**
  * @brief  Helper macro to calculate analog reference voltage (Vref+)
  *         (unit: mVolt) from ADC conversion data of internal voltage
  *         reference VrefInt.
  *         Computation is using VrefInt calibration value
  *         stored in system memory for each device during production.
  * @note   This voltage depends on user board environment: voltage level
  *         connected to pin Vref+.
  *         On devices with small package, the pin Vref+ is not present
  *         and internally bonded to pin Vdda.
  * @note   ADC measurement data must correspond to a resolution of 12bits
  *         (full scale digital value 4095). If not the case, the data must be
  *         preliminarily rescaled to an equivalent resolution of 12 bits.
  * @param  __VREFINT_ADC_DATA__: ADC conversion data (resolution 12 bits)
  *         of internal voltage reference VrefInt (unit: digital value).
  * @retval Analog reference voltage (unit: mV)
  */
#define __LL_ADC_CALC_VREFANALOG_VOLTAGE(__VREFINT_ADC_DATA__)                 \
  (((uint32_t)(*VREFINT_CAL_ADDR) * VREFINT_CAL_VREF) / (__VREFINT_ADC_DATA__))

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  *         Computation is using temperature sensor calibration values
  *         stored in system memory for each device during production.
  * @note   Calculation formula:
  *           Temperature = ((TS_ADC_DATA - TS_CAL1)
  *                           * (TS_CAL2_TEMP - TS_CAL1_TEMP))
  *                         / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP
  *           with TS_ADC_DATA = temperature sensor raw data measured by ADC
  *                Avg_Slope = (TS_CAL2 - TS_CAL1)
  *                            / (TS_CAL2_TEMP - TS_CAL1_TEMP)
  *                TS_CAL1   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL1 (calibrated in factory)
  *                TS_CAL2   = equivalent TS_ADC_DATA at temperature
  *                            TEMP_DEGC_CAL2 (calibrated in factory)
  *         Caution: Calculation relevancy under reserve that calibration
  *                  parameters are correct (address and data).
  *                  To calculate temperature using temperature sensor
  *                  datasheet typical values (generic values less, therefore
  *                  less accurate than calibrated values),
  *                  use helper macro @ref __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS().
  * @note   As calculation input, the analog reference voltage (Vref+) must be
  *         defined as it impacts the ADC LSB equivalent voltage.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   ADC measurement data must correspond to a resolution of 12bits
  *         (full scale digital value 4095). If not the case, the data must be
  *         preliminarily rescaled to an equivalent resolution of 12 bits.
  * @param  __VREFANALOG_VOLTAGE__ Analog reference voltage (unit: mV)
  * @param  __TEMPSENSOR_ADC_DATA__ ADC conversion data (resolution 12 bits)
  *         of internal temperature sensor (unit: digital value).
  * @retval Temperature (unit: degree Celsius)
  */
#define __LL_ADC_CALC_TEMPERATURE(__VREFANALOG_VOLTAGE__, __TEMPSENSOR_ADC_DATA__) \
  (((( ((int32_t)(((__TEMPSENSOR_ADC_DATA__) * (__VREFANALOG_VOLTAGE__))           \
                  / TEMPSENSOR_CAL_VREFANALOG)                                     \
        - (int32_t) *TEMPSENSOR_CAL1_ADDR)                                         \
     ) * (int32_t)(TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP)                    \
    ) / (int32_t)((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR) \
   ) + TEMPSENSOR_CAL1_TEMP                                                        \
  )

/**
  * @brief  Helper macro to calculate the temperature (unit: degree Celsius)
  *         from ADC conversion data of internal temperature sensor.
  *         Computation is using temperature sensor typical values
  *         (refer to device datasheet).
  * @note   Calculation formula:
  *           Temperature = (TS_ADC_DATA * conv_uV - TS_TYP_CAL1_VOLT)
  *                         / Avg_Slope + CAL1_TEMP
  *           with TS_ADC_DATA      = temperature sensor raw data measured by ADC
  *                                   (unit: digital value)
  *                Avg_Slope        = temperature sensor slope
  *                                   (unit: uV/Degree Celsius)
  *                TS_TYP_CAL1_VOLT = temperature sensor digital value at
  *                                   temperature CAL1_TEMP (unit: mV)
  *         Caution: Calculation relevancy under reserve the temperature sensor
  *                  of the current device has characteristics in line with
  *                  datasheet typical values.
  *                  If temperature sensor calibration values are available on
  *                  on this device (presence of macro __LL_ADC_CALC_TEMPERATURE()),
  *                  temperature calculation will be more accurate using
  *                  helper macro @ref __LL_ADC_CALC_TEMPERATURE().
  * @note   As calculation input, the analog reference voltage (Vref+) must be
  *         defined as it impacts the ADC LSB equivalent voltage.
  * @note   Analog reference voltage (Vref+) must be either known from
  *         user board environment or can be calculated using ADC measurement
  *         and ADC helper macro @ref __LL_ADC_CALC_VREFANALOG_VOLTAGE().
  * @note   ADC measurement data must correspond to a resolution of 12bits
  *         (full scale digital value 4095). If not the case, the data must be
  *         preliminarily rescaled to an equivalent resolution of 12 bits.
  * @param  __TEMPSENSOR_TYP_AVGSLOPE__   Device datasheet data: Temperature sensor slope typical value (unit: uV/DegCelsius).
  *                                       On STM32L4, refer to device datasheet parameter "Avg_Slope".
  * @param  __TEMPSENSOR_TYP_CAL1_V__     Device datasheet data: Temperature sensor voltage typical value (at temperature and Vref+ defined in parameters below) (unit: mV).
  *                                       On STM32L4, refer to device datasheet parameter "V30".
  * @param  __TEMPSENSOR_CAL1_TEMP__      Device datasheet data: Temperature at which temperature sensor voltage (see parameter above) is corresponding(unit: mV)
  * @param  __TEMPSENSOR_CAL_VREFANALOG__ Analog voltage reference (Vref+) voltage (unit: mV)
  * @param  __VREFANALOG_VOLTAGE__        Analog reference voltage at which temperature sensor voltage (see parameter above) is corresponding(unit: mV)
  * @param  __TEMPSENSOR_ADC_DATA__       ADC conversion data (resolution 12 bits) of internal
  *                                       temperature sensor (unit: digital value).
  * @retval Temperature (unit: degree Celsius)
  */
#define __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(__TEMPSENSOR_TYP_AVGSLOPE__,\
                                             __TEMPSENSOR_TYP_CAL1_V__,\
                                             __TEMPSENSOR_CAL1_TEMP__,\
                                             __TEMPSENSOR_CAL_VREFANALOG__,\
                                             __VREFANALOG_VOLTAGE__,\
                                             __TEMPSENSOR_ADC_DATA__)          \
  ((( ((int32_t)((((__TEMPSENSOR_ADC_DATA__) * (__VREFANALOG_VOLTAGE__))       \
                  / __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B))             \
                 * 1000)                                                       \
       -                                                                       \
       (int32_t)(((__TEMPSENSOR_TYP_CAL1_V__))                                 \
                 * 1000)                                                       \
      )                                                                        \
    ) / (__TEMPSENSOR_TYP_AVGSLOPE__)                                          \
   ) + (__TEMPSENSOR_CAL1_TEMP__)                                              \
  )

/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Functions ADC Exported Functions
  * @{
  */

/** @defgroup ADC_LL_EF_DMA_Management ADC DMA management
  * @{
  */
/* Note: LL ADC functions to set DMA transfer are located into sections of    */
/*       configuration of ADC instance, groups and multimode (if available):  */
/*       @ref LL_ADC_REG_SetDMATransfer(), ...                                */

/**
  * @brief  Function to help to configure DMA transfer from ADC: retrieve the
  *         ADC register address from ADC instance and a list of ADC registers
  *         intended to be used (most commonly) with DMA transfer.
  *         These ADC registers are data registers:
  *         when ADC conversion data is available in ADC data registers,
  *         ADC generates a DMA transfer request.
  * @note   This macro is intended to be used with LL DMA driver, refer to 
  *         function "LL_DMA_ConfigAddresses()".
  *         Example:
  *           LL_DMA_ConfigAddresses(DMA1,
  *                                  LL_DMA_CHANNEL_1,
  *                                  LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
  *                                  (uint32_t)&< array or variable >,
  *                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  * @note   For devices with several ADC: in multimode, some devices
  *         use a different data register outside of ADC instance scope
  *         (common data register). This macro manages this register difference,
  *         only ADC instance has to be set as parameter.
  * @rmtoll DR       RDATA          LL_ADC_DMA_GetRegAddr\n
  *         CDR      RDATA_MST      LL_ADC_DMA_GetRegAddr\n
  *         CDR      RDATA_SLV      LL_ADC_DMA_GetRegAddr
  * @param  ADCx ADC instance
  * @param  Register This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA
  *         @arg @ref LL_ADC_DMA_REG_REGULAR_DATA_MULTI (1)
  *         (1) Available on devices with several ADC instances.
  * @retval ADC register address
  */
#if defined(ADC2)
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t Register)
{
  register uint32_t data_reg_addr = 0;
  
  if (Register == LL_ADC_DMA_REG_REGULAR_DATA)
  {
    /* Retrieve address of register DR */
    data_reg_addr = (uint32_t)&(ADCx->DR);
  }
  else /* (Register == LL_ADC_DMA_REG_REGULAR_DATA_MULTI) */
  {
    /* Retrieve address of register CDR */
    data_reg_addr = (uint32_t)&((__LL_ADC_COMMON_INSTANCE(ADCx))->CDR);
  }
  
  return data_reg_addr;
}
#else
__STATIC_INLINE uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t Register)
{
  /* Retrieve address of register DR */
  return (uint32_t)&(ADCx->DR);
}
#endif

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Common Configuration of ADC hierarchical scope: common to several ADC
  * @{
  */

/**
  * @brief  Set parameter common to several ADC: Clock source and prescaler.
  * @note   On this STM32 family, if ADC group injected is used, some
  *         clock ratio constraints between ADC clock and AHB clock
  *         must be respected.
  *         Refer to reference manual.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      CKMODE         LL_ADC_SetCommonClock\n
  *         CCR      PRESC          LL_ADC_SetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  ClockSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV1
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t ClockSource)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_CKMODE | ADC_CCR_PRESC, ClockSource);
}

/**
  * @brief  Get parameter common to several ADC: Clock source and prescaler.
  * @rmtoll CCR      CKMODE         LL_ADC_GetCommonClock\n
  *         CCR      PRESC          LL_ADC_GetCommonClock
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV1
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV2
  *         @arg @ref LL_ADC_CLOCK_SYNC_PCLK_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV1
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV2
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV4
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV6
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV8
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV10
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV12
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV16
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV32
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV64
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV128
  *         @arg @ref LL_ADC_CLOCK_ASYNC_DIV256
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_CKMODE | ADC_CCR_PRESC));
}

/**
  * @brief  Set parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  *         One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      VREFEN         LL_ADC_SetCommonPathInternalCh\n
  *         CCR      TSEN           LL_ADC_SetCommonPathInternalCh\n
  *         CCR      VBATEN         LL_ADC_SetCommonPathInternalCh
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  PathInternal This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_VREFEN | ADC_CCR_TSEN | ADC_CCR_VBATEN, PathInternal);
}

/**
  * @brief  Get parameter common to several ADC: measurement path to internal
  *         channels (VrefInt, temperature sensor, ...).
  *         One or several values can be selected.
  *         Example: (LL_ADC_PATH_INTERNAL_VREFINT |
  *                   LL_ADC_PATH_INTERNAL_TEMPSENSOR)
  * @rmtoll CCR      VREFEN         LL_ADC_GetCommonPathInternalCh\n
  *         CCR      TSEN           LL_ADC_GetCommonPathInternalCh\n
  *         CCR      VBATEN         LL_ADC_GetCommonPathInternalCh
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_ADC_PATH_INTERNAL_NONE
  *         @arg @ref LL_ADC_PATH_INTERNAL_VREFINT
  *         @arg @ref LL_ADC_PATH_INTERNAL_TEMPSENSOR
  *         @arg @ref LL_ADC_PATH_INTERNAL_VBAT
  */
__STATIC_INLINE uint32_t LL_ADC_GetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_VREFEN | ADC_CCR_TSEN | ADC_CCR_VBATEN));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Instance Configuration of ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Set ADC calibration factor in the mode single-ended
  *         or differential (for devices with differential mode available).
  *         This function is intended to set calibration parameters
  *         without performing a new calibration using
  *         @ref LL_ADC_StartCalibration().
  * @note   In case of setting calibration factors of both modes single ended
  *         and differential (parameter LL_ADC_BOTH_SINGLE_DIFF_ENDED):
  *         both calibration factors must be concatenated.
  *         To perform this processing, use helper macro
  *         @ref __LL_ADC_CALIB_FACTOR_SINGLE_DIFF().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled, without calibration on going, without conversion
  *         on going on group regular.
  * @rmtoll CALFACT  CALFACT_S      LL_ADC_SetCalibrationFactor\n
  *         CALFACT  CALFACT_D      LL_ADC_SetCalibrationFactor
  * @param  ADCx ADC instance
  * @param  SingleDiff This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  *         @arg @ref LL_ADC_BOTH_SINGLE_DIFF_ENDED
  * @param  CalibrationFactor 0x00...0x7F
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetCalibrationFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
  MODIFY_REG(ADCx->CALFACT,
             SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK,
             CalibrationFactor << POSITION_VAL(SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK));
}

/**
  * @brief  Get ADC calibration factor in the mode single-ended
  *         or differential (for devices with differential mode available).
  *         Calibration factors are set by hardware after performing a
  *         calibration  using function @ref LL_ADC_StartCalibration().
  * @rmtoll CALFACT  CALFACT_S      LL_ADC_GetCalibrationFactor\n
  *         CALFACT  CALFACT_D      LL_ADC_GetCalibrationFactor
  * @param  ADCx ADC instance
  * @param  SingleDiff This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval 0x00...0x7F
  */
__STATIC_INLINE uint32_t LL_ADC_GetCalibrationFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff)
{
  /* Retrieve bits with position in register depending on parameter           */
  /* "SingleDiff".                                                            */
  /* Parameter used with mask "ADC_SINGLEDIFF_CALIB_FACTOR_MASK" because      */
  /* containing other bits reserved for other purpose.                        */
  return (uint32_t)(READ_BIT(ADCx->CALFACT, (SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK)) >> POSITION_VAL(SingleDiff & ADC_SINGLEDIFF_CALIB_FACTOR_MASK));
}

/**
  * @brief  Set ADC data resolution.
  *         Refer to reference manual for alignments formats versus ADC resolutions.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     RES            LL_ADC_SetResolution
  * @param  ADCx ADC instance
  * @param  Resolution This parameter can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_RES, Resolution);
}

/**
  * @brief  Get ADC data resolution.
  *         Refer to reference manual for alignments formats versus ADC resolutions.
  * @rmtoll CFGR     RES            LL_ADC_GetResolution
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_RESOLUTION_12B
  *         @arg @ref LL_ADC_RESOLUTION_10B
  *         @arg @ref LL_ADC_RESOLUTION_8B
  *         @arg @ref LL_ADC_RESOLUTION_6B
  */
__STATIC_INLINE uint32_t LL_ADC_GetResolution(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_RES));
}

/**
  * @brief  Set ADC conversion data alignment.
  *         Refer to reference manual for alignments formats 
  *         dependencies to ADC resolutions.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     ALIGN          LL_ADC_SetDataAlignment
  * @param  ADCx ADC instance
  * @param  DataAlignment This parameter can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_ALIGN, DataAlignment);
}

/**
  * @brief  Get ADC conversion data alignment.
  *         Refer to reference manual for alignments formats 
  *         dependencies to ADC resolutions.
  * @rmtoll CFGR     ALIGN          LL_ADC_GetDataAlignment
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_DATA_ALIGN_RIGHT
  *         @arg @ref LL_ADC_DATA_ALIGN_LEFT
  */
__STATIC_INLINE uint32_t LL_ADC_GetDataAlignment(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_ALIGN));
}

/**
  * @brief  Set ADC low power mode:
  *          * ADC low power mode "auto wait": Dynamic low power mode, 
  *            ADC conversions occurrences are limited to the minimum necessary
  *            in order to reduce power consumption.
  *            New ADC conversion starts only when the previous
  *            unitary conversion data (for ADC group regular)
  *            or previous sequence conversions data (for ADC group injected)
  *            has been retrieved by user software.
  *            In the meantime, ADC remains idle: does not performs any 
  *            other conversion.
  *            This mode allows to automatically adapt the ADC conversions
  *            trigs to the speed of the software that reads the data. 
  *            Moreover, this avoids risk of overrun for low frequency
  *            applications.
  *            How to use this low power mode:
  *             * Do not use with interruption or DMA since these modes
  *               have to clear immediately the EOC flag to free the
  *               IRQ vector sequencer.
  *             * Do use with polling: 1. Start conversion, 
  *               2. Later on, when conversion data is needed: poll for end of
  *               conversion  to ensure that conversion is completed and
  *               retrieve ADC conversion data. This will trig another
  *               ADC conversion start.
  *          * ADC low power mode "auto power-off" (feature available on 
  *            this device if parameter LL_ADC_LP_MODE_AUTOOFF is available):
  *            the ADC automatically powers-off after a conversion and 
  *            automatically wakes-up when a new conversion is triggered 
  *            (with startup time between trigger and start of sampling).
  *            This feature can be combined with low power mode "auto wait".
  * @note   With ADC low power mode "auto wait", the ADC conversion data read 
  *         is corresponding to previous ADC conversion start, independently 
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AUTDLY         LL_ADC_SetLowPowerMode
  * @param  ADCx ADC instance
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetLowPowerMode(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_AUTDLY, LowPowerMode);
}

/**
  * @brief  Get ADC low power mode:
  *          * ADC low power mode "auto wait": Dynamic low power mode, 
  *            ADC conversions occurrences are limited to the minimum necessary
  *            in order to reduce power consumption.
  *            New ADC conversion starts only when the previous
  *            unitary conversion data (for ADC group regular)
  *            or previous sequence conversions data (for ADC group injected)
  *            has been retrieved by user software.
  *            In the meantime, ADC remains idle: does not performs any 
  *            other conversion.
  *            This mode allows to automatically adapt the ADC conversions
  *            trigs to the speed of the software that reads the data. 
  *            Moreover, this avoids risk of overrun for low frequency
  *            applications.
  *            How to use this low power mode:
  *             * Do not use with interruption or DMA since these modes
  *               have to clear immediately the EOC flag to free the
  *               IRQ vector sequencer.
  *             * Do use with polling: 1. Start conversion, 
  *               2. Later on, when conversion data is needed: poll for end of
  *               conversion  to ensure that conversion is completed and
  *               retrieve ADC conversion data. This will trig another
  *               ADC conversion start.
  *          * ADC low power mode "auto power-off" (feature available on 
  *            this device if parameter LL_ADC_LP_MODE_AUTOOFF is available):
  *            the ADC automatically powers-off after a conversion and 
  *            automatically wakes-up when a new conversion is triggered 
  *            (with startup time between trigger and start of sampling).
  *            This feature can be combined with low power mode "auto wait".
  * @note   With ADC low power mode "auto wait", the ADC conversion data read 
  *         is corresponding to previous ADC conversion start, independently 
  *         of delay during which ADC was idle.
  *         Therefore, the ADC conversion data may be outdated: does not
  *         correspond to the current voltage level on the selected
  *         ADC channel.
  * @rmtoll CFGR     AUTDLY         LL_ADC_GetLowPowerMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_LP_MODE_NONE
  *         @arg @ref LL_ADC_LP_AUTOWAIT
  */
__STATIC_INLINE uint32_t LL_ADC_GetLowPowerMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_AUTDLY));
}

/**
  * @brief  Set ADC selected offset number 1, 2, 3 or 4:
  *          * ADC channel to which the offset programmed will be applied
  *            (independently of channel mapped on ADC group regular
  *            or group injected)
  *          * Offset level (offset to be subtracted from the raw
  *            converted data).
  *         Caution: Offset format is dependent to ADC resolution:
  *         offset has to be left-aligned on bit 11, the LSB (right bits)
  *         are set to 0.
  * @note   This function enables the offset, by default. It can be forced
  *         to disable state using function LL_ADC_SetOffsetState().
  * @note   If a channel is mapped on several offsets numbers, only the offset
  *         with the lowest value is considered for the subtraction.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @note   On STM32L4, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN1..5).
  * @rmtoll OFR1     OFFSET1_CH     LL_ADC_SetOffset\n
  *         OFR1     OFFSET1        LL_ADC_SetOffset\n
  *         OFR1     OFFSET1_EN     LL_ADC_SetOffset\n
  *         OFR2     OFFSET2_CH     LL_ADC_SetOffset\n
  *         OFR2     OFFSET2        LL_ADC_SetOffset\n
  *         OFR2     OFFSET2_EN     LL_ADC_SetOffset\n
  *         OFR3     OFFSET3_CH     LL_ADC_SetOffset\n
  *         OFR3     OFFSET3        LL_ADC_SetOffset\n
  *         OFR3     OFFSET3_EN     LL_ADC_SetOffset\n
  *         OFR4     OFFSET4_CH     LL_ADC_SetOffset\n
  *         OFR4     OFFSET4        LL_ADC_SetOffset\n
  *         OFR4     OFFSET4_EN     LL_ADC_SetOffset
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @param  OffsetLevel 0x000...0xFFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOffset(ADC_TypeDef* ADCx, uint32_t Offsety, uint32_t Channel, uint32_t OffsetLevel)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  
  MODIFY_REG(*preg,
             ADC_OFR1_OFFSET1_EN | ADC_OFR1_OFFSET1_CH | ADC_OFR1_OFFSET1,
             ADC_OFR1_OFFSET1_EN | (Channel & ADC_CHANNEL_ID_NUMBER_MASK) | OffsetLevel);
}

/**
  * @brief  Get ADC selected offset number 1, 2, 3 or 4:
  *          * Channel to which the offset programmed will be applied
  *            (independently of channel mapped on ADC group regular
  *            or group injected)
  * @note   Usage of the returned channel number:
  *          - To reinject this channel into another function LL_ADC_xxx:
  *            the returned channel number is only partly formatted on definition
  *            of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *            with literals LL_ADC_CHANNEL_x, then the selected
  *            literal LL_ADC_CHANNEL_x can be used as parameter for another
  *            function.
  *          - To get the channel number in decimal format:
  *            process the returned value with the helper macro
  *            @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @note   On STM32L4, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN1..5).
  * @rmtoll OFR1     OFFSET1_CH     LL_ADC_GetOffsetChannel\n
  *         OFR2     OFFSET2_CH     LL_ADC_GetOffsetChannel\n
  *         OFR3     OFFSET3_CH     LL_ADC_GetOffsetChannel\n
  *         OFR4     OFFSET4_CH     LL_ADC_GetOffsetChannel
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  *         (1, 2, 3, 4) For ADC channel read back from ADC register,
  *                      comparison with internal channel parameter to be done
  *                      using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetChannel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  
  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSET1_CH);
}

/**
  * @brief  Get ADC instance selected offset number 1, 2, 3 or 4:
  *          * Offset level (offset to be subtracted from the raw
  *            converted data).
  *          Caution: Offset format is dependent to ADC resolution:
  *          offset has to be left-aligned on bit 11, the LSB (right bits)
  *          are set to 0.
  * @rmtoll OFR1     OFFSET1        LL_ADC_GetOffsetLevel\n
  *         OFR2     OFFSET2        LL_ADC_GetOffsetLevel\n
  *         OFR3     OFFSET3        LL_ADC_GetOffsetLevel\n
  *         OFR4     OFFSET4        LL_ADC_GetOffsetLevel
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval 0x000...0xFFF
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetLevel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  
  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSET1);
}

/**
  * @brief  Set ADC instance selected offset number 1, 2, 3 or 4:
  *          * Force offset disable (or enable) without modifying offset channel
  *            or value.
  * @note   This function should be needed only in case of offset to be
  *         enabled-disabled dynamically, and should not be needed in other cases:
  *         function LL_ADC_SetOffset() automatically enables the offset.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll OFR1     OFFSET1_EN     LL_ADC_SetOffsetState\n
  *         OFR2     OFFSET2_EN     LL_ADC_SetOffsetState\n
  *         OFR3     OFFSET3_EN     LL_ADC_SetOffsetState\n
  *         OFR4     OFFSET4_EN     LL_ADC_SetOffsetState
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @param  OffsetState This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_DISABLE
  *         @arg @ref LL_ADC_OFFSET_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOffsetState(ADC_TypeDef *ADCx, uint32_t Offsety, uint32_t OffsetState)
{
  register uint32_t *preg = (uint32_t *)((uint32_t)
                            ((uint32_t)(&ADCx->OFR1) + (Offsety*4)));
  
  MODIFY_REG(*preg,
             ADC_OFR1_OFFSET1_EN,
             OffsetState);
}

/**
  * @brief  Get ADC instance selected offset number 1, 2, 3 or 4:
  *          * Get offset state disabled or enabled.
  * @rmtoll OFR1     OFFSET1_EN     LL_ADC_GetOffsetState\n
  *         OFR2     OFFSET2_EN     LL_ADC_GetOffsetState\n
  *         OFR3     OFFSET3_EN     LL_ADC_GetOffsetState\n
  *         OFR4     OFFSET4_EN     LL_ADC_GetOffsetState
  * @param  ADCx ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_1
  *         @arg @ref LL_ADC_OFFSET_2
  *         @arg @ref LL_ADC_OFFSET_3
  *         @arg @ref LL_ADC_OFFSET_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OFFSET_DISABLE
  *         @arg @ref LL_ADC_OFFSET_ENABLE
  */
__STATIC_INLINE uint32_t LL_ADC_GetOffsetState(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->OFR1, Offsety);
  
  return (uint32_t) READ_BIT(*preg, ADC_OFR1_OFFSET1_EN);
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Regular Configuration of ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Set ADC group regular conversion trigger source:
  *         internal (SW start) or external from timer or external interrupt.
  * @note   Setting trigger source to external trigger also set trigger polarity
  *         to rising edge 
  *         (default setting for compatibility with some ADC on other
  *         STM32 families having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_REG_SetTrigEdge().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_SetTrigSource\n
  *         CFGR     EXTEN          LL_ADC_REG_SetTrigSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SW_START
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC3
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_CC2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_CC4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_CC4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_EXTI_LINE11
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTrigSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_EXTEN | ADC_CFGR_EXTSEL, TriggerSource);
}

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         internal (SW start) or external from timer or external interrupt.
  * @note   To determine whether group regular trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to 
  *         " if(LL_ADC_REG_GetTrigSource(ADC1) == LL_ADC_REG_TRIG_SW_START) ")
  *         use function @ref LL_ADC_REG_IsTrigSourceSWStart.
  * @rmtoll CFGR     EXTSEL         LL_ADC_REG_GetTrigSource\n
  *         CFGR     EXTEN          LL_ADC_REG_GetTrigSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_SW_START
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC1
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM1_CC3
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM2_CC2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM3_CC4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM4_CC4
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_REG_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_REG_TRIG_EXT_EXTI_LINE11
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTrigSource(ADC_TypeDef *ADCx)
{
  register uint32_t TriggerSource = READ_BIT(ADCx->CFGR, ADC_CFGR_EXTSEL | ADC_CFGR_EXTEN);
  
  /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
  /* corresponding to ADC_CFGR_EXTEN {0; 1; 2; 3}.                            */
  register uint32_t ShiftExten = ((TriggerSource & ADC_CFGR_EXTEN) >> (ADC_REG_TRIG_EXTEN_BITOFFSET_POS - 2));
  
  /* Set bitfield corresponding to ADC_CFGR_EXTEN and ADC_CFGR_EXTSEL         */
  /* to match with triggers literals definition.                              */
  return ((TriggerSource
           & (ADC_REG_TRIG_SOURCE_MASK >> ShiftExten) & ADC_CFGR_EXTSEL)
          | ((ADC_REG_TRIG_EDGE_MASK >> ShiftExten) & ADC_CFGR_EXTEN)
         );
}

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         (0: trigger source external trigger, 1: trigger source SW start).
  * @note   In case of group regular trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_GetTrigSource().
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_IsTrigSourceSWStart
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsTrigSourceSWStart(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CFGR, ADC_CFGR_EXTEN) == (LL_ADC_REG_TRIG_SW_START & ADC_CFGR_EXTEN));
}

/**
  * @brief  Set ADC group regular conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_SetTrigEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetTrigEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_EXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group regular conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll CFGR     EXTEN          LL_ADC_REG_GetTrigEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_REG_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetTrigEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_EXTEN));
}

/**
  * @brief  Set ADC continuous conversion mode on ADC group regular:
  *         whether ADC conversions are performed:
  *          * single mode: one conversion per trigger
  *          * continuous mode: after the first trigger, following
  *            conversions launched successively automatically.
  * @note   It is not possible to enable both ADC continuous mode
  *         and ADC group regular discontinuous mode.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     CONT           LL_ADC_REG_SetContinuousMode
  * @param  ADCx ADC instance
  * @param  Continuous This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_CONT, Continuous);
}

/**
  * @brief  Get ADC continuous conversion mode on ADC group regular:
  *         whether ADC conversions are performed:
  *          * single mode: one conversion per trigger
  *          * continuous mode: after the first trigger, following
  *            conversions launched successively automatically.
  * @rmtoll CFGR     CONT           LL_ADC_REG_GetContinuousMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_CONV_SINGLE
  *         @arg @ref LL_ADC_REG_CONV_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetContinuousMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_CONT));
}

/**
  * @brief  Set ADC group regular conversion data transfer: no transfer or transfer by DMA.
  *         If transfer by DMA selected, specifies the DMA requests
  *         mode:
  *          * Limited mode (One shot mode): DMA transfer requests are stopped
  *            when number of DMA data transfers (number of
  *            ADC conversions) is reached.
  *            This ADC mode is intended to be used with DMA mode non-circular.
  *          * Unlimited mode: DMA transfer requests are unlimited,
  *            whatever number of DMA data transfers (number of
  *            ADC conversions).
  *            This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *        (overrun flag and interruption if enabled).
  * @note   For devices with several ADC instances: ADC multimode DMA
  *         settings are available using function @ref LL_ADC_SetMultiDMATransfer().
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     DMAEN          LL_ADC_REG_SetDMATransfer\n
  *         CFGR     DMACFG         LL_ADC_REG_SetDMATransfer
  * @param  ADCx ADC instance
  * @param  DMATransfer This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_DMAEN | ADC_CFGR_DMACFG, DMATransfer);
}

/**
  * @brief  Get ADC group regular conversion data transfer: no transfer or transfer by DMA.
  *         If transfer by DMA selected, specifies the DMA requests
  *         mode:
  *          * Limited mode (One shot mode): DMA transfer requests are stopped
  *            when number of DMA data transfers (number of
  *            ADC conversions) is reached.
  *            This ADC mode is intended to be used with DMA mode non-circular.
  *          * Unlimited mode: DMA transfer requests are unlimited,
  *            whatever number of DMA data transfers (number of
  *            ADC conversions).
  *            This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   For devices with several ADC instances: ADC multimode DMA
  *         settings are available using function @ref LL_ADC_GetMultiDMATransfer().
  * @note   To configure DMA source address (peripheral address),
  *         use function @ref LL_ADC_DMA_GetRegAddr().
  * @rmtoll CFGR     DMAEN          LL_ADC_REG_GetDMATransfer\n
  *         CFGR     DMACFG         LL_ADC_REG_GetDMATransfer
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_NONE
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_LIMITED
  *         @arg @ref LL_ADC_REG_DMA_TRANSFER_UNLIMITED
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetDMATransfer(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_DMAEN | ADC_CFGR_DMACFG));
}

/**
  * @brief  Set ADC group regular behaviour in case of overrun:
  *         data preserved or overwritten.
  * @note   Compatibility with devices without feature overrun:
  *         other devices without this feature have a behaviour
  *         equivalent to data overwritten.
  *         The default setting of overrun is data preserved.
  *         Therefore, for compatibility with all devices, parameter
  *         overrun should be set to data overwritten.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_SetOverrun
  * @param  ADCx ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetOverrun(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_OVRMOD, Overrun);
}

/**
  * @brief  Get ADC group regular behaviour in case of overrun:
  *         data preserved or overwritten.
  * @rmtoll CFGR     OVRMOD         LL_ADC_REG_GetOverrun
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref LL_ADC_REG_OVR_DATA_OVERWRITTEN
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetOverrun(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_OVRMOD));
}

/**
  * @brief  Set ADC group regular sequencer length and scan direction.
  *          * For devices with sequencer fully configurable
  *            (function "LL_ADC_REG_SetSequencerRanks()" available):
  *            sequencer length and each rank affectation to a channel 
  *            are configurable.
  *            This function performs:
  *            - Sequence length: Set number of ranks in the scan sequence.
  *            - Sequence direction: Unless specified in parameters, sequencer
  *              scan direction is forward (from rank 1 to rank n).
  *            Sequencer ranks are selected using
  *            function "LL_ADC_REG_SetSequencerRanks()".
  *          * For devices with sequencer not fully configurable
  *            (function "LL_ADC_REG_SetSequencerChannels()" available):
  *            sequencer length and each rank affectation to a channel 
  *            are defined by channel number.
  *            This function performs:
  *            - Sequence length: Number of ranks in the scan sequence is
  *              defined by number of channels set in the sequence,
  *              rank of each channel is fixed by channel HW number.
  *              (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *            - Sequence direction: Unless specified in parameters, sequencer
  *              scan direction is forward (from lowest channel number to
  *              highest channel number).
  *            Sequencer ranks are selected using
  *            function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     L              LL_ADC_REG_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->SQR1, ADC_SQR1_L, SequencerNbRanks);
}

/**
  * @brief  Get ADC group regular sequencer length and scan direction.
  *          * For devices with sequencer fully configurable
  *            (function "LL_ADC_REG_SetSequencerRanks()" available):
  *            sequencer length and each rank affectation to a channel 
  *            are configurable.
  *            This function performs:
  *            - Sequence length: Set number of ranks in the scan sequence.
  *            - Sequence direction: Unless specified in parameters, sequencer
  *              scan direction is forward (from rank 1 to rank n).
  *            Sequencer ranks are selected using
  *            function "LL_ADC_REG_SetSequencerRanks()".
  *          * For devices with sequencer not fully configurable
  *            (function "LL_ADC_REG_SetSequencerChannels()" available):
  *            sequencer length and each rank affectation to a channel 
  *            are defined by channel number.
  *            This function performs:
  *            - Sequence length: Number of ranks in the scan sequence is
  *              defined by number of channels set in the sequence,
  *              rank of each channel is fixed by channel HW number.
  *              (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
  *            - Sequence direction: Unless specified in parameters, sequencer
  *              scan direction is forward (from lowest channel number to
  *              highest channel number).
  *            Sequencer ranks are selected using
  *            function "LL_ADC_REG_SetSequencerChannels()".
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll SQR1     L              LL_ADC_REG_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS
  *         @arg @ref LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->SQR1, ADC_SQR1_L));
}

/**
  * @brief  Set ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC continuous mode
  *         and ADC group regular discontinuous mode.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group regular discontinuous mode.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_SetSequencerDiscont\n
  *         CFGR     DISCNUM        LL_ADC_REG_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_DISCEN | ADC_CFGR_DISCNUM, SeqDiscont);
}

/**
  * @brief  Get ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     DISCEN         LL_ADC_REG_GetSequencerDiscont\n
  *         CFGR     DISCNUM        LL_ADC_REG_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_1RANK
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_2RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_3RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_4RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_5RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_6RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_7RANKS
  *         @arg @ref LL_ADC_REG_SEQ_DISCONT_8RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_DISCEN | ADC_CFGR_DISCNUM));
}

/**
  * @brief  Set ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  *         This function performs:
  *          - Channels ordering into each rank of scan sequence:
  *            whatever channel can be placed into whatever rank.
  * @note   On this STM32 family, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 family, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @rmtoll SQR1     SQ1            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ2            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ3            LL_ADC_REG_SetSequencerRanks\n
  *         SQR1     SQ4            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ5            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ6            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ7            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ8            LL_ADC_REG_SetSequencerRanks\n
  *         SQR2     SQ9            LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ10           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ11           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ12           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ13           LL_ADC_REG_SetSequencerRanks\n
  *         SQR3     SQ14           LL_ADC_REG_SetSequencerRanks\n
  *         SQR4     SQ15           LL_ADC_REG_SetSequencerRanks\n
  *         SQR4     SQ16           LL_ADC_REG_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register and register position depending on parameter "Rank".         */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1, __ADC_MASK_SHIFT(Rank, ADC_REG_SQRX_REGOFFSET_MASK));
  
  MODIFY_REG(*preg,
             ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK),
             (Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_REG_RANK_ID_SQRX_MASK)));
}

/**
  * @brief  Get ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   On this STM32 family, ADC group regular sequencer is
  *         fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *          - To reinject this channel into another function LL_ADC_xxx:
  *            the returned channel number is only partly formatted on definition
  *            of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *            with literals LL_ADC_CHANNEL_x, then the selected
  *            literal LL_ADC_CHANNEL_x can be used as parameter for another
  *            function.
  *          - To get the channel number in decimal format:
  *            process the returned value with the helper macro
  *            @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll SQR1     SQ1            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ2            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ3            LL_ADC_REG_GetSequencerRanks\n
  *         SQR1     SQ4            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ5            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ6            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ7            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ8            LL_ADC_REG_GetSequencerRanks\n
  *         SQR2     SQ9            LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ10           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ11           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ12           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ13           LL_ADC_REG_GetSequencerRanks\n
  *         SQR3     SQ14           LL_ADC_REG_GetSequencerRanks\n
  *         SQR4     SQ15           LL_ADC_REG_GetSequencerRanks\n
  *         SQR4     SQ16           LL_ADC_REG_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_REG_RANK_1
  *         @arg @ref LL_ADC_REG_RANK_2
  *         @arg @ref LL_ADC_REG_RANK_3
  *         @arg @ref LL_ADC_REG_RANK_4
  *         @arg @ref LL_ADC_REG_RANK_5
  *         @arg @ref LL_ADC_REG_RANK_6
  *         @arg @ref LL_ADC_REG_RANK_7
  *         @arg @ref LL_ADC_REG_RANK_8
  *         @arg @ref LL_ADC_REG_RANK_9
  *         @arg @ref LL_ADC_REG_RANK_10
  *         @arg @ref LL_ADC_REG_RANK_11
  *         @arg @ref LL_ADC_REG_RANK_12
  *         @arg @ref LL_ADC_REG_RANK_13
  *         @arg @ref LL_ADC_REG_RANK_14
  *         @arg @ref LL_ADC_REG_RANK_15
  *         @arg @ref LL_ADC_REG_RANK_16
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  *         (1, 2, 3, 4) For ADC channel read back from ADC register,
  *                      comparison with internal channel parameter to be done
  *                      using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_REG_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1, __ADC_MASK_SHIFT(Rank, ADC_REG_SQRX_REGOFFSET_MASK));
  
  return (uint32_t) (READ_BIT(*preg,
                              ADC_CHANNEL_ID_NUMBER_MASK_POSBIT0 << (Rank & ADC_REG_RANK_ID_SQRX_MASK))
                     << (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_REG_RANK_ID_SQRX_MASK))
                    );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Group_Injected Configuration of ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Set ADC group injected conversion trigger source:
  *         internal (SW start) or external from timer or external interrupt.
  * @note   Setting trigger source to external trigger also set trigger polarity
  *         to rising edge 
  *         (default setting for compatibility with some ADC on other
  *         STM32 families having this setting set by HW default value).
  *         In case of need to modify trigger edge, use
  *         function @ref LL_ADC_INJ_SetTrigEdge().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_SetTrigSource\n
  *         JSQR     JEXTEN         LL_ADC_INJ_SetTrigSource
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SW_START
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN, TriggerSource);
}

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         internal (SW start) or external from timer or external interrupt.
  * @note   To determine whether group injected trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         (equivalent to 
  *         " if(LL_ADC_INJ_GetTrigSource(ADC1) == LL_ADC_INJ_TRIG_SW_START) ")
  *         use function @ref LL_ADC_INJ_IsTrigSourceSWStart.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_GetTrigSource\n
  *         JSQR     JEXTEN         LL_ADC_INJ_GetTrigSource
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SW_START
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigSource(ADC_TypeDef *ADCx)
{
  register uint32_t TriggerSource = READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTSEL | ADC_JSQR_JEXTEN);
  
  /* Value for shift of {0; 4; 8; 12} depending on value of bitfield          */
  /* corresponding to ADC_JSQR_JEXTEN {0; 1; 2; 3}.                           */
  register uint32_t ShiftJexten = ((TriggerSource & ADC_JSQR_JEXTEN) >> (ADC_INJ_TRIG_EXTEN_BITOFFSET_POS - 2));
  
  /* Set bitfield corresponding to ADC_JSQR_JEXTEN and ADC_JSQR_JEXTSEL       */
  /* to match with triggers literals definition.                              */
  return ((TriggerSource
           & (ADC_INJ_TRIG_SOURCE_MASK >> ShiftJexten) & ADC_JSQR_JEXTSEL)
          | ((ADC_INJ_TRIG_EDGE_MASK >> ShiftJexten) & ADC_JSQR_JEXTEN)
         );
}

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         (0: trigger source external trigger, 1: trigger source SW start).
  * @note   In case of group injected trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_INJ_GetTrigSource.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_IsTrigSourceSWStart
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsTrigSourceSWStart(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN) == (LL_ADC_INJ_TRIG_SW_START & ADC_JSQR_JEXTEN));
}

/**
  * @brief  Set ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_SetTrigEdge
  * @param  ADCx ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JEXTEN, ExternalTriggerEdge);
}

/**
  * @brief  Get ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @rmtoll JSQR     JEXTEN         LL_ADC_INJ_GetTrigEdge
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JEXTEN));
}

/**
  * @brief  Set ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group injected discontinuous mode.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_SetTrigAuto
  * @param  ADCx ADC instance
  * @param  InjTrigAuto This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t InjTrigAuto)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_JAUTO, InjTrigAuto);
}

/**
  * @brief  Get ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @rmtoll CFGR     JAUTO          LL_ADC_INJ_GetTrigAuto
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref LL_ADC_INJ_TRIG_FROM_GRP_REGULAR
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetTrigAuto(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_JAUTO));
}

/**
  * @brief  Set ADC group injected contexts queue mode.
  *         A context is a setting of injected group sequencer:
  *          * injected group trigger
  *          * sequencer length
  *          * sequencer ranks
  *         If contexts queue is disabled:
  *          * only 1 sequence can be configured
  *            and is active perpetually.
  *         If contexts queue is enabled:
  *          * up to 2 contexts can be queued
  *            and are checked in and out as a FIFO stack (first-in, first-out).
  *          * If a new context is set when queues is full, error is triggered
  *            by interruption "Injected Queue Overflow".
  *          * Two behaviours are possible when all contexts have been processed:
  *            the contexts queue can maintain the last context active perpetually
  *            or can be empty and injected group triggers are disabled.
  *          * Triggers can be only external (not internal SW start)
  *          * Caution: The sequence must be fully configured in one time
  *            (one write of register JSQR makes a check-in of a new context
  *            into the queue).
  *            Therefore functions to set separately injected trigger and
  *            sequencer channels cannot be used, register JSQR must be set
  *            using function @ref LL_ADC_INJ_ConfigQueueContext().
  * @note   This parameter can be modified only when no conversion is on going
  *         on either groups regular or injected.
  * @note   A modification of the context mode (bit JQDIS) causes the contexts
  *         queue to be flushed and the register JSQR is cleared.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     JQM            LL_ADC_INJ_SetQueueMode\n
  *         CFGR     JQDIS          LL_ADC_INJ_SetQueueMode
  * @param  ADCx ADC instance
  * @param  QueueMode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_QUEUE_DISABLE
  *         @arg @ref LL_ADC_INJ_QUEUE_2CONTEXTS_LAST_ACTIVE
  *         @arg @ref LL_ADC_INJ_QUEUE_2CONTEXTS_END_EMPTY
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetQueueMode(ADC_TypeDef *ADCx, uint32_t QueueMode)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_JQM | ADC_CFGR_JQDIS, QueueMode);
}

/**
  * @brief  Get ADC group injected context queue mode.
  * @rmtoll CFGR     JQM            LL_ADC_INJ_GetQueueMode\n
  *         CFGR     JQDIS          LL_ADC_INJ_GetQueueMode
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_QUEUE_DISABLE
  *         @arg @ref LL_ADC_INJ_QUEUE_2CONTEXTS_LAST_ACTIVE
  *         @arg @ref LL_ADC_INJ_QUEUE_2CONTEXTS_END_EMPTY
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetQueueMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_JQM | ADC_CFGR_JQDIS));
}

/**
  * @brief  Set ADC group injected sequencer length and scan direction.
  *            * Sequence length: Set number of ranks in the sequence.
  *            * Sequence direction: Unless specified in parameters, sequencer
  *              scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JL             LL_ADC_INJ_SetSequencerLength
  * @param  ADCx ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JL, SequencerNbRanks);
}

/**
  * @brief  Get ADC group injected sequencer length and scan direction.
  *          * Sequence length: Set number of ranks in the sequence.
  *          * Sequence direction: Unless specified in parameters, sequencer
  *            scan direction is forward (from rank 1 to rank n).
  * @note   Sequencer disabled is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @rmtoll JSQR     JL             LL_ADC_INJ_GetSequencerLength
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR, ADC_JSQR_JL));
}

/**
  * @brief  Set ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group injected discontinuous mode.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_SetSequencerDiscont
  * @param  ADCx ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CFGR, ADC_CFGR_JDISCEN, SeqDiscont);
}

/**
  * @brief  Get ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @rmtoll CFGR     JDISCEN        LL_ADC_INJ_GetSequencerDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_DISCONT_1RANK
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR, ADC_CFGR_JDISCEN));
}

/**
  * @brief  Set ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   On this STM32 family, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 family, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN1..5).
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ2           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ3           LL_ADC_INJ_SetSequencerRanks\n
  *         JSQR     JSQ4           LL_ADC_INJ_SetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  /* Set bits with content of parameter "Channel" with bits position          */
  /* in register depending on parameter "Rank".                               */
  /* Parameters "Rank" and "Channel" are used with masks because containing   */
  /* other bits reserved for other purpose.                                   */
  MODIFY_REG(ADCx->JSQR,
             ADC_CHANNEL_ID_NUMBER_MASK >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_INJ_RANK_ID_JSQR_MASK)),
             (Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_INJ_RANK_ID_JSQR_MASK)));
}

/**
  * @brief  Get ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   Usage of the returned channel number:
  *          - To reinject this channel into another function LL_ADC_xxx:
  *            the returned channel number is only partly formatted on definition
  *            of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *            with literals LL_ADC_CHANNEL_x, then the selected
  *            literal LL_ADC_CHANNEL_x can be used as parameter for another
  *            function.
  *          - To get the channel number in decimal format:
  *            process the returned value with the helper macro
  *            @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  * @rmtoll JSQR     JSQ1           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ2           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ3           LL_ADC_INJ_GetSequencerRanks\n
  *         JSQR     JSQ4           LL_ADC_INJ_GetSequencerRanks
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  *         (1, 2, 3, 4) For ADC channel read back from ADC register,
  *                      comparison with internal channel parameter to be done
  *                      using helper macro @ref __LL_ADC_CHANNEL_INTERNAL_TO_EXTERNAL().
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  return (uint32_t)(READ_BIT(ADCx->JSQR,
                             ADC_CHANNEL_ID_NUMBER_MASK >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_INJ_RANK_ID_JSQR_MASK)))
                    << (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (Rank & ADC_INJ_RANK_ID_JSQR_MASK))
                   );
}

/**
  * @brief  Set one context on ADC group injected that will be checked in
  *         contexts queue.
  *         A context is a setting of injected group sequencer:
  *          * injected group trigger
  *          * sequencer length
  *          * sequencer ranks
  *         This function is intended to be used when contexts queue is enabled,
  *         because the sequence must be fully configured in one time
  *         (functions to set separately injected trigger and sequencer channels
  *         cannot be used):
  *         Refer to function @ref LL_ADC_INJ_SetQueueMode().
  * @note   In the contexts queue, only the active context can be read.
  *         The parameters of this function can be read using functions:
  *          - @ref LL_ADC_INJ_GetTrigSource()
  *          - @ref LL_ADC_INJ_GetTrigEdge()
  *          - @ref LL_ADC_INJ_GetSequencerRanks()
  * @note   On this STM32 family, to measure internal channels (VrefInt,
  *         TempSensor, ...), measurement paths to internal channels must be
  *         enabled separately.
  *         This can be done using function @ref LL_ADC_SetCommonPathInternalCh().
  * @note   On this STM32 family, some fast channels are available: fast analog inputs
  *         coming from GPIO pads (ADC_IN1..5).
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @rmtoll JSQR     JEXTSEL        LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JEXTEN         LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JL             LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JSQ1           LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JSQ2           LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JSQ3           LL_ADC_INJ_ConfigQueueContext\n
  *         JSQR     JSQ4           LL_ADC_INJ_ConfigQueueContext
  * @param  ADCx ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_SW_START
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM2_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_EXTI_LINE15
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_CC4
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC3
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM3_CC1
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_TIM15_TRGO
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref LL_ADC_INJ_TRIG_EXT_RISINGFALLING
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_DISABLE
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS
  *         @arg @ref LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS
  * @param  Rank1_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @param  Rank2_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @param  Rank3_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @param  Rank4_Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_ConfigQueueContext(ADC_TypeDef *ADCx,
                                                   uint32_t TriggerSource,
                                                   uint32_t ExternalTriggerEdge,
                                                   uint32_t SequencerNbRanks,
                                                   uint32_t Rank1_Channel,
                                                   uint32_t Rank2_Channel,
                                                   uint32_t Rank3_Channel,
                                                   uint32_t Rank4_Channel)
{
  /* Set bits with content of parameter "Rankx_Channel" with bits position    */
  /* in register depending on literal "LL_ADC_INJ_RANK_x".                    */
  /* Parameters "Rankx_Channel" and "LL_ADC_INJ_RANK_x" are used with masks   */
  /* because containing other bits reserved for other purpose.                */
  MODIFY_REG(ADCx->JSQR           ,
             ADC_JSQR_JEXTSEL |
             ADC_JSQR_JEXTEN  |
             ADC_JSQR_JSQ4    |
             ADC_JSQR_JSQ3    |
             ADC_JSQR_JSQ2    |
             ADC_JSQR_JSQ1    |
             ADC_JSQR_JL          ,
             TriggerSource       |
             ExternalTriggerEdge |
             ((Rank4_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (LL_ADC_INJ_RANK_4 & ADC_INJ_RANK_ID_JSQR_MASK))) |
             ((Rank3_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (LL_ADC_INJ_RANK_3 & ADC_INJ_RANK_ID_JSQR_MASK))) |
             ((Rank2_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (LL_ADC_INJ_RANK_2 & ADC_INJ_RANK_ID_JSQR_MASK))) |
             ((Rank1_Channel & ADC_CHANNEL_ID_NUMBER_MASK) >> (POSITION_VAL(ADC_CHANNEL_ID_NUMBER_MASK) - (LL_ADC_INJ_RANK_1 & ADC_INJ_RANK_ID_JSQR_MASK))) |
             SequencerNbRanks
            );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_Channels Configuration of ADC hierarchical scope: channels
  * @{
  */

/**
  * @brief  Set sampling time of the selected ADC channel.
  *         Unit: ADC clock cycles.
  *         On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   In case of internal channel (VrefInt, TempSensor, ...) to be
  *         converted:
  *         sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  *         Refer to device datasheet for timings values (parameters TS_vrefint,
  *         TS_temp, ...).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 family, ADC processing time is:
  *          - 12.5 ADC clock cycles at ADC resolution 12 bits
  *          - 10.5 ADC clock cycles at ADC resolution 10 bits
  *          - 8.5 ADC clock cycles at ADC resolution 8 bits
  *          - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll SMPR1    SMP0           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP1           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP2           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP3           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP4           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP5           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP6           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP7           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP8           LL_ADC_SetChannelSamplingTime\n
  *         SMPR1    SMP9           LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP10          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP11          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP12          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP13          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP14          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP15          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP16          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP17          LL_ADC_SetChannelSamplingTime\n
  *         SMPR2    SMP18          LL_ADC_SetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @param  SamplingTime This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_92CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_247CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_640CYCLES_5
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
  /* Set bits with content of parameter "SamplingTime" with bits position     */
  /* in register and register position depending on parameter "Channel".      */
  /* Parameter "Channel" is used with masks because containing                */
  /* other bits reserved for other purpose.                                   */
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPRX_REGOFFSET_MASK));
    
  MODIFY_REG(*preg,
             ADC_SMPR1_SMP0 << __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPx_BITOFFSET_MASK),
             SamplingTime   << __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPx_BITOFFSET_MASK));
}

/**
  * @brief  Get sampling time of the selected ADC channel. 
  *         Unit: ADC clock cycles.
  *         On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   Conversion time is the addition of sampling time and processing time.
  *         On this STM32 family, ADC processing time is:
  *          - 12.5 ADC clock cycles at ADC resolution 12 bits
  *          - 10.5 ADC clock cycles at ADC resolution 10 bits
  *          - 8.5 ADC clock cycles at ADC resolution 8 bits
  *          - 6.5 ADC clock cycles at ADC resolution 6 bits
  * @rmtoll SMPR1    SMP0           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP1           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP2           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP3           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP4           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP5           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP6           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP7           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP8           LL_ADC_GetChannelSamplingTime\n
  *         SMPR1    SMP9           LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP10          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP11          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP12          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP13          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP14          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP15          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP16          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP17          LL_ADC_GetChannelSamplingTime\n
  *         SMPR2    SMP18          LL_ADC_GetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1           (5)
  *         @arg @ref LL_ADC_CHANNEL_2           (5)
  *         @arg @ref LL_ADC_CHANNEL_3           (5)
  *         @arg @ref LL_ADC_CHANNEL_4           (5)
  *         @arg @ref LL_ADC_CHANNEL_5           (5)
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  *         @arg @ref LL_ADC_CHANNEL_15
  *         @arg @ref LL_ADC_CHANNEL_16
  *         @arg @ref LL_ADC_CHANNEL_17
  *         @arg @ref LL_ADC_CHANNEL_18
  *         @arg @ref LL_ADC_CHANNEL_VREFINT      (1)
  *         @arg @ref LL_ADC_CHANNEL_TEMPSENSOR   (4)
  *         @arg @ref LL_ADC_CHANNEL_VBAT         (4)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC2 (2)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH1_ADC3 (3)
  *         @arg @ref LL_ADC_CHANNEL_DAC1CH2_ADC3 (3)
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  *         (5) On STM32L4, fast channel (0.188 us for 12-bit resolution (ADC conversion rate up to 5.33 Ms/s)).
  *             Other channels are slow channels (0.238 us for 12-bit resolution (ADC conversion rate up to 4.21 Ms/s)).
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_SAMPLINGTIME_2CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_6CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_12CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_24CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_47CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_92CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_247CYCLES_5
  *         @arg @ref LL_ADC_SAMPLINGTIME_640CYCLES_5
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPRX_REGOFFSET_MASK));
  
  return (uint32_t)(READ_BIT(*preg,
                             ADC_SMPR1_SMP0 << __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPx_BITOFFSET_MASK))
                    >> __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPx_BITOFFSET_MASK)
                   );
}

/**
  * @brief  Set mode single-ended or differential input of the selected
  *         ADC channel.
  *         Channel ending is on channel scope: independently of channel mapped
  *         on ADC group regular or injected.
  *         In differential mode: Differential measurement is carried out
  *         between the selected channel 'i' (positive input) and
  *         channel 'i+1' (negative input). Only channel 'i' has to be
  *         configured, channel 'i+1' is configured automatically.
  * @note   Refer to Reference Manual to ensure the selected channel is available
  *         in differential mode.
  *         For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  * @note   On STM32L4, channels 15, 16, 17, 18 of ADC1, ADC2, ADC3 (if available)
  *         are internally fixed to single-ended inputs configuration.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @note   One or several values can be selected.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll DIFSEL   DIFSEL         LL_ADC_GetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  * @param  SingleDiff This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SingleDiff)
{
  /* Bits of channels in single or differential mode are set only for         */
  /* differential mode (for single mode, mask of bits allowed to be set is    */
  /* shifted out of range of bits of channels in single or differential mode. */
  MODIFY_REG(ADCx->DIFSEL,
             Channel & ADC_SINGLEDIFF_CHANNEL_MASK,
             (Channel & ADC_SINGLEDIFF_CHANNEL_MASK) & (ADC_DIFSEL_DIFSEL << (SingleDiff & ADC_SINGLEDIFF_CHANNEL_SHIFT_MASK)));
}

/**
  * @brief  Get mode single-ended or differential input of the selected
  *         ADC channel.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  *         Therefore, to ensure a channel is configured in single-ended mode,
  *         the configuration of channel itself and the channel 'i-1' must be
  *         read back (to ensure that the selected channel channel has not been
  *         configured in differential mode by the previous channel).
  * @note   Refer to Reference Manual to ensure the selected channel is available
  *         in differential mode.
  *         For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.
  * @note   On STM32L4, channels 15, 16, 17, 18 of ADC1, ADC2, ADC3 (if available)
  *         are internally fixed to single-ended inputs configuration.
  * @note   One or several values can be selected. In this case, the value
  *         returned is null if all channels are in single ended-mode.
  *         Example: (LL_ADC_CHANNEL_4 | LL_ADC_CHANNEL_12 | ...)
  * @rmtoll DIFSEL   DIFSEL         LL_ADC_GetChannelSamplingTime
  * @param  ADCx ADC instance
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_CHANNEL_0
  *         @arg @ref LL_ADC_CHANNEL_1
  *         @arg @ref LL_ADC_CHANNEL_2
  *         @arg @ref LL_ADC_CHANNEL_3
  *         @arg @ref LL_ADC_CHANNEL_4
  *         @arg @ref LL_ADC_CHANNEL_5
  *         @arg @ref LL_ADC_CHANNEL_6
  *         @arg @ref LL_ADC_CHANNEL_7
  *         @arg @ref LL_ADC_CHANNEL_8
  *         @arg @ref LL_ADC_CHANNEL_9
  *         @arg @ref LL_ADC_CHANNEL_10
  *         @arg @ref LL_ADC_CHANNEL_11
  *         @arg @ref LL_ADC_CHANNEL_12
  *         @arg @ref LL_ADC_CHANNEL_13
  *         @arg @ref LL_ADC_CHANNEL_14
  * @retval 0: channel in single-ended mode, else: channel in differential mode
  */
__STATIC_INLINE uint32_t LL_ADC_GetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel)
{
  return (uint32_t)(READ_BIT(ADCx->DIFSEL, (Channel & ADC_SINGLEDIFF_CHANNEL_MASK)));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_AnalogWatchdog Configuration of ADC transversal scope: analog watchdog
  * @{
  */

/**
  * @brief  Set ADC analog watchdog monitored channels:
  *         a single channel, multiple channels or all channels,
  *         on ADC groups regular and-or injected.
  * @note   Once monitored channels are selected, analog watchdog
  *         is enabled.
  * @note   In case of need to define a single channel to monitor
  *         with analog watchdog from sequencer channel definition,
  *         use helper macro @ref __LL_ADC_ANALOGWD_CHANNEL_GROUP().
  * @note   On this STM32 family, there are 2 kinds of analog watchdog
  *         instance:
  *          - AWD standard (instance AWD1):
  *            - channels monitored: can monitor 1 channel or all channels.
  *            - groups monitored: ADC groups regular and-or injected.
  *            - resolution: resolution is not limited (corresponds to
  *              ADC resolution configured).
  *          - AWD flexible (instances AWD2, AWD3):
  *            - channels monitored: flexible on channels monitored, selection is
  *              channel wise, from from 1 to all channels.
  *              Specificity of this analog watchdog: Multiple channels can
  *              be selected. For example:
  *              (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *            - groups monitored: not selection possible (monitoring on both
  *              groups regular and injected).
  *              Channels selected are monitored on regular and injected groups:
  *              LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *              LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *            - resolution: resolution is limited to 8 bits: if ADC resolution is
  *              12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *              the 2 LSB are ignored.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWD1CH         LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     AWD1SGL        LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     AWD1EN         LL_ADC_SetAnalogWDMonitChannels\n
  *         CFGR     JAWD1EN        LL_ADC_SetAnalogWDMonitChannels\n
  *         AWD2CR   AWD2CH         LL_ADC_SetAnalogWDMonitChannels\n
  *         AWD3CR   AWD3CH         LL_ADC_SetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDChannelGroup This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ         (1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG       (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ       (4)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ      (4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_INJ             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG_INJ            (4)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG_INJ    (3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG_INJ    (3)
  *         (0) On STM32L4, parameter available only on analog watchdog number: AWD1.
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDChannelGroup)
{
  /* Set bits with content of parameter "AWDChannelGroup" with bits position  */
  /* in register and register position depending on parameter "AWDy".         */
  /* Parameters "AWDChannelGroup" and "AWDy" are used with masks because      */
  /* containing other bits reserved for other purpose.                        */
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->CFGR, __ADC_MASK_SHIFT(AWDy, ADC_AWD_CRX_REGOFFSET_MASK)
                                                             + ((AWDy & ADC_AWD_CR12_REGOFFSETGAP_MASK) * ADC_AWD_CR12_REGOFFSETGAP_VAL));
  
  MODIFY_REG(*preg,
             (AWDy & ADC_AWD_CR_ALL_CHANNEL_MASK),
             AWDChannelGroup & AWDy);
}

/**
  * @brief  Get ADC analog watchdog monitored channel.
  * @note   Usage of the returned channel number:
  *          - To reinject this channel into another function LL_ADC_xxx:
  *            the returned channel number is only partly formatted on definition
  *            of literals LL_ADC_CHANNEL_x. Therefore, it has to be compared
  *            with literals LL_ADC_CHANNEL_x, then the selected
  *            literal LL_ADC_CHANNEL_x can be used as parameter for another
  *            function.
  *          - To get the channel number in decimal format:
  *            process the returned value with the helper macro
  *            @ref __LL_ADC_CHANNEL_TO_DECIMAL_NB().
  *            Applicable only when the analog watchdog is set to monitor
  *            one channel.
  * @note   On this STM32 family, there are 2 kinds of analog watchdog
  *         instance:
  *          - AWD standard (instance AWD1):
  *            - channels monitored: can monitor 1 channel or all channels.
  *            - groups monitored: ADC groups regular and-or injected.
  *            - resolution: resolution is not limited (corresponds to
  *              ADC resolution configured).
  *          - AWD flexible (instances AWD2, AWD3):
  *            - channels monitored: flexible on channels monitored, selection is
  *              channel wise, from from 1 to all channels.
  *              Specificity of this analog watchdog: Multiple channels can
  *              be selected. For example:
  *              (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *            - groups monitored: not selection possible (monitoring on both
  *              groups regular and injected).
  *              Channels selected are monitored on regular and injected groups:
  *              LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *              LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *            - resolution: resolution is limited to 8 bits: if ADC resolution is
  *              12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *              the 2 LSB are ignored.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR     AWD1CH         LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     AWD1SGL        LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     AWD1EN         LL_ADC_GetAnalogWDMonitChannels\n
  *         CFGR     JAWD1EN        LL_ADC_GetAnalogWDMonitChannels\n
  *         AWD2CR   AWD2CH         LL_ADC_GetAnalogWDMonitChannels\n
  *         AWD3CR   AWD3CH         LL_ADC_GetAnalogWDMonitChannels
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_AWD_DISABLE
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_INJ        (0)
  *         @arg @ref LL_ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_7_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_8_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_INJ           (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_9_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_10_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_11_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_12_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_13_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_14_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_15_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_16_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_17_REG_INJ
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_INJ          (0)
  *         @arg @ref LL_ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_INJ          (0)(1)
  *         @arg @ref LL_ADC_AWD_CH_VREFINT_REG_INJ         (1)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG       (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_INJ       (4)(4)
  *         @arg @ref LL_ADC_AWD_CH_TEMPSENSOR_REG_INJ      (4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_INJ             (0)(4)
  *         @arg @ref LL_ADC_AWD_CH_VBAT_REG_INJ            (4)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_INJ     (0)(2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC2_REG_INJ    (2)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH1_ADC3_REG_INJ    (3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_INJ     (0)(3)
  *         @arg @ref LL_ADC_AWD_CH_DAC1CH2_ADC3_REG_INJ    (3)
  *         (0) On STM32L4, parameter available only on analog watchdog number: AWD1.
  *         (1) On STM32L4, parameter available only on ADC instance: ADC1.
  *         (2) On STM32L4, parameter available only on ADC instance: ADC2.
  *         (3) On STM32L4, parameter available only on ADC instance: ADC3.
  *         (4) On STM32L4, parameter available only on ADC instances: ADC1, ADC3.
  */
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->CFGR, __ADC_MASK_SHIFT(AWDy, ADC_AWD_CRX_REGOFFSET_MASK)
                                                             + ((AWDy & ADC_AWD_CR12_REGOFFSETGAP_MASK) * ADC_AWD_CR12_REGOFFSETGAP_VAL));
  
  return (uint32_t)(READ_BIT(*preg,
                             AWDy)
                   );
}

/**
  * @brief  Set ADC analog watchdog thresholds value of both thresholds
  *         high and low.
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   On this STM32 family, there are 2 kinds of analog watchdog
  *         instance:
  *          - AWD standard (instance AWD1):
  *            - channels monitored: can monitor 1 channel or all channels.
  *            - groups monitored: ADC groups regular and-or injected.
  *            - resolution: resolution is not limited (corresponds to
  *              ADC resolution configured).
  *          - AWD flexible (instances AWD2, AWD3):
  *            - channels monitored: flexible on channels monitored, selection is
  *              channel wise, from from 1 to all channels.
  *              Specificity of this analog watchdog: Multiple channels can
  *              be selected. For example:
  *              (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *            - groups monitored: not selection possible (monitoring on both
  *              groups regular and injected).
  *              Channels selected are monitored on regular and injected groups:
  *              LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *              LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *            - resolution: resolution is limited to 8 bits: if ADC resolution is
  *              12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *              the 2 LSB are ignored.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll TR1      HT1            LL_ADC_ConfigAnalogWDThresholds\n
  *         TR2      HT2            LL_ADC_ConfigAnalogWDThresholds\n
  *         TR3      HT3            LL_ADC_ConfigAnalogWDThresholds\n
  *         TR1      LT1            LL_ADC_ConfigAnalogWDThresholds\n
  *         TR2      LT2            LL_ADC_ConfigAnalogWDThresholds\n
  *         TR3      LT3            LL_ADC_ConfigAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdHighValue For AWD1: 0x000...0xFFF, for AWD2, AWD3: 0x00...0xFF
  * @param  AWDThresholdLowValue For AWD1: 0x000...0xFFF, for AWD2, AWD3: 0x00...0xFF
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigAnalogWDThresholds(ADC_TypeDef* ADCx, uint32_t AWDy, uint32_t AWDThresholdHighValue, uint32_t AWDThresholdLowValue)
{
  /* Set bits with content of parameter "AWDThresholdxxxValue" with bits      */
  /* position in register and register position depending on parameter        */
  /* "AWDy".                                                                  */
  /* Parameters "AWDy" and "AWDThresholdxxxValue" are used with masks because */
  /* containing other bits reserved for other purpose.                        */
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->TR1, __ADC_MASK_SHIFT(AWDy, ADC_AWD_TRX_REGOFFSET_MASK));
  
  MODIFY_REG(*preg,
             ADC_TR1_HT1 | ADC_TR1_LT1,
             (AWDThresholdHighValue << ADC_TR1_HT1_BITOFFSET_POS) | AWDThresholdLowValue);
}

/**
  * @brief  Set ADC analog watchdog threshold value of threshold
  *         high or low.
  * @note   If values of both thresholds high or low must be set,
  *         use function @ref LL_ADC_ConfigAnalogWDThresholds().
  * @note   On this STM32 family, there are 2 kinds of analog watchdog
  *         instance:
  *          - AWD standard (instance AWD1):
  *            - channels monitored: can monitor 1 channel or all channels.
  *            - groups monitored: ADC groups regular and-or injected.
  *            - resolution: resolution is not limited (corresponds to
  *              ADC resolution configured).
  *          - AWD flexible (instances AWD2, AWD3):
  *            - channels monitored: flexible on channels monitored, selection is
  *              channel wise, from from 1 to all channels.
  *              Specificity of this analog watchdog: Multiple channels can
  *              be selected. For example:
  *              (LL_ADC_AWD_CHANNEL4_REG_INJ | LL_ADC_AWD_CHANNEL5_REG_INJ | ...)
  *            - groups monitored: not selection possible (monitoring on both
  *              groups regular and injected).
  *              Channels selected are monitored on regular and injected groups:
  *              LL_ADC_AWD_CHANNELxx_REG_INJ (do not use parameters
  *              LL_ADC_AWD_CHANNELxx_REG and LL_ADC_AWD_CHANNELxx_INJ)
  *            - resolution: resolution is limited to 8 bits: if ADC resolution is
  *              12 bits the 4 LSB are ignored, if ADC resolution is 10 bits
  *              the 2 LSB are ignored.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll TR1      HT1            LL_ADC_SetAnalogWDThresholds\n
  *         TR2      HT2            LL_ADC_SetAnalogWDThresholds\n
  *         TR3      HT3            LL_ADC_SetAnalogWDThresholds\n
  *         TR1      LT1            LL_ADC_SetAnalogWDThresholds\n
  *         TR2      LT2            LL_ADC_SetAnalogWDThresholds\n
  *         TR3      LT3            LL_ADC_SetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  * @param  AWDThresholdValue: For AWD1: 0x000...0xFFF, for AWD2, AWD3: 0x00...0xFF          
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef* ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow, uint32_t AWDThresholdValue)
{
  /* Set bits with content of parameter "AWDThresholdValue" with bits         */
  /* position in register and register position depending on parameters       */
  /* "AWDThresholdsHighLow" and "AWDy".                                       */
  /* Parameters "AWDy" and "AWDThresholdValue" are used with masks because    */
  /* containing other bits reserved for other purpose.                        */
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->TR1, __ADC_MASK_SHIFT(AWDy, ADC_AWD_TRX_REGOFFSET_MASK));
  
  MODIFY_REG(*preg,
             AWDThresholdsHighLow,
             AWDThresholdValue << POSITION_VAL(AWDThresholdsHighLow));
}

/**
  * @brief  Get ADC analog watchdog threshold value of threshold high,
  *         threshold low or raw data with ADC thresholds high and low concatenated.
  * @note   If raw data with raw data with ADC thresholds high and low is retrieved,
  *         the data of each threshold high or low can still be isolated
  *         using helper macro:
  *         @ref __LL_ADC_ANALOGWD_THRESHOLDS_HIGH_LOW().
  * @rmtoll TR1      HT1            LL_ADC_GetAnalogWDThresholds\n
  *         TR2      HT2            LL_ADC_GetAnalogWDThresholds\n
  *         TR3      HT3            LL_ADC_GetAnalogWDThresholds\n
  *         TR1      LT1            LL_ADC_GetAnalogWDThresholds\n
  *         TR2      LT2            LL_ADC_GetAnalogWDThresholds\n
  *         TR3      LT3            LL_ADC_GetAnalogWDThresholds
  * @param  ADCx ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD1
  *         @arg @ref LL_ADC_AWD2
  *         @arg @ref LL_ADC_AWD3
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref LL_ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref LL_ADC_AWD_THRESHOLD_LOW
  *         @arg @ref LL_ADC_AWD_THRESHOLDS_HIGH_LOW
  * @retval For AWD1: 0x000...0xFFF, for AWD2, AWD3: 0x00...0xFF
*/
__STATIC_INLINE uint32_t LL_ADC_GetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->TR1, __ADC_MASK_SHIFT(AWDy, ADC_AWD_TRX_REGOFFSET_MASK));
  
  return (uint32_t)(READ_BIT(*preg,
                             (AWDThresholdsHighLow | ADC_TR1_LT1))
                    >> POSITION_VAL(AWDThresholdsHighLow)
                   );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_oversampling Configuration of ADC transversal scope: oversampling
  * @{
  */

/**
  * @brief  Set ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on devices).
  *         If both groups regular and injected are selected,
  *         specify behaviour of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR2    ROVSE          LL_ADC_SetOverSamplingScope\n
  *         CFGR2    JOVSE          LL_ADC_SetOverSamplingScope\n
  *         CFGR2    ROVSM          LL_ADC_SetOverSamplingScope
  * @param  ADCx ADC instance
  * @param  OvsScope This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref LL_ADC_OVS_GRP_INJECTED
  *         @arg @ref LL_ADC_OVS_GRP_INJ_REG_RESUMED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingScope(ADC_TypeDef *ADCx, uint32_t OvsScope)
{
  MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSM, OvsScope);
}

/**
  * @brief  Get ADC oversampling scope: ADC groups regular and-or injected
  *         (availability of ADC group injected depends on devices).
  *         If both groups regular and injected are selected,
  *         specify behaviour of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  * @rmtoll CFGR2    ROVSE          LL_ADC_GetOverSamplingScope\n
  *         CFGR2    JOVSE          LL_ADC_GetOverSamplingScope\n
  *         CFGR2    ROVSM          LL_ADC_GetOverSamplingScope
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DISABLE
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref LL_ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref LL_ADC_OVS_GRP_INJECTED
  *         @arg @ref LL_ADC_OVS_GRP_INJ_REG_RESUMED
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingScope(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_ROVSE | ADC_CFGR2_JOVSE | ADC_CFGR2_ROVSM));
}

/**
  * @brief  Set ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group: number of oversampled conversions
  *         are done either in:
  *          * continuous mode (all conversions of oversampling ratio
  *            are done from 1 trigger)
  *          * discontinuous mode (each conversion of oversampling ratio
  *            needs a trigger).
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @note   On STM32L4, oversampling discontinuous mode (triggered mode)
  *         can be used only when oversampling is set on group regular only
  *         and in resumed mode.
  * @rmtoll CFGR2    TROVS          LL_ADC_SetOverSamplingDiscont
  * @param  ADCx ADC instance
  * @param  OverSamplingDiscont This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_REG_CONT
  *         @arg @ref LL_ADC_OVS_REG_DISCONT
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetOverSamplingDiscont(ADC_TypeDef *ADCx, uint32_t OverSamplingDiscont)
{
  MODIFY_REG(ADCx->CFGR2, ADC_CFGR2_TROVS, OverSamplingDiscont);
}

/**
  * @brief  Get ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group: number of oversampled conversions
  *         are done either in:
  *          * continuous mode (all conversions of oversampling ratio
  *            are done from 1 trigger)
  *          * discontinuous mode (each conversion of oversampling ratio
  *            needs a trigger).
  * @rmtoll CFGR2    TROVS          LL_ADC_GetOverSamplingDiscont
  * @param  ADCx ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_OVS_REG_CONT
  *         @arg @ref LL_ADC_OVS_REG_DISCONT
  */
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_TROVS));
}

/**
  * @brief  Set ADC oversampling (impacting both ADC groups regular and injected)
  *         parameters:
  *          * ratio
  *          * shift
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CFGR2    OVSS           LL_ADC_ConfigOverSamplingRatioShift\n
  *         CFGR2    OVSR           LL_ADC_ConfigOverSamplingRatioShift
  * @param  ADCx ADC instance
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_RATIO_2
  *         @arg @ref LL_ADC_OVS_RATIO_4
  *         @arg @ref LL_ADC_OVS_RATIO_8
  *         @arg @ref LL_ADC_OVS_RATIO_16
  *         @arg @ref LL_ADC_OVS_RATIO_32
  *         @arg @ref LL_ADC_OVS_RATIO_64
  *         @arg @ref LL_ADC_OVS_RATIO_128
  *         @arg @ref LL_ADC_OVS_RATIO_256
  * @param  Shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_1
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_2
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_3
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_4
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_5
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_6
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_7
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_8
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ConfigOverSamplingRatioShift(ADC_TypeDef *ADCx, uint32_t Ratio, uint32_t Shift)
{
  MODIFY_REG(ADCx->CFGR2, (ADC_CFGR2_OVSS | ADC_CFGR2_OVSR), (Shift | Ratio));
}

/**
  * @brief  Get ADC oversampling (impacting both ADC groups regular and injected)
  *         parameters:
  *          * ratio
  * @rmtoll CFGR2    OVSR           LL_ADC_GetOverSamplingRatio
  * @param  ADCx ADC instance
  * @retval Ratio This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_RATIO_2
  *         @arg @ref LL_ADC_OVS_RATIO_4
  *         @arg @ref LL_ADC_OVS_RATIO_8
  *         @arg @ref LL_ADC_OVS_RATIO_16
  *         @arg @ref LL_ADC_OVS_RATIO_32
  *         @arg @ref LL_ADC_OVS_RATIO_64
  *         @arg @ref LL_ADC_OVS_RATIO_128
  *         @arg @ref LL_ADC_OVS_RATIO_256
*/
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingRatio(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSR));
}

/**
  * @brief  Get ADC oversampling (impacting both ADC groups regular and injected)
  *         parameters:
  *          * shift
  * @rmtoll CFGR2    OVSS           LL_ADC_GetOverSamplingShift
  * @param  ADCx ADC instance
  * @retval Shift This parameter can be one of the following values:
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_NONE
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_1
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_2
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_3
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_4
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_5
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_6
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_7
  *         @arg @ref LL_ADC_OVS_DATA_SHIFT_8
*/
__STATIC_INLINE uint32_t LL_ADC_GetOverSamplingShift(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CFGR2, ADC_CFGR2_OVSS));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Configuration_ADC_Multimode Configuration of ADC hierarchical scope: multimode
  * @{
  */

#if defined(ADC2)
/**
  * @brief  Set ADC multimode configuration to operate in independent mode
  *         or multimode (for devices with several ADC instances).
  *         If multimode configuration: the selected ADC instance is
  *         either master or slave depending on hardware.
  *         Refer to reference manual.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      DUAL           LL_ADC_SetMultimode
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  Multimode This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_INDEPENDENT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INTERL
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_ALTERN
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMultimode(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t Multimode)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_DUAL, Multimode);
}

/**
  * @brief  Get ADC multimode configuration to operate in independent mode
  *         or multimode (for devices with several ADC instances).
  *         If multimode configuration: the selected ADC instance is
  *         either master or slave depending on hardware.
  *         Refer to reference manual.
  * @rmtoll CCR      DUAL           LL_ADC_GetMultimode
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_INDEPENDENT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INTERL
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_SIMULT
  *         @arg @ref LL_ADC_MULTI_DUAL_INJ_ALTERN
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT
  *         @arg @ref LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultimode(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_DUAL));
}

/**
  * @brief  Set ADC multimode conversion data transfer: no transfer
  *         or transfer by DMA.
  *         If ADC multimode transfer by DMA is not selected:
  *         each ADC uses its own DMA channel, with its individual
  *         DMA transfer settings.
  *         If ADC multimode transfer by DMA is selected:
  *         One DMA channel is used for both ADC (DMA of ADC master)
  *         Specifies the DMA requests mode:
  *          * Limited mode (One shot mode): DMA transfer requests are stopped
  *            when number of DMA data transfers (number of
  *            ADC conversions) is reached.
  *            This ADC mode is intended to be used with DMA mode non-circular.
  *          * Unlimited mode: DMA transfer requests are unlimited,
  *            whatever number of DMA data transfers (number of
  *            ADC conversions).
  *            This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   How to retrieve multimode conversion data:
  *         Whatever multimode transfer by DMA setting: using function
  *         @ref LL_ADC_REG_ReadMultiConversionData32().
  *         If ADC multimode transfer by DMA is selected: conversion data
  *         is a raw data with ADC master and slave concatenated.
  *         A macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled
  *         or enabled without conversion on going on group regular.
  * @rmtoll CCR      MDMA           LL_ADC_SetMultiDMATransfer\n
  *         CCR      DMACFG         LL_ADC_SetMultiDMATransfer
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  DMATransfer This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_REG_DMA_EACH_ADC
  *         @arg @ref LL_ADC_MULTI_REG_DMA_LIMIT_RES12_10B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_LIMIT_RES8_6B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_UNLMT_RES12_10B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_UNLMT_RES8_6B
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMultiDMATransfer(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t DMATransfer)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_MDMA | ADC_CCR_DMACFG, DMATransfer);
}

/**
  * @brief  Get ADC multimode conversion data transfer: no transfer
  *         or transfer by DMA.
  *         If ADC multimode transfer by DMA is not selected:
  *         each ADC uses its own DMA channel, with its individual
  *         DMA transfer settings.
  *         If ADC multimode transfer by DMA is selected:
  *         One DMA channel is used for both ADC (DMA of ADC master)
  *         Specifies the DMA requests mode:
  *          * Limited mode (One shot mode): DMA transfer requests are stopped
  *            when number of DMA data transfers (number of
  *            ADC conversions) is reached.
  *            This ADC mode is intended to be used with DMA mode non-circular.
  *          * Unlimited mode: DMA transfer requests are unlimited,
  *            whatever number of DMA data transfers (number of
  *            ADC conversions).
  *            This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA requests mode is set to unlimited and DMA is set to
  *         mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @note   How to retrieve multimode conversion data:
  *         Whatever multimode transfer by DMA setting: using function
  *         @ref LL_ADC_REG_ReadMultiConversionData32().
  *         If ADC multimode transfer by DMA is selected: conversion data
  *         is a raw data with ADC master and slave concatenated.
  *         A macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  * @rmtoll CCR      MDMA           LL_ADC_GetMultiDMATransfer\n
  *         CCR      DMACFG         LL_ADC_GetMultiDMATransfer
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_REG_DMA_EACH_ADC
  *         @arg @ref LL_ADC_MULTI_REG_DMA_LIMIT_RES12_10B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_LIMIT_RES8_6B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_UNLMT_RES12_10B
  *         @arg @ref LL_ADC_MULTI_REG_DMA_UNLMT_RES8_6B
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultiDMATransfer(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_MDMA | ADC_CCR_DMACFG));
}

/**
  * @brief  Set ADC multimode delay between 2 sampling phases.
  * @note   The sampling delay range depends on ADC resolution:
  *          - ADC resolution 12 bits can have maximum delay of 12 cycles.
  *          - ADC resolution 10 bits can have maximum delay of 10 cycles.
  *          - ADC resolution  8 bits can have maximum delay of  8 cycles.
  *          - ADC resolution  6 bits can have maximum delay of  6 cycles.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         All ADC instances of the ADC common group must be disabled.
  *         This check can be done with function @ref LL_ADC_IsEnabled() for each
  *         ADC instance or by using helper macro helper macro
  *         @ref __LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE().
  * @rmtoll CCR      DELAY          LL_ADC_SetMultiTwoSamplingDelay
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  TwoSamplingDelay This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES  (1)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES  (1)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES  (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES  (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES (3)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES (3)
  *         (1) Parameter available only if ADC resolution is 12, 10 or 8 bits.
  *         (2) Parameter available only if ADC resolution is 12 or 10 bits.
  *         (3) Parameter available only if ADC resolution is 12 bits.
  * @retval None
  */
__STATIC_INLINE void LL_ADC_SetMultiTwoSamplingDelay(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t TwoSamplingDelay)
{
  MODIFY_REG(ADCxy_COMMON->CCR, ADC_CCR_DELAY, TwoSamplingDelay);
}

/**
  * @brief  Get ADC multimode delay between 2 sampling phases.
  * @rmtoll CCR      DELAY          LL_ADC_GetMultiTwoSamplingDelay
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES  (1)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES  (1)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES  (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES  (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_10CYCLES (2)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_11CYCLES (3)
  *         @arg @ref LL_ADC_MULTI_TWOSMP_DELAY_12CYCLES (3)
  *         (1) Parameter available only if ADC resolution is 12, 10 or 8 bits.
  *         (2) Parameter available only if ADC resolution is 12 or 10 bits.
  *         (3) Parameter available only if ADC resolution is 12 bits.
  */
__STATIC_INLINE uint32_t LL_ADC_GetMultiTwoSamplingDelay(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CCR, ADC_CCR_DELAY));
}
#endif /* ADC2 */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Instance Operation on ADC hierarchical scope: ADC instance
  * @{
  */

/**
  * @brief  Put ADC instance in deep power down state.
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       DEEPPWD        LL_ADC_EnableDeepPowerDown
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableDeepPowerDown(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_DEEPPWD);
}

/**
  * @brief  Disable ADC deep power down mode.
  * @note   In case of ADC calibration necessary: When ADC is in deep-power-down
  *         state, the internal analog calibration is lost. After exiting from
  *         deep power down, calibration must be relaunched or calibration factor
  *         (preliminarily saved) must be set back into calibration register.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       DEEPPWD        LL_ADC_DisableDeepPowerDown
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableDeepPowerDown(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  CLEAR_BIT(ADCx->CR, (ADC_CR_DEEPPWD | ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance deep power down state.
  *         (0: deep power down is disabled, 1: deep power down is enabled)
  * @rmtoll CR       DEEPPWD        LL_ADC_IsDeepPowerDownEnabled
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsDeepPowerDownEnabled(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_DEEPPWD) == (ADC_CR_DEEPPWD));
}

/**
  * @brief  Enable ADC instance internal voltage regulator.
  * @note   On this STM32 family, after ADC internal voltage regulator enable,
  *         a delay for ADC internal voltage regulator stabilization
  *         is required before performing a ADC calibration or ADC enable.
  *         Refer to device datasheet, parameter tADCVREG_STUP.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADVREGEN       LL_ADC_EnableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableInternalRegulator(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADVREGEN);
}

/**
  * @brief  Disable ADC internal voltage regulator.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADVREGEN       LL_ADC_DisableInternalRegulator
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableInternalRegulator(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CR, (ADC_CR_ADVREGEN | ADC_CR_BITS_PROPERTY_RS));
}

/**
  * @brief  Get the selected ADC instance internal voltage regulator state.
  *         (0: internal regulator is disabled, 1: internal regulator is
  *         enabled).
  * @rmtoll CR       ADVREGEN       LL_ADC_IsInternalRegulatorEnabled
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsInternalRegulatorEnabled(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADVREGEN) == (ADC_CR_ADVREGEN));
}

/**
  * @brief  Enable the selected ADC instance.
  * @note   On this STM32 family, after ADC enable, a delay for 
  *         ADC internal analog stabilization is required before performing a
  *         ADC conversion start.
  *         Refer to device datasheet, parameter tSTAB.
  * @note   On this STM32 family, flag LL_ADC_ISR_ADRDY is raised when the ADC
  *         is enabled and when conversion clock (not core clock) is active.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled and ADC internal voltage regulator enabled.
  * @rmtoll CR       ADEN           LL_ADC_Enable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADEN);
}

/**
  * @brief  Disable the selected ADC instance.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be not disabled. Must be enabled without conversion on going
  *         on either groups regular or injected.
  * @rmtoll CR       ADDIS          LL_ADC_Disable
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADDIS);
}

/**
  * @brief  Get the selected ADC instance enable state.
  *         (0: ADC is disabled, 1: ADC is enabled).
  * @note   On this STM32 family, flag LL_ADC_ISR_ADRDY is raised when the ADC
  *         is enabled and when conversion clock (not core clock) is active.
  * @rmtoll CR       ADEN           LL_ADC_IsEnabled
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabled(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADEN) == (ADC_CR_ADEN));
}

/**
  * @brief  Get the selected ADC instance disable state.
  *         (0: no ADC disable command on going)
  * @rmtoll CR       ADDIS          LL_ADC_IsDisableOngoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsDisableOngoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADDIS) == (ADC_CR_ADDIS));
}

/**
  * @brief  Start ADC calibration in the mode single-ended
  *         or differential (for devices with differential mode available).
  * @note   On this STM32 family, a delay of 4 ADC clock cycles is required
  *         between ADC end of calibration and ADC enable.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be ADC disabled.
  * @rmtoll CR       ADCAL          LL_ADC_StartCalibration\n
  *         CR       ADCALDIF       LL_ADC_StartCalibration
  * @param  ADCx ADC instance
  * @param  SingleDiff This parameter can be one of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval None
  */
__STATIC_INLINE void LL_ADC_StartCalibration(ADC_TypeDef *ADCx, uint32_t SingleDiff)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_ADCALDIF | ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADCAL | (SingleDiff & ADC_SINGLEDIFF_CALIB_START_MASK));
}

/**
  * @brief  Get ADC calibration state.
  *         (0: calibration complete, 1: calibration in progress)
  * @rmtoll CR       ADCAL          LL_ADC_IsCalibrationOnGoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsCalibrationOnGoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADCAL) == (ADC_CR_ADCAL));
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Regular Operation on ADC hierarchical scope: group regular
  * @{
  */

/**
  * @brief  Start ADC group regular conversion.
  * @note   On this STM32 family, this function is relevant for both 
  *         internal trigger (SW start) and external trigger:
  *          - If ADC trigger has been set to software start, ADC conversion
  *            starts immediately.
  *          - If ADC trigger has been set to external trigger, ADC conversion
  *            will start at next trigger event (on the selected trigger edge)
  *            following the ADC start conversion command.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular.
  * @rmtoll CR       ADSTART        LL_ADC_REG_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADSTART);
}

/**
  * @brief  Stop ADC group regular conversion.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group regular,
  *         without ADC disable command on going.
  * @rmtoll CR       ADSTP          LL_ADC_REG_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_ADSTP);
}

/**
  * @brief  Get ADC group regular conversion state.
  *         (0: no conversion is on going on ADC group regular)
  * @rmtoll CR       ADSTART        LL_ADC_REG_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADSTART) == (ADC_CR_ADSTART));
}

/**
  * @brief  Get ADC group regular command of conversion stop state
  *         (0: no command of conversion stop is on going on ADC group regular).
  * @rmtoll CR       ADSTP          LL_ADC_REG_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_REG_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_ADSTP) == (ADC_CR_ADSTP));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         all ADC configurations: all ADC resolutions and
  *         all oversampling increased data width (for devices
  *         with feature oversampling).
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData32
  * @param  ADCx ADC instance
  * @retval 0x00000000...0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadConversionData32(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 12 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData12
  * @param  ADCx ADC instance
  * @retval 0x000...0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData12(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 10 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData10
  * @param  ADCx ADC instance
  * @retval 0x000...0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_REG_ReadConversionData10(ADC_TypeDef *ADCx)
{
  return (uint16_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 8 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData8
  * @param  ADCx ADC instance
  * @retval 0x00...0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData8(ADC_TypeDef *ADCx)
{
  return (uint8_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         ADC resolution 6 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_REG_ReadConversionData32.
  * @rmtoll DR       RDATA          LL_ADC_REG_ReadConversionData6
  * @param  ADCx ADC instance
  * @retval 0x00...0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_REG_ReadConversionData6(ADC_TypeDef *ADCx)
{
  return (uint8_t)(READ_BIT(ADCx->DR, ADC_DR_RDATA));
}

#if defined(ADC2)
/**
  * @brief  Get ADC multimode conversion data of ADC master, ADC slave
  *         or raw data with ADC master and slave concatenated.
  * @note   If raw data with ADC master and slave concatenated is retrieved,
  *         a macro is available to get the conversion data of
  *         ADC master or ADC slave: see helper macro
  *         @ref __LL_ADC_MULTI_CONV_DATA_MASTER_SLAVE().
  *         (however this macro is mainly intended for multimode
  *         transfer by DMA, because this function can do the same
  *         by getting multimode conversion data of ADC master or ADC slave
  *         separately).
  * @rmtoll CDR      RDATA_MST      LL_ADC_REG_ReadMultiConversionData32\n
  *         CDR      RDATA_SLV      LL_ADC_REG_ReadMultiConversionData32
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  ConvData This parameter can be one of the following values:
  *         @arg @ref LL_ADC_MULTI_MASTER
  *         @arg @ref LL_ADC_MULTI_SLAVE
  *         @arg @ref LL_ADC_MULTI_MASTER_SLAVE
  * @retval 0x00000000...0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_REG_ReadMultiConversionData32(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t ConvData)
{
  return (uint32_t)(READ_BIT(ADCxy_COMMON->CDR,
                             (ConvData | ADC_CDR_RDATA_SLV))
                    >> POSITION_VAL(ConvData)
                   );
}
#endif /* ADC2 */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_Operation_ADC_Group_Injected Operation on ADC hierarchical scope: group injected
  * @{
  */

/**
  * @brief  Start ADC group injected conversion.
  * @note   On this STM32 family, this function is relevant for both 
  *         internal trigger (SW start) and external trigger:
  *          - If ADC trigger has been set to software start, ADC conversion
  *            starts immediately.
  *          - If ADC trigger has been set to external trigger, ADC conversion
  *            will start at next trigger event (on the selected trigger edge)
  *            following the ADC start conversion command.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group injected,
  *         without conversion stop command on going on group injected.
  * @rmtoll CR       JADSTART       LL_ADC_INJ_StartConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StartConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_JADSTART);
}

/**
  * @brief  Stop ADC group injected conversion.
  * @note   On this STM32 family, setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled with conversion on going on group injected,
  *         without ADC disable command on going.
  * @rmtoll CR       JADSTP         LL_ADC_INJ_StopConversion
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_INJ_StopConversion(ADC_TypeDef *ADCx)
{
  /* Note: Write register with some additional bits forced to state reset     */
  /*       instead of modifying only the selected bit for this function,      */
  /*       to not interfere with bits with HW property "rs".                  */
  MODIFY_REG(ADCx->CR,
             ADC_CR_BITS_PROPERTY_RS,
             ADC_CR_JADSTP);
}

/**
  * @brief  Get ADC group injected conversion state.
  *         (0: no conversion is on going on ADC group injected)
  * @rmtoll CR       JADSTART       LL_ADC_INJ_IsConversionOngoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_JADSTART) == (ADC_CR_JADSTART));
}

/**
  * @brief  Get ADC group injected command of conversion stop state
  *         (0: no command of conversion stop is on going on ADC group injected).
  * @rmtoll CR       JADSTP         LL_ADC_INJ_IsStopConversionOngoing
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR, ADC_CR_JADSTP) == (ADC_CR_JADSTP));
}

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         all ADC configurations: all ADC resolutions and
  *         all oversampling increased data width (for devices
  *         with feature oversampling).
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData32\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData32
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval 0x00000000...0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_ADC_INJ_ReadConversionData32(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_INJ_JDRX_REGOFFSET_MASK));
  
  return (uint32_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 12 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData12\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData12
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval 0x000...0xFFF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData12(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_INJ_JDRX_REGOFFSET_MASK));
  
  return (uint16_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 10 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData10\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData10
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval 0x000...0x3FF
  */
__STATIC_INLINE uint16_t LL_ADC_INJ_ReadConversionData10(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_INJ_JDRX_REGOFFSET_MASK));
  
  return (uint16_t)(READ_BIT(*preg,
                             ADC_JDR1_JDATA)
                   );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 8 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData8\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData8
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval 0x00...0xFF
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData8(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_INJ_JDRX_REGOFFSET_MASK));
  
  return (uint8_t)(READ_BIT(*preg,
                            ADC_JDR1_JDATA)
                  );
}

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         ADC resolution 6 bits.
  * @note   For devices with feature oversampling: Oversampling
  *         can increase data width, function for extended range
  *         may be needed: @ref LL_ADC_INJ_ReadConversionData32.
  * @rmtoll JDR1     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR2     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR3     JDATA          LL_ADC_INJ_ReadConversionData6\n
  *         JDR4     JDATA          LL_ADC_INJ_ReadConversionData6
  * @param  ADCx ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref LL_ADC_INJ_RANK_1
  *         @arg @ref LL_ADC_INJ_RANK_2
  *         @arg @ref LL_ADC_INJ_RANK_3
  *         @arg @ref LL_ADC_INJ_RANK_4
  * @retval 0x00...0x3F
  */
__STATIC_INLINE uint8_t LL_ADC_INJ_ReadConversionData6(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_INJ_JDRX_REGOFFSET_MASK));
  
  return (uint8_t)(READ_BIT(*preg,
                            ADC_JDR1_JDATA)
                  );
}

/**
  * @}
  */

/** @defgroup ADC_LL_EF_FLAG_Management ADC flag management
  * @{
  */

/**
  * @brief  Get flag ADC ready.
  * @rmtoll ISR      ADRDY          LL_ADC_IsActiveFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_ADRDY(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_ADRDY) == (ADC_ISR_ADRDY));
}

/**
  * @brief  Get flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_IsActiveFlag_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOC(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_EOC) == (ADC_ISR_EOC));
}

/**
  * @brief  Get flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_IsActiveFlag_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOS(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_EOS) == (ADC_ISR_EOS));
}

/**
  * @brief  Get flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_IsActiveFlag_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_OVR(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_OVR) == (ADC_ISR_OVR));
}

/**
  * @brief  Get flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_IsActiveFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_EOSMP(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_EOSMP) == (ADC_ISR_EOSMP));
}

/**
  * @brief  Get flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_IsActiveFlag_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOC(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_JEOC) == (ADC_ISR_JEOC));
}

/**
  * @brief  Get flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_IsActiveFlag_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JEOS(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_JEOS) == (ADC_ISR_JEOS));
}

/**
  * @brief  Get flag ADC group injected contexts queue overflow.
  * @rmtoll ISR      JQOVF          LL_ADC_IsActiveFlag_JQOVF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_JQOVF(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_JQOVF) == (ADC_ISR_JQOVF));
}

/**
  * @brief  Get flag ADC analog watchdog 1 flag
  * @rmtoll ISR      AWD1           LL_ADC_IsActiveFlag_AWD1
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_AWD1) == (ADC_ISR_AWD1));
}

/**
  * @brief  Get flag ADC analog watchdog 2.
  * @rmtoll ISR      AWD2           LL_ADC_IsActiveFlag_AWD2
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_AWD2) == (ADC_ISR_AWD2));
}

/**
  * @brief  Get flag ADC analog watchdog 3.
  * @rmtoll ISR      AWD3           LL_ADC_IsActiveFlag_AWD3
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_AWD3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->ISR, ADC_ISR_AWD3) == (ADC_ISR_AWD3));
}

/**
  * @brief  Clear flag ADC ready.
  * @rmtoll ISR      ADRDY          LL_ADC_ClearFlag_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_ADRDY);
}

/**
  * @brief  Clear flag ADC group regular end of unitary conversion.
  * @rmtoll ISR      EOC            LL_ADC_ClearFlag_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_EOC);
}

/**
  * @brief  Clear flag ADC group regular end of sequence conversions.
  * @rmtoll ISR      EOS            LL_ADC_ClearFlag_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_EOS);
}

/**
  * @brief  Clear flag ADC group regular overrun.
  * @rmtoll ISR      OVR            LL_ADC_ClearFlag_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_OVR);
}

/**
  * @brief  Clear flag ADC group regular end of sampling phase.
  * @rmtoll ISR      EOSMP          LL_ADC_ClearFlag_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_EOSMP);
}

/**
  * @brief  Clear flag ADC group injected end of unitary conversion.
  * @rmtoll ISR      JEOC           LL_ADC_ClearFlag_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_JEOC);
}

/**
  * @brief  Clear flag ADC group injected end of sequence conversions.
  * @rmtoll ISR      JEOS           LL_ADC_ClearFlag_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_JEOS);
}

/**
  * @brief  Clear flag ADC group injected contexts queue overflow.
  * @rmtoll ISR      JQOVF          LL_ADC_ClearFlag_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_JQOVF(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_JQOVF);
}

/**
  * @brief  Clear flag ADC analog watchdog 1.
  * @rmtoll ISR      AWD1           LL_ADC_ClearFlag_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_AWD1);
}

/**
  * @brief  Clear flag ADC analog watchdog 2.
  * @rmtoll ISR      AWD2           LL_ADC_ClearFlag_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD2(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_AWD2);
}

/**
  * @brief  Clear flag ADC analog watchdog 3.
  * @rmtoll ISR      AWD3           LL_ADC_ClearFlag_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_ClearFlag_AWD3(ADC_TypeDef *ADCx)
{
  WRITE_REG(ADCx->ISR, ADC_ISR_AWD3);
}

#if defined(ADC2)
/**
  * @brief  Get flag multimode ADC ready of the ADC master.
  * @rmtoll CSR      ADRDY_MST      LL_ADC_IsActiveFlag_MST_ADRDY
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_ADRDY(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_ADRDY_MST) == (ADC_CSR_ADRDY_MST));
}

/**
  * @brief  Get flag multimode ADC ready of the ADC slave.
  * @rmtoll CSR      ADRDY_SLV      LL_ADC_IsActiveFlag_SLV_ADRDY
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_ADRDY(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_ADRDY_SLV) == (ADC_CSR_ADRDY_SLV));
}

/**
  * @brief  Get flag multimode ADC group regular end of unitary conversion of the ADC master.
  * @rmtoll CSR      EOC_MST        LL_ADC_IsActiveFlag_MST_EOC
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOC(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOC_SLV) == (ADC_CSR_EOC_SLV));
}

/**
  * @brief  Get flag multimode ADC group regular end of unitary conversion of the ADC slave.
  * @rmtoll CSR      EOC_SLV        LL_ADC_IsActiveFlag_SLV_EOC
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOC(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOC_SLV) == (ADC_CSR_EOC_SLV));
}

/**
  * @brief  Get flag multimode ADC group regular end of sequence conversions of the ADC master.
  * @rmtoll CSR      EOS_MST        LL_ADC_IsActiveFlag_MST_EOS
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOS(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOS_MST) == (ADC_CSR_EOS_MST));
}

/**
  * @brief  Get flag multimode ADC group regular end of sequence conversions of the ADC slave.
  * @rmtoll CSR      EOS_SLV        LL_ADC_IsActiveFlag_SLV_EOS
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOS(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOS_SLV) == (ADC_CSR_EOS_SLV));
}

/**
  * @brief  Get flag multimode ADC group regular overrun of the ADC master.
  * @rmtoll CSR      OVR_MST        LL_ADC_IsActiveFlag_MST_OVR
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_OVR(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_OVR_MST) == (ADC_CSR_OVR_MST));
}

/**
  * @brief  Get flag multimode ADC group regular overrun of the ADC slave.
  * @rmtoll CSR      OVR_SLV        LL_ADC_IsActiveFlag_SLV_OVR
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_OVR(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_OVR_SLV) == (ADC_CSR_OVR_SLV));
}

/**
  * @brief  Get flag multimode ADC group regular end of sampling of the ADC master.
  * @rmtoll CSR      EOSMP_MST      LL_ADC_IsActiveFlag_MST_EOSMP
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_EOSMP(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOSMP_MST) == (ADC_CSR_EOSMP_MST));
}

/**
  * @brief  Get flag multimode ADC group regular end of sampling of the ADC slave.
  * @rmtoll CSR      EOSMP_SLV      LL_ADC_IsActiveFlag_SLV_EOSMP
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_EOSMP(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_EOSMP_SLV) == (ADC_CSR_EOSMP_SLV));
}

/**
  * @brief  Get flag multimode ADC group injected end of unitary conversion of the ADC master.
  * @rmtoll CSR      JEOC_MST       LL_ADC_IsActiveFlag_MST_JEOC
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JEOC(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JEOC_MST) == (ADC_CSR_JEOC_MST));
}

/**
  * @brief  Get flag multimode ADC group injected end of unitary conversion of the ADC slave.
  * @rmtoll CSR      JEOC_SLV       LL_ADC_IsActiveFlag_SLV_JEOC
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JEOC(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JEOC_SLV) == (ADC_CSR_JEOC_SLV));
}

/**
  * @brief  Get flag multimode ADC group injected end of sequence conversions of the ADC master.
  * @rmtoll CSR      JEOS_MST       LL_ADC_IsActiveFlag_MST_JEOS
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JEOS(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JEOS_MST) == (ADC_CSR_JEOS_MST));
}

/**
  * @brief  Get flag multimode ADC group injected end of sequence conversions of the ADC slave.
  * @rmtoll CSR      JEOS_SLV       LL_ADC_IsActiveFlag_SLV_JEOS
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JEOS(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JEOS_SLV) == (ADC_CSR_JEOS_SLV));
}

/**
  * @brief  Get flag multimode ADC group injected context queue overflow of the ADC master.
  * @rmtoll CSR      JQOVF_MST      LL_ADC_IsActiveFlag_MST_JQOVF
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_JQOVF(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JQOVF_MST) == (ADC_CSR_JQOVF_MST));
}

/**
  * @brief  Get flag multimode ADC group injected context queue overflow of the ADC slave.
  * @rmtoll CSR      JQOVF_SLV      LL_ADC_IsActiveFlag_SLV_JQOVF
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_JQOVF(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_JQOVF_SLV) == (ADC_CSR_JQOVF_SLV));
}

/**
  * @brief  Get flag multimode ADC analog watchdog 1 of the ADC master.
  * @rmtoll CSR      AWD1_MST       LL_ADC_IsActiveFlag_MST_AWD1
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD1(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD1_MST) == (ADC_CSR_AWD1_MST));
}

/**
  * @brief  Get flag multimode analog watchdog 1 of the ADC slave.
  * @rmtoll CSR      AWD1_SLV       LL_ADC_IsActiveFlag_SLV_AWD1
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD1(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD1_SLV) == (ADC_CSR_AWD1_SLV));
}

/**
  * @brief  Get flag multimode ADC analog watchdog 2 of the ADC master.
  * @rmtoll CSR      AWD2_MST       LL_ADC_IsActiveFlag_MST_AWD2
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD2(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD2_MST) == (ADC_CSR_AWD2_MST));
}

/**
  * @brief  Get flag multimode ADC analog watchdog 2 of the ADC slave.
  * @rmtoll CSR      AWD2_SLV       LL_ADC_IsActiveFlag_SLV_AWD2
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD2(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD2_SLV) == (ADC_CSR_AWD2_SLV));
}

/**
  * @brief  Get flag multimode ADC analog watchdog 3 of the ADC master.
  * @rmtoll CSR      AWD3_MST       LL_ADC_IsActiveFlag_MST_AWD3
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_MST_AWD3(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD3_MST) == (ADC_CSR_AWD3_MST));
}

/**
  * @brief  Get flag multimode ADC analog watchdog 3 of the ADC slave.
  * @rmtoll CSR      AWD3_SLV       LL_ADC_IsActiveFlag_SLV_AWD3
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsActiveFlag_SLV_AWD3(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (READ_BIT(ADCxy_COMMON->CSR, ADC_CSR_AWD3_SLV) == (ADC_CSR_AWD3_SLV));
}
#endif /* ADC2 */

/**
  * @}
  */

/** @defgroup ADC_LL_EF_IT_Management ADC IT management
  * @{
  */

/**
  * @brief  Enable ADC ready.
  * @rmtoll IER      ADRDYIE        LL_ADC_EnableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_ADRDY);
}

/**
  * @brief  Enable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_EnableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_EOC);
}

/**
  * @brief  Enable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_EnableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_EOS);
}

/**
  * @brief  Enable ADC group regular interruption overrun.
  * @rmtoll IER      OVRIE          LL_ADC_EnableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_OVR);
}

/**
  * @brief  Enable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_EnableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_EOSMP);
}

/**
  * @brief  Enable interruption ADC group injected end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_EnableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOC(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_JEOC);
}

/**
  * @brief  Enable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_EnableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_JEOS);
}

/**
  * @brief  Enable interruption ADC group injected context queue overflow.
  * @rmtoll IER      JQOVFIE        LL_ADC_EnableIT_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_JQOVF(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_JQOVF);
}

/**
  * @brief  Enable interruption ADC analog watchdog 1.
  * @rmtoll IER      AWD1IE         LL_ADC_EnableIT_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_AWD1);
}

/**
  * @brief  Enable interruption ADC analog watchdog 2.
  * @rmtoll IER      AWD2IE         LL_ADC_EnableIT_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_AWD2);
}

/**
  * @brief  Enable interruption ADC analog watchdog 3.
  * @rmtoll IER      AWD3IE         LL_ADC_EnableIT_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_EnableIT_AWD3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_AWD3);
}

/**
  * @brief  Disable interruption ADC ready.
  * @rmtoll IER      ADRDYIE        LL_ADC_DisableIT_ADRDY
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_ADRDY);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      EOCIE          LL_ADC_DisableIT_EOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_EOC);
}

/**
  * @brief  Disable interruption ADC group regular end of sequence conversions.
  * @rmtoll IER      EOSIE          LL_ADC_DisableIT_EOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_EOS);
}

/**
  * @brief  Disable interruption ADC group regular overrun.
  * @rmtoll IER      OVRIE          LL_ADC_DisableIT_OVR
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_OVR);
}

/**
  * @brief  Disable interruption ADC group regular end of sampling.
  * @rmtoll IER      EOSMPIE        LL_ADC_DisableIT_EOSMP
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_EOSMP);
}

/**
  * @brief  Disable interruption ADC group regular end of unitary conversion.
  * @rmtoll IER      JEOCIE         LL_ADC_DisableIT_JEOC
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOC(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_JEOC);
}

/**
  * @brief  Disable interruption ADC group injected end of sequence conversions.
  * @rmtoll IER      JEOSIE         LL_ADC_DisableIT_JEOS
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_JEOS);
}

/**
  * @brief  Disable interruption ADC group injected context queue overflow.
  * @rmtoll IER      JQOVFIE        LL_ADC_DisableIT_JQOVF
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_JQOVF(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_JQOVF);
}

/**
  * @brief  Disable interruption ADC analog watchdog 1.
  * @rmtoll IER      AWD1IE         LL_ADC_DisableIT_AWD1
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD1(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_AWD1);
}

/**
  * @brief  Disable interruption ADC analog watchdog 2.
  * @rmtoll IER      AWD2IE         LL_ADC_DisableIT_AWD2
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD2(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_AWD2);
}

/**
  * @brief  Disable interruption ADC analog watchdog 3.
  * @rmtoll IER      AWD3IE         LL_ADC_DisableIT_AWD3
  * @param  ADCx ADC instance
  * @retval None
  */
__STATIC_INLINE void LL_ADC_DisableIT_AWD3(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->IER, ADC_IER_AWD3);
}

/**
  * @brief  Get state of interruption ADC ready.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      ADRDYIE        LL_ADC_IsEnabledIT_ADRDY
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_ADRDY(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_ADRDY) == (ADC_IER_ADRDY));
}

/**
  * @brief  Get state of interruption ADC group regular end of unitary conversion.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      EOCIE          LL_ADC_IsEnabledIT_EOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOC(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_EOC) == (ADC_IER_EOC));
}

/**
  * @brief  Get state of interruption ADC group regular end of sequence conversions.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      EOSIE          LL_ADC_IsEnabledIT_EOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOS(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_EOS) == (ADC_IER_EOS));
}

/**
  * @brief  Get state of interruption ADC group regular overrun.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      OVRIE          LL_ADC_IsEnabledIT_OVR
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_OVR(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_OVR) == (ADC_IER_OVR));
}

/**
  * @brief  Get state of interruption ADC group regular end of sampling.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      EOSMPIE        LL_ADC_IsEnabledIT_EOSMP
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_EOSMP(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_EOSMP) == (ADC_IER_EOSMP));
}

/**
  * @brief  Get state of interruption ADC group injected end of unitary conversion.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      JEOCIE         LL_ADC_IsEnabledIT_JEOC
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOC(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_JEOC) == (ADC_IER_JEOC));
}

/**
  * @brief  Get state of interruption ADC group injected end of sequence conversions.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      JEOSIE         LL_ADC_IsEnabledIT_JEOS
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JEOS(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_JEOS) == (ADC_IER_JEOS));
}

/**
  * @brief  Get state of interruption ADC group injected context queue overflow interrupt state
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      JQOVFIE        LL_ADC_IsEnabledIT_JQOVF
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_JQOVF(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_JQOVF) == (ADC_IER_JQOVF));
}

/**
  * @brief  Get state of interruption ADC analog watchdog 1.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      AWD1IE         LL_ADC_IsEnabledIT_AWD1
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_AWD1) == (ADC_IER_AWD1));
}

/**
  * @brief  Get state of interruption Get ADC analog watchdog 2.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      AWD2IE         LL_ADC_IsEnabledIT_AWD2
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_AWD2) == (ADC_IER_AWD2));
}

/**
  * @brief  Get state of interruption Get ADC analog watchdog 3.
  *         (0: interrupt disabled, 1: interrupt enabled)
  * @rmtoll IER      AWD3IE         LL_ADC_IsEnabledIT_AWD3
  * @param  ADCx ADC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_ADC_IsEnabledIT_AWD3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IER, ADC_IER_AWD3) == (ADC_IER_AWD3));
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

#endif /* ADC1 || ADC2 || ADC3 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L4xx_LL_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
