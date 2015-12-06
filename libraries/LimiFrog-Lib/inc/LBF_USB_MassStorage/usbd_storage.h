/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Inc/usbd_storage.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header for usbd_storage.c module
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
#ifndef __USBD_STORAGE_H_
#define __USBD_STORAGE_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern USBD_StorageTypeDef  USBD_DISK_fops;

#endif /* __USBD_STORAGE_H_ */
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
