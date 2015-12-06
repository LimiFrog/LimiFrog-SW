This directory proposes a template to create LimiFrog projects.


## The Makefile takes care of compiling and linking all libraries as well as any .c files you put under /src (where you would typically put your source files) and .h files you put under /inc (where you would typically put your header files).

Tune the Makefile according to your needs, e.g. if you require specific compile/link options or if you introduce new file paths not yet known from the Makefile.


## Under /src, a main.c template is proposed, hopefully it is self-explanatory if you look at it.

A template file stm32.c for handling interrupt requests is also provided. In particular, it lists all potential interrupt sources and has place holders for Interrupt Service Routines. Fill the in with your ISR code where relevant. For legibility and conciseness, you may want to discard ISR entries that will never be used in your application.


## Under /inc, 3 files are proposed (2 of them important for configuring your application) :

> "User_Configuration.h" where you can set a few configuration flags to :
  - indicate if your board has/uses the OLED display (used by OLED configuration libraries)
  - indicate if your board has/uses the BlueTooth 4.1 module and, if so, at what speed UART (baud rate) exchanges between the STM32 and this BLE module should take place
  - configure in a simple way usage on the extension port. This is done through enabling a number of preset configurations that cover the most common requirements. Other configurations are possible and would need to be written by the user. 

> "IT_Priorities_UserDefinable.h" where you can specify the respective priorities of the interrupts you use in your system.

> "stm32_it.h" where you would e.g. make public the prototypes of functions implemented in stm32_it.c that you would like to call from somewhere else -- for example, from the main().

