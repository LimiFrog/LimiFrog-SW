
ReadMe file - 

Preliminary Note:
LimiFrog used to be called La BlueFrog.
There may be places in the documentation where this name change has not been refected yet.
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
		-- /Project-A
			-- ..........
		-- /STARTUP
			-- startup_stm32l476xx.s
					  # startup file called before main, 
			-- STM32L476RE_FLASH.ld
					  # linker script for STM32L476RE
	-- /documentation
		-- LBF-V2_SW_Organization.pdf
		   # Organization of the provided software
		-- Using_Programmation_Connector.pdf
		   # Guide for connecting the ST-Link V2 programmer/debugger
		-- LBF-V2_Board_HW.pdf
		   # Outline of board hardware and inter-chip connections
		-- BlueFrog_gcc_dev.pdf
		   # Guidelines to use La BlueFrog with gcc under Linux 
		-- /APIs
			-- /HAL (Cube) for STM32 On-Chip Peripherals
			-- /FatFS_File_System_doc
			-- /STemWin Gfx Library
		 	   # programming interfaces for the FAT File Sysem, the STemWin
		 	   # Gfx library and the STM32 HAL Cube peripheral drivers,
			-- La-BlueFrog_API.pdf
		 	  # Basic functions developped for easy usage of La BlueFrog
		-- /datasheets
		   # datasheets and user manuals of ICs used on La BlueFrog
	-- /btle_firmwares
			-- *.bin
			   # Executables for the BlueTooth Low-Energy module (relies 
   			   # on an embedded Cortex-M0). Can be used to implement 
   			   # specific 'profiles' when BTLE is enabled



=================================

To write an application, user may first call within main() a few board init and optional middleware initialization functions (see /PROJECT_TEMPLATE under /projects as well as examples provided). This will configures the STM32 clocks, IOs, etc. and define a number of abstraction layers to use the IC on-board. User can then write its application code, relying on functions/macros defined in the provided libs and middleware provided, for easier (higher level) control of on-chip peripherals and on-board chips.

See examples provided under /projects.
The example projects provided can be simply built by "make build" and programmed into the STM32 by "make run"

================================

Regarding development chains for the STM32, there are a number of options, with or without IDE. Without IDE, development can be done with gcc and Makefiles under Linux. With IDE, there are several commercial options, but an interesting free option (under Eclipse, available fro windows and for Linux) is the new "STM32 Workbench" provided by AC6 in partnership with ST-- see http://www.openstm32.org



