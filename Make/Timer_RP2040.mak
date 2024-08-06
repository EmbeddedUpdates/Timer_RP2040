#Component specific makefile for Timer_RP2040
$(info Executing: Components/Timer_RP2040/make/Timer_RP2040.mak)
#C files that should be compiled in this component
C_SOURCE_FILES += Components/Timer_RP2040/Source/Timer_RP2040.c

#include path for header files in this component
INCLUDE_PATH += $(ROOT_DIR)/Components/Timer_RP2040/Include

## Unity Test Framework
# define unit specific testing files here which will be compiled and executed first.
# These tests should be executed each build and only if they pass should the rest of build continue.

# we want to output the results of the test run to a file - if it passed, we can make a file:
# TIMER_RP2040_TEST.passed
# TIMER_RP2040_TEST.failed
# Then this file is used as a target of the overall build. If that file doesnt exist, we continue with
# tests but will fail for the overall app compilation.

# is there value for making a makefile for single module testing? Yes. Should we do that first? Yes.

