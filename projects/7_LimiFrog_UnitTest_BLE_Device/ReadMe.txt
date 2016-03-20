BlueTooth Low Energy Test
==========================

// ---- Pre-requisites :
// BTLE must be enabled by suitable #define in User_Configuration.h
// Name of the file containing code to download by STM32 
// into BTLE module also defined there -- download occurs
// during LBF_Board_Init() phase.
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


- Initializes Module, 
   With BTLE enabled in user configuration file, LBF_Board_Inits() will include the
   download by STM32 of specified executable into BTLE module.

- Enables USB

- Monitors data received from BLE module (over UART3 Rx),
  assembles it into a string that will be displayed upon reception of a \n (carriage return character)

- Transmits a text message over BLE using UART3 Tx if general-purpose side-push switch is pressed


===>   This demo can be used in conjunction with the DSPS App (iOS or Android) provided by Dialog Semi and available on Apple's or Google's App Stores.
Once the App has paired with LimiFrog's BLE (DA1458x):
- the string sent by LimiFrog appears in the receive section of the 'Console' and 'Rx/Tx' tabs of the App
- the transmit section of these tabs allows to send data to LimiFrog, as follows :
  . in the console section, any char entered is immediately transmitted.
    As per the code in main(), these will be displayed as a string of chars on the OLED
    once you enter a final Carriage Return ('enter')
  . in the Rx/Tx section, the data is not sent until you press 'Send'.
    As per the code in main(), to display a string on LimiFrog, 
    you can enter it in the Tx section of the Rx/Tx tab 
    *and conclude it with a Carriage Return character*.
    Any text after this CR will be ignored by LimiFrog 
    (will be received while LimiFrog is busy displaying the string till CR and UART3 is off)


