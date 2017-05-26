BLE_DSPS_App.aia
================

This is an "MIT App Inventor 2" project. MIT App Inventor 2 is a simple framework that aims at allowing anyone with no or limited Android coding skills to build decent Android Apps (appinventor.mit.edu).

The .aia project provided implements a demo Android app to connect with LimiFrog through BLE and exchange data with it. 

See also the following blog post for details and pictures:
  http://www.limifrog.io/2017/05/ble-transfers-using-mit-app-inventor-for-android


The intended set-up is as follows :

– LimiFrog is configured to run the DSPS (Dialog Serial Port Service), a custom profile provided by Dialog. See LimiFrog documentation and have a look, for example, at project 7_LimiFrog_UnitTest_BLE_Device.

– a smartphone (with BLE capability of course) running at least Android 5 (Lollipop) is required.  

– the .aia source package is to be imported into an MIT App Inventor 2 session. 

– an AI2 account is required (easy set-up, start here: http://appinventor.mit.edu/explore/index-2.html -- note however you need a Google account in the first place). AI2 enables easy live testing on your smartphone (just need to install MIT’s “AI2 Companion App” first), with the App under test downloaded over WiFi. Once you’re happy with your code, AI2 can package it as a standard Android App (.apk) and save it or directly install it on your phone.


The interface is deliberately designed to expose different steps in BLE connection and transfer:

> the Start Scan button instructs the App to look for nearby BLE devices advertizing their presence. The devices found (ID + RSSI) are then listed below that button.

> The user can select the index (1 for first device displayed, etc.) of that to which he/she wants to connect and click the ‘Connect’ button. To connect to LimiFrog running the Dialog DSPS firmware, the device to choose is that whose information includes ID DA1458x  (which is the name of the BLE chip used in LimiFrog). 

> A message to send to the Android device can be entered in the text box of the Tx control section. It is sent over BLE when button “Send Message” is pressed. 

> The data sent by LimiFrog over BLE can be monitored or ignored, the choice is done through button “Enable data reception” / “Disable data reception” (button text toggles depending on current state). 
