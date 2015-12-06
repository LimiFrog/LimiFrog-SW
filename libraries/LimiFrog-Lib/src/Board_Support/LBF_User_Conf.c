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
* Description    : User-edited routine to configure the extension port and
		   select board configuration option (without/with OLED/BLE).
* Input Param    : None.
* Output Param   : pExtPortConfig - pointer to structure that will hold the user-
		     defined parameters to configure the extension port
* Return         : None.
*******************************************************************************/


void LBF_User_Conf( LBF_ExtPortConfig_t* pExtPortConfig )
{

    /******************************************************************
    * Now Populate configuration structure with values defined above
    * Done this way for better legibility of above section
    *
    * No need for user to configure anything below this line
    * 
    ******************************************************************/
    
    pExtPortConfig->UART2_SPI_Baudrate =  EXT_PORT_UART2_SPI_Baudrate;
    pExtPortConfig->UART4_Baudrate =  EXT_PORT_UART4_Baudrate;	   


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

    // Position 2 dedicated to MIC monitoring

    // Position 1 is GND
}



/***************************************************************END OF FILE****/
