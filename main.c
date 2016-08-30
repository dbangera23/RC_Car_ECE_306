//******************************************************************************
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
//------------------------------------------------------------------------------

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
volatile char one_time;

/*===========================================================================
// Function name: main
//
// Description: This is the main routine for the program. Execution of code starts here.
//              The operating system is Back Ground Fore Ground.
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: Time_Sequence
//          big
//          size_count
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/

void main(void){
//------------------------------------------------------------------------------
// Main Program
// 
//  
//------------------------------------------------------------------------------
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System 
  Init_Conditions();
  Time_Sequence = START;                        // 
  Init_Timers();                            // Initialize Timers
  waitForTimer(CLOCKINIT);               // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  Init_ADC();                               // Init
  stopMotors();
//             1234567890
  setDefaultMonitor();
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  runStraightForever(true);
 while(ALWAYS) {                            // Can the Operating system run
  Switches_Process_Main();                       // Check for switch state change 
   if(Time_Sequence > MAINLOOPDONE){
    Time_Sequence = START;
  }
 }
//------------------------------------------------------------------------------
}




