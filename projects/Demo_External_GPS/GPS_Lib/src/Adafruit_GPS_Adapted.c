/*******************************************************************************
 * Adafruit_GPS_Adapted.c
 * 
 * Derived from Adafruit's GPS library for their "Ultimate GPS" Module :
 *  https://www.adafruit.com/products/746
 *
 * Originally an Arduino sketch
 * See  https://github.com/adafruit/Adafruit_GPS
 *
 =========
 * Original copyright notice below :

     This is our GPS library
     Adafruit invests time and resources providing this open source code,
     please support Adafruit and open-source hardware by purchasing
     products from Adafruit!

     Written by Limor Fried/Ladyada for Adafruit Industries.
     BSD license, check license.txt for more information
     All text above must be included in any redistribution
 =========

********************************************************************************/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>  // to use functions isdigit(), isalpha()

#include "LBF_Services.h"  // to use LBF_Delay_ms()

#include "Adafruit_GPS_Adapted.h"

#include "stm32l4xx_ll_dma.h"  // Low-layer driver for DMA
#include "stm32l4xx_ll_usart.h"  // Low-layer driver for USART

#include "xprintf.h"  // to use xsprintf etc.
#include "LBF_Init_PresetConf_ExtPort.h"  // to use preset conf of UART4 
#include "IT_Priorities_UserDefinable.h"  // to use user-defined priority level for UART4 IT
#include "LBF_Led_Based_Debug.h"

UART_HandleTypeDef hUart4; 


// -------------------------------------------------
// Local 'helper' functions :

static void GPS_Launch_DMA2_Ch3_for_UART4_Tx
	(char *pUart4_Tx_Data, uint16_t Num_Bytes );


// -------------------------------------------------
// Global variables used only in this file :

// how long are max NMEA lines to parse?
#define MAXLINELENGTH 120

// we double buffer: read one line in and leave one for the main program
volatile char line1[MAXLINELENGTH];
volatile char line2[MAXLINELENGTH];

// our index into filling the current line
volatile uint8_t lineidx=0;

// pointers to the double buffers
volatile char *currentline;
volatile char *lastline;

volatile bool recvdflag;
volatile bool inStandbyMode;


// -------------------------------------------------
// Global variables usable by user
//  (declared as 'extern' in header file) :

Class_Adafruit_GPS_t Class_Adafruit_GPS;



// **************************************************************
// Function code :


// -------------------------------------------------

bool Adafruit_GPS_parse(char *nmea) {

int32_t degree;
long minutes;
char degreebuff[10];

uint16_t sum;
uint8_t i;
char *p;
float timef;
uint32_t time;
uint32_t fulldate;


  // do checksum check

  // first look if we even have one
  if (nmea[strlen(nmea)-4] == '*') {
    sum = Adafruit_GPS_parseHex(nmea[strlen(nmea)-3]) * 16;
    sum += Adafruit_GPS_parseHex(nmea[strlen(nmea)-2]);
    
    // check checksum 
    for (i=2; i < (strlen(nmea)-4); i++) {
      sum ^= nmea[i];
    }
    if (sum != 0) {
      // bad checksum :(
      return false;
    }
  }

  // look for a few common sentences
  if (strstr(nmea, "$GPGGA")) {
    // found GGA
    p = nmea; // was "char *p = nmea" in C++;
    // get time
    p = strchr(p, ',')+1;
    timef = atof(p);
    time = (uint32_t)timef;  // was "uint32_t time = timef"in C++;
    Class_Adafruit_GPS.hour = time / 10000;
    Class_Adafruit_GPS.minute = (time % 10000) / 100;
    Class_Adafruit_GPS.seconds = (time % 100);

    Class_Adafruit_GPS.milliseconds = fmod(timef, 1.0) * 1000;

    // parse out latitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 2);
      p += 2;
      degreebuff[2] = '\0';
      degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      minutes = 50 * atol(degreebuff) / 3;
      Class_Adafruit_GPS.latitude_fixed = degree + minutes;
      Class_Adafruit_GPS.latitude = degree / 100000 + minutes * 0.000006F;
      Class_Adafruit_GPS.latitudeDegrees = 
        (Class_Adafruit_GPS.latitude-100*(int)(Class_Adafruit_GPS.latitude/100))/60.0; 
         // int... changed to (int) for C-style typecast
      Class_Adafruit_GPS.latitudeDegrees += (int)(Class_Adafruit_GPS.latitude/100); 
         // int... changed to (int) for C-style typecast
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'S') Class_Adafruit_GPS.latitudeDegrees *= -1.0;
      if (p[0] == 'N') Class_Adafruit_GPS.lat = 'N';
      else if (p[0] == 'S') Class_Adafruit_GPS.lat = 'S';
      else if (p[0] == ',') Class_Adafruit_GPS.lat = 0;
      else return false;
    }
    
    // parse out Class_Adafruit_GPS.longitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 3);
      p += 3;
      degreebuff[3] = '\0';
      degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      minutes = 50 * atol(degreebuff) / 3;
      Class_Adafruit_GPS.longitude_fixed = degree + minutes;
      Class_Adafruit_GPS.longitude = degree / 100000 + minutes * 0.000006F;
      Class_Adafruit_GPS.longitudeDegrees = (Class_Adafruit_GPS.longitude-100*(int)(Class_Adafruit_GPS.longitude/100))/60.0;
	// int... changed to (int) for C-style typecast
      Class_Adafruit_GPS.longitudeDegrees += (int)(Class_Adafruit_GPS.longitude/100);
	// int... changed to (int) for C-style typecast
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'W') Class_Adafruit_GPS.longitudeDegrees *= -1.0;
      if (p[0] == 'W') Class_Adafruit_GPS.lon = 'W';
      else if (p[0] == 'E') Class_Adafruit_GPS.lon = 'E';
      else if (p[0] == ',') Class_Adafruit_GPS.lon = 0;
      else return false;
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.fixquality = atoi(p);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.satellites = atoi(p);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.HDOP = atof(p);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.altitude = atof(p);
    }
    
    p = strchr(p, ',')+1;
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.geoidheight = atof(p);
    }
    return true;
  }
  if (strstr(nmea, "$GPRMC")) {
   // found RMC
    char *p = nmea;

    // get time
    p = strchr(p, ',')+1;
    float timef = atof(p);
    uint32_t time = timef;
    Class_Adafruit_GPS.hour = time / 10000;
    Class_Adafruit_GPS.minute = (time % 10000) / 100;
    Class_Adafruit_GPS.seconds = (time % 100);

    Class_Adafruit_GPS.milliseconds = fmod(timef, 1.0) * 1000;

    p = strchr(p, ',')+1;
    // Serial.println(p);
    if (p[0] == 'A') 
      Class_Adafruit_GPS.fix = true;
    else if (p[0] == 'V')
      Class_Adafruit_GPS.fix = false;
    else
      return false;

    // parse out latitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 2);
      p += 2;
      degreebuff[2] = '\0';
      long degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      minutes = 50 * atol(degreebuff) / 3;
      Class_Adafruit_GPS.latitude_fixed = degree + minutes;
      Class_Adafruit_GPS.latitude = degree / 100000 + minutes * 0.000006F;
      Class_Adafruit_GPS.latitudeDegrees = 
	(Class_Adafruit_GPS.latitude-100*(int)(Class_Adafruit_GPS.latitude/100))/60.0;
	// int... changed to (int) for C-style typecast
      Class_Adafruit_GPS.latitudeDegrees += (int)(Class_Adafruit_GPS.latitude/100);
	// int... changed to (int) for C-style typecast
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'S') Class_Adafruit_GPS.latitudeDegrees *= -1.0;
      if (p[0] == 'N') Class_Adafruit_GPS.lat = 'N';
      else if (p[0] == 'S') Class_Adafruit_GPS.lat = 'S';
      else if (p[0] == ',') Class_Adafruit_GPS.lat = 0;
      else return false;
    }
    
    // parse out Class_Adafruit_GPS.longitude
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      strncpy(degreebuff, p, 3);
      p += 3;
      degreebuff[3] = '\0';
      degree = atol(degreebuff) * 10000000;
      strncpy(degreebuff, p, 2); // minutes
      p += 3; // skip decimal point
      strncpy(degreebuff + 2, p, 4);
      degreebuff[6] = '\0';
      minutes = 50 * atol(degreebuff) / 3;
      Class_Adafruit_GPS.longitude_fixed = degree + minutes;
      Class_Adafruit_GPS.longitude = degree / 100000 + minutes * 0.000006F;
      Class_Adafruit_GPS.longitudeDegrees = 
	(Class_Adafruit_GPS.longitude-100*(int)(Class_Adafruit_GPS.longitude/100))/60.0;
	// int... changed to (int) for C-style typecast
      Class_Adafruit_GPS.longitudeDegrees += (int)(Class_Adafruit_GPS.longitude/100);
	// int... changed to (int) for C-style typecast
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      if (p[0] == 'W') Class_Adafruit_GPS.longitudeDegrees *= -1.0;
      if (p[0] == 'W') Class_Adafruit_GPS.lon = 'W';
      else if (p[0] == 'E') Class_Adafruit_GPS.lon = 'E';
      else if (p[0] == ',') Class_Adafruit_GPS.lon = 0;
      else return false;
    }
    // Class_Adafruit_GPS.speed
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.speed = atof(p);
    }
    
    // Class_Adafruit_GPS.angle
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      Class_Adafruit_GPS.angle = atof(p);
    }
    
    p = strchr(p, ',')+1;
    if (',' != *p)
    {
      fulldate = atof(p);
      Class_Adafruit_GPS.day = fulldate / 10000;
      Class_Adafruit_GPS.month = (fulldate % 10000) / 100;
      Class_Adafruit_GPS.year = (fulldate % 100);
    }
    // we dont parse the remaining, yet!
    return true;
  }

  return false;
}



// -------------------------------------------------

char Adafruit_GPS_read(void) 
{
char c = 0;
  
  if (Class_Adafruit_GPS.Rx_UART4_avail) 
  {
      Class_Adafruit_GPS.Rx_UART4_avail = false;   // reset flag

      if ( ! Class_Adafruit_GPS.paused) 
      {
          c = Class_Adafruit_GPS.Uart4_Rx_Char;

          if (c == '\n') 
          {
              currentline[lineidx] = 0;

              if (currentline == line1)
              {
                  currentline = line2;
                  lastline = line1;
              } 
              else 
              {
                  currentline = line1;
                  lastline = line2;
              }

              lineidx = 0;
              recvdflag = true;
           }

          currentline[lineidx++] = c;
          if (lineidx >= MAXLINELENGTH)
               lineidx = MAXLINELENGTH-1;
      }
  }
  return c;
}


// -------------------------------------------------

void Adafruit_GPS_common_init(void) {

  recvdflag   = false;
  Class_Adafruit_GPS.paused      = false;
  lineidx     = 0;
  currentline = line1;
  lastline    = line2;

  Class_Adafruit_GPS.hour = 0;
  Class_Adafruit_GPS.minute = 0;
  Class_Adafruit_GPS.seconds = 0;
  Class_Adafruit_GPS.year = 0;
  Class_Adafruit_GPS.month = 0;
  Class_Adafruit_GPS.day = 0;
  Class_Adafruit_GPS.fixquality = 0; 
  Class_Adafruit_GPS.satellites = 0;

  Class_Adafruit_GPS.lat = 0;
  Class_Adafruit_GPS.lon = 0;
  Class_Adafruit_GPS.mag = 0; 

  Class_Adafruit_GPS.fix = false; // bool
  Class_Adafruit_GPS.milliseconds = 0; // uint16_t

  Class_Adafruit_GPS.latitude = 0;
  Class_Adafruit_GPS.longitude = 0;
  Class_Adafruit_GPS.geoidheight = 0;
  Class_Adafruit_GPS.altitude = 0;
  Class_Adafruit_GPS.speed = 0;
  Class_Adafruit_GPS.angle = 0;
  Class_Adafruit_GPS.magvariation = 0;
  Class_Adafruit_GPS.HDOP = 0;

  Class_Adafruit_GPS.TxDMA_complete_UART4 = false;
  Class_Adafruit_GPS.Rx_UART4_avail = false;


}


// -------------------------------------------------


void GPS_sendCommand_Blocking(const char *str) 
{
uint16_t  StringLength;
char	Uart4_Tx_Data[256];

    xsprintf( Uart4_Tx_Data, "%s\n", str);  
     //create string to be output  - NOT VERY EFFICICENT ?

    StringLength = (uint16_t) strlen( Uart4_Tx_Data );  
     // = yields number of 'real' chars +2 to account for \r, \n (or '\0' ?)

    // Start DMA for 'StringLength' bytes Tx on UART4
    GPS_Launch_DMA2_Ch3_for_UART4_Tx( Uart4_Tx_Data, StringLength);

    while( !Class_Adafruit_GPS.TxDMA_complete_UART4 );
    // Wait until DMA done 

}


// -------------------------------------------------

bool Adafruit_GPS_newNMEAreceived(void) {
  return recvdflag;
}


// -------------------------------------------------

void Adafruit_GPS_pause(bool p) {
  Class_Adafruit_GPS.paused = p;
}


// -------------------------------------------------

char *Adafruit_GPS_lastNMEA(void) {
  recvdflag = false;
  return (char *)lastline;
}


// -------------------------------------------------

// read a Hex value and return the decimal equivalent
uint8_t Adafruit_GPS_parseHex(char c) {
    if (c < '0')
      return 0;
    if (c <= '9')
      return c - '0';
    if (c < 'A')
       return 0;
    if (c <= 'F')
       return (c - 'A')+10;
    // if (c > 'F')
    return 0;
}


// -------------------------------------------------

bool Adafruit_GPS_waitForSentence(const char *wait4me, uint8_t max) {
char str[20];
char *nmea ;

  uint8_t i=0;
  while (i < max) {
    if (Adafruit_GPS_newNMEAreceived()) { 
      nmea = Adafruit_GPS_lastNMEA();   //was "char *nmea = lastNMEA();" in C++  
      strncpy(str, nmea, 20);
      str[19] = 0;
      i++;

      if (strstr(str, wait4me))
	return true;
    }
  }

  return false;
}


// -------------------------------------------------

bool Adafruit_GPS_LOCUS_StartLogger(void) {
    GPS_sendCommand_Blocking(PMTK_LOCUS_STARTLOG);
  recvdflag = false;
//  return Adafruit_GPS_waitForSentence(PMTK_LOCUS_STARTSTOPACK);
  return Adafruit_GPS_waitForSentence(PMTK_LOCUS_STARTSTOPACK, MAXWAITSENTENCE);
}


// -------------------------------------------------

bool Adafruit_GPS_LOCUS_StopLogger(void) {
  GPS_sendCommand_Blocking(PMTK_LOCUS_STOPLOG);
  recvdflag = false;
//  return Adafruit_GPS_waitForSentence(PMTK_LOCUS_STARTSTOPACK);
  return Adafruit_GPS_waitForSentence(PMTK_LOCUS_STARTSTOPACK, MAXWAITSENTENCE);
}


// -------------------------------------------------

bool Adafruit_GPS_LOCUS_ReadStatus(void) {

char *response;
uint16_t parsed[10];
uint8_t i;
  
  GPS_sendCommand_Blocking(PMTK_LOCUS_QUERY_STATUS);
  
//  if (! Adafruit_GPS_waitForSentence("$PMTKLOG"))
  if (! Adafruit_GPS_waitForSentence("$PMTKLOG", MAXWAITSENTENCE))
    return false;

  response = Adafruit_GPS_lastNMEA(); // was "char *response = lastNMEA();" in C++

  for (i=0; i<10; i++) parsed[i] = -1;
  
  response = strchr(response, ',');
  for (i=0; i<10; i++) {
    if (!response || (response[0] == 0) || (response[0] == '*')) 
      break;
    response++;
    parsed[i]=0;
    while ((response[0] != ',') && 
	   (response[0] != '*') && (response[0] != 0)) {
      parsed[i] *= 10;
      char c = response[0];
      if (isdigit((uint32_t)c))    // was "if (isDigit(c))" in C++
        parsed[i] += c - '0';
      else
        parsed[i] = c;
      response++;
    }
  }
  Class_Adafruit_GPS.LOCUS_serial = parsed[0];
  Class_Adafruit_GPS.LOCUS_type = parsed[1];
  if (isalpha(parsed[2])) {   // was isAlpha in C++
    parsed[2] = parsed[2] - 'a' + 10; 
  }
  Class_Adafruit_GPS.LOCUS_mode = parsed[2];
  Class_Adafruit_GPS.LOCUS_config = parsed[3];
  Class_Adafruit_GPS.LOCUS_interval = parsed[4];
  Class_Adafruit_GPS.LOCUS_distance = parsed[5];
  Class_Adafruit_GPS.LOCUS_speed = parsed[6];
  Class_Adafruit_GPS.LOCUS_status = !parsed[7];
  Class_Adafruit_GPS.LOCUS_records = parsed[8];
  Class_Adafruit_GPS.LOCUS_percent = parsed[9];

  return true;
}


// -------------------------------------------------


bool Adafruit_GPS_standby(void) {
  if (inStandbyMode) {
    return false;  // Returns false if already in standby mode, so that you do not wake it up by sending commands to GPS
  }
  else {
    inStandbyMode = true;
    GPS_sendCommand_Blocking(PMTK_STANDBY);
    //return waitForSentence(PMTK_STANDBY_SUCCESS);  // don't seem to be fast enough to catch the message, or something else just is not working
    return true;
  }
}


// -------------------------------------------------

bool Adafruit_GPS_wakeup(void) {
  if (inStandbyMode) {
   inStandbyMode = false;
    GPS_sendCommand_Blocking("");  // send byte to wake it up
    return Adafruit_GPS_waitForSentence(PMTK_AWAKE, MAXWAITSENTENCE);
  }
  else {
      return false;  // Returns false if not in standby mode, nothing to wakeup
  }
}

//

// --------------------------------------------------


void GPS_Config_UART4(void)
{

 // --- Set up UART4 To use as Hardware serial i/f of GPS board        -------------
 // ---  We'll send Tx data using DMA2 Channel3
 // ---  We'll get Rx data one byte at a time with IT upon byte received

 // NOTE: Must also configure positions 8 and 7 of external connector 
 //  as UART4 Tx and RX through ../inc/user_Configuration.h



    // ---  Use preset configuration for UART4 (8-bit, 1 stop bit, no parity...):
    LBF_Init_PresetConf_UART4 (&hUart4, 9600) ;  
	//9600bit/s baud rate is default of GPS board

    // ----------------------
    // We want to use DMA with UART4 Tx: Initialize DMA
    // From Ref Manual Tables 37-39 :
    // UART4 Tx can use DMA2, Channel3 and is assigned req #2 of this channel


    // Configure NVIC for DMA transfer complete/error interrupts */
    // (parameters __DMA2_Channelxx_IRQn_PRIO expected to be defined 
    //  in e.g. IT_Priorities_UserDefinable.h)
    // Tx DMA :
    NVIC_SetPriority(DMA2_Channel3_IRQn, __DMA2_Channel3_IRQn_PRIO);  
    NVIC_EnableIRQ(DMA2_Channel3_IRQn);

    // ----------------------
    // We want to use IT of UART4 byte Rx

   // Configure NVIC for UART4 interrupt */
    // (parameters __UART4_IRQn_PRIO expected to be defined 
    //  in e.g. IT_Priorities_UserDefinable.h)
    // Tx DMA :
    NVIC_SetPriority(UART4_IRQn, __UART4_IRQn_PRIO);  
    NVIC_EnableIRQ(UART4_IRQn);

    // Set up Rx IT on UART4: enable RXNE and Error interrupts 
    LL_USART_EnableIT_RXNE(UART4);
    LL_USART_EnableIT_ERROR(UART4);

    // Enable UART4
    Class_Adafruit_GPS.Rx_UART4_avail = false;
    LL_USART_Enable(UART4);

    // Wait for USART initialisation - just in case
    while((!(LL_USART_IsActiveFlag_TEACK(UART4))) || (!(LL_USART_IsActiveFlag_REACK(UART4))));

    // Enable clock of DMA2:
    __DMA2_CLK_ENABLE();

    // Configure transmit DMA functional parameters
    LL_DMA_ConfigTransfer(DMA2, LL_DMA_CHANNEL_3, 
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH | 
                        LL_DMA_PRIORITY_MEDIUM            | 
                        LL_DMA_MODE_NORMAL                | 
                        LL_DMA_PERIPH_NOINCREMENT         | 
                        LL_DMA_MEMORY_INCREMENT           | 
                        LL_DMA_PDATAALIGN_BYTE            | 
                        LL_DMA_MDATAALIGN_BYTE);
}

/* ============================================================================= */

// Callback functions called from UART4 Rx Interrupt routine
//  and DMA2 Ch3 (used for UART4 Tx) Interrupt Routine


void GPS_Callback_UART4_TxDMA_IT(void)
// UART4 Tx is the source of this interrupt
{
  if(LL_DMA_IsActiveFlag_TC3(DMA2))  // Transfer Complete IT
  {

    LL_DMA_ClearFlag_GI3(DMA2);  // // global clear of all channel3 DMA2 IT flags
    Class_Adafruit_GPS.TxDMA_complete_UART4 = true;  

    // Disable Req from UART and DMA channels 
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_3);
    LL_USART_DisableDMAReq_TX(UART4);

  }

  else if(LL_DMA_IsActiveFlag_TE3(DMA2))  // Error
  {
    LBF_Led_StopNBlinkOnFalse (false);
  }
}

// -----------------------------------------


void GPS_Callback_UART4_Rx_IT(void) 
{
// UART4 Rx is the source of this interrupt
    if(LL_USART_IsActiveFlag_RXNE(UART4))
    {
        Class_Adafruit_GPS.Rx_UART4_avail = true;
        Class_Adafruit_GPS.Uart4_Rx_Char = LL_USART_ReceiveData8(UART4); //this also clears flag RXNE
    }
    else  // error IT
    {
        LBF_Led_StopNBlinkOnFalse (false);
    }
}


/* ============================================================================= */

/*****************************************
 ****  PRIVATE "Helper" FUNCTIONS   ******
 ****************************************/



static void GPS_Launch_DMA2_Ch3_for_UART4_Tx
	(char *pUart4_Tx_Data, uint16_t Num_Bytes )
{

// This routine configures DMA2 Ch3 so it can serve UART4 Tx 
// to send data to external GPS chip

    LL_DMA_ConfigAddresses(DMA2, LL_DMA_CHANNEL_3,
                         (uint32_t)pUart4_Tx_Data, 
                         LL_USART_DMA_GetRegAddr(UART4, LL_USART_DMA_REG_DATA_TRANSMIT),
                         LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_CHANNEL_3));
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_3, Num_Bytes); 
    LL_DMA_SetPeriphRequest(DMA2, LL_DMA_CHANNEL_3, LL_DMA_REQUEST_2);


    LL_DMA_ClearFlag_GI3(DMA2);  // // global clear of all channel3 DMA2 IT flags


    // Enable DMA transfer complete/error interrupts  
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_3);
    LL_DMA_EnableIT_TE(DMA2, LL_DMA_CHANNEL_3);


    Class_Adafruit_GPS.TxDMA_complete_UART4 = false;

    // Enable DMA requests from UART4 Tx
    LL_USART_EnableDMAReq_TX(UART4);

    // Enable DMA Channel Tx 
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_3);

   // Transfer has now started...
   // Completion will be detected through IT and DMA is to be disabled in ISR

}

// -------------------------------------------------
