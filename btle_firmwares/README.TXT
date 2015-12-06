
The files stored in this directory implement different BlueTooth Low-Energy (BTLE) profiles.
They are executable firmware for the BTLE module.

Here is the principle -- assuming usage of the provided initalization libraries:
> Function LBF_Selective_Inits(), called at start of main(), checks if BTLE_ENABLE is defined in User_Configuration.h . If so:
> it also gets the name of the required BTLE firmware from this same cnfig file 
> It then looks for a file of that name at the root of its file system (the file system resides on the data Flash memory, formatted as a FAT drive).
> It gets the STM32 to send a reset signal to the BTLE module,
> After this reset, the BTLE module will automatically download firmware from the STM32 (through a UART interface) according to a protocol known from both parties.
> Once this is done the BTLE firmware starts executing, the BTLE module is functional. 

Therefore, from the user's point of view, all that's required to run on the STM32 a program that exploits the BTLE module is :
- put the intended BTLE firmware on LimiFrog's Flash (typically by connecting to a PC with LimiFrog implementing USB and therefore detected as a USB drive from the PC), 
- set the enable flag and indicate the BTLE firmware filename in the User_Configuration.h file associated to that STM32 program
- compile and run the program




