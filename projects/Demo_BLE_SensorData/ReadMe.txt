DEMO OF USING BLE TO TRANSMIT SENSOR DATA - CAN BE PAIRED WITH ANDROID DEMO
===========================================================================

Monitor Magnetometer (and optionally Accelerometer) and regularly send results over BLE.

The BLE is configured for peripheral role (i.e. server) to pair with a device having the BLE central role (i.e. client) -- for example a smartphone.

A smartphone running the provided Android App will be able to track and show in real-time the orientation of the LimiFrog module, using the received magnetometer data. The LimiFrog module must however be standing upright (and may pivote around the vertical axis).

BLE is enabled by the code (in its init phase) based on file User_Configuration.h, which also specifies the name of the BLE firmawre to be used (BTLE_D.BIN).  This firmware MUST be present on the file system of LimiFrog prior to using this demo.

This firmware gets the BLE module to behave as a "serial cable replacement". That is, the STM32 can send data to the BLE module using UART3 just as though it was communicating with another UART-capable device. The BLE module running this firmware takes care of converting the UART data as BLE services.
See the ReadMe file in the library directory that contains the firmware executables (.../libraries/btle_firmware).

Note-
Because the ratio of magnetic field X, Y and Z component is more important than their asolute values to correctly track the orientation of the module, in general the smartphone demo works OK without calibrating the magnetometer (so with an offset present). However in some cases the offset is too large and a calibration is requried. Calibration can be performed any time by pressing the egenral purpose user button and following the instructions displayed on screen.



