/* =========================================================================
    Unity - A Test Framework for C
    ThrowTheSwitch.org
    Copyright (c) 2007-24 Mike Karlesky, Mark VanderVoord, & Greg Williams
    SPDX-License-Identifier: MIT
========================================================================= */


/* #include "Timer_RP2040.h" */
#include "Timer_RP2040_Test.h"
#include "unity.h"

#pragma ab

void setUp(void)
{
  Timer_RP2040_Status = TIMER_RP2040_UNINIT;
  Timer_Live = Timer_Uninit;
}

/* 
  These are run after each test, so we want to make sure the global variable is 'UNINIT' 
  so that each test can behave as if its its own test. 
*/
void tearDown(void)
{

}

/* HELPER FUNCTIONS */

void printJustOneMember(unsigned int * member, char * memberName)
{
  printf("%s address: %#010x\n", memberName, member);
  printf("%s value: %#010x\n", memberName, *member);
}

void printTimerLive(void)
{
  printf("\n");
  printf("Timer_Live:\n");
  printJustOneMember((unsigned int *)&Timer_Live, "Timer_Live");
  printJustOneMember(&Timer_Live.TIMEHW, "Timer_Live_TIMEHW");
  printJustOneMember(&Timer_Live.TIMELW, "Timer_Live_TIMELW");
  printJustOneMember(&Timer_Live.TIMEHR, "Timer_Live_TIMEHR");
  printJustOneMember(&Timer_Live.TIMELR, "Timer_Live_TIMELR");
  printf("\n");
}

/* TESTS */

void test_Init_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_OK;
  retVal = Timer_RP2040_Init();

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* Reads for the TIMEHR and TIMELR  Registers */
void test_ReadLow_ReturnsOK( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeLow = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerLow(&timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_ReadHigh_ReturnsOK( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerHigh(&timeHigh);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_ReadLow_ReturnsInvalidParam_NullPointer( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32* timeLow = NULL;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerLow(timeLow);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_ReadHigh_ReturnsInvalidParam_NullPointer( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32* timeHigh = NULL;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerHigh(timeHigh);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_ReadLow_ProvidesValidResult( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeLow = 0;
  Timer_Live.TIMELR = 0xFACEBEEF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerLow(&timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, timeLow);
}

void test_ReadHigh_ProvidesValidResult( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0;
  Timer_Live.TIMEHR = 0xFACEBEEF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_ReadTimerHigh(&timeHigh);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, timeHigh);
}


/* Writes for the TIMEHR and TIMELR  Registers */
void test_WriteLow_ReturnsOK( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeLow = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_WriteTimerLow(timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_WriteHigh_ReturnsOK( void )
{ 
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_WriteTimerHigh(timeHigh);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_WriteLow_ProvidesValidResult( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeLow = 0xFACEBEEF;
  Timer_Live.TIMELW = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_WriteTimerLow(timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, Timer_Live.TIMELW);
}

void test_WriteHigh_ProvidesValidResult( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0xFACEBEEF;
  Timer_Live.TIMEHW = 0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_WriteTimerHigh(timeHigh);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, Timer_Live.TIMEHW);
}

void test_WriteTimer_ProvidesValidResultZero( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0x00000000;
  uint32 timeLow = 0x00000000;
  Timer_Live.TIMEHW = 0xFACEBEEF;
  Timer_Live.TIMELW = 0xDEADBEEF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_TimerWrite(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.TIMEHW);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.TIMELW);
}

void test_WriteTimer_ProvidesValidResultN( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0xFACEBEEF;
  uint32 timeLow = 0xDEADBEEF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_TimerWrite(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, Timer_Live.TIMEHW);
  TEST_ASSERT_EQUAL(0xDEADBEEF, Timer_Live.TIMELW);
}

void test_WriteTimer_ProvidesValidResultOnes( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0xFFFFFFFF;
  uint32 timeLow = 0xFFFFFFFF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  retVal = Timer_RP2040_TimerWrite(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFFFFFFFF, Timer_Live.TIMEHW);
  TEST_ASSERT_EQUAL(0xFFFFFFFF, Timer_Live.TIMELW);
}

void test_ReadTimer_FailsForInvalidPointer( void )
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 * badTimePointer = 0x00000000;
  retVal = Timer_RP2040_TimerRead(badTimePointer, badTimePointer);
  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_ReadTimer_ProvidesValidResultZero(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0xFFFFFFFF;
  uint32 timeLow = 0xFFFFFFFF;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.TIMELR = 0x0;
  Timer_Live.TIMEHR = 0x0;
  retVal = Timer_RP2040_TimerRead(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, timeHigh);
  TEST_ASSERT_EQUAL(0x0, timeLow);
}

void test_ReadTimer_ProvidesValidResultN(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0x0;
  uint32 timeLow = 0x0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.TIMELR = 0xFACEBEEF;
  Timer_Live.TIMEHR = 0xDEADFADE;
  retVal = Timer_RP2040_TimerRead(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, timeLow);
  TEST_ASSERT_EQUAL(0xDEADFADE, timeHigh);
}

void test_ReadTimer_ProvidesValidResultOnes(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  uint32 timeHigh = 0x0;
  uint32 timeLow = 0x0;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.TIMELR = 0xFFFFFFFF;
  Timer_Live.TIMEHR = 0xFFFFFFFF;
  retVal = Timer_RP2040_TimerRead(&timeHigh, &timeLow);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFFFFFFFF, timeLow);
  TEST_ASSERT_EQUAL(0xFFFFFFFF, timeLow);
}

/* Tests of the pause register */
void test_Pause_Pause(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_Pause();

  TEST_ASSERT_EQUAL(TIMER_PAUSE_SET, Timer_Live.PAUSE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Unpause_ReturnsOK(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_Unpause();

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Unpause_Unpause(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_Unpause();

  TEST_ASSERT_EQUAL(0x0, Timer_Live.PAUSE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* Make sure that Pause works on its own*/
void test_Pause_ReturnsOK(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_Pause();

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

