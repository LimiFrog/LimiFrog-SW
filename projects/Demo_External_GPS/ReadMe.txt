Use of an External GPS module
=============================

This demo demonstrates usage of an external GPS board :
this is Adafruit's "Ultimate GPS Breakout":  https://www.adafruit.com/products/746
based on a GTop all-in-one GPS module (incl. antenna), architectured around MediaTek's MTK3339 GPS chip.

Connections between the GPS board and LimiFrog are as follows :
---------------------------------------------------------------
- VIN of breakout board = VCC_LDO (3.3V) on position 6 of LimiFrog's extension connector 
- GND of breakout board = GND on position 9 of LimiFrog's extension connector 
- TX of breakout board = UART4_RX on position 7 of LimiFrog's extension connector 
- RX of breakout board = UART4_TX on position 8 of LimiFrog's extension connector 
- FIX, PPS and EN of breakout board can optionally be connected to available GPIO pins of LimiFrog's extension connector
File User_Configuration.h is used for correct configuration of the extension port according to the above.

The GPS library implemented here is mostly a straight adaptation of Adafruit's GPS library for Arduino.

This library (GPS_Lib) is provided as part of the project.
The provided Makefile takes care of adding paths to ./GPS_Lib for correct compilation.


This demo essentially does the following :
------------------------------------------

> If USB is connected, just set LimiFrog to behave as USB drive (Mass Storage Device):
  this allows to access from PC all files present on the file system,
  in particular log file "GPS.CSV" (see below)
Else:
> Provide 3.3V from on-bord LDO to GPS module
> Configure GPS using NMEA messages over UART4 TX on extension port
> Receive and parse NMEA messages from GPS module over UART4 RX on extension port,
  at specific update rat (e.g. 1Hz)
> When fix is obtained: every few seconds (e.g. 4s), display key parameters (time,
  latitude, longitude, altitude, speed, # of satellites) on screen
  and save them on Flash is file GPS.CSV (text format with tab-separated columns)
> User can pause and restart logging by pressing LimiFrog's general purpose push button.

Because a FatFS file system can be fatally corrupted if a write operation to the drive does not complete, it is recommended to always pause data logging before switching off LimiFrog. This makes sure no write operation is ongoing when the power-down request is processed.

Note: this demo assumes LimiFrog's Flash has initially been formatted as FatFS file system. This can for example be done using project LimiFrog_FatFS_FORMAT.
