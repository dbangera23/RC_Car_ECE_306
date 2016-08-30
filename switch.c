//******************************************************************************
//
//  Description: This file contains the code for switches
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

// Global Variables
extern volatile bool switch1DB;
extern volatile bool switch2DB;
extern volatile bool switch1;
extern volatile bool switch2;
extern volatile unsigned int SW1DBCount;
extern volatile unsigned int SW2DBCount;

/*===========================================================================
// Function name: Switches_Process
//
// Description: This function does the appropriate action for each button
//              press. button1 for select function. button2 for running
//              function.
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: None
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Switches_Process_Main(void){
//------------------------------------------------------------------------------
// function to switch what shows on screen
// 
//------------------------------------------------------------------------------
 if(Switch_1_Read()){
        iterateFunction();
        setSpecificLCD("Select","Function:",currentFunction(),"");
 }
  if(Switch_2_Read()){
        runDemo();
  }
//------------------------------------------------------------------------------
}

/*===========================================================================
// Function name: Switch_1_Read
//
// Description: This function returns true if the switch 1 was pressed.
// 
// Passed: None
// Locals: None
// Returned: bool
// Globals: switch1
//          switch1DB
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
bool Switch_1_Read(void){
  if(switch1){
    if(!switch1DB){
      switch1 = false;
      return true;
    }
  }
  return false;
}

/*===========================================================================
// Function name: Switch_2_Read
//
// Description: This function returns true if the switch 2 was pressed.
// 
// Passed: None
// Locals: None
// Returned: bool
// Globals: switch2
//          switch2DB
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
bool Switch_2_Read(void){
  if(switch2){
    if(!switch2DB){
      switch2 = false;
      return true;
    }
  }
  return false;
}
