/*******************************************************************************
 * main.c
 * 
 * (c)2015 LimiFrog / CYMEYA
 * This program is licensed under the terms of the MIT License.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * Please refer to the License File LICENSE.txt located at the root of this
 * project for full licensing conditions, 
 * or visit https://opensource.org/licenses/MIT.
 ******************************************************************************/

// ==============================================================================
// NOTE :
// This file uses extensively functions defined in library GPS_Lib, provided as 
// part of this project, which is an adaptation of Adafruit's GPS library for 
// their "Ultimate GPS" Module :
// Refer to https://www.adafruit.com/products/746 where documentation
// pertaining to the GPS module and the associated library can be found.
// ============================================================================== 


#include "LBF_Global.h"

#include "Adafruit_GPS_Adapted.h"   


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

bool  Success = true;

/* ================================================================ */
/* Board Initializations and Configurations except OLED             */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)                */
/* ================================================================ */

   LBF_Board_Inits();
   // Includes selective inits with actions driven by configuration
   // file User_Configuration.h under ../inc

   LBF_Led_ON();


/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */


    // If USB cable is plugged in, don't do anything,
    //  just allow access to internal files from PC in "USB stick" mode.
    // Will have to power off and back on without USB cable plugged in
    //  to run in "active" mode 
    if ( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_9 )== GPIO_PIN_SET )   
		// GPIO A Pin 9 = VBUS_SENSE input on STM32, bears 5V if USB plugged in, else Gnd
    {
        Success &= LBF_LaunchUSB_MassStorage(); // ... Use LimiFrog as USB Mass Storage (FS)
        LBF_Led_StopNBlinkOnFalse (Success);
        while(1); 
    }


    /* ... To initialize FatFS                                      */
    /*     and mount the Data Flash as FAT File System              */
//LBF_Delay_ms(10);
    Success &= LBF_FatFS_Init();
//LBF_Delay_ms(10);


    /* ... To initialize the STemWin Graphical Library              */ 
    /*     Caution: reserves some RAM - keep some for stack/heap    */
    Success &= LBF_emWin_Init();

    // ERROR HANDLER
    /* Replace by your own as wished */
    LBF_Led_StopNBlinkOnFalse (Success);
    	// stops here if one of above inits has failed

    LBF_Led_OFF();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */


uint32_t  Now, LastTime;
bool  Parse_ok;
bool  Tracking;
bool PreviousFix = true;

FIL MyFile;
uint32_t wbytes_count; /* File write counts */
char wtext[128]; /* File write buffer */
const char FileName[] = "GPS.CSV";

char Str_Date[16]; 
char Str_Time[24]; 
char Str_Latitude[16];
char Str_Longitude[16]; 
char Str_Speed[10]; 
char Str_Altitude[8];
char Str_Satellites[5]; 
// !!! CAUTION : if char array is no sufficient to hold full formatted string (incl. control chars 
// and final \0) when using sprintf in the code below, execution will continue with potentially  
// very side effects hard-to-debug  (experience talking here !!!)





/* ==  Body     ======================================== */


    // Provide power (13V) to OLED panel, enable display
    LBF_OLED_Switch_ON();

   // Set Font Size for Display
    GUI_SetFont(&GUI_Font13B_ASCII);

    // Initialize GPS library
    Adafruit_GPS_common_init(); 

    // --- Set up UART4 To use as Hardware serial i/f of GPS board        -------------
    // ---  We'll send Tx data using DMA2 Channel3
    // ---  We'll get Rx data one byte at a time with IT upon byte received
    GPS_Config_UART4(); 	 // in GPS_Lib
    	// NOTE: Must also configure positions 8 and 7 of external connector 
    	//  as UART4 Tx and RX through ../inc/user_Configuration.h

    // -- Note:
    // -- Better provide power to GPS module after configuring UART4,
    // -- else, with battery backup installed on GPS module,
    // -- GPS starts talking on UART4 as soon as power is provided,
    // -- before full UART4 initialization, and this causes errors on UART4

    // --- Provide 3.3V from LDO on VCC_LDO (ext. connector Position 6) 
    // --- to power GPS board  
    LBF_Enable_LDO();
    LBF_OLED_PrintString("3.3V out for GPS chip\n");  


    // Turn on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS_sendCommand_Blocking(PMTK_SET_NMEA_OUTPUT_RMCGGA);

    // Set the update rate
    GPS_sendCommand_Blocking(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
      // Adafruit says:
      // For the parsing code to work nicely and have time to sort thru the data, and
      // print it out we don't suggest using anything higher than 1 Hz

    // Request updates on antenna status, comment out to keep quiet
    GPS_sendCommand_Blocking(PGCMD_ANTENNA);


    Now = HAL_GetTick();
    LastTime= Now;

    LBF_OLED_PrintString("Start parsing\n"); 


    // -------  Wait for first fix    -----------------------------------

    while ( !Class_Adafruit_GPS.fix )
    {
      Adafruit_GPS_read();  
	 // monitors UART4 RX, update read line buffer, NMEA received flag...
     
      // if a sentence is received, we can check the checksum, parse it...
      if (Adafruit_GPS_newNMEAreceived())
      {
          Parse_ok = Adafruit_GPS_parse( Adafruit_GPS_lastNMEA() );   
	  // this also sets the newNMEAreceived() flag to false
      }

    }


    // -------  Fix obtained          -----------------------------------

    // Display date and fix success

    GUI_DispString("\nFix: "); GUI_DispDecMin((int)Class_Adafruit_GPS.fix);
    GUI_DispString(" Quality: "); GUI_DispDecMin((int)Class_Adafruit_GPS.fixquality); 
    GUI_DispString("\n");

    sprintf( Str_Date, "%2d-%2d-20%2d\n", Class_Adafruit_GPS.day, Class_Adafruit_GPS.month, Class_Adafruit_GPS.year);
    GUI_DispString("\nDate: ");  GUI_DispString(Str_Date);

    // Write header in text file
    strcpy( wtext, "Time \tLatitude \tLongitude \tAltitude \tSpeed \tSatellites \r\n");
    if( f_open(&MyFile, FileName, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK )
    {
        f_write(&MyFile, Str_Date, strlen(Str_Date), (void *)&wbytes_count) ;
        f_write(&MyFile, wtext, strlen(wtext), (void *)&wbytes_count) ;
        f_close(&MyFile);
    }


    GUI_DispString("Push button to\n start/pause tracking\n");  
    while (! LBF_State_Switch1_IsOn() ); // wait for button pushed... 
    Tracking = true;
    LBF_Delay_ms(100);  // skip bounces
    while ( LBF_State_Switch1_IsOn() ); // ...and released


    // -------  Track                   -----------------------------------

    while(1)
    {

	Adafruit_GPS_read();  
	 // monitors UART4 RX, update read line buffer, NMEA received flag...
     
        // if a sentence is received, we can check the checksum, parse it...
	if (Adafruit_GPS_newNMEAreceived())
	{
	    Parse_ok = Adafruit_GPS_parse( Adafruit_GPS_lastNMEA() );   
	    // this also sets the newNMEAreceived() flag to false
	}

	if (Parse_ok)   //skip if last parsing failed
	{

	    if ( !Class_Adafruit_GPS.fix )   // Fix lost
	    {
	        if (PreviousFix)  // is it the first detection of loss ?
		{
 		    if (   (f_open(&MyFile, FileName, FA_WRITE)  == FR_OK)
                        && (f_lseek(&MyFile, f_size(&MyFile)   ) == FR_OK)   )
     		            // f_lseek to append (go to end of file)
		    {
			f_write(&MyFile, "Fix lost!\n", 10, (void *)&wbytes_count) ;
			f_close(&MyFile);
		    }

		    GUI_Clear();
		    GUI_DispString("\nFIX LOST!\n");
		}
	    }      
	    else if (Tracking)  // Fix OK, tracking on (not paused)
	    {

		// Print out the current stats every few seconds :
		Now = HAL_GetTick();
		if ((Now - LastTime)>1000) 
		{ 
		    LastTime  = Now; 
		    GUI_Clear();
    
		    GUI_SetColor(0x0000FF); //Blue

		    xsprintf( Str_Time, "%2d:%2d:%2d \t", 
			Class_Adafruit_GPS.hour, 
			Class_Adafruit_GPS.minute, 
			Class_Adafruit_GPS.seconds );  
		    GUI_DispString("Time: ");  GUI_DispString(Str_Time);


		    GUI_SetColor(GUI_WHITE);
		    if (Class_Adafruit_GPS.fix) 
		    {

			sprintf( Str_Latitude, "%+.6f \t", Class_Adafruit_GPS.latitudeDegrees);  
			sprintf( Str_Longitude, "%+.6f \t", Class_Adafruit_GPS.longitudeDegrees); 
			sprintf( Str_Altitude, "%.0f \t", Class_Adafruit_GPS.altitude);  
			sprintf( Str_Speed, "%.4f \t", Class_Adafruit_GPS.speed);  
			sprintf( Str_Satellites, "%d \t", Class_Adafruit_GPS.satellites);  
    
			GUI_DispString("\n\nLocation:\n");
			GUI_DispString(Str_Latitude);  GUI_DispString(", "); GUI_DispString(Str_Longitude);  
    
			GUI_DispString("\nAltitude:"); GUI_DispString(Str_Altitude);  GUI_DispString("\n");
    
			GUI_DispString("\nSpeed (knots):");  GUI_DispString(Str_Speed);  
    
			GUI_DispString("\n# of sat.:");  GUI_DispString(Str_Satellites);  
			GUI_DispString("\n");


			if (f_open(&MyFile, FileName, FA_WRITE) != FR_OK)
			{
		    		GUI_DispString("\n f_open fail! \n");
				f_close(&MyFile);
				while(1);
			}
			else if (f_lseek(&MyFile, f_size(&MyFile)) != FR_OK)  
	    		       // f_lseek to append (go to end of file)
			       // Could use mode FA_APPEND instead if switching to more recent release of FatFS
			{
		    		GUI_DispString("\n f_seek fail! \n");
				f_close(&MyFile);
				while(1);
			}
			else 
			{
			    Success &= ( f_write(&MyFile, Str_Time, strlen(Str_Time), (void *)&wbytes_count) == FR_OK);
			    Success &= ( f_write(&MyFile, Str_Latitude, strlen(Str_Latitude), (void *)&wbytes_count)  == FR_OK);
			    Success &= ( f_write(&MyFile, Str_Longitude, strlen(Str_Longitude), (void *)&wbytes_count)  == FR_OK);
			    Success &= ( f_write(&MyFile, Str_Altitude, strlen(Str_Altitude), (void *)&wbytes_count)  == FR_OK);
			    Success &= ( f_write(&MyFile, Str_Speed, strlen(Str_Speed), (void *)&wbytes_count)  == FR_OK);
			    Success &= ( f_write(&MyFile, Str_Satellites, strlen(Str_Satellites), (void *)&wbytes_count)  == FR_OK);
			    Success &= ( f_write(&MyFile, "\r\n", 2, (void *)&wbytes_count)  == FR_OK);
			    if (!Success)  
			    {
		    		GUI_DispString("\n f_write fail! \n");
				while(1);
			    }

			    Success &= ( f_close(&MyFile) == FR_OK );
			    if (!Success)  
			    {
		    		GUI_DispString("\n f_close fail! \n");
				while(1);
			    }
			}

		     } // End if (Class_Adafruit_GPS.fix) 
		} // End      if ( ((Now ...


		// Is there a requets to stop tracking ?
		if (LBF_State_Switch1_IsOn())
		{
		    if (   (f_open(&MyFile, FileName, FA_WRITE)  == FR_OK)
		        && (f_lseek(&MyFile, f_size(&MyFile)   ) == FR_OK)   )
     		      // f_lseek to append (go to end of file)
		    {
			f_write(&MyFile, "Tracking Paused...\n", 19, (void *)&wbytes_count) ;
			f_close(&MyFile);
		    }

		    GUI_Clear();
		    GUI_DispString("\nTRACKING PAUSED\n");
		    Tracking = false;

		    // wait for button release then delay to skip bounces
		    while( LBF_State_Switch1_IsOn() );
		    LBF_Delay_ms(100);
		}

	    }  // end elseif Tracking

	    else  // Fix still valid, but tracking paused
	    {
		if (LBF_State_Switch1_IsOn())
		{
		    Tracking = true ;

		    // wait for button release then delay to skip bounces
		    while( LBF_State_Switch1_IsOn() );
		    LBF_Delay_ms(100);
		}

	    } 

	PreviousFix = Class_Adafruit_GPS.fix;
	}// end if Parse_ok

    } // End while(1)

}


/***************************************************************END OF FILE****/
