#include "Timer_RP2040.h"

/************************************************************
  LOCAL VARIABLES
************************************************************/
extern tTimer_RP2040_Status Timer_RP2040_Status;

extern tRP2040_Timer Timer_Uninit;

extern volatile tRP2040_Timer Timer_Live;

/************************************************************
  LOCAL FUNCTIONS
************************************************************/

extern Std_ErrorCode Timer_RP2040_Pause ( void );

extern Std_ErrorCode Timer_RP2040_Unpause ( void );

extern Std_ErrorCode Timer_RP2040_ReadTimerLow ( uint32 * TimerLow );
extern Std_ErrorCode Timer_RP2040_ReadTimerHigh ( uint32 * TimerHigh );

extern Std_ErrorCode Timer_RP2040_WriteTimerLow ( uint32 TimerLow );
extern Std_ErrorCode Timer_RP2040_WriteTimerHigh ( uint32 TimerHigh );
