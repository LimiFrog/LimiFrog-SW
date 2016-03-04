################################################################################
# Common.mk for LimiFrog-0.x :
#
# Part of Makefile common to all projects to create :
# - List of source files
# - List of include files
# - List of libs
# - Path to targets that will be built
#
# This is called from the Makefile that pertains to each project
# 
# The user should add his own customizations in the Makefile present in each
# project rather than here
#
################################################################################


# Directory paths
SRC_DIR         = ./src
INC_DIR         = ./inc
OBJ_DIR         = ./obj
BIN_DIR         = ./obj
RACINE          = ../..
CMSIS_DIR       = $(RACINE)/libraries/CMSIS_L4xx
HAL_DIR         = $(RACINE)/libraries/STM32L4xx_HAL_Driver
SENSORS_DIR     = $(RACINE)/libraries/Sensor_APIs
USB_DIR		= $(RACINE)/libraries/STM32L4_USB_Device_Library
FATFS_DIR	= $(RACINE)/libraries/FatFS_Lib
STEMWIN_DIR	= $(RACINE)/libraries/STemWin_Lib
LIMIFROG_DIR    = $(RACINE)/libraries/LimiFrog-Lib



# Linker script
LINKER          = $(RACINE)/projects/COMMON/STM32L476RE_FLASH.ld

# Source file paths : Common
VPATH          := $(SRC_DIR):$(RACINE)/projects/COMMON

# Source file paths : STM32L4xx_HAL_Driver
VPATH          := $(VPATH):$(HAL_DIR)/Src
HAL_SRC   = $(notdir $(wildcard $(HAL_DIR)/Src/*.c))

# Source file paths : Sensor_APIs
VPATH          := $(VPATH):$(SENSORS_DIR)/LSM6DS3/src
VPATH          := $(VPATH):$(SENSORS_DIR)/LPS25H/src
SENSORS_SRC   = $(notdir $(wildcard $(SENSORS_DIR)/*/src/*.c))

# Source file paths : STM32_USB_Device_Library /Class/MSC & /Core
VPATH          := $(VPATH):$(USB_DIR)/Class/MSC/Src
USB_CLASSMSC_SRC   = $(notdir $(wildcard $(USB_DIR)/Class/MSC/Src/*.c))
VPATH          := $(VPATH):$(USB_DIR)/Core/Src
USB_CORE_SRC   = $(notdir $(wildcard $(USB_DIR)/Core/Src/*.c))

# Source file paths : FatFS_Lib
VPATH          := $(VPATH):$(FATFS_DIR)/src
FATFS_SRC   = $(notdir $(wildcard $(FATFS_DIR)/src/*.c))

# Source file paths : LimiFrog-Lib
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/Utilities
DEBUG_SRC    = $(notdir $(wildcard $(LIMIFROG_DIR)/src/Utilities/*.c))
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/LBF_API
LBF_API_SRC    = $(notdir $(wildcard $(LIMIFROG_DIR)/src/LBF_API/*.c))
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/LBF_Board_Inits
LBF_BSP_SRC    = $(notdir $(wildcard $(LIMIFROG_DIR)/src/LBF_Board_Inits/*.c))
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/LBF_USB_MassStorage
LBF_USBMS_SRC    = $(notdir $(wildcard $(LIMIFROG_DIR)/src/LBF_USB_MassStorage/*.c))
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/LBF_STemWin
LBF_STEMWIN_SRC    = $(notdir $(wildcard $(LIMIFROG_DIR)/src/LBF_STemWin/*.c))
VPATH          := $(VPATH):$(LIMIFROG_DIR)/src/LBF_DataFlash_FatFS
LBF_FATFS_SRC   = $(notdir $(wildcard $(LIMIFROG_DIR)/src/LBF_DataFlash_FatFS/*.c))
# TODO - use wildcards where possible  ...



#----------------------------------------------------------------------------
# Creation of list of source files
SOURCES = \
	$(notdir $(wildcard $(RACINE)/projects/COMMON/*.s)) \
	$(notdir $(wildcard $(RACINE)/projects/COMMON/*.c)) \
	$(notdir $(wildcard $(SRC_DIR)/*.c)) \
	$(HAL_SRC) \
	$(SENSORS_SRC) \
	$(USB_CLASSMSC_SRC) \
	$(USB_CORE_SRC) \
	$(FATFS_SRC) \
	$(DEBUG_SRC) \
	$(LBF_API_SRC) \
	$(LBF_BSP_SRC) \
	$(LBF_USBMS_SRC) \
	$(LBF_STEMWIN_SRC) \
	$(LBF_FATFS_SRC) 
# TODO - could define a single $(LIMIFROG_SRC) for all these paths ?

INCLUDES = \
	$(INC_DIR) \
	$(CMSIS_DIR)/Device/ST/STM32L4xx/Include \
	$(CMSIS_DIR)/Include \
	$(HAL_DIR)/Inc \
	$(SENSORS_DIR)/LSM6DS3/inc \
	$(SENSORS_DIR)/LPS25H/inc \
	$(SENSORS_DIR)/VL6180X/inc \
	$(SENSORS_DIR)/LIS3MDL/inc \
	$(USB_DIR)/Class/MSC/Inc \
	$(USB_DIR)/Core/Inc \
	$(FATFS_DIR)/inc \
	$(STEMWIN_DIR)/inc \
	$(LIMIFROG_DIR)/inc \
	$(LIMIFROG_DIR)/inc/Utilities \
	$(LIMIFROG_DIR)/inc/LBF_API \
	$(LIMIFROG_DIR)/inc/LBF_Board_Inits \
	$(LIMIFROG_DIR)/inc/LBF_USB_MassStorage \
	$(LIMIFROG_DIR)/inc/LBF_STemWin \
	$(LIMIFROG_DIR)/inc/LBF_DataFlash_FatFS \
	$(LIMIFROG_DIR)/inc/LBF_Defs 
# TODO - use wildcards where possible  ...


LIBS = -L$(STEMWIN_DIR)/Lib -lSTemWin528_CM4_GCC \
       -L$(CMSIS_DIR)/Lib/GCC -larm_cortexM4lf_math  
# STemWin528_CM4_GCC and path to arm_cortexM4lf_math are for GNU GCC - 
# If using different toolchain e.g. Keil, need to point to different package


#------------------------------------------------------------------------------

# Compilation Tools
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld
CP      = arm-none-eabi-objcopy
OD      = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

#------------------------------------------------------------------------------

# Targets to build
TARGET_BIN = $(BIN_DIR)/$(TARGET).bin
TARGET_HEX = $(OBJ_DIR)/$(TARGET).hex
TARGET_LST = $(OBJ_DIR)/$(TARGET).lst
TARGET_ELF = $(OBJ_DIR)/$(TARGET).elf
TARGET_OBJ = $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(basename $(SOURCES))))

#-------------------------------------------------------------------------------#

