/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Inc/usbd_conf.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   General low level driver configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF_H
#define __USBD_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Common Config */
#define USBD_MAX_NUM_INTERFACES               1
#define USBD_MAX_NUM_CONFIGURATION            1
#define USBD_MAX_STR_DESC_SIZ                 0x100
#define USBD_SUPPORT_USER_STRING              0 
#define USBD_SELF_POWERED                     1
#define USBD_DEBUG_LEVEL                      0

/* MSC Class Config */
#define MSC_MEDIA_PACKET                      512  // formerly, for L1
//#define MSC_MEDIA_PACKET                      8192  // NEW for L4

/* Exported macro ------------------------------------------------------------*/
/* Memory management macros */   

// L4 Cube Lib did this :
/*
#define USBD_malloc               malloc
#define USBD_free                 free
#define USBD_memset               memset
#define USBD_memcpy               memcpy
*/  

// Get back to solution that was used with L1 :
/* For footprint reasons and since only one allocation is handled in the MSC class 
   driver, the malloc/free is changed into a static allocation method */

void *USBD_static_malloc(uint32_t size);
void USBD_static_free(void *p);
// These functions must be described in usbd_conf.c

#define MAX_STATIC_ALLOC_SIZE     155  // MSC Class Driver Structure size
//#define MAX_STATIC_ALLOC_SIZE     2560  // MSC Class Driver Structure size - ATTEMPT TO INCREASE...

/*
#define USBD_malloc               malloc
#define USBD_free                 free
*/
#define USBD_malloc               (uint32_t *)USBD_static_malloc
#define USBD_free                 USBD_static_free

#define USBD_memset               // Not used
#define USBD_memcpy               // Not used 



    
/* DEBUG macros */  
#if (USBD_DEBUG_LEVEL > 0)
#define  USBD_UsrLog(...)   printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_UsrLog(...)   
#endif                            
                            
#if (USBD_DEBUG_LEVEL > 1)

#define  USBD_ErrLog(...)   printf("ERROR: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_ErrLog(...)   
#endif 
                                                        
#if (USBD_DEBUG_LEVEL > 2)                         
#define  USBD_DbgLog(...)   printf("DEBUG : ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_DbgLog(...)                         
#endif

/* Exported functions ------------------------------------------------------- */

#endif /* __USBD_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
