This example Android application is intended to be used in conjunction with the LimiFrog demo stored under: 
  LimiFrog-SW/projects/Demo_BLE_SensorData

It estimates the orientation of LimiFrog based on magnetometer data sent by LimiFrog and reflects it on the screen of the smartphone (LimiFrog is assumed to be standing upright on a flat surface).

Sensor data is exchanged over a BlueTooth Low-Energy link using a custom profile that allows to receive/transmit raw bytes.

LimiFrog_V2.apk is the executable that may be installed on an Android smartphone.

The Android source files found under /LimiFrog_V2 in this directory may be used as an example of how to use the custom BLE profile to exchange data between LimiFrog and a smartphone/tablet over BLE.


The Android code is by: Olivier Lorente.
It includes some code snippets provided on the web by Martin Wooley of the BlueTooth SIG.


