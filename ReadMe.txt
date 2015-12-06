
READ-ME FILE -

This software package is a collection of libraries, example code and documentation to help the user get started with LimiFrog.

The initial release(s) of this software package is mostly the result of my work (Xavier-C). This package is provided as a first step, knowing that many things could still be added or improved (I'm not -yet- a software expert ;-). It is provided "as is" with no warranty whatsoever (see licensing files).

This has been developed with an "easy prototyping" objective in mind. This means trading off performance optimization for ease of use in some places. If you need something more optimized you may either use your own choice of libraries, or perhaps start from this and rework those sections that specifically need optimzation.


About the underlying libraries :
================================

The libraries and examples provided build upon the HAL (Hardware Abstraction Layer) drivers provided by ST. This library is intended to control any STM32 in a flexible way at relatively high level and to  maximize portability across the STM32 portfolio. However, it also introduces some overheads that may not be desirable for some applications.

If you would rather use lower-level libraries :
- one option is to take advantage of ST's recent addition to the HAL: a set of Low Layer APIs (LL) "offering a fast light-weight expert-oriented layer which is closer to the hardware than the HAL" (available for a selected set of peripherals);
- another option is to use your favorite 3rd party library; one example is the libopencm3 project (previsouly known as libopenstm32): libopencm3.org . There is initial STM32L4 support at the time of writing.



Note  -  La BlueFrog / LimiFrog
===============================
LimiFrog used to be called La BlueFrog.
There may be places in the documentation where this name change has not been reflected yet.
Therefore, please consider names La BlueFrog and LimiFrog are fully interchangeable.
This also explains why LimiFrog libraries are prefixed "LBF_".



================================
FILE STRUCTURE:

/<LimiFrog root directory>

	-- /libraries
		-- /LimiFrog-Lib
		   # Board init and controls  -  LimiFrog specific
		   # Adaptation Layers for Middlewares (USBD, FatFS, emWin)
		-- /CMSIS
		   # ARM Cortex-M4 libs  -  supplied by ARM/ST
		-- /STM32L4xx_HAL_Driver
		   # Hardware Abstraction Layer for config of STM32 on-chip periphs 
		   # Supplied by ST as part of "STM32 C
		-- /STM32_USB-Device_Library
		   # USB2.0 (full speed) device driver -from ST
		-- /FatFS_Lib
		   # FAT File System  - from ST, derived from ChaN's open-source FatFS
		-- /STemWin_Lib
		   # Rich Graphics Library - from ST under licence from Segger (emWin)
		-- /Sensor_APIs
		   # Vendor-provided sensor APIs (with some adaptation) 
                     Only LSM6DS3 for now. Mostly the .h files are interesting 
                     (register definitions)

	-- /projects
		-- /Project-A
			-- /inc
				xxx.h
			-- /src
				xxx.c
			-- Makefile
			   # Invoked by make statement to compile/link/load project,
			   # type make -help for usage options
			-- /obj 
			   # automagically created and filled in when building project with 'make'  
		-- /Project-B
			-- ..........
		-- /TEMPLATE
		   # Templates user files to get started with LimiFrog and create a project
		   # which can be built and run with provided Makefile
		-- /STARTUP
			-- startup_stm32l476xx.s
					  # startup file called before main, 
			-- STM32L476RE_FLASH.ld
					  # linker script for STM32L476RE
	-- /documentation
		-- LimiFrog_SW_Organization.pdf
		   # Organization of the provided software
		-- Using_Programmation_Connector.pdf
		   # Guide for connecting the ST-Link V2 programmer/debugger
		-- LimiFrog_Board_HW.pdf
		   # Outline of board hardware and inter-chip connections
		-- LimiFrog_gcc_dev.pdf
		   # Guidelines to use La BlueFrog with gcc and Makefiles 
		-- /APIs
			-- /HAL (Cube) for STM32 On-Chip Peripherals
			-- /FatFS_File_System_doc
			-- /STemWin Gfx Library
		 	   # programming interfaces for the FAT File Sysem, the STemWin
		 	   # Gfx library and the STM32 HAL Cube peripheral drivers,
			-- LimiFrog_API.pdf
		 	   # Board Support Package and libraries to help get started with LimiFrog
			-- /Sensors
			   # Documentation on 3rd party sensor APIs
		-- /datasheets
		   # datasheets and user manuals of ICs used on LimiFrog
	-- /btle_firmwares
			-- *.bin
			   # Executables for the BlueTooth Low-Energy module (relies 
   			   # on an embedded Cortex-M0). Can be used to implement 
   			   # specific 'profiles' when BTLE is enabled



=================================
USAGE:

To write an application, user may first call within main() a few board init and optional middleware initialization functions (see /PROJECT_TEMPLATE under /projects as well as examples provided). This will configures the STM32 clocks, IOs, etc. and define a number of abstraction layers to use the IC on-board. User can then write its application code, relying on functions/macros defined in the provided libs and middleware provided, for easier (higher level) control of on-chip peripherals and on-board chips.

See examples provided under /projects.
The example projects provided can be simply built by "make build" and programmed into the STM32 by "make run"

================================
TOOL CHAINS:

Regarding development chains for the STM32, there are a number of options, with or without IDE. Without IDE, development can be done with gcc and Makefiles in a terminal environment. Some guidance is provided in the /documentation directory. With IDE, there are several commercial options, but an interesting free option (under Eclipse, available for Windows and for Linux) is the  "OpenSTM32 Workbench" provided by AC6 in partnership with ST-- see http://www.openstm32.org



