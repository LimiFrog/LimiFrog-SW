/*******************************************************************************
 * LBF_OLED_Init.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/



#include "LBF_lowlev_API.h"

#include "LBF_OLED_Init.h"


/*******************************************************************************
 * @brief  : Configure the OLED. Does NOT enable display - to do independently
 * @param  : Pointer to a config buffer. If NULL then default config is used.
 * @return : Noe.
 ******************************************************************************/
void LBF_OLED_Init(uint16_t *fconf)
{
    /* 
     * note : Procedure de configuration selon
     * la datasheet du densitron DD-160128FC-1A
     */

    LBF_OLED_RESET_LOW();
    LBF_Delay_ms(2);
    LBF_OLED_RESET_HIGH();
    LBF_Delay_ms(2);

    // display off, analog reset
    LBF_OLED_WriteReg(0x04, 0x01);
    LBF_Delay_ms(10);
    // Power save mode : normal
    LBF_OLED_WriteReg(0x04, 0x00);
    LBF_Delay_ms(10);
    
    // Display off
    LBF_OLED_WriteReg(0x06, 0x00);
    
    // Export1 internal clock and OSC operates with external resistor
    LBF_OLED_WriteReg(0x02, 0x01);


    // Iref controlled by external resistor
    LBF_OLED_WriteReg(0x80, 0x00);
    
//    if(fconf[0] == 0xFFFF)
    if(fconf == NULL)
    {
        // VALEURS PAR DEFAUTS ************************************************
        
        // Clock div ratio 1: freq setting 90Hz
        LBF_OLED_WriteReg(0x03, 0x30);
        
        // Driving current R G B - default R = 82uA / G = 56uA / B = 58uA
        LBF_OLED_WriteReg(0x10, 0x52);     // 0x52
        LBF_OLED_WriteReg(0x11, 0x38);     // 0x38
        LBF_OLED_WriteReg(0x12, 0x3A);     // 0x3A
        
        // Precharge time R G B
        LBF_OLED_WriteReg(0x08, 0x01);     // 0x04 / 0x01
        LBF_OLED_WriteReg(0x09, 0x01);     // 0x05 / 0x01
        LBF_OLED_WriteReg(0x0A, 0x01);     // 0x05 / 0x01
        
        // Precharge current R G B
        LBF_OLED_WriteReg(0x0B, 0x0A);     // 0x9D / 0x0A
        LBF_OLED_WriteReg(0x0C, 0x0A);     // 0x8C / 0x0A
        LBF_OLED_WriteReg(0x0D, 0x0A);     // 0x57 / 0x0A
    }
    else
    {
        uint8_t freq;
        freq = (uint8_t)(fconf[1]/5) - 15;
        // Frame Frequency
        LBF_OLED_WriteReg(0x03, (freq << 4));   
        
        // Driving current R G B
        LBF_OLED_WriteReg(0x10, (uint8_t)fconf[2]);
        LBF_OLED_WriteReg(0x11, (uint8_t)fconf[3]);
        LBF_OLED_WriteReg(0x12, (uint8_t)fconf[4]);
        
        // Precharge time R G B
        LBF_OLED_WriteReg(0x08, (uint8_t)fconf[5]);
        LBF_OLED_WriteReg(0x09, (uint8_t)fconf[6]);
        LBF_OLED_WriteReg(0x0A, (uint8_t)fconf[7]);
        
        // Precharge current R G B
        LBF_OLED_WriteReg(0x0B, (uint8_t)fconf[8]);
        LBF_OLED_WriteReg(0x0C, (uint8_t)fconf[9]);
        LBF_OLED_WriteReg(0x0D, (uint8_t)fconf[10]);
    }
    



//    * Display mode set :
//     *  - RGB
//     *  - Column = 0->159
//     *  - Column data display = Normal display
//     *
    LBF_OLED_WriteReg(0x13, 0x00);
    
    // External interface mode=MPU
    LBF_OLED_WriteReg(0x14, 0x31);     // 0x01 ?
    
//   * Memory write mode :
//     *  - 8 bits dual transfer
//     *  - 65K support
//     *  - Horizontal address counter is increased
//     *  - Vertical address counter is increased
//     *  - The data is continuously written horizontally
//     *
    LBF_OLED_WriteReg(0x16, 0x66);
    
    // Duty = 128
    LBF_OLED_WriteReg(0x28, 0x7F);
    
    // Display start on line 0
    LBF_OLED_WriteReg(0x29, 0x00);
    
    //DDRAM read address start point 0x2E~0x2F
    LBF_OLED_WriteReg(0x2E, 0x00);     // X
    LBF_OLED_WriteReg(0x2F, 0x00);     // Y
    
    // Display screen saver size 0x33~0x36
    LBF_OLED_WriteReg(0x33, 0x00);     // Screen saver columns start
    LBF_OLED_WriteReg(0x34, 0x9F);     // Screen saver columns end
    LBF_OLED_WriteReg(0x35, 0x00);     // Screen saver row start
    LBF_OLED_WriteReg(0x36, 0x7F);     // Screen saver row end

    // CLEAR SCREEN !!
    LBF_OLED_Clear();

}


/***************************************************************END OF FILE****/





