Implementation of USB Device fucntionalities in La BlueFrog relies on device drivers supplied by ST and found in .../libraries/STM32_USB_Device_Library.

The files found in the present directory are derived from examples provided by ST in the STM32L4 Cube Library -- specifically, in package STM32Cube_FW_L4_V1.1.0 :  STM32Cube_FW_L4_V1.1.0/Projects/STM32L476G_EVAL/Applications/USB_Device/MSC_Standalone. They were slightly adapted for La BLueFrog, including in the following aspects:
- priority of USB interrupt made user configurable

