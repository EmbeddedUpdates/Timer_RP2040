/**
 * 
* @file "Timer_RP2040.h"
* @author Madrick3
* @brief Provides a global timebase for software through the generation of a global microsecond timebase. The timebase relies
* on a  one microsend reference that is generated in the watchdog, and is derived from the reference clock (REFCLK).
* A 64-bit timer is managed, and is not able to overflow on it's own - thoughtful use of the module provides
* completely monotic use in practice, although setting the time to a specific large value like 0xFFFFFFFF will result
* in overflow. Otherwise, the module initializes, manages, and clears the timer, also manages the alarms which may
* trigger interrupts.
* 
* @COMPONENT: TIMER_RP2040
* @VERSION: 01.01.00 
*/
/************************************************************
  Version History
  -----------------------------------------------------------
  Revision |  Author   |  Change ID  |  Description
  01.01.00 |  Madrick3 |  Skeleton   |  Initial Creation
************************************************************/

/************************************************************
  DEFINES
************************************************************/

#define ALARM0_INDEX 0
#define ALARM1_INDEX 1
#define ALARM2_INDEX 2
#define ALARM3_INDEX 3
#define ALARM_MAX_INDEX ALARM3_INDEX

#define TIMER_RP2040_ALLALARMS_BITMASK 0x0000000F
#define TIMER_RP2040_ALLINTERRUPTS_BITMASK TIMER_RP2040_ALLALARMS_BITMASK

#if !defined( VIRTUAL_TARGET )
#define TIMER_RP2040_LOCAL static
#else
#define TIMER_RP2040_LOCAL 
#endif

/************************************************************
  INCLUDES
************************************************************/
#include "Platform_Types.h"
#include "Timer_RP2040_SFR.h"
#include "Watchdog_RP2040.h"

/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/* ENUM for tracking the init status of the module. */
typedef enum Timer_RP2040_Status_Tag {
  TIMER_RP2040_UNINIT = 0,
  TIMER_RP2040_INIT = 1,
  TIMER_RP2040_INVALID = 0xFF
} tTimer_RP2040_Status;

/* Check alarm status results - useful for polling mode where we want to see if an alarm has been triggered */
typedef enum Timer_RP2040_AlarmStatus_Tag {
  /* Alarm not set and Interrupt not set */
  TIMER_RP2040_ALARM_NOT_SET =           0,
  /* Alarm set and Interrupt not set */
  TIMER_RP2040_ALARM_SET_NOT_TRIGGERED = 1,
  /* Interrupt flag for alarm is set */
  TIMER_RP2040_ALARM_TRIGGERED =         2,
  /* Something has gone wrong or an invalid request was made */
  TIMER_RP2040_ALARM_FAILED =            0xFF
} tTimer_RP2040_AlarmStatus;

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

/**
 * Initializes the timer module for a basic runtime implemetations: Arms ALARM0 as a 1ms timer, clears TIME, and begins
 * the timer. Can fail if the RP2040_Watchdog is not already initialized. (See RP2040 datasheet section 4.7.2 'Tick
 * Generation'). Interrupts are not necessarily enabled at this stage.
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
extern Std_ErrorCode Timer_RP2040_Init ( void );

/**
 * Updates internal tracking variables that the timer is 'uninit'. Disables all alarms. Pauses the timer. Expects that
 * the timer module was previously enabled, and will report an error if the module was not initialized. Will disable
 * interrupts as well.
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
extern Std_ErrorCode Timer_RP2040_Deinit ( void );

/**
 * Writes directly to the TIMER_INTE register, given an uint8 bitmask. Will report a parameter failure if the bitmask
 * parameter is not within the acceptable range [1,15]. Will not disable, clear, or otherwise touch alarms.
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
extern Std_ErrorCode Timer_RP2040_InterruptEnable ( uint32 bmp_intEnable );

/**
 * Writes directly to the TIMER_INTE register, given an uint8 bitmask. Will report a parameter failure if the bitmask
 * parameter is not within the acceptable range [1,15]. Will not disable, clear, or otherwise touch alarms.
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
extern Std_ErrorCode Timer_RP2040_InterruptDisable (  uint8  bmp_intDisable );

/**
 * Reads from TIMER_TIMELR and TIMER_TIMEHR. Is not threadsafe - future improvements can be made by utilizing the RAWL
 * and RAWH registers instead. This read is not threadsafe, and enforces latching on the timer, so interrupts should
 * be stopped specifically during this read.
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
extern Std_ErrorCode Timer_RP2040_TimerRead (  uint32 *  TimerHigh,  uint32 *  TimerLow );

/**
 * Writes to TIMER_TIMELW and TIMER_TIMEHW. Is not threadsafe - future improvements can be made by utilizing the RAWL
 * and RAWH registers instead. This write is not threadsafe, and enforces latching on the timer, so interrupts should
 * be stopped specifically during this write.
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
extern Std_ErrorCode Timer_RP2040_TimerWrite (  uint32 *  TimerHigh,  uint32 *  TimerLow );

/**
 * Reads from TimerAWL. Stores the result in the input buffer provided. Does not lock or cause any side-effects.
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
extern Std_ErrorCode Timer_RP2040_TimerRead32 (  uint32 *  TimerLow );

/**
 * Checks alarm 'n' to see if it has been triggered yet. Returns '1' if
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
extern tTimer_RP2040_AlarmStatus Timer_RP2040_CheckAlarmN (  uint8  alarmIndex );

/**
 * Disables the alarm indicated by index 'alarmIndex'. rites to the TIMER_ARMED register to disarm the alarm indicated
 * by the 'alarmIndex'. Reports OK if successful, and NOT_OK if failed. Checks input parameter is within range [0:3]
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
extern Std_ErrorCode Timer_RP2040_DisarmAlarmN (  uint8  alarmIndex );


/**
 * Disables the alarm indicated by index 'alarmIndex'. rites to the TIMER_ARMED register to disarm the alarm indicated
 * by the 'alarmIndex'. Reports OK if successful, and NOT_OK if failed. Checks input parameter is within range [0:3]
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
extern Std_ErrorCode Timer_RP2040_ArmAlarmN (  uint8  alarmIndex, uint32 triggerTime );
