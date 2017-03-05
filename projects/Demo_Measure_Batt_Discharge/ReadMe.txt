Monitoring the dischargeing of the LiPo battery 
===============================================

This demo monitors (displays and logs) the LiPo battery voltage in very demanding power usage conditions.

Specifically :
The program gets the OLED display to cycle through a pattern of brightly colored squares.
Those pictures are chosen to be very demanding in terms of OLED power consumption.
The voltage provided by the battery is assessed every minute, briefly displayed on screen and logged in a .CSV file stored on LimiFrog's file system (in data Flash).

The intended use case is as follows: 
- start from a fully loaded battery 
- run the program until the battery is empty (or, more precisely, the on-board PMIC cuts power because it detects battery voltage has dropped to 3V).
- then the user can connect LimiFrog to a PC through USB, copy the log file and analyze the data using e.g. Excel or any other suitable program to, for example, display a curve showing battery voltage vs time.

Notes: 
1) this demo assumes LimiFrog's Flash has initially been formatted as FatFS file system. This can for example be done using project LimiFrog_FatFS_FORMAT.
2) A blog post about this experiment and results obtained can be found here: http://www.limifrog.io/2017/03/monitoring-the-lipo-battery/
