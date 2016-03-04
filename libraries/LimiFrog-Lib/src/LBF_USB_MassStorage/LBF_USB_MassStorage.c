/*******************************************************************************
 * LBF_USB_MassStorage.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "usbd_libs.h"
#include "LBF_USB_MassStorage.h"
#include "LBF_custom_types.h"

/* Private variables ---------------------------------------------------------*/

USBD_HandleTypeDef USBD_Device;

/* Functions -----------------------------------------------------------------*/


bool  LBF_LaunchUSB_MassStorage(void) 
{

bool  Success = true;


  /* Init MSC Application */
  Success &= ( USBD_Init(&USBD_Device, &MSC_Desc, 0) == USBD_OK ) ;
  
  /* Add Supported Class */
  Success &= ( USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS) == USBD_OK ) ;
  
  /* Add Storage callbacks for MSC Class */
  Success &= ( USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops) == USBD_OK ) ;
  
  /* Start Device Process */
  Success &= ( USBD_Start(&USBD_Device) == USBD_OK );
 

  return Success;
}
 

/**************************************************************/

bool  LBF_DeInitUSB_MassStorage(void) 
{

bool  Success = true;

  /* Stop Device Process */
  Success &= ( USBD_Stop(&USBD_Device) == USBD_OK );

  /* DeInit MSC Application */
  Success &= ( USBD_DeInit(&USBD_Device) == USBD_OK ) ;
  
  return Success;
}
 

/***************************************************************END OF FILE****/
