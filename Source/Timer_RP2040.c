/**
 * 
* @file "Timer_RP2040.c"
* @author Madrick3
* @brief Provides a global timebase for software through the generation of a global microsecond timebase. The timebase relies
* on a  one microsend reference that is generated in the watchdog, and is derived from the reference clock (REFCLK).
* A 64-bit timer is managed, and is not able to overflow on it's own - thoughtful use of the module provides
* completely monotic use in practice, although setting the time to a specific large value like 0xFFFFFFFF will result
* in overflow. Otherwise, the module initializes, manages, and clears the timer, also manages the alarms which may
* trigger interrupts.
* 
* @COMPONENT: TIMER_RP2040
* @VERSION: 00.01.00 
*/
/************************************************************
  Version History
  -----------------------------------------------------------
  Revision |  Author   |  Change ID  |  Description
  00.00.00 |  AUTHOR   |  DRAFT      |  Initial Creation
************************************************************/

/************************************************************
  DEFINES
************************************************************/

/************************************************************
  INCLUDES
************************************************************/
#include "Timer_RP2040.h"


/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  LOCAL VARIABLES
************************************************************/
static tTimer_RP2040_Status Timer_RP2040_Status = TIMER_RP2040_UNINIT;

/************************************************************
  LOCAL FUNCTIONS
************************************************************/

/**
 * Writes to the TIMER_PAUSE register, reports E_OK if Timer is paused. Reports E_NOT_OK if the timer did not pause.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_Pause ( void )
{
  Std_ErrorCode retVal = E_OK;

  /* No prechecks are performed for the write - so that the pause may be performed even during init */


  /* if pre-checks are performed, lets do the actual pause. */
  if( E_OK == retVal )
  {
    *TIMER_REG_PAUSE = (TIMER_PAUSE_MASK & TIMER_PAUSE_SET);
  }

  /* Check to see if the timer is paused - if it is, return ok, otherwise report notok */
  if( E_OK == retVal )
  {
    if( TIMER_PAUSE_SET != (*TIMER_REG_PAUSE & TIMER_PAUSE_MASK) )
    {
      /* Timer was not paused - report an error. */
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}

/**
 * Writes to the TIMER_PAUSE register, reports OK if Timer is unpaused. Reports NOT_OK if the timer did not unpause.
 * There is possible room for improvement here in reporting E_NOT_OK in the case that the timer was not paused already.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_Unpause ( void )
{
  Std_ErrorCode retVal = E_OK;

  /* No prechecks are performed for the write - so that the unpause may be performed even during init */


  /* if pre-checks are performed, lets do the actual unpause. */
  if( E_OK == retVal )
  {
    *TIMER_REG_PAUSE = (TIMER_PAUSE_MASK & TIMER_PAUSE_CLR);
  }

  /* Check to see if the timer is unpaused - if it is, return ok, otherwise report notok */
  if( E_OK == retVal )
  {
    if( TIMER_PAUSE_CLR != (*TIMER_REG_PAUSE & TIMER_PAUSE_MASK) )
    {
      /* Timer is paused - report an error. */
      retVal = E_NOT_OK;
    }
  }
  
  return retVal;
}

/**
 * Reads from TIMER_TIMELR register. Reports bits {31:0} in the out buffer 'TimerLow'.
 * @param TimerLow: Output buffer for TIMEL read
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_ReadTimerLow ( uint32 * TimerLow )
{
  Std_ErrorCode retVal = E_OK;

  /* Check the input parameter is a reasonable address */
  if( NULL == TimerLow )
  {
    retVal = E_INVALID_PARAM;
  }

  /* Confirm that the module has been initialized already - otherwise report error */
  if( Timer_RP2040_Status != TIMER_RP2040_INIT )
  {
    retVal = E_MODULE_UNINIT;
  }

  /* if pre-checks are performed, read from the register. */
  if( E_OK == retVal )
  {
    *TimerLow = *TIMER_REG_TIMELR;
  }

  /* No post-checks are considered for this read. */
  
  return retVal;
}

/**
 * Reads from TIMER_TIMEHR register. Reports bits {63:32} in the out buffer 'TimerHigh'.
 * @param TimerHigh: Output buffer for TIMEH read
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_ReadTimerHigh ( uint32 * TimerHigh )
{
  Std_ErrorCode retVal = E_OK;

  /* Check the input parameter is a reasonable address */
  if( NULL == TimerHigh )
  {
    retVal = E_INVALID_PARAM;
  }

  /* Confirm that the module has been initialized already - otherwise report error */
  if( Timer_RP2040_Status != TIMER_RP2040_INIT )
  {
    retVal = E_MODULE_UNINIT;
  }

  /* if pre-checks are performed, read from the register. */
  if( E_OK == retVal )
  {
    *TimerHigh = *TIMER_REG_TIMEHR;
  }

  /* No post-checks are considered for this read. */
  
  return retVal;
}

/**
 * Writes to TIMER_TIMELW register. Does not perform input checking
 * @param TimerLow: Input word for TIMEL write
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_WriteTimerLow ( uint32 TimerLow )
{
  Std_ErrorCode retVal = E_OK;

  /* No prechecks are performed for the write - so that the write may be performed even during init */

  /* if pre-checks are performed, write to the register. */
  if( E_OK == retVal )
  {
    *TIMER_REG_TIMELW = TimerLow;
  }

  /* No post-checks are considered for this write . */
  
  return retVal;
}

/**
 * Writes to TIMER_TIMEHW register. Does not perform input checking.
 * @param TimerHigh: Input word for TIMEH read
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
static Std_ErrorCode Timer_RP2040_WriteTimerHigh ( uint32 TimerHigh )
{
  Std_ErrorCode retVal = E_OK;

  /* No prechecks are performed for the write - so that the write may be performed even during init */

  /* if pre-checks are performed, write to the register. */
  if( E_OK == retVal )
  {
    *TIMER_REG_TIMEHW = TimerHigh;
  }

  /* No post-checks are considered for this write . */
  
  return retVal;
}



/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

/**
 * Initializes the RP2040  timer. Prepares ALARM0 for 1ms triggeers. Will fail if the tick generation is not yet initialized.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful
 *
 * @pre  Tick generation is already started in the watchdog module. 
 * @post  ALARM0 is armed. 
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_Init ( void )
{
  Std_ErrorCode retVal = E_OK;

  /* Implement pre-check with the RP2040 Watchdog */
  if( WATCHDOG_RP2040_INIT != Watchdog_RP2040_IsInit())
  {
    retVal = E_NOT_OK;
  }

  /* First lets pause and clear the timer */
  if( E_OK == retVal ){
    retVal = Timer_RP2040_Pause();
    if( E_OK == retVal ){
      retVal = Timer_RP2040_TimerWrite(ZERO32, ZERO32);
    }
  }

  /* Now, lets prepare an alarm */
  if( E_OK == retVal ){
    /* Sets alarm0 for 1000us (1ms) */
    retVal = Timer_RP2040_ArmAlarmN(ALARM0_INDEX, 1000);
  }

  /* First lets unpause the timer */
  if( E_OK == retVal ){
    retVal = Timer_RP2040_Unpause();
  }

  /* If everything was successful, lets update the init status. */
  if( E_OK == retVal ){
    Timer_RP2040_Status = TIMER_RP2040_INIT;
  }

  return retVal;
}


/**
 * Deinitializes the timer software module. Disables all alarms, Pauses the timer register, but does not reset the timer.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre Timer module was previously enabled.
 * @post Alarms are all disabeled, Timer is paused.
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_Deinit ( void )
{
  Std_ErrorCode retVal = E_OK;

  /* Check that the module was previously init */
  if( TIMER_RP2040_INIT != Timer_RP2040_Status )
  {
    retVal = E_MODULE_UNINIT;
  }

  /* Pause the timer */
  if( E_OK == retVal )
  {
    retVal = Timer_RP2040_Pause();
  }

  /* Disable all alarms */
  if( E_OK == retVal )
  {
    /* Disable all 4 possible alarms */
    /* Possible improvement to provide 'DisableAllAlarms' API or 'DisableAlarmBitmask' API */
    retVal |= Timer_RP2040_DisarmAlarmN(ALARM0_INDEX);
    retVal |= Timer_RP2040_DisarmAlarmN(ALARM1_INDEX);
    retVal |= Timer_RP2040_DisarmAlarmN(ALARM2_INDEX);
    retVal |= Timer_RP2040_DisarmAlarmN(ALARM3_INDEX);
  }

  /* Disable all interrupts */
  if( E_OK == retVal )
  {
    /* Disable all 4 possible alarms */
    retVal |= Timer_RP2040_InterruptDisable( TIMER_RP2040_ALLALARMS_BITMASK );
  }

  /* Change module status */
  if( E_OK == retVal )
  {
    Timer_RP2040_Status = TIMER_RP2040_UNINIT;
  }

  return retVal;

}


/**
 * Enables interrupts for the ALARMS given by the bitmask parameter.
 * @param bmp_intEnable: bitmap for which interrupts should be enabled. Acceptable values are between (and including) 1d (0b0001) and 15d (0b1111)
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre Timer module was previously enabled.
 * @post Interrupts are enabled.
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_InterruptEnable (  uint32 bmp_intEnable )
{
  Std_ErrorCode retVal = E_OK;
  
  /* Check that the module was previously init */
  if( TIMER_RP2040_INIT != Timer_RP2040_Status )
  {
    retVal = E_MODULE_UNINIT;
  }

  /* 
    a value greater than '15' would be invalid. 
    acceptable range: [0b0001-0b1111]  
  */
  if( bmp_intEnable > TIMER_RP2040_ALLINTERRUPTS_BITMASK ){
    retVal = E_INVALID_PARAM;
  }

  /* input parameter is a bitmap, zero would do nothing. */
  if( bmp_intEnable == 0 ){
    retVal = E_INVALID_PARAM;
  }

  /* Write to the INTE register with the bitmask */
  if( E_OK == retVal )
  {
    *TIMER_REG_INTE = bmp_intEnable;
  }

  return retVal;
}


/**
 * Disables interrupts for the ALARMS given by the bitmask parameter.
 * @param bmp_intDisable: bitmap for which interrupts should be disabled. Acceptable values are between (and including) 1d (0b0001) and 15d (0b1111)
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre Timer module was previously enabled.
 * @post Interrupts are disabled.
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_InterruptDisable (  uint8  bmp_intDisable )
{
  Std_ErrorCode retVal = E_OK;
  
  /* Check that the module was previously init */
  if( TIMER_RP2040_INIT != Timer_RP2040_Status )
  {
    retVal = E_MODULE_UNINIT;
  }

  /* 
    a value greater than '15' would be invalid. 
    acceptable range: [0b0001-0b1111]  
  */
  if( bmp_intDisable > TIMER_RP2040_ALLINTERRUPTS_BITMASK ){
    retVal = E_INVALID_PARAM;
  }

  /* input parameter is a bitmap, zero would do nothing. */
  if( bmp_intDisable == 0 ){
    retVal = E_INVALID_PARAM;
  }

  /* Write to the INTE register with the bitmask */
  if( E_OK == retVal )
  {
    /* bitmap must be inverted to write '0' to disable. */
    *TIMER_REG_INTE = (~(bmp_intDisable));
  }

  return retVal;
}


/**
 * Reads 64 bit timer and reports the data back in two 32 bit values (high and low)
 * @param TimerHigh: Pointer to where timer bits [63:32] will be stored.
 * @param TimerLow: Pointer to where timer bits [31:0] will be stored.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_TimerRead (  uint32 *  TimerHigh,  uint32 *  TimerLow )
{
  Std_ErrorCode retVal = E_OK;

  /* Check the input parameter is a reasonable address */
  if( (NULL == TimerHigh) || (NULL == TimerLow))
  {
    retVal = E_INVALID_PARAM;
  }

  /* module does not need to be init for reads. No init-check performed. */

  /* Perform both reads independently */
  if( E_OK == retVal)
  {
    /* Must read TIMELR before TIMEHR */
    retVal |= Timer_RP2040_ReadTimerLow(TimerLow);
    retVal |= Timer_RP2040_ReadTimerHigh(TimerHigh);
  }

  return retVal;
}


/**
 * Writes 64 bit timer values to the timer utilizing two 32 bit integers.
 * @param TimerHigh: Pointer to where timer bits [63:32] will be loaded from.
 * @param TimerLow: Pointer to where timer bits [31:0] will be loaded from.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_TimerWrite (  uint32 *  TimerHigh,  uint32 *  TimerLow )
{
  Std_ErrorCode retVal = E_OK;

  /* Check the input parameter is a reasonable address */
  if( (NULL == TimerHigh) || (NULL == TimerLow))
  {
    retVal = E_INVALID_PARAM;
  }

  /* module does not need to be init for writes. No init-check performed. */

  /* Perform both writes independently */
  if( E_OK == retVal)
  {
    /* Must write to TIMELW before TIMEHW */
    retVal |= Timer_RP2040_WriteTimerLow(TimerLow);
    retVal |= Timer_RP2040_WriteTimerHigh(TimerHigh);
  }

  return retVal;
}


/**
 * Reads the timer from TIMER_TIMERAWL - stores the result in the buffer provided.
 * @param TimerLow: Pointer to where timer bits [31:0] will be stored.
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_TimerRead32 (  uint32 *  TimerLow )
{
  Std_ErrorCode retVal = E_OK;

  /* Check to make sure pointer won't cause an exception */
  if( NULL == TimerLow )
  {
    retVal = E_INVALID_PARAM;
  }

  if( E_OK == retVal )
  {
    /* read only from RAW-L register. No side-effects.*/
    *TimerLow = *TIMER_REG_TIMERAWL;
  }

  return retVal;
}


/**
 * Reads the timer from TIMER_TIMERAWL - stores the result in the buffer provided.
 * @param alarmIndex: Index of Alarm to be checked, must be within range [0:3].
 *
 * @return 
 *         0: if the alarm is has been triggered.
 *         1: if the alarm is set.
 *         0xFF: if there was an issue in processing the request
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
tTimer_RP2040_AlarmStatus Timer_RP2040_CheckAlarmN ( uint8 alarmIndex )
{
  tTimer_RP2040_AlarmStatus retVal = TIMER_RP2040_ALARM_FAILED;

  /* First check the alarm index is in a reasonable range */
  if( alarmIndex <= ALARM_MAX_INDEX )
{
    /* Assume the alarm is not set. */
    retVal = TIMER_RP2040_ALARM_NOT_SET;
  }

  /* If the alarm index is ok - lets read from the relevant alarm register to see the status */
  if( retVal != TIMER_RP2040_ALARM_FAILED )
  {
    /* if the alarm is zero,*/
    if( ZERO32 == *TIMER_REG_ALARMn(alarmIndex) )
    {
      /* here, we may have triggered the alarm already, so the interrupt must be checked. */
      if( ZERO32 != (*TIMER_REG_INTS && (INT_TO_BITMAP(alarmIndex))) )
      {
        /* 00 !=  (0b0001 && (0b0001)) -> Interrupt is set. */
        retVal = TIMER_RP2040_ALARM_TRIGGERED;
      }
    }
    else
    {
      /* If there is a value in the alarm register, we know its not yet been triggered. */
      retVal = TIMER_RP2040_ALARM_SET_NOT_TRIGGERED;
    }
  }

  /* 
    There is an interesting case where the alarm is set and the interrupt is set. This seems problematic in use,
    but could be considered here. 
  */

  return retVal;
}


/**
 * Writes to the TIMER_ARMED register to disarm the alarm indicated by the 'alarmIndex'.
 * @param alarmIndex: Index of Alarm to be checked, must be within range [0:3].
 *
 * @return 
 *         0: 'E_OK' if successful 
 *         1: 'E_NOT_OK' if the operation is not successful 
 *         2: 'E_PARAM' if the input parameter is not valid 
 *         3: 'E_MODULE_UNINIT' if the timer is not yet initialized
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
Std_ErrorCode Timer_RP2040_DisarmAlarmN (  uint8  alarmIndex )
{
  /* Empty Function Stub */
}


