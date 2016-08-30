//******************************************************************************
//
//  Description: This file contains the motor code
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include "functions.h"
#include "macros.h"
#include "msp430.h"
//------------------------------------------------------------------------------

// Global Variables
unsigned int dutyL = DUTY_CLEAR;
unsigned int dutyR = DUTY_CLEAR;
//------------------------------------------------------------------------------

/*===========================================================================
// Function name: stopMotors
//
// Description: Stops left Motors
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
void stopMotorsL(void){
  P3OUT &= ~(R_FORWARD | L_FORWARD);
 
}

/*===========================================================================
// Function name: stopMotors
//
// Description: Stops Right Motors
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
void stopMotorsR(void){
   P3OUT &= ~(R_REVERSE | L_REVERSE);
}

/*===========================================================================
// Function name: stopMotors
//
// Description: Stops All Motors by calling stopMotorL and stopMotorR
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
void stopMotors(void){
  stopMotorsL();
  stopMotorsR();
}
/*===========================================================================
// Function name: setDutyL
//
// Description: Sets the duty of the motors on the left motor
// 
// Passed: unsigned int DutyPercent
// Locals: None
// Returned: DutyL
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
bool setDutyL(unsigned int DutyPercent){
  if(DutyPercent > FULL_DUTY) return false;
  else {
    dutyL = DutyPercent;
    return true;
  }
}

/*===========================================================================
// Function name: setDutyR
//
// Description: sets the duty for the right Motor
// 
// Passed: unsigned int DutyPercent
// Locals: None
// Returned: None
// Globals: DutyR
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
bool setDutyR(unsigned int DutyPercent){
  if(DutyPercent > FULL_DUTY) return false;
  else {
    dutyR = DutyPercent;
    return true;
  }
}

/*===========================================================================
// Function name: runMotorsForward
//
// Description: Runs both motors forward with appropriate duty
// 
// Passed: None
// Locals: walk
// Returned: None
// Globals: dutyL
//          dutyR
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runMotorsForward(void){
  stopMotors();
  for(unsigned int walk = DUTY_START; walk <= FULL_DUTY; walk = walk<<1){
    if(walk & dutyL & dutyR){
     P3OUT |= L_FORWARD;
     P3OUT |= R_FORWARD;
     five_msec_sleep(TWO);
    }else if(walk & dutyR){
      P3OUT |= R_FORWARD;
      P3OUT &= ~L_FORWARD;
      five_msec_sleep(TWO);
    }else if(walk & dutyL){
      P3OUT |= L_FORWARD;
      P3OUT &= ~R_FORWARD;
      five_msec_sleep(TWO);
    }
  }
}
   
/*===========================================================================
// Function name: runMotorsReverse
//
// Description: Runs both motors reverse with appropriate duty
// 
// Passed: None
// Locals: walk
// Returned: None
// Globals: dutyL
//          dutyR
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runMotorsReverse(void){
  stopMotors();
  for(unsigned int walk = DUTY_START; walk <= FULL_DUTY; walk = walk<<1){
    if(walk & dutyL & dutyR){
     P3OUT |= L_REVERSE;
     P3OUT |= R_REVERSE;
     five_msec_sleep(TWO);
    }else if(walk & dutyR){
      P3OUT |= R_REVERSE;
      P3OUT &= ~L_REVERSE;
      five_msec_sleep(TWO);
    }else if(walk & dutyL){
      P3OUT |= L_REVERSE;
      P3OUT &= ~R_REVERSE;
      five_msec_sleep(TWO);
    }
  }
}

/*===========================================================================
// Function name: spinR
//
// Description: Spins the car right but running right motor reverse
//              and left motor forward
// 
// Passed: None
// Locals: walk
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void spinR(void){
  stopMotors();
  for(unsigned int walk = DUTY_START; walk < FULL_DUTY; walk = walk<<1){
    P3OUT |= R_REVERSE;
    P3OUT |= L_FORWARD;
    waitForTimer(TWO);
  }
}

/*===========================================================================
// Function name: runMotorsReverse
//
// Description: Spins the car right but running left motor reverse
//              and right motor forward
// 
// Passed: None
// Locals: walk
// Returned: None
// Globals: None
//          
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void spinL(void){
  stopMotors();
  for(unsigned int walk = DUTY_START; walk < FULL_DUTY; walk = walk<<1){
    P3OUT |= L_REVERSE;
    P3OUT |= R_FORWARD;
    waitForTimer(TWO);
  }
}