# Tests for the RP2040 Timer module

*  ~~Reads to the TIMEHR work~~

*  ~~Reads to the TIMELR work~~

*  ~~Writes to the TIMEHW register works~~
    * ~~Write of zero works~~
    * ~~Write of FFFFFFFF works~~
    * ~~Write of FACEBEEF works~~

*  ~~Writes to the TIMELW register works~~
    * ~~Write of zero works~~
    * ~~Write of FFFFFFFF works~~
    * ~~Write of FACEBEEF works~~

*  ~~Pausing~~
    * ~~Pausing the timer works~~
    * ~~Unpausing the timer works~~

*  ~~Reads of the Alarm0 register works~~
    * ~~Reads of AlarmN~~
* ~~Setting a Alarm0 of 0 shall fail~~
    * ~~Setting AlarmN with 0 shall fail~~
* ~~Setting an Alarm0 of N shall work~~
    * ~~Setting AlarmN with N shall work~~

* ~~Reads of the ARMED register works~~
    * ~~Writes to the ARMED register works~~

* Reads of the TIMER Raw H work
    * Reads of the TIMER RAW L work
    * Reads of TimerRAW work together

* Reads of the Interrupt Status register work
* Writes to the Interrupt Force Register work
    * Writes to the Interrupt Force Register can be seen in the interrupt status register through test mock

* Reads of the Interrupt Raw status register work
    * Writes to the raw interrupt status register work
    * Test Mock of raw status register affects masked status register

* Reads of the Interrupt Enable Register work
    * Writes to the interrupt enable regsiter work
    * Test Mock checks with INTE register for reporting INTS




## Big Tests
*  Init Clears the TIMEHR and TIMELR values
* ~~Setting an Alarm does not affect other Alarms~~



# These are things that should be done in HL code
* Can convert us to ms
* can convert ms to us

* can conver ms to seconds
* can convert seconds to ms

* can convert minutes to seconds
* can convert seconds to minutes

* Two alarms can be created for one hardware alarm
    * Alarm Entries do not interfere with each other
* Alarm Entries can be created for absolute times
* Alarm Entries can be created for relative times


