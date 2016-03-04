BlueTooth Low Energy Test
==========================

Initialize Module, Enable USB
With BTLE enabled in user configuration file,
 LBF_Board_Selective_Inits() will include download by STM32 of specified executable into BTLE module.

Upon pressing switch 1 (side-push button), La BLueFrog sends a text message over BTLE.
This can be read on ad-hoc iOS or Android application.


// ---- Pre-requisites :
// BTLE must be enabled by #define in User_Configuration.h
// Name of the file containing code to download by STM32 
// into BTLE module also defined there -- download occurs
// during LBF_Board_Selective_Inits() phase.
// This executable must be present on FAT File System on Flash 
// (typically stored there from PC through USB).
// In this demo, code is supposed to be Serial Port Service
// snippet provided by Dialog -- this configures the BTLE
// to behave as UART cable replacement. Data sent to
// BTLE module over UART1 at 115200 baud is transitted over BTLE
// This data can be received by DSPS application running in iOS
// or Android, provided by Dialog, available on Appple/Android
// app stores
// --------------------------------------------------------

