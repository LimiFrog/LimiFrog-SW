 USB Device Test (Mass Storage)
===============================

Initialize board

Configure board as Mass Storage Device (8MB)
USB Device Stack runs on STM32, Physical Storage space is Data Flash

LimiFrog gets recognized by PC as USB Mass Storage drive.

LimiFrog turns LED on if USB line D+ is pulled high (meaning the STM32
is signalling itself as a USB device to the Host)
+ pressing push-button Switch1 toggles the LED as long as it remains pressed.


**Limitation**: if Flash is not empty and not FAT formatted, PC OS reports abnormal disk behavior.

If Flash is empty/erased, then PC proposes to format the drive (FAT16)
Note Flash can also be formatted by running demo "LimiFrog-FatFS-Format".

