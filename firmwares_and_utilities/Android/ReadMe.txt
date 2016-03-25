This Android application is intended to be used in conjunction with the LimiFrog demo stored under: LimiFrog-SW/projects/Demo_BLE_SensorData

Data is exchanged over a BlueTooth Low-Energy link between LimiFrog and a smartphone running this App .
A custom profile that allows to receive/transmit raw bytes is used.
See LimiFrog-SW/projects/Demo_BLE_SensorData.

The .apk file is the Android executable.

The Android source files [to be made available soon] may be used as example of how to use this custom profile and could be adapted to exchange any kind of data between LimiFrog and a smartphone/tablet over BLE.

The example Android code provided here estimates the orientation of LimiFrog  based on magnetometer data sent by LimiFrog and reflects it on the screen of the smartphone (LimiFrog is assumed to be standing on a flat surface).
