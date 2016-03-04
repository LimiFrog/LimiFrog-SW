/*******************************************************************************
 * LFB_OLED_lowlevAPI.h
 ******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LFB_OLED_LOWLEVAPI_H
#define __LFB_OLED_LOWLEVAPI_H

#include <stdint.h>
// required as we declare a function as uint_8 below and
// want to keep this .h self-sufficient
#include "LBF_pin_aliases.h"
// same rationale as we use pin names


/* Exported macros --------------------------------------------------------*/

#define LBF_OLED_CS_LOW()           GPIO_LOW(OLED_CS_PORT, OLED_CS_PIN)
#define LBF_OLED_CS_HIGH()          GPIO_HIGH(OLED_CS_PORT, OLED_CS_PIN)
#define LBF_OLED_RS_LOW()           GPIO_LOW(OLED_RS_PORT, OLED_RS_PIN)
#define LBF_OLED_RS_HIGH()          GPIO_HIGH(OLED_RS_PORT, OLED_RS_PIN)
#define LBF_OLED_RESET_LOW()        GPIO_LOW(OLED_RESET_PORT, OLED_RESET_PIN)
#define LBF_OLED_RESET_HIGH()       GPIO_HIGH(OLED_RESET_PORT, OLED_RESET_PIN)

/* Exported constants  */

/* Colors for OLED in rgb565 format */
#define BLACK                   0x0000
#define WHITE                   0xFFFF
#define RED                     0xF800
#define GREEN                   0x07E0
#define BLUE                    0x001F
#define YELLOW                  0xFFE0
#define CYAN                    0x07FF
#define LIGHT_BLUE              0x1C9F
#define ORANGE                  0xFD20

/* Screen dimensions - 160x128 for DD-160128FC-1A */
#define X_FULL_SCREEN  160
#define Y_FULL_SCREEN  128

/* Exported functions ------------------------------------------------------- */


void LBF_OLED_Switch_ON (void);
void LBF_OLED_Switch_OFF (void);

void LBF_OLED_Clear (void);

//TO DO
// void LBF_OLED_Brightness (tbd);

void LBF_OLED_Fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color565);
void LBF_OLED_Fill_XY(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color565);

void LBF_OLED_DisplayBuffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t *pBuffer);
void LBF_OLED_DisplayBuffer_XY(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t *pBuffer);

void LBF_OLED_SendCmd (uint8_t Value);
void LBF_OLED_WriteReg (uint8_t RegName, uint8_t RegValue);
void LBF_OLED_SPI1_16bTransferStream_DMA1Ch3 (uint16_t* pTxBuffer, uint32_t TxLength);


// !!! The following 4 functions actually encapsulate emWin functtions, 
// !!! which means this middleware must have been enabled. 
// The interest is to provide very simple printf-like means to display messages on the screen
void LBF_OLED_PrintString(char* string);
void LBF_OLED_PrintDec(int32_t SignedInteger);
void LBF_OLED_PrintHex(uint16_t   Unsigned16);
void LBF_OLED_Overwrite_CurrentLine(void);



#endif  /*__LFB_OLED_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
