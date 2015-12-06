/*******************************************************************************
 * LBF_FatFS_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/




#include "LBF_lowlev_API.h"
#include "ff_gen_drv.h"   // in turn, pulls ff.h and diskio.h
#include "DataFlash_diskio.h"

// Please refer to ChaN's FatFS documentation available on the web


FATFS DataFlash_DISK_FatFs; /* File system object for User logical drive */
char DataFlash_DISK_Path[4]; /* User logical drive path */


/* =================================================================== */

bool LBF_FatFS_Init (void)
{

bool Success = true;

    Success &= (FATFS_LinkDriver(&DataFlash_DISK_Driver, DataFlash_DISK_Path) == 0);
    if (Success)
    {
       Success &= (f_mount(&DataFlash_DISK_FatFs, (TCHAR const*)DataFlash_DISK_Path, 0) == FR_OK);
    }
    return Success;

}

/* =================================================================== */

void LBF_FatFS_DeInit (void)
{
    FATFS_UnLinkDriver(DataFlash_DISK_Path);
}

/********    END OF FILE  *****************************************************************/

