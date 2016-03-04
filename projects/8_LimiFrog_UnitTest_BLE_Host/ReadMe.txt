BlueTooth Low Energy Test, HOST
===============================

Initialize Module, Enable USB
With BTLE enabled in user configuration file,
 LBF_Board_Inits() will include download by STM32 of specified executable into BTLE module.

QUICK AND DIRTY IMPLEMENTATION so far
Just shows the BLE link is working in Host Mode

LimiFrog running this demo can be coupled with 
second LimiFrog running demo "7_LimiFrog_UnitTest_BLE_Device"


// ---- Pre-requisites :
// BTLE must be enabled by #define in User_Configuration.h
// Name of the file containing code to download by STM32 
// into BTLE module also defined there -- download occurs
// during LBF_Board_Inits() phase.
// This file (ie. BLE firmware executable) must be present 
// on FAT File System on Flash 
// (typically stored there from PC through USB).
// In this demo, this firmware is supposed to be Serial Port Service
// snippet provided by Dialog, "HOST" role
// -- this configures the BTLE to behave as UART cable replacement. 
// (Payload) data received from BLE radio reception is passed-on
// over  UART3 at 115200 baud 
//
// This data could be received by other LimiFrog module 
// with BLE running the same "UART replacement cable" custom 
// profile, in device role (e.g. running code provided in project
// 7_LimiFrog_UnitTest_BLE_Device
// --------------------------------------------------------
