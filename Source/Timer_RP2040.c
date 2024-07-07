
/**
 * @file Timer_RP2040.c
 * @author pflaherty
 * @date 06.23.2024
 * @brief Timer_RP2040 initializes, manages, and clears 
 * 
 * COMPONENT: 
 * VERSION: 
 *
 * Change History
 * 
 */


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
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  LOCAL FUNCTIONS
************************************************************/

/**
 * BRIEF: Pauses the RP2040 Timer
 * DESC: Writes to the TIMER_PAUSE register, reports OK is Timer is paused.
 *       Reports NOT_OK if the timer did not pause
 * 
 * RETURN: 
 *         0: 'OK' if the Timer becomes paused
 *         1: 'NOT_OK' if the timer is not paused
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: Timer is enabled. Timer is not paused.
 * POSTCONDITIONS: Timer is paused. 
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_Pause ( void )
{
}

/**
 * BRIEF: Unpauses the RP2040 Timer
 * DESC: Writes to the TIMER_PAUSE register, reports OK is Timer is unpaused.
 *       Reports NOT_OK if the timer did not pause
 * 
 * RETURN: 
 *         0: 'OK' if the Timer becomes paused
 *         1: 'NOT_OK' if the timer is not paused
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: Timer is enabled. Timer is paused.
 * POSTCONDITIONS: Timer is running.
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_Unpause( void )
{

}

/**
 * BRIEF: Read lower word of the timer register
 * DESC: Reads from TIMER_TIMELR. Reports bits {31:0} of the timer value and stores it in TimerLow param.
 * 
 * PARAM: TimerLow - buffer to store the value of the timer
 * 
 * RETURN: 
 *         0: 'OK' if the Timer can be read
 *         1: 'NOT_OK' if the timer read fails
 *         2: 'INVALID_PARAM' if the provided buffer is null
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: None
 * POSTCONDITIONS: None
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_ReadTimerLow ( uint32 * TimerLow )
{

}

/**
 * BRIEF: Read Upper word from the timer. Stores to provided buffer.
 * DESC: Reads from TIMER_TIMERAWH. Stores bits {63:32} to the provided buffer.
 * 
 * PARAM: TimerHigh - buffer to store the value of the timer
 * 
 * RETURN: 
 *         0: 'OK' if the Timer can be read
 *         1: 'NOT_OK' if the timer read fails
 *         2: 'INVALID_PARAM' if the provided buffer is null
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: None
 * POSTCONDITIONS: None
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_ReadTimerHigh ( uint32 * TimerHigh )
{

}

/**
 * BRIEF: Stores the provided value to the lower 32 bits of the timer
 * DESC: Stores to TIMER_TIMELW
 * 
 * PARAM: TimerLow - buffer to store the value of the timer
 * 
 * RETURN: 
 *         0: 'OK' if the value can be stored
 *         1: 'NOT_OK' if the timer write fails
 *         2: 'INVALID_PARAM' if the provided buffer is null
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: None
 * POSTCONDITIONS: None
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_SetTimerLow ( uint32 * TimerLow )
{

}

/**
 * BRIEF: Stores the provided value to the higher 32 bits of the timer
 * DESC: Stores to TIMER_TIMEHW
 * 
 * PARAM: TimerHigh - buffer to store the value of the timer
 * 
 * RETURN: 
 *         0: 'OK' if the value can be stored
 *         1: 'NOT_OK' if the timer write fails
 *         2: 'INVALID_PARAM' if the provided buffer is null
 *         3: 'MODULE_UNINIT' if the timer is not yet initialized.
 * 
 * PRECONDITIONS: None
 * POSTCONDITIONS: None
 * INVARIANTS: None
 * 
 */
static Std_ErrorCode Timer_RP2040_SetTimerHigh ( uint32 * TimerHigh )
{

}


/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

/**
 * Initializes the Timer module, and arms Alarm0
 */
Std_ErrorCode Timer_RP2040_Init ( void )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Pauses the Timer, Resets the Timer, Disarms all alarms.
 */
Std_ErrorCode Timer_RP2040_Deinit ( void )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Enables Interrupts for the timer - Should be used with care
 */
Std_ErrorCode Timer_RP2040_InterruptEnable ( void )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Disables Interrupts for the timer - Should be used with care
 */
Std_ErrorCode Timer_RP2040_InterruptDisable ( void )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Stores the current timer value into the two provided uint32 buffers
 */
Std_ErrorCode Timer_RP2040_ReadTimer ( uint32 * TimerHigh, uint32 * TimerLow )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Loads the provided uint32 buffers into the Timer counter
 */
Std_ErrorCode Timer_RP2040_SetTimer ( uint32 * TimerHigh, uint32 * TimerLow )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Reports 'True' if the alarm has been triggered, False if not
 */
Std_ErrorCode Timer_RP2040_CheckAlarm ( uint8 n )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Enables the Alarm
 */
Std_ErrorCode Timer_RP2040_SetAlarm ( uint8 n )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

/**
 * Disarms the alarm
 */
Std_ErrorCode Timer_RP2040_DisarmAlarm ( uint8 n )
{
  Std_ErrorCode retVal = NOT_OK;
  return retVal;
}

