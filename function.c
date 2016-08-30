//******************************************************************************
//
//  Description: This file contains the code for different functions of the car
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "macros.h"
//------------------------------------------------------------------------------

// Global Variables
char * function[] = {"Project 3","Project 4","Project 5","Homework 8","Project 6","Homework 9","Project 8"};
int currFunctionNum = FUNCTIONNUM;
//------------------------------------------------------------------------------

/*===========================================================================
// Function name: setDutyL
//
// Description: Select the next function.
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: currFunctionNum
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void iterateFunction(void){
  currFunctionNum++;
  if(currFunctionNum > FUNCTIONNUM){
    currFunctionNum = START;
  }
}

/*===========================================================================
// Function name: currentFunction
//
// Description: returns the name of the current selected function
// 
// Passed: None
// Locals: None
// Returned: function[currFunctionNum]
// Globals: currFunctionNum
//          function[]
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
/===========================================================================*/
char * currentFunction(void){
  return function[currFunctionNum];
}