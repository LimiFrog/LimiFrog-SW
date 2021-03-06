/*******************************************************************************
 * LBF_User_Conf.c
 * 
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

#include "LBF_Global.h"
#include "LBF_User_Conf.h"
#include "User_Configuration.h"  //configuration file in user's project


/*******************************************************************************
* Function Name  : User_Config
* Description    : Populate configuration structure according to user's
*                  directives (found in User_Configuration.h)
* Input Param    : None.
* Output Param   : pExtPortConfig - pointer to structure that will hold the user-
		     defined parameters to configure the extension port
* Return         : None.
*******************************************************************************/


void LBF_User_Conf( LBF_ExtPortConfig_t* pExtPortConfig )
{

    pExtPortConfig->Pos11.Function = EXT_PORT_POS11_Function;  
    pExtPortConfig->Pos11.GPIO_Conf = EXT_PORT_POS11_GPIOtype;

    pExtPortConfig->Pos10.Function = EXT_PORT_POS10_Function;  
    pExtPortConfig->Pos10.GPIO_Conf = EXT_PORT_POS10_GPIOtype;
  
    pExtPortConfig->Pos9.Function = EXT_PORT_POS9_Function;  
    pExtPortConfig->Pos9.GPIO_Conf = EXT_PORT_POS9_GPIOtype;

    pExtPortConfig->Pos8.Function = EXT_PORT_POS8_Function;  
    pExtPortConfig->Pos8.GPIO_Conf = EXT_PORT_POS8_GPIOtype;

    pExtPortConfig->Pos7.Function = EXT_PORT_POS7_Function;  
    pExtPortConfig->Pos7.GPIO_Conf = EXT_PORT_POS7_GPIOtype;

    // Position 6 is reserved to VCC_LDO
    pExtPortConfig->Pos6.Function = EXT_PORT_POS6_Function;  

    pExtPortConfig->Pos5.Function = EXT_PORT_POS5_Function;  
    pExtPortConfig->Pos5.GPIO_Conf = EXT_PORT_POS5_GPIOtype;

    pExtPortConfig->Pos4.Function = EXT_PORT_POS4_Function;  
    pExtPortConfig->Pos4.GPIO_Conf = EXT_PORT_POS4_GPIOtype;

    pExtPortConfig->Pos3.Function = EXT_PORT_POS3_Function;  
    pExtPortConfig->Pos3.GPIO_Conf = EXT_PORT_POS3_GPIOtype;

    pExtPortConfig->Pos2.Function = EXT_PORT_POS2_Function;  
    pExtPortConfig->Pos2.GPIO_Conf = EXT_PORT_POS2_GPIOtype;

    // Position 1: N/A  (dedicated to MIC monitoring)


}


/***************************************************************END OF FILE****/
