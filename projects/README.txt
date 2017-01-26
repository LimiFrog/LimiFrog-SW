COMMON:
=======
Contains files for compile and link, shared by all projects. 
Do not modidy unless you know what you're doing.


LimiFrog_PROJECT_TEMPLATE
=========================
Contains a template project, usable as a starting point by the user if he/she wishes to create projects with a structure similar to those provided as examples and demos in this LimiFrog software package.


LimiFrog_FatFS_FORMAT
=====================
Formatting in FAT file system format of the Data Flash.
*** CAUTION ***
All data present on the Data Flash prior to (re-)formatting will be lost.
See also ReadMe file in this directory.



******************
   Unit Tests
******************

(each of the following directories contains a ReadMe file that outlines what the code is doing) 


0_LimiFog_UnitTest_LED:
	LED blinking

1_LimiFrog_UnitTest_DataFlash:  
	Data Flash sanity check - 
	Exercizing Flash abstraction layer (hide pages, sectors etc.)

2_LimiFrog_UnitTest_OLED:  
	Basic OLED display 
	Exercizing basic graphics primitives for OLED access

3_LimiFrog_UnitTest_USBD_MassStorage:  
	USB Mass Storage
	Exercizing USB stack in device mode

4_LimiFrog_UnitTest_FatFs: 
	FAT File System
	Exercizing Fat-FS middleware

5_LimiFrog_UnitTest_Sensors: 
	Sensor sanity check
	I2C accesses to all sensors

6_LimiFrog_UnitTest_Battery: 
	Periodic measurement of battery voltage
	Using Timer to generate periodic IT

7_LimiFrog_UnitTest_BLE_Device: 
	BlueTooth 4.1, peripheral mode (BLE server)

8_LimiFrog_UnitTest_BLE_Host: 
	BlueTooth 4.1, central mode (BLE client)

9_LimiFrog_UnitTest_Timer_PWM: 
	Timers and PWM in different modes

10_LimiFrog_UnitTest_Mic_ADCwatchdog:
	Microphone + ADC Analog Watchdog
	Periodic sampling using timer

11_LimiFrog_UnitTest_Combined:
	Self-checking combination of several unit tests
	*** CAUTION ***
	Includes a re-formatting of the Data Flash, all previous data will be lost



******************
   Demos
******************


Demo_Accel_Viz_TimeDomain:
	Real-time graph of acceleration measured on X, Y, Z axis

Demo_Magnetometer_Viz_FFT
	Real-time graph of magnetic field measured on X, Y, Z axis
	+ FFT on Z-axis component

Demo_Compass:
	Display magnetic North

Demo_PressureTemp_NoiseLevel:
	Display atmospheric pressure and ambiant temp (inside case)
	Toggle background color upon noise level exceeding threshold 

Demo_ProxDist_VL6180X:
	Measure distance to any object present in front of VL6180X detector.
	Display as graded color bar.

Demo_AudioSpectro:
	Microphone --> (out) --> (resistor-based biasing) --> (in) -->
	PGA --> ADC
	Captured data displayed in time-domain 
	or in frequency domain after FFT

Demo_BLE_SensorData:
	Accelerometer and Magnetometer sensor data sent over BLE
	as a series of bytes.
	Can be paired with Android demo.

Demo_Multiple:
	Combination of several demos in sequence
	Go from one step to the next by detecting noise threshold -
	1) LimiFrog logo + proximity detector
	2) Caroussel of pictures + accelerometer
	3) Accelerometer + graph display
	4) Magnetomer + FFT + graph display
	5) Proximity and Distance Detector
	6) Pressure Sensor

Demo_Extension_Port:
	Use pins of extension port as GPIO, UART, SPI, IT, PWM, etc.	
	Can be mostly self-checking by having external loopback.
  
Demo_External_GPS:
	Get GPS geolocation data from Adafruit's "Ultimate GPS" break-out board
        (MediaTek MTK3339 based), connected to LimiFrog through its extension
        connector.
        Update information (latitude, longitude and some more) every few seconds, 
        display on screen and fill .CSV log file on LimiFrog's file system.
        File can then be opened on PC when connecting LimiFrog to USB.


