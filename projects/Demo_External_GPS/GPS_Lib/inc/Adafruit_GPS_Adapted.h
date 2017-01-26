/*******************************************************************************
 * Adafruit_GPS_Adapted.h
 * 
 * Derived from Adafruit's GPS library for their "Ultimate GPS" Module :
 *  https://www.adafruit.com/products/746
 *
 * Originally an Arduino sketch
 * See  https://github.com/adafruit/Adafruit_GPS
 *
 * Original copyright notice below :

 =========
    This is the Adafruit GPS library - the ultimate GPS library
    for the ultimate GPS module!

    Tested and works great with the Adafruit Ultimate GPS module
    using MTK33x9 chipset
        ------> http://www.adafruit.com/products/746
    Pick one up today at the Adafruit electronics shop 
    and help support open source hardware & software! -ada

    Adafruit invests time and resources providing this open source code, 
    please support Adafruit and open-source hardware by purchasing 
    products from Adafruit!

    Written by Limor Fried/Ladyada  for Adafruit Industries.  
    BSD license, check license.txt for more information
    All text above must be included in any redistribution

   // Fllybob added lines 34,35 and 40,41 to add 100mHz logging capability 
 =========
********************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ADAFRUIT_GPS_H
#define _ADAFRUIT_GPS_H


/* Includes to keep this header self-sufficient  -----------------------------*/
#include <stdbool.h>  
#include <stdint.h>
//to be able to use bool and uintxx_t types in function prototype below 


/* This GPS library makes uses of interrupts from DMA2 Ch3 (for UART4 Tx)
   and from UART4 (for UART4 Rx). Specifying a default priority level here 
   allows compiling this lib independently of whether it's used by user
   application. When this GPS lib is used, user can specify her own prirority
   levels (typ. in IT_Priorities_UserDefinable.h) which will override those
   conditioned by following ifndef               -----------------------------*/
#ifndef __DMA2_Channel3_IRQn_PRIO
  #define __DMA2_Channel3_IRQn_PRIO	0xA
#endif
#ifndef __UART4_IRQn_PRIO
  #define __UART4_IRQn_PRIO	0xA
#endif




/* Define Aliases for PMTK Commands    ----------------------------------------*/


// different commands to set the update rate from once a second (1 Hz) to 10 times a second (10Hz)
// Note that these only control the rate at which the position is echoed, to actually speed up the
// position fix you must also send one of the position fix rate commands below too.
#define PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ  "$PMTK220,10000*2F" // Once every 10 seconds, 100 millihertz.
#define PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ  "$PMTK220,5000*1B"  // Once every 5 seconds, 200 millihertz.
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"
// Position fix update rate commands.
#define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ  "$PMTK300,10000,0,0,0,0*2C" // Once every 10 seconds, 100 millihertz.
#define PMTK_API_SET_FIX_CTL_200_MILLIHERTZ  "$PMTK300,5000,0,0,0,0*18"  // Once every 5 seconds, 200 millihertz.
#define PMTK_API_SET_FIX_CTL_1HZ  "$PMTK300,1000,0,0,0,0*1C"
#define PMTK_API_SET_FIX_CTL_5HZ  "$PMTK300,200,0,0,0,0*2F"
// Can't fix position faster than 5 times a second!


#define PMTK_SET_BAUD_57600 "$PMTK251,57600*2C"
#define PMTK_SET_BAUD_9600 "$PMTK251,9600*17"

// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// turn on GPRMC and GGA
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn on ALL THE DATA
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// turn off output
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// to generate your own sentences, check out the MTK command datasheet and use a checksum calculator
// such as the awesome http://www.hhhh.org/wiml/proj/nmeaxor.html

#define PMTK_LOCUS_STARTLOG  "$PMTK185,0*22"
#define PMTK_LOCUS_STOPLOG "$PMTK185,1*23"
#define PMTK_LOCUS_STARTSTOPACK "$PMTK001,185,3*3C"
#define PMTK_LOCUS_QUERY_STATUS "$PMTK183*38"
#define PMTK_LOCUS_ERASE_FLASH "$PMTK184,1*22"
#define LOCUS_OVERLAP 0
#define LOCUS_FULLSTOP 1

#define PMTK_ENABLE_SBAS "$PMTK313,1*2E"
#define PMTK_ENABLE_WAAS "$PMTK301,2*2E"

// standby command & boot successful message
#define PMTK_STANDBY "$PMTK161,0*28"
#define PMTK_STANDBY_SUCCESS "$PMTK001,161,3*36"  // Not needed currently
#define PMTK_AWAKE "$PMTK010,002*2D"

// ask for the release and version
#define PMTK_Q_RELEASE "$PMTK605*31"

// request for updates on antenna status 
#define PGCMD_ANTENNA "$PGCMD,33,1*6C" 
#define PGCMD_NOANTENNA "$PGCMD,33,0*6D" 

// how long to wait when we're looking for a response
#define MAXWAITSENTENCE 5


/* -------------------------------------------------------------------*/
/* -- Originally (public) methods (member function prototypes)   ---- */
/* --  of C++ class Adafruit_GPS                                 ---- */
/* -- Turned into exported C function prototypes :              ----- */
/* -------------------------------------------------------------------*/

  void Adafruit_GPS_begin(uint32_t baud); 
  char *Adafruit_GPS_lastNMEA(void); 
  bool Adafruit_GPS_newNMEAreceived();
  void Adafruit_GPS_common_init(void);

  void GPS_sendCommand_Blocking(const char *str);
  
  void Adafruit_GPS_pause(bool b);

  uint8_t Adafruit_GPS_parseHex(char c);

  char Adafruit_GPS_read(void);
  bool Adafruit_GPS_parse(char *);

  bool Adafruit_GPS_wakeup(void);
  bool Adafruit_GPS_standby(void);

  bool Adafruit_GPS_waitForSentence(const char *wait, uint8_t max);
  bool Adafruit_GPS_LOCUS_StartLogger(void);
  bool Adafruit_GPS_LOCUS_StopLogger(void);
  bool Adafruit_GPS_LOCUS_ReadStatus(void);

  // New to cope with UART4 of STM32 used for TX/Rx
  void GPS_Config_UART4(void);
  inline void __attribute__((always_inline)) GPS_Callback_UART4_TxDMA_IT(void);
  inline void __attribute__((always_inline)) GPS_Callback_UART4_Rx_IT(void);


/* -------------------------------------------------------------------*/
/* -- Originally, attributes (member variables) of C++ class     ---- */
/* --  Adafruit_GPS (where most were "public"...)                ---- */
/* -- Turned into a global structure :                          ----- */
/* -------------------------------------------------------------------*/

typedef struct  
{
    
  // Below members were declared as "public" in class "Adafruit_GPS" :

    uint8_t hour, minute, seconds, year, month, day;
    uint16_t milliseconds;

    // Floating point latitude and longitude value in degrees.
    float latitude, longitude;

    // Fixed point latitude and longitude value with degrees stored in units of 1/100000 degrees,
    // and minutes stored in units of 1/100000 degrees.  See pull #13 for more details:
    //   https://github.com/adafruit/Adafruit-GPS-Library/pull/13
    int32_t latitude_fixed, longitude_fixed;

    float latitudeDegrees, longitudeDegrees;
    float geoidheight, altitude;
    float speed, angle, magvariation, HDOP;
    char lat, lon, mag;
    bool fix;
    uint8_t fixquality, satellites;

    uint16_t LOCUS_serial, LOCUS_records;
    uint8_t LOCUS_type, LOCUS_mode, LOCUS_config, LOCUS_interval, 
            LOCUS_distance, LOCUS_speed, LOCUS_status, LOCUS_percent;

  // Below members were declared as "private" in class "Adafruit_GPS" :
    bool paused;

  // New members vs Adafruit_GPS, to cope with UART4 of STM32 used for TX/Rx 

    bool volatile TxDMA_complete_UART4;
    bool volatile Rx_UART4_avail ;
    char volatile Uart4_Rx_Char;

}  Class_Adafruit_GPS_t;


extern Class_Adafruit_GPS_t Class_Adafruit_GPS;



#endif  /*  __ADAFRUIT_GPS_H  */


