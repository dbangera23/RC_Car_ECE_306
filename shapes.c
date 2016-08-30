//******************************************************************************
//
//  Description: This file contains the code to make the car run shapes
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"
//------------------------------------------------------------------------------

// Global Variables
extern int currFunctionNum;
extern volatile bool countdown;
char * Running = "Running";
extern volatile unsigned int LThreshold;
extern volatile unsigned int RThreshold;
//------------------------------------------------------------------------------


/*===========================================================================
// Function name: runShape
//
// Description: Runs the selected shape twice
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
void runShape(unsigned int shape){
  for(int walk = START; walk<TWO; walk++){
    switch(shape){
    case CIRCLE:
      setSpecificLCD(Running,"Circle","","");
      runCircleL();
      setDefaultMonitor();
      break;
    case FIGURE8:
       setSpecificLCD(Running,"Figure 8","","");
      runFigure8();
      setDefaultMonitor();
      break;
    case TRIANGLE:
       setSpecificLCD(Running,"Triangle","","");
      runTriangle();
      setDefaultMonitor();
      break;
    default:
      break;
    }
  }
}

/*===========================================================================
// Function name: runCircleL
//
// Description: Runs one circle counterclockwise
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
void runCircleL(void){
  if(setDutyR(FULL_DUTY)){
    if(setDutyL(ONE_DUTY)){
      for(int walk = START; walk < CIRCLEEND; walk++){
        runMotorsForward();
      }
    }
  }
  stopMotors();
}

/*===========================================================================
// Function name: runCircleR
//
// Description: Runs one circle clockwise
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
void runCircleR(void){
  if(setDutyR(ONE_DUTY)){
    if(setDutyL(FULL_DUTY)){
      for(int walk = START; walk < (CIRCLEEND-ONE); walk++){
        runMotorsForward();
      }
    }
  }
  stopMotors();
}

/*===========================================================================
// Function name: runFigure8
//
// Description: Runs two opposite circles in sucession to create a figure 8
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
void runFigure8(void){
  runCircleL();
  five_msec_sleep(TWO);
  runCircleR();
}

/*===========================================================================
// Function name: runTriangle
//
// Description: Runs the appropriate straights and turns to create a triangle
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

void runTriangle(void){
    runStraight(SHAPEBIAS, true);
    runTriangleTurn(NEVER);
    runStraight(SHAPEBIAS, true);
    runTriangleTurn(TRIANGLE_BIAS);
    runStraight(SHAPEBIAS, true);
    runTriangleTurn(TRIANGLE_BIAS);
}

/*===========================================================================
// Function name: runStraight
//
// Description: Runs in a straight line for a set period of time. 
//              Can induce a bias to run longer or shorter. Will run forward
//              or backwards
// 
// Passed: int bias
//         bool forward
// Locals: walk
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runStraight(int bias, bool forward){
  if(setDutyR(FULL_DUTY>>WHEEL_BIAS)){
      if(setDutyL(FULL_DUTY)){
        for(int walk = START; walk < (ONE+bias); walk++){
          if(forward){
            runMotorsForward();
          }else{
            runMotorsReverse();
        }
      }
    }
  }
  stopMotors();
}

/*===========================================================================
// Function name: runStraightTillTime
//
// Description: Runs in a straight line for a set period of time. 
//              will run forward or backward
// 
// Passed: unsigned int time
//         bool forward
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runStraightTillTime(unsigned int time, bool forward){
  if(setDutyR(FULL_DUTY>>WHEEL_BIAS)){
      if(setDutyL(FULL_DUTY)){
        startCountdown(time);
        while(countdown){         
          if(forward){
            runMotorsForward();
          }else{
            runMotorsReverse();
          }
        }
      }
  }
  stopMotors();
}

/*===========================================================================
// Function name: runStraightForever
//
// Description: Runs straight full speed until told to stop somewhere else. 
//              Can be told to run forward or backwards
// 
// Passed: bool forward
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runStraightForever(bool forward){
  setDutyR(FULL_DUTY);
  setDutyL(FULL_DUTY);
  stopMotors();
  if(forward){
    runMotorsForward();
  }else{
    runMotorsReverse();
  }
}
/*===========================================================================
// Function name: runTriangleTurn
//
// Description: Creates a 1/3 of a circle to demonstrate the turn of a triangle 
//              Can induce a bias to create more of a circle or less
// 
// Passed: bias
// Locals: walk2
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runTriangleTurn(int bias){
  if(setDutyR(ONE_DUTY)){
      if(setDutyL(FULL_DUTY)){
        for(int walk2 = START; walk2 < TRIANGLE_TURN+bias; walk2++){
          runMotorsForward();
        }
      }
    }
  stopMotors();
}

/*===========================================================================
// Function name: runOnLine
//
// Description: Runs along the black line course. Bias for how long to run
// 
// Passed: unsigned int bias
// Locals: unsigned int leftSensor
//         unsigned int rightSensor
// Returned: None
// Globals: countdown
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runOnLine(unsigned int bias){
  startCountdown(DEMO8TIME+bias);
  while(countdown){
    P3OUT &= ~(R_FORWARD | L_FORWARD);
    waitForTimer(TWO);
    unsigned int leftSensor = ReadSensor(ADC_L_DETECT);
    unsigned int rightSensor = ReadSensor(ADC_R_DETECT);
    if((leftSensor > LThreshold) && (rightSensor < RThreshold)){
      P3OUT |= R_FORWARD;
      P3OUT |= L_FORWARD;
    } else if((leftSensor < LThreshold) && (rightSensor < RThreshold)){
      P3OUT &= ~L_FORWARD;
      P3OUT |= R_FORWARD; 
    } else if((leftSensor > LThreshold) && (rightSensor > RThreshold)){
      P3OUT &= ~R_FORWARD;
      P3OUT |= L_FORWARD;
    } else if((leftSensor < LThreshold) && (rightSensor > RThreshold)){
      P3OUT &= ~L_FORWARD;
      P3OUT |= R_FORWARD;
    }
    waitForTimer(ONE);
  }
}