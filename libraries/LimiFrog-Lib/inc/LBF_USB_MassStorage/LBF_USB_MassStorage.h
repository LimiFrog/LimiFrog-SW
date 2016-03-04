/*******************************************************************************
 * LBF_USB_MassStorage.h
 ******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_USB_MASSSTORAGE_H
#define __LBF_USB_MASSSTORAGE_H


/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>  
         //to be able to use bool type below and keep this .h self-contained


/* Exported functions ------------------------------------------------------- */

bool   LBF_LaunchUSB_MassStorage (void);
bool  LBF_DeInitUSB_MassStorage(void) ;


#endif  /*__LBF_USB_MASSSTORAGE_H*/

/***************************************************************END OF FILE****/
