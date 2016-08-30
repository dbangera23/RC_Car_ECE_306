//******************************************************************************
//
//  Description: This file contains the Initialization code
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include "functions.h"
#include "macros.h"
//------------------------------------------------------------------------------

// Global Variables
extern char display_line_1[DISPLINESIZE];
extern char display_line_2[DISPLINESIZE];
extern char display_line_3[DISPLINESIZE];
extern char display_line_4[DISPLINESIZE];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
//------------------------------------------------------------------------------

/*===========================================================================
// Function name: Init_Conditions
//
// Description: Initializations configurations
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: display_line_1
//          display_line_2
//          display_line_3
//          display_line_4
//          display_1
//          display_2
//          display_3
//          display_4
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Init_Conditions(void){
// Interrupts are disabled by default, enable them. 
  enable_interrupts();
  display_1 = &display_line_1[NEVER];
  display_2 = &display_line_2[NEVER];
  display_3 = &display_line_3[NEVER];
  display_4 = &display_line_4[NEVER];

//------------------------------------------------------------------------------
}

