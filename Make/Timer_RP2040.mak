#Component specific makefile for Timer_RP2040
$(info Executing: Components/Timer_RP2040/make/Timer_RP2040.mak)
#C files that should be compiled in this component
C_SOURCE_FILES += Components/Timer_RP2040/Source/Timer_RP2040.c

#include path for header files in this component
INCLUDE_PATH += $(ROOT_DIR)/Components/Timer_RP2040/Include

