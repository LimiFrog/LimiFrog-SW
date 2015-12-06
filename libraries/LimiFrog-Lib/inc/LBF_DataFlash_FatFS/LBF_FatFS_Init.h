/*******************************************************************************
 * LBF_FatFS_Init.h
 ******************************************************************************/

// To prevent recursive inclusion
#ifndef __FATFS_INIT
#define __FATFS_INIT


#include <stdbool.h>  
//to be able to use bool type below and keep this .h self-contained


bool LBF_FatFS_Init (void);

void LBF_FatFS_DeInit (void);



#endif // __FATFS_INIT


/********    END OF FILE  *****************************************************************/

