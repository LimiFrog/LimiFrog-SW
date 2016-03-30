
README FILE -

This software package is a collection of libraries, example code and documentation to help the user get started with LimiFrog. 
It is provided "as is", in the hope it will be useful (especially to people with limited STM32 experience).

Please read the licensing information in Licenses.txt.

This package has been developed with a "prototyping" objective in mind -- trading off performance optimization for ease of use in some places. If you need something more optimized you may either use your own implementations, or perhaps start from this package and rework sections that need optimization for your application.


About the underlying libraries :
================================

The libraries and examples provided mostly build upon the HAL (Hardware Abstraction Layer) drivers provided by ST. This library is intended to control all STM32 peripherals in a flexible way at relatively high level and to  maximize portability across the STM32 portfolio. However, it also introduces some overheads that may not be desirable for some applications.

ST also provides a lower-level Library, which they present as "a set of Low Layer APIs (LL) offering a fast light-weight expert-oriented layer which is closer to the hardware than the HAL" (available for a selected set of peripherals).
In the provided LimiFrog SW package, this library has been used in a few places where higher performance was required (typically for fast access to the Data Flash and the OLED Display).

If you need to optimize performance or power consumption, you may want to use more extensively this LL library.
Another option is to use your favorite 3rd party library; one example is the libopencm3 project (previsouly known as libopenstm32): libopencm3.org . There is initial STM32L4 support at the time of writing.



Note  -  La BlueFrog / LimiFrog
===============================
LimiFrog used to be called La BlueFrog.
There might be places in the documentation where this name change has not been reflected yet. Therefore, please consider names La BlueFrog and LimiFrog are fully interchangeable.
This also explains why LimiFrog libraries are prefixed "LBF_".



================================
FILE STRUCTURE:

/<LimiFrog root directory>

	-- /libraries
		-- /LimiFrog-Lib
		    # Board init and controls  -  LimiFrog specific
		    # Adaptation Layers for Middlewares (USBD, FatFS, emWin)
		-- /CMSIS_L4xx
		    # ARM Cortex-M4 libs  -  supplied by ARM/ST
		-- /STM32L4xx_HAL_Driver
		    # Hardware Abstraction Layer for config of STM32 on-chip periphs 
		    # Supplied by ST as part of "STM32 C
		-- /STM32L4_USB_Device_Library
		    # USB2.0 full speed drivers -from ST
		-- /FatFS_Lib
		    # FAT File System  - from ST, derived from ChaN's open-source FatFS
		-- /STemWin_Lib
		    # Rich Graphics Library - from ST under licence from Segger (emWin)
		-- /Sensor_APIs
		    # Vendor-provided sensor APIs (with some adaptation) 
                     

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
			    # contains object files as well as executable files,
			    # automagically filled when building project with 'make'  
			-- /ready_for_use
			    # .bin file (the result of compiling and linking this project), ready
			    # to be flashed into the STM32 + any files (pictures, etc.) that 
			    # this particular demo expects to find in the file system = Data Flash 
			    # (can be put there by user through USB when running code that implements
			    # USB mass storage)
		-- /Project-B
			-- ..........
		-- /TEMPLATE
		    # Template user files to get started with LimiFrog and create a project
		    # which can be built and run with provided Makefile
		-- /COMMON
		    # Files required to properly compile and link any LimiFrog project 
		    # Normally don't need to be modified - but advanced users may tune some
			-- startup_stm32l476xx.s
				# startup file called before main, 
			-- STM32L476RE_FLASH.ld
				# linker script for STM32L476RE
			-- sysmem.c
				# minimal System Memory calls file
			-- system_stm32l4xx.c
				# system inits - optional relocation of vector table
			-- Common.mk
				# Part of Makefile common to all projects


	-- /documentation

		-- /LimiFrog
		     -- Dev_Environment
			-- LimiFrog_gcc_dev.pdf
		   	    # Guidelines to use La BlueFrog with gcc and Makefiles 
			-- Using_Programmation_Connector.pdf
		   	    # Guide for connecting the ST-Link V2 programmer/debugger
			-- LimiFrog_with_Eclipse_IDE_STM32_System_Workbench.pdf
		   	    # Tips to use an IDE based on Eclipse + gcc + OpenOCD
			-- Flashing_LimiFrog_over_USB.pdf
			    # TODO
			-- /LimiFrog_with_Eclipse_IDE_STM32_System_Workbench
			    # Information on using the sw package with this IDE
		     -- Hw_and_Interfaces
			-- Anatomy-LimiFrog.pdf
		   	    # Identification of the main parts and controls of LimiFrog 
			-- LimiFrog_Board_HW.pdf
		   	    # Outline of board hardware and inter-chip connections
			-- Operating_OLED_FPC_Rotary_Backlock_Connector.pdf
		 	    # Instructions to properly connect/unconnect OLED display

			-- LimiFrog_Extension_Connector.pdf
		   	    # Overview of signals available through the extension port
		     -- Programming
			-- LimiFrog_SW_Organization.pdf
		   	    # Organization of the provided software
			-- LimiFrog_API.pdf
		 	    # Board Support Package and Libs to get started with LimiFrog
		     -- Known_Limitations_and_Features.pdf

		-- /3rd_Party_APIs
			-- /HAL (Cube) for STM32 On-Chip Peripherals
			-- /FatFS_File_System_doc
			-- /STemWin Gfx Library
		 	    # programming interfaces for the FAT File Sysem, the STemWin
		 	    # Gfx library and the STM32 HAL Cube peripheral drivers,
			-- /Sensors
			    # Documentation on 3rd party sensor APIs

		-- /datasheets
		    # datasheets and user manuals of ICs used on LimiFrog

	-- /firmwares_and_utilities
		-- /Android
		    # example Android App for use with LimiFrog BLE
		
		-- /LimiFrog_BLE_module
			-- *.bin
			   # Executables for the BlueTooth Low-Energy module (relies 
   			   # on an embedded Cortex-M0). 
		-- /ST
			-- stlink_udev_rule
			   # Reference udev rules when using the ST-Link/V2 under Linux 

	-- Licenses.txt
	    # Licensing information for provided software


NOTE: By default the Makefile compiles all HAL libraries (only those that are actually used by the application end up as binary in Flash, of course -- the linker takes care of this). To speed up compilation you might want to change this by editing file :  LimiFrog_SW/libraries/Lim_Frog-Lib/inc/LBF_Defs/stm32l4xx_hal_conf.h


=================================
USAGE:

To write an application, user may first call within main() a few board init and optional middleware initialization functions (see /PROJECT_TEMPLATE under /projects as well as examples provided). This will configures the STM32 clocks, IOs, etc. and define a number of abstraction layers to use the IC on-board. User can then write its application code, possibly relying on functions/macros defined in the provided libs and middleware provided, for easier (higher level) control of on-chip peripherals and on-board chips.

See examples provided under /projects.
The example projects provided can be simply built by "make build" and programmed into the STM32 by "make run" (if using gcc + Makefiles with command line interface)

================================
TOOL CHAINS:

Regarding development chains for the STM32, there are a number of options, with or without IDE. Without IDE, development can be done with gcc and Makefiles in a terminal environment. Some guidance is provided in the /documentation directory. With IDE, there are several commercial options, one free option (under Eclipse, available for Windows and for Linux) is the  "OpenSTM32 Workbench" provided by AC6 in partnership with ST-- see http://www.openstm32.org



