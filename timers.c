//******************************************************************************
//
//  Description: This file contains the timers code
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include "functions.h"
#include "macros.h"
#include  "msp430.h"
//------------------------------------------------------------------------------

//Global Variables
volatile unsigned int count;
volatile unsigned int count2;
volatile bool startWaiting = false;
volatile bool startWaiting2 = false;
volatile bool countdown;
volatile unsigned int countTimer;

/*===========================================================================
// Function name: Init_Timers
//
// Description: Initialize all timers
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

/*===========================================================================
// Function name: runDemo
//
// Description: Wait function set up to wait until the timer has counted up to
//              the appropriate time.
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: count
//          startWaiting
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void waitForTimer(unsigned int UpTo){
  count = START;
  for(startWaiting = true; count < UpTo; ){
  }
  startWaiting = false;
}

/*===========================================================================
// Function name: runDemo
//
// Description: Initialize Timer_A0
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: count
//          startWaiting
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Init_Timer_A0(void){
  TA0CTL = TASSEL__SMCLK;               // SMCLK source
  TA0CTL |= TACLR;                      // Resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINOUS;              // Continuous up
  TA0CTL |= ID__2;                      // Divide clock by 8
  TA0CTL &= ~TAIE;                      // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG;                     // Clear Overflow Interrupt flag
  
  TA0EX0 = TAIDEX_7;                    // Divide clock by an additional 8
  
  TA0CCR0 = TA0CCR0_INTERVAL;           // CCR0
  TA0CCTL0 |= CCIE;                     // CCR0 enable interrupt
  
// TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
// TA0CCTL1 |= CCIE; // CCR1 enable interrupt
// TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
// TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}

/*===========================================================================
// Function name: startTimer
//
// Description: start a timer using timer A0
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: count2
//          startWaiting2
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void startTimer(void){
  count2 = START;
  startWaiting2 = true;
}

/*===========================================================================
// Function name: stopTimer
//
// Description: stop the Timer previously started. Return count time
// 
// Passed: None
// Locals: None
// Returned: unsigned int
// Globals: count2
//          startWaiting2
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
unsigned int stopTimer(void){
  startWaiting2 = false;
  return count2;
}

/*===========================================================================
// Function name: startCountdown
//
// Description: start a countdown. Separate from start timer count and 
//              wait for timer count
// 
// Passed: unsigned int time
// Locals: None
// Returned: None
// Globals: countTimer
//          countdown
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void startCountdown(unsigned int time){
  countTimer = time;
  countdown = true;
}

