/*********************************************************************
* Customized by LimiFrog/CYMEYA, 2015
*/
/*********************************************************************
*          Portions COPYRIGHT 2014 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.24 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_LBF.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
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

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

#include "LBF_lowlev_API.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  160
#define YSIZE_PHYS  128 

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdSendCmd
*
* Function description:
*   Sets display register (i.e. send register index to display controller)
*/
static void LcdSendCmd(U8 Data) 
{
    LBF_OLED_SendCmd( (uint8_t)(Data) );
}

/********************************************************************
*
*       LcdSend8BitData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdSend8BitData(U8 Data) 
{
    LBF_OLED_CS_LOW();
    LBF_OLED_SPI_TransferByte((uint8_t)(Data));
    LBF_OLED_CS_HIGH();
    /* OLED_RS assumed to be high all that time (default level) */
}

/*******************************************************************
*
*       LcdSend8BitDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdSend8BitDataMultiple(U8 * pData, int NumItems)
{
    LBF_OLED_CS_LOW();
    while (NumItems--)
    {
    LBF_OLED_SPI_TransferByte((uint8_t) *pData++ );
    }
    LBF_OLED_CS_HIGH();
    /* OLED_RS assumed to be high all that time (default level) */
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
* NOT EXPECTED TO BE CALLED - Return 0x00 only
* 
*/
static void LcdReadDataMultiple(U8 * pData, int NumItems) {
  while (NumItems--) {
    *pData++ = 0x00;
  }
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) 
{
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};

  // If multiple buffering is required, this has to be done *before* 
  // creation of the display driver devce that come just below
  // (see User Manual section 21.4.1) -- as follows:
  // GUI_MULTIBUF_Config(NUM_BUFFERS);
 

  // See User Manual section 31.7.4 for details on configuring GUIDRV_FlexColor
  // (which is the appropriate driver for display controller Syncoam SEPS525
  //  used in the DD160128FC-1A and -2B OLED Screens)

  //
  // Driver Selection (Set display driver and color conversion for first layer)
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 0);

  // Optional here: LCD_SetDevFunc() 
  //
  // To set optional or custom defined routines
  // Supported values for this FlexColor driver:
  // LCD_DEVFUNC_READMPIXELS, LCD_DEVFUNC_READPIXELS
  // - used to set a custom routine to read multiple/single pixels
  // from display controller 
  // But swith DD160128FC in SPI mode we can't read back anyway...


  // Configure physical size of display
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);

  // Configure display orientation
  // Can be any combination of GUI_MIRROR_X|GUI_MIRROR_Y|GUI_SWAP_XY;
  // Keep Default here

  GUIDRV_FlexColor_Config(pDevice, &Config);


  // Required GUI_PORT_API routines :
  // User Manual says -
  // "The required GUI_PORT_API routines depend on the used interface. If a cache 
  // is used the routines for reading data are unnecessary for each interface."
  // For 8-bit interface : 
  // pfWrite8_A0 - Data Type: void (*) (U8 Data)
  // pfWrite8_A1 - Data Type: void (*) (U8 Data)
  // pfWriteM8_A1 -  Data Type: void (*) (U8 * pData, int NumItems)
  // pfReadM8_A1 - Data Type: void (*) (U8 * pData, int NumItems)
  PortAPI.pfWrite8_A0  = LcdSendCmd;
  PortAPI.pfWrite8_A1  = LcdSend8BitData;
  PortAPI.pfWriteM8_A1 = LcdSend8BitDataMultiple;
  PortAPI.pfReadM8_A1  = LcdReadDataMultiple;    //no action there - Reads not supported


  // Configure bus width, cache usage and hardware routines
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, 
                           GUIDRV_FLEXCOLOR_F66718, 
                           GUIDRV_FLEXCOLOR_M16C0B8);
    // GUIDRV_FLEXCOLOR_F66718 is a macro that sets GUI driver to use SEPS525 
    // GUIDRV_FLEXCOLOR_M16C1B8 selects 16bpp, cache, 8-bit bus
    //   same without cache is: ...._M16C0B8


}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *pData)
{
  int r;
  (void) LayerIndex;
  (void) pData;

  switch (Cmd)
  {
    case LCD_X_INITCONTROLLER:
    {
      // Init of OLED screen could be done here 
      // But already done externally with OLED_Init()
      return 0;
    }
    default:
      r = -1;

  }
  return r;


}

/*************************** End of file ****************************/

