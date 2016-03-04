/*******************************************************************************
 * Carroussel_Demo.c
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


bool DecodeBMPFile(char* FileName);
bool NextDemoRequest(void);

static bool  NewPictureRequired( uint8_t* pDir );



/* -------------------------------------------------------------------*/

void 	Carroussel_Demo(void)
{

//FIL MyFile;
DIR  dir;
FILINFO  FileInfoStruct;
char listBMPfiles[50][13]; //to store up to 50 file names of 13 char each
uint8_t fnameLength;

bool FatFS_Ok = true;

uint8_t ImgIndex = 0;
uint8_t TotalBMPImg = 0;

uint8_t   direction;

uint32_t  StartTime;


/* -- Open root directory  ------------------------------ */

    FatFS_Ok &= (f_opendir( &dir, "/") == FR_OK);  

    LBF_Led_StopNBlinkOnFalse (FatFS_Ok);   //in case of FatFS error


/* -- Search all BMP file  ------------------------------ */

    FatFS_Ok &= ( f_readdir( &dir, &FileInfoStruct) == FR_OK);   // 


    while (FileInfoStruct.fname[0]!=0)   //as long as item is found
    {
	fnameLength = strlen(FileInfoStruct.fname);

        if ( FileInfoStruct.fname[fnameLength-3]=='B' 
          && FileInfoStruct.fname[fnameLength-2]=='M' 
          && FileInfoStruct.fname[fnameLength-1]=='P' )
	{	
            // copy found file name to current entry of table of BMP file names
	    strcpy( &listBMPfiles[ImgIndex][0] , FileInfoStruct.fname);  
	    ImgIndex++;
	}

        //next item  (break on error) :
        if (f_readdir( &dir, &FileInfoStruct) != FR_OK) break;

    }
    TotalBMPImg = ImgIndex;

    f_closedir(&dir) ;   


/* --  Decode BMP files with switch control   -------------------------------- */
 

    DecodeBMPFile("FROG.SPE"); 
   // Initial picture 

   LBF_Delay_ms(1000);

    ImgIndex = 0;
    while(1)
    {

      if ( NextDemoRequest() )
	 return;		// EXIT of new demo is requested
      else
      {
          if ( NewPictureRequired( &direction ) )
          {
            if ( direction == 0) 
            {
	        LBF_Led_ON();
                if (ImgIndex++ == (TotalBMPImg-1) ) 
                {
                     ImgIndex = 0;   // roll-over
                }
	        DecodeBMPFile(&listBMPfiles[ImgIndex][0]);

	        // Wait for switch release before continuing
	        //while( LBF_State_Switch1_IsOn() );  

	        LBF_Led_OFF();
            }

            if ( direction == 1) 
            {
	        LBF_Led_ON();
                if (ImgIndex-- == 0) 
                {
                    ImgIndex = TotalBMPImg - 1;   // roll-over
                }
	        DecodeBMPFile(&listBMPfiles[ImgIndex][0]);

    	        // Wait for switch release before continuing
	        //while( LBF_State_Switch2_IsOn() );  

	        LBF_Led_OFF();
            }
	    // Display new pic for a minimum time before continuing
	    // EXCEPT if request for Next Demo
	    StartTime = HAL_GetTick();
	    while ( (HAL_GetTick() - StartTime) < 600)
	    {
      		if ( NextDemoRequest() )
	 	    return;	
	    }

          } // end if ( NewPictureRequired... )
      } 

    }  // end while(1)


}



/* =====  Private functions     ==============================================*/

static bool NewPictureRequired( uint8_t* pDir )
{
//bool  ret = false;
bool      Tilted_Screen = false ;
int8_t     Y_Accel_HighByte;

// bool static Previous_Tilted_Screen = true;


  if ( (LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x1E) & 0x01) == 0x01)
  // XLDA bit set i.e. new accel data available
  {
        Y_Accel_HighByte =  (int8_t) LBF_I2CSensors_ReadSingleReg(LSM6DS3_CHIPID, 0x2B);   

        if (Y_Accel_HighByte > 16 ) 
        {
            Tilted_Screen = true;
            *pDir = 0;
        }
        if (Y_Accel_HighByte < -16 )
        {
            Tilted_Screen = true;
            *pDir = 1;
        }
/*
	if ( (Tilted_Screen) && !(Previous_Tilted_Screen) )
        {
	    ret = true;
        }

	Previous_Tilted_Screen = Tilted_Screen;
*/
   }

   return Tilted_Screen;
  
}


/***************************************************************END OF FILE****/



