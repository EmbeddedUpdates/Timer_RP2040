
/**
 * @file Timer_RP2040_SFR.h
 * @author pflaherty
 * @date 07.21.2024
 * @brief SFR definitions for the RP2040 Timer from RP2040 datasheet Chapter 4.6.5
 * 
 * COMPONENT: Timer_RP2040
 * VERSION: 01.01.00
 *
 * Change History
 * 06.23.2024 - pflaherty - Initial Creation
 * 07.21.2024 - pflaherty - Integration to skeleton code from template generator
 */

/************************************************************
  Version History
  -----------------------------------------------------------
  Revision |  Author   |  Change ID |  Description
  01.00.00 |  Madrick3 |  draft     |  Initial Creation.
  01.01.00 |  Madrick3 |  skeleton  |  Integration for initial testing
************************************************************/

/************************************************************
  INCLUDES
************************************************************/
/* #include "Generic_SFR.h" */
#if defined (RP2040)
#define SFR_IOS(x) ((unsigned int *)(x))
#endif /* VIRTUAL TARGET*/
#if defined (VIRTUAL_TARGET)
/* Virtual target has a 64 bit memory address which is marked as type long */
#define SFR_IOS(x) ((unsigned long *)(x))
#endif /* VIRTUAL TARGET*/
/************************************************************
  DEFINES
************************************************************/
#if !defined( VIRTUAL_TARGET )
/* Base Register Address */
#define TIMER_BASE                      0x40054000uL

#else /* VIRTUAL TARGET */

typedef struct vtt_RP2040_Timer
{
  uint32 TIMEHW;
  uint32 TIMELW;
  uint32 TIMEHR;
  uint32 TIMELR;
  uint32 ALARM0;
  uint32 ALARM1;
  uint32 ALARM2;
  uint32 ALARM3;
  uint32 ARMED;
  uint32 TIMERAWH;
  uint32 TIMERAWL;
  uint32 DBGPAUSE;
  uint32 PAUSE;
  uint32 INTR;
  uint32 INTE;
  uint32 INTF;
  uint32 INTS;
} tRP2040_Timer;

/* Virtual Target has 64 bit word size and must be casted as such to accomodate virtual access */
#define TIMER_BASE (uint64)&Timer_Live

#endif
/* Register Offsets */
#define TIMER_REG_TIMEHW_OFFSET         0x00uL
#define TIMER_REG_TIMELW_OFFSET         0x04uL
#define TIMER_REG_TIMEHR_OFFSET         0x08uL
#define TIMER_REG_TIMELR_OFFSET         0x0CuL
#define TIMER_REG_ALARM0_OFFSET         0x10uL
#define TIMER_REG_ALARM1_OFFSET         0x14uL
#define TIMER_REG_ALARM2_OFFSET         0x18uL
#define TIMER_REG_ALARM3_OFFSET         0x1CuL
/* Function like-macro for accessing ALARM based on index */
#define TIMER_REG_ALARMn_OFFSET(n)      (0x10uL + (0x04uL*n))
#define TIMER_REG_ARMED_OFFSET          0x20uL
#define TIMER_REG_TIMERAWH_OFFSET       0x24uL
#define TIMER_REG_TIMERAWL_OFFSET       0x28uL
#define TIMER_REG_DBGPAUSE_OFFSET       0x2CuL
#define TIMER_REG_PAUSE_OFFSET          0x30uL
#define TIMER_REG_INTR_OFFSET           0x34uL
#define TIMER_REG_INTE_OFFSET           0x38uL
#define TIMER_REG_INTF_OFFSET           0x3CuL
#define TIMER_REG_INTS_OFFSET           0x40uL

/* Offset Register Pointers */
#define TIMER_REG_TIMEHW                SFR_IOS(TIMER_BASE + TIMER_REG_TIMEHW_OFFSET)
#define TIMER_REG_TIMELW                SFR_IOS(TIMER_BASE + TIMER_REG_TIMELW_OFFSET)
#define TIMER_REG_TIMEHR                SFR_IOS(TIMER_BASE + TIMER_REG_TIMEHR_OFFSET)
#define TIMER_REG_TIMELR                SFR_IOS(TIMER_BASE + TIMER_REG_TIMELR_OFFSET)
#define TIMER_REG_ALARM0                SFR_IOS(TIMER_BASE + TIMER_REG_ALARM0_OFFSET)
#define TIMER_REG_ALARM1                SFR_IOS(TIMER_BASE + TIMER_REG_ALARM1_OFFSET)
#define TIMER_REG_ALARM2                SFR_IOS(TIMER_BASE + TIMER_REG_ALARM2_OFFSET)
#define TIMER_REG_ALARM3                SFR_IOS(TIMER_BASE + TIMER_REG_ALARM3_OFFSET)
#define TIMER_REG_ALARMn(n)             SFR_IOS(TIMER_BASE + TIMER_REG_ALARMn_OFFSET(n))
#define TIMER_REG_ARMED                 SFR_IOS(TIMER_BASE + TIMER_REG_ARMED_OFFSET)
#define TIMER_REG_TIMERAWH              SFR_IOS(TIMER_BASE + TIMER_REG_TIMERAWH_OFFSET)
#define TIMER_REG_TIMERAWL              SFR_IOS(TIMER_BASE + TIMER_REG_TIMERAWL_OFFSET)
#define TIMER_REG_DBGPAUSE              SFR_IOS(TIMER_BASE + TIMER_REG_DBGPAUSE_OFFSET)
#define TIMER_REG_PAUSE                 SFR_IOS(TIMER_BASE + TIMER_REG_PAUSE_OFFSET)
#define TIMER_REG_INTR                  SFR_IOS(TIMER_BASE + TIMER_REG_INTR_OFFSET)
#define TIMER_REG_INTE                  SFR_IOS(TIMER_BASE + TIMER_REG_INTE_OFFSET)
#define TIMER_REG_INTF                  SFR_IOS(TIMER_BASE + TIMER_REG_INTF_OFFSET)
#define TIMER_REG_INTS                  SFR_IOS(TIMER_BASE + TIMER_REG_INTS_OFFSET)

/* Set high to pause the timer - low to unpause. */
#define TIMER_PAUSE_MASK                0x00000001
#define TIMER_PAUSE_SET                 0x00000001
#define TIMER_PAUSE_CLR                 0x00000000

/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

