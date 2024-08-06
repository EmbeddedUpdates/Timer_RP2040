/* =========================================================================
    Unity - A Test Framework for C
    ThrowTheSwitch.org
    Copyright (c) 2007-24 Mike Karlesky, Mark VanderVoord, & Greg Williams
    SPDX-License-Identifier: MIT
========================================================================= */


#include "Timer_RP2040.h"
#include "unity.h"

#pragma ab

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{
}

void test_Init_ReturnsOK(void)
{
  /* All of these should pass */
  Std_ErrorCode retVal = E_OK;
  retVal = Timer_RP2040_Init();

  TEST_ASSERT_EQUAL(E_OK, retVal);
}
