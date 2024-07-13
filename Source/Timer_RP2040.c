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
  /* Empty Function Stub */
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
  /* Empty Function Stub */
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
static Std_ErrorCode Timer_RP2040_ReadTimerLow (  uint32 *  TimerLow )
{
  /* Empty Function Stub */
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
static Std_ErrorCode Timer_RP2040_ReadTimerHigh (  uint32 *  TimerHigh )
{
  /* Empty Function Stub */
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
static Std_ErrorCode Timer_RP2040_WriteTimerLow (  uint32  TimerLow )
{
  /* Empty Function Stub */
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
static Std_ErrorCode Timer_RP2040_WriteTimerHigh (  uint32  TimerHigh )
{
  /* Empty Function Stub */
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
  /* Empty Function Stub */
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
  /* Empty Function Stub */
}


/**
 * Enables interrupts for the ALARMS given by the bitmask parameter.
 * @param int_bitmask: Bitmask for which interrupts should be enabled. Acceptable values are between (and including) 1d (0b0001) and 15d (0b1111)
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
Std_ErrorCode Timer_RP2040_InterruptEnable (  uint8  int_bitmask )
{
  /* Empty Function Stub */
}


/**
 * Disables interrupts for the ALARMS given by the bitmask parameter.
 * @param int_bitmask: Bitmask for which interrupts should be disabled. Acceptable values are between (and including) 1d (0b0001) and 15d (0b1111)
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
Std_ErrorCode Timer_RP2040_InterruptDisable (  uint8  int_bitmask )
{
  /* Empty Function Stub */
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
  /* Empty Function Stub */
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
  /* Empty Function Stub */
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
  /* Empty Function Stub */
}


/**
 * Reads the timer from TIMER_TIMERAWL - stores the result in the buffer provided.
 * @param alarmIndex: Index of Alarm to be disarmed, must be within range [0:3].
 *
 * @return 
 *         0: if the alarm is not triggered.
 *         1: if the alarm is triggered.
 *
 * @pre n/a
 * @post n/a
 * @invariant n/a
 *
 */
uint8 Timer_RP2040_CheckAlarmN (  uint8  alarmIndex )
{
  /* Empty Function Stub */
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


