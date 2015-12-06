/*******************************************************************************
 * LBF_FLASH_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_FLASH_Init.h"



/* Privates prototypes -------------------------------------------------------*/
 
static void FLASH_ConfigurePageSize (void);

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise the Adesto Data Flash.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_Init(void)
{
    /* Configure ADESTO DataFlash in xxx-byte per page mode */
    FLASH_ConfigurePageSize();
    
}




/*******************************************************************************

 * @brief  : Configure the page size of ADESTO DataFlash.
 * @param  : None.
 * @return : None.
 ******************************************************************************/
void FLASH_ConfigurePageSize(void)
{
 
    /* Select the FLASH: Chip Select low */
    LBF_FLASH_CS_LOW();

    /* Send Page Size Configuration Command for xxx bytes/page  */
    LBF_FLASH_SendByte(LBF_FLASH_CMD_PAGESIZE1);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_PAGESIZE2);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_PAGESIZE3);
    LBF_FLASH_SendByte(LBF_FLASH_CMD_PAGESIZE4);

    /* Deselect the FLASH: Chip Select high */
    LBF_FLASH_CS_HIGH();

    /* Wait the end of Flash writing */
    LBF_FLASH_WaitForWriteEnd();

}


