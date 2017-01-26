################################################################################
#
# Makefile for LimiFrog-0.x
# 
################################################################################


# Identify OS (Windows / others esp. Linux)
ifeq ($(OS), Windows_NT)  
# true for any Windows OS
  UNAME := Windows
else
  UNAME := $(shell uname -s)
endif


# INCLUDE EXTERNAL MAKEFILE (common to different projects)
# List of source files (SOURCES), of include files (INCLUDES)
# and libs (LIBS)
# + Paths to targets that will be built
include ../COMMON/Common.mk

# ============================================
# SPECIFIC FOR THIS EXAMPLE:
# Add Paths to GPS Library -
# GPS_DIR		= $(RACINE)/libraries/GPS_Lib ...MOVED !!!
GPS_DIR		= ./GPS_Lib
# Source file paths : GPS_Lib
VPATH          := $(VPATH):$(GPS_DIR)/src
GPS_SRC   = $(notdir $(wildcard $(GPS_DIR)/src/*.c))
# Append source and include files to existing list :
#SOURCES := $(SOURCES) $(GPS_SRC) 
SOURCES += $(GPS_SRC)
INCLUDES += $(GPS_DIR)/inc


# Name of executable
TARGET          = limifrog

# Pamaterizable defines
DEBUGGER        = DEBUG

# Optimization (0,1,2,s)
OPT             = 0
# See https://gcc.gnu.org/onlinedocs/gcc-4.4.1/gcc/Optimize-Options.html
# for details on compilation flags
# CAUTION: some optimizations limit debugging possibilities

# Cortex-M4 architecture flags
ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16


# Compile flags
CFLAGS = \
	$(ARCH_FLAGS) \
	$(addprefix -I,$(INCLUDES)) \
	-O$(OPT) \
	-Wall \
	-ffunction-sections \
	-fdata-sections \
	-DSTM32L4 \
	-DSTM32L476xx \
	-DUSE_HAL_DRIVER \
	-D$(DEBUGGER) \
	-fno-exceptions \
	-Wno-write-strings\
	-g
# For debug, to be able to see the source code, a -ggdb or -g flag is typically required


# Linker flags
LDFLAGS = \
	$(ARCH_FLAGS) \
	-static \
	-Wl,-gc-sections \
	-T$(LINKER) 
# Could add --specs=nano.specs (plus possibly -lc -lnosys) to use newlib-nano and save on size of text and data sections
# See e.g. https://plus.google.com/+AndreyYurovsky/posts/XUr9VBPFDn7 and 


# Assembler flags
ASFLAGS = \
	$(ARCH_FLAGS) \
	-x assembler-with-cpp \
	$(addprefix -I,$(INCLUDES))


#-------------------------------------------------------------------------------#
# Built Targets :


ifneq ($(UNAME), Windows)
 all:  build run size
endif

ifeq ($(UNAME), Windows) 
  all: $(TARGET_BIN) $(TARGET_HEX) $(TARGET_LST)
else
  build: $(TARGET_BIN) $(TARGET_HEX) $(TARGET_LST)
endif

$(TARGET_BIN): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(CP) -O binary $< $@

$(TARGET_HEX): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(CP) -O ihex $< $@

$(TARGET_LST): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(OD) -S $< > $@

$(TARGET_ELF): $(TARGET_OBJ)
	@echo "\033[01;33m==========  GENERATION  ====================================\033[m"
	@echo "-> "$(notdir $@)""
	@$(CC)  $(LDFLAGS) -o  $@  $^ $(LIBS)

$(OBJ_DIR)/%.o: %.c
ifeq ($(UNAME), Windows) 
#	@mkdir $(dir $@)  
#  Option -p inexistent in Windows, covered by default 
else
	@mkdir -p $(dir $@)
endif
	@echo "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
ifeq ($(UNAME), Windows) 
#	@mkdir $(dir $@)  
#  Option -p inexistent in Windows, covered by default 
else
	@mkdir -p $(dir $@)
endif
	@echo "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(CFLAGS) -c -o $@ $<  

$(OBJ_DIR)/%.o: %.s
ifeq ($(UNAME), Windows) 
#	@mkdir $(dir $@)  
#  Option -p inexistent in Windows, covered by default 
else
	@mkdir -p $(dir $@)
endif
	@echo "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(ASFLAGS) -c -o $@ $<

run: $(TARGET_BIN)
	@echo "\033[01;33m==========  PROGRAMMATION  =================================\033[m"
	@st-flash write $< 0x8000000

size: $(TARGET_ELF)
	@echo "\033[01;33m==========  SIZE  ========================================\033[m"
	@$(SIZE) $<

clean:
	@echo "\033[01;41m-> SUPRESSION !\033[m"
	@rm -vf $(TARGET_BIN)
	@rm -vf $(TARGET_HEX)
	@rm -vf $(TARGET_LST)
	@rm -vf $(TARGET_ELF)
ifeq ($(UNAME), Windows) 
	@rm -vf $(OBJ_DIR)/*.o
else	
	@rm -vf $(SRC_DIR)/*~
endif

purge:
	@echo "\033[01;41m-> SUPRESSION !!\033[m"
	@rm -vRf $(OBJ_DIR)



help:
	@echo ""
	@echo "#==============================================================#"
	@echo "# Makefile for LimiFrog-0.x                                    #"
	@echo "#                                                              #"
	@echo "# Usage: make [options]                                        #"
	@echo "#                                                              #"
	@echo "#  options:                                                    #"
	@echo "#   build     compile complete project (with *.o)              #"
	@echo "#   run       program STM32 on the board                       #"
	@echo "#   size      show size of binary                              #"
	@echo "#   clean     erase files *.bin *.hex *.lst *.elf *~           #"
	@echo "#   purge     erase directory:   obj/                          #"
	@echo "#   help      show this help                                   #"
	@echo "#==============================================================#"
	@echo ""

#----------------------------------------------------------------------------------
