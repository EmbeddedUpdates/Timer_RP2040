
/**
 * @file Timer_RP2040.h
 * @author pflaherty
 * @date 06.24.2024
 * @brief Main Header file for the RP2040 Timer module
 * 
 * COMPONENT: TIMER_RP2040
 * VERSION: 01.00.00
 *
 * Change History
 * 01.00.00 - Initial Creation - pflaherty
 */


/************************************************************
  DEFINES
************************************************************/

/************************************************************
  INCLUDES
************************************************************/
#include "Platform_Types.h"
#include "Timer_RP2040_SFR.h"
/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  GLOBAL VARIABLES
************************************************************/

/************************************************************
  LOCAL VARIABLES
************************************************************/

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

/**
 * BRIEF: Initializes the Timer module, and arms Alarm0
 * DESC: Enables the timer
 *        1. Checks the timer is was init previously
 *        2. Pauses the Timer
 *        3. Resets the Timer
 *        4. Disarms all alarms
 *        5. Resets globabl variables for tracking
 * 
 * RETURN: 
 *         0: 'OK' if the value can be stored
 *         1: 'NOT_OK' if the timer write fails
 * 
 * PRECONDITIONS: Timer is not Enabled
 * POSTCONDITIONS: Timer is enabled
 * INVARIANTS: None
 * 
 */
Std_ErrorCode Timer_RP2040_Init ( void );

/**
 * BRIEF: Pauses the Timer, Resets the Timer, Disarms all alarms.
 * DESC: Shuts down the Timer so that it can be restarted.
 *        1. Checks the timer is was init previously
 *        2. Pauses the Timer
 *        3. Resets the Timer
 *        4. Disarms all alarms
 *        5. Resets globabl variables for tracking
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is enabled
 * POSTCONDITIONS: Timer is not enabled
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_Deinit ( void );


/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_InterruptEnable ( void );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_InterruptDisable ( void );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_ReadTimer ( uint32 * TimerHigh, uint32 * TimerLow );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_SetTimer ( uint32 * TimerHigh, uint32 * TimerLow );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_ReadTimerLow ( uint32 * TimerLow );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_ReadTimerHigh ( uint32 * TimerHigh );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_SetTimerLow ( uint32 * TimerLow );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_SetTimerHigh ( uint32 * TimerHigh );


/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_CheckAlarm ( uint8 n );

/**
 * FUNC: Std_ReturnType Function_Name ( void )
 * BRIEF: Short Description about the function
 * DESC: Longer description of how it works
 * 
 * RETURN: 0 if Successful, other for specific failure
 * 
 * PRECONDITIONS: Timer is Initialized
 * POSTCONDITIONS: Timer is Paused
 * INVARIANTS: None
 * 
 */
Std_ReturnType Timer_RP2040_DisarmAlarm ( uint8 n );
