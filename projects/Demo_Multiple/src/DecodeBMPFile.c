/*******************************************************************************
 * DecodeBMPFile.c
 *
 * Private function of main()
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


#include "string.h"

static uint32_t  little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
static uint16_t  little_endian_16b (uint8_t data1, uint8_t data2);


bool  DecodeBMPFile(char* FileName)
{

FIL MyFile;

bool  FatFS_Ok = true;
bool  ValidBMP = true;
bool TopToBottomBMP;

BYTE BMPFileHeader[14];
BYTE BMPImageHeader[40];
BYTE BMPLineBuffer[3*160];

UINT rbytes_count; /* File read counts */

uint32_t  OffsetHead;
uint32_t  ImgWidth, ImgHeight;
int32_t  ImgHeight_signed;

uint8_t   R, G, B;
uint16_t  PixelLine565[160];


uint16_t  i,j;


    /* --- Open File and Read File Hedader + Image Header  ------------------- */

    FatFS_Ok &= ( f_open(&MyFile, FileName, FA_OPEN_EXISTING|FA_READ) == FR_OK );

    FatFS_Ok &= ( f_read( &MyFile, BMPFileHeader, sizeof(BMPFileHeader), &rbytes_count ) == FR_OK);

    FatFS_Ok &= ( f_read( &MyFile, BMPImageHeader, sizeof(BMPImageHeader), &rbytes_count) == FR_OK);
 

    /* --- Extract and Check Information from Header Contents  ---------------- */

    // Check first 2 bytes are B,M - Bytes 0,1 in File Header
    ValidBMP &= ( (BMPFileHeader[0] == 0x42) && (BMPFileHeader[1] == 0x4D) );

    // Get Offset to Start of Pixel Data - Bytes 10-13 of File Header
    OffsetHead = little_endian_32b( BMPFileHeader[10], 
				    BMPFileHeader[11],
				    BMPFileHeader[12],
				    BMPFileHeader[13] );

    // Check picture is 24bpp - Bytes 14-15 of Image Header
    ValidBMP &= ( little_endian_16b( BMPImageHeader[14], BMPImageHeader[15] ) == 24 );

    // Get picture width in pix - Bytes 4-7 of Image Header
    ImgWidth = little_endian_32b(   BMPImageHeader[4], 
				    BMPImageHeader[5],
				    BMPImageHeader[6],
				    BMPImageHeader[7] );

    // Get picture height in pix - Bytes 8-11 of Image Header
    ImgHeight_signed = little_endian_32b(  BMPImageHeader[8], 
				    	   BMPImageHeader[9],
			   	   	   BMPImageHeader[10],
				   	   BMPImageHeader[11] );
   //Negative Height in BMP indicated Top to Bottom image coding
   if (ImgHeight_signed<0)
   {     TopToBottomBMP = true;
	 ImgHeight = (uint32_t)(-ImgHeight_signed);
   }
   else
   {     TopToBottomBMP = false;
	 ImgHeight = (uint32_t)(ImgHeight_signed);
   }

    // Check picture not greater than 160x128
    ValidBMP &= (  (ImgWidth <= 160) && (ImgHeight <= 128) );



    /* --- Now Read and Display Picture line by line  ------------------------ */
    /* --  unless BMP had issues                      ------------------------ */

    if (!ValidBMP)
    {
        LBF_OLED_Fill(0,0,160,128, BLUE);
    }
    else
    {

    // THIS EXECUTES SLOWLY AND WOULD NEED TO BE OPTIMIZED
    // Need to investigate what is the bottleneck

    // Move Read Pointer to start of pixel data 
    FatFS_Ok  &=  ( f_lseek( &MyFile, (DWORD)(OffsetHead)) == FR_OK );


    for(i=0; i<ImgHeight; i++)
    {
         FatFS_Ok  &=  ( f_read( &MyFile, BMPLineBuffer, 3*ImgWidth,&rbytes_count) == FR_OK);

	 // Create RGB565 buffer for OLED
	 for (j=0; j<ImgWidth;j++)
	 {
	     B = BMPLineBuffer[j*3] >> 3;      // truncate 3 LSBs
	     G = BMPLineBuffer[j*3 + 1] >> 2;  // truncate 2 LSBs
	     R = BMPLineBuffer[j*3 + 2] >> 3;  // truncate 3 LSBs
	     PixelLine565[j] =  (uint16_t)((R << 11) | (G << 5) | B);
	 }
	 if (TopToBottomBMP)
	 {
             LBF_OLED_DisplayBuffer( 0, i, (uint8_t)(ImgWidth), 1, PixelLine565 );
         }   
	 else
	 {
             LBF_OLED_DisplayBuffer( 0, (uint8_t)(ImgHeight-1-i),(uint8_t)(ImgWidth), 1, PixelLine565 );

         }   
     }
     }

     FatFS_Ok  &=  (f_close(&MyFile) == FR_OK);

     return (FatFS_Ok & ValidBMP);
}

/* ---------------------------------------------------------------
 * @brief  : 32-bit little-endian to big-endian conversion
 * @param  : little endian data
 * @return : Permuted data on 4 bytes
   --------------------------------------------------------------- */
uint32_t little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    return (uint32_t)(data1 | (data2 << 8) | (data3 << 16) | (data4 << 24));
}



/* ---------------------------------------------------------------
 * @brief  : 16-bit little-endian to big-endian conversion
 * @param  : little endian data
 * @return : Permuted data on 2 bytes
   --------------------------------------------------------------- */
uint16_t little_endian_16b (uint8_t data1, uint8_t data2)
{
    return (uint16_t)(data1 | (data2 << 8));
}



/*===============  END OF FILE ================================================================*/


