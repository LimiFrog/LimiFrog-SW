Combined Unit Tests for LimiFrog
=================================

This is intended to be mostly self-checking.
It delibarately does not use (hence check) the OLED to be usable on the board stand-alone.


0) Init board and emit short flash on LED

1) Active 13V generation for OLED (even though not used - just to check no perturbation)

2) Format Flash as FAT File System
   !!! CAUTION:  THIS MEANS YOU LOOSE ALL DATA YOU PUT ON DATA FLASH / FILE SYTEM

3) Write short message on file system (log succesful formatting)
   Read it back - check it's OK

4) Check all sensors WHO_AM_I register (via I2C)

5) Download dummy firmware into BLE module - just to check UART exchanges with BLE module work fine

6) Switch off 13V

7) Launch USB (mostly to check init reports OK status - but also means LimiFrog should mount on PC as USB drive)

8) Set positions 11-10, 8-7, 6-2 of the extension port to Logic1
   ==> can be probed to check level = VCC (2.93V nom.)
   Position 9 = GND, Position 6 should bear 3.33V nom (VCC_LDO)

9) Report result :
   Fixed LED if success
   Blink if failure
   (Nothing => SW hung)


   
