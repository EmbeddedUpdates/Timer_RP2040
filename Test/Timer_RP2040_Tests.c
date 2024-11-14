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
  printJustOneMember(&Timer_Live.ALARM0, "Timer_Live_ALARM0");
  printJustOneMember(&Timer_Live.ALARM1, "Timer_Live_ALARM1");
  printJustOneMember(&Timer_Live.ALARM2, "Timer_Live_ALARM2");
  printJustOneMember(&Timer_Live.ALARM3, "Timer_Live_ALARM3");
  printJustOneMember(&Timer_Live.INTS, "Timer_Live_INTS");
  printf("\n");
}

/* TESTS */

void test_Init_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_OK;
  retVal = Timer_RP2040_Init();

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Init_ReturnsOK_ClearsTIMEHRandTIMELR(void)
{
  Std_ErrorCode retVal = E_OK;
  retVal = Timer_RP2040_Init();

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x00000000, Timer_Live.TIMEHR);
  TEST_ASSERT_EQUAL(0x00000000, Timer_Live.TIMELR);
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

/* Alarm Reads */
void test_Alarm_CheckAlarm_0NotSet(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_CheckAlarmN(0x0);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_NOT_SET, retVal);
}

void test_Alarm_CheckAlarm_nNotSet(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  int i;

  for(i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = TIMER_RP2040_ALARM_FAILED;
    retVal = Timer_RP2040_CheckAlarmN(i);
    TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_NOT_SET, retVal);
  }
}

void test_Alarm_CheckAlarm_0Set(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.ALARM0 = 0xFACEBEEF;
  Timer_Live.ARMED =  0x00000001;

  retVal = Timer_RP2040_CheckAlarmN(0x0);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_SET_NOT_TRIGGERED, retVal);
}

void test_Alarm_CheckAlarm_nSet(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.ALARM0 = 0xABCD1234;
  Timer_Live.ALARM1 = 0x00000001;
  Timer_Live.ALARM2 = 0xFFFFFFFF;
  Timer_Live.ALARM3 = 0xCACACACA;
  Timer_Live.ARMED =  0x0000000F;
  int i;

  for( i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = TIMER_RP2040_ALARM_FAILED;
    retVal = Timer_RP2040_CheckAlarmN(i);
    TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_SET_NOT_TRIGGERED, retVal);
  }
}

void test_Alarm_CheckAlarm_0Triggered(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  /* 
    This is an assumption that the ALARM is set to 0 when 
    the interrupt is serviced
  */
  
  Timer_Live.ALARM0 = 0x0;
  Timer_Live.INTS = 0x00000001;

  retVal = Timer_RP2040_CheckAlarmN(0x0);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_TRIGGERED, retVal);
}

void test_Alarm_CheckAlarm_nTriggered(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  int i;

  /* 
    This is an assumption that the ALARM is set to 0 when 
    the interrupt is serviced
  */
  
  Timer_Live.ALARM0 = 0x0;
  Timer_Live.ALARM1 = 0x0;
  Timer_Live.ALARM2 = 0x0;
  Timer_Live.ALARM3 = 0x0;
  Timer_Live.INTS = 0x0000000F;

  for( i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = TIMER_RP2040_ALARM_FAILED;
    retVal = Timer_RP2040_CheckAlarmN(i);
    TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_TRIGGERED, retVal);
  }
}

void test_Alarm_CheckAlarm_InvalidIndex(void)
{
  /* Set the module to Init */
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_NOT_SET;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_CheckAlarmN(0x4);
  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_FAILED, retVal);

  retVal = Timer_RP2040_CheckAlarmN(0xFF);
  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_FAILED, retVal);

}

/* Alarm Writes */
void test_Alarm_SetAlarm0_With0_Fails(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_ArmAlarmN(0, ZERO32);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_Alarm_SetAlarm0_WithN(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_ArmAlarmN(0, 0xFACEBEEF);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Alarm_SetAlarm0_WithOnes(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_ArmAlarmN(0, 0xFFFFFFFF);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Alarm_SetAlarmN_With0_Fails(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  int i;

  for( i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = E_NOT_OK;
    retVal = Timer_RP2040_ArmAlarmN(i, 0x0);
    TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
  }

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_Alarm_SetAlarmN_WithN(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  int i;

  for( i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = E_NOT_OK;
    retVal = Timer_RP2040_ArmAlarmN(i, 0xFACEBEEF);
    TEST_ASSERT_EQUAL(E_OK, retVal);

    TEST_ASSERT_EQUAL(0xFACEBEEF, *(&Timer_Live.ALARM0 + i));
  }

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Alarm_SetAlarmN_WithOnes(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  int i;

  for( i = 0; i <= ALARM_MAX_INDEX; i++)
  {
    retVal = E_NOT_OK;
    retVal = Timer_RP2040_ArmAlarmN(i, 0xFFFFFFFF);
    TEST_ASSERT_EQUAL(E_OK, retVal);

    TEST_ASSERT_EQUAL(0xFFFFFFFF, *(&Timer_Live.ALARM0 + i));
  }

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Alarm_SetAlarmN_InvalidIndex_Fails(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x4;

  retVal = Timer_RP2040_ArmAlarmN(alarmIndex, 0xFFFFFFFF);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}


/* Alarm disarm */
void test_Alarm_DisarmAlarm_0WasNotSetStillNotSet(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x0;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM0);
  /* ARMED is never set to 1 since that is done in the hardware when writing to the ALARM register */
  /* ARMED should be 0x1 due to hardware, then written to  in hardware it would be 0x0 */
  /* So it is not easy to test the "ARMED" register behavior here */
  /* TEST_ASSERT_EQUAL(0x1, Timer_Live.ARMED); */
}

void test_Alarm_DisarmAlarm_0WasSetIsNotSet(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x0;

  Timer_Live.ALARM0 = 0xFACEBEEF;
  Timer_Live.ARMED = 0x1;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM0);
  /* ARMED is not checked because that is hadnled in hardware cirtcuit*/
}

void test_Alarm_DisarmAlarm_nWasNotSetStillNotSet(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x1;

  Timer_Live.ALARM0 = 0xFACEBEEF;
  Timer_Live.ALARM1 = 0x0;
  Timer_Live.ARMED = 0x1;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM1);
  /* ARMED is not checked because that is hadnled in hardware cirtcuit*/
}

void test_Alarm_DisarmAlarm_nWasSetIsNotSet(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x1;

  Timer_Live.ALARM0 = 0xFACEBEEF;
  Timer_Live.ALARM1 = 0xFACEBEEF;
  Timer_Live.ARMED = 0x3;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM1);
  /* ARMED is not checked because that is hadnled in hardware cirtcuit*/
}

void test_Alarm_DisarmAlarm_0WasNotSetStillNotSet_nNotTouched(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x0;

  Timer_Live.ALARM0 = 0x0;
  Timer_Live.ALARM1 = 0xFACEBEEF;
  Timer_Live.ARMED = 0x2;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM0);
  TEST_ASSERT_EQUAL(0xFACEBEEF, Timer_Live.ALARM1);
  /* ARMED is not checked because that is hadnled in hardware cirtcuit*/
}

void test_Alarm_DisarmAlarm_0WasSetIsNotSet_nNotTouched(void)
{
  /* Set the module to Init */
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint8 alarmIndex = 0x0;

  Timer_Live.ALARM0 = 0xFACEBEEF;
  Timer_Live.ALARM1 = 0xFACEBEEF;
  Timer_Live.ARMED = 0x3;

  retVal = Timer_RP2040_DisarmAlarmN(alarmIndex);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x0, Timer_Live.ALARM0);
  TEST_ASSERT_EQUAL(0xFACEBEEF, Timer_Live.ALARM1);
  /* ARMED is not checked because that is hadnled in hardware cirtcuit*/
}

/* TIMERAW reads */
void test_TIMERAW_ReadTIMERAWL_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 time; 

  retVal = Timer_RP2040_TimerRead32(&time);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_TIMERAW_ReadTIMERAWL_ReturnsOKWithN(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 time; 

  Timer_Live.TIMERAWL = 0xFACEBEEF;

  retVal = Timer_RP2040_TimerRead32(&time);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFACEBEEF, time);
}

/* INTR */ /* INTR is Raw Interrupts - this must be written to to service an interrupt */
void test_Interrupt_InterruptClear_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptClearN(0x0);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* INTR */ /* INTR is Raw Interrupts - this must be written to to service an interrupt */
void test_Interrupt_InterruptClear_ReturnsInvalidParam(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptClearN(0x4);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_Interrupt_InterruptClear_ClearsInterrupt(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  Timer_Live.INTR = 0x0000000;
  retVal = Timer_RP2040_InterruptClearN(0x0);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x1, Timer_Live.INTR);
}

void test_Interrupt_InterruptClear_ClearsInterruptDoesNotClearOthers(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  Timer_Live.INTR = 0x9;
  retVal = Timer_RP2040_InterruptClearN(0x0);

  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x9, Timer_Live.INTR);
}

/* INTE */ /* INTE is Interrupt Enable Mask */
void test_Interrupt_InterruptEnable_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x00000001;

  retVal = Timer_RP2040_InterruptEnable(bmp_intMask);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptEnable_EnablesInterrupt(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x00000001;

  retVal = Timer_RP2040_InterruptEnable(bmp_intMask);

  TEST_ASSERT_EQUAL(0x1, Timer_Live.INTE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptEnable_EnablesInterruptWithoutTouchingOthers(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x1;
  Timer_Live.INTE = 0x2;

  retVal = Timer_RP2040_InterruptEnable(bmp_intMask);

  TEST_ASSERT_EQUAL(0x3, Timer_Live.INTE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptDisable_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x00000001;

  retVal = Timer_RP2040_InterruptDisable(bmp_intMask);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptDisable_DisablesInterrupt(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x00000001; /* disable int0 */
  Timer_Live.INTE = 0x00000001; /* int0 is enabled */

  retVal = Timer_RP2040_InterruptDisable(bmp_intMask);

  TEST_ASSERT_EQUAL(0x00000000, Timer_Live.INTE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptDisable_DisablesInterruptWithoutTouchingOthers(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  uint32 bmp_intMask = 0x00000001; /* int 0 should become disabled */

  Timer_Live.INTE = 0x00000003; /* int 0 and 1 is enabled */

  retVal = Timer_RP2040_InterruptDisable(bmp_intMask);


  TEST_ASSERT_EQUAL(0x00000002, Timer_Live.INTE);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* INTF */ /* INTF is Interrupt Force - we can write to this to trigger the interrupt */
void test_Interrupt_InterruptTrigger_ReturnsOK(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptNTrigger(0x0);

  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptTrigger_ReturnsInvalidParam(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptNTrigger(0x4);
  retVal |= Timer_RP2040_InterruptNTrigger(0xF);
  retVal |= Timer_RP2040_InterruptNTrigger(0xF);

  TEST_ASSERT_EQUAL(E_INVALID_PARAM, retVal);
}

void test_Interrupt_InterruptTrigger_SetsInterrupt(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptNTrigger(0x0);

  TEST_ASSERT_EQUAL(Timer_Live.INTF, 0x1);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_Interrupt_InterruptTrigger_SetsInterruptWithoutTouchingOthers(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.INTF = 0x2;

  retVal = Timer_RP2040_InterruptNTrigger(0x0);

  TEST_ASSERT_EQUAL(Timer_Live.INTF, 0x3);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* INTS */ /* INTS is a read only register - for polling use case */
void test_Interrupt_InterruptCheck_ReturnsFailed(void)
{
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;

  retVal = Timer_RP2040_InterruptNStatusCheck(0x4);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_FAILED, retVal);
}

void test_Interrupt_InterruptCheck_IsSet(void)
{
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.INTS = 0x1;

  retVal = Timer_RP2040_InterruptNStatusCheck(0x0);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_TRIGGERED, retVal);
}

void test_Interrupt_InterruptCheck_IsNotSet(void)
{
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;
  Timer_RP2040_Status = TIMER_RP2040_INIT;
  Timer_Live.INTS = 0x1;

  retVal = Timer_RP2040_InterruptNStatusCheck(0x1);

  TEST_ASSERT_EQUAL(TIMER_RP2040_ALARM_NOT_SET, retVal);
}



