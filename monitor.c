//******************************************************************************
//
//  Description: This file contains the monitor code
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
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
extern char * circle;
extern char * figure8;
//------------------------------------------------------------------------------

/*===========================================================================
// Function name: Display Process
//
// Description: Clears the display and then displays the words on the lcd
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: display_1
//          display_2
//          display_3
//          display_4
//          posL1
//          posL2
//          posL3
//          posL4
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}

/*===========================================================================
// Function name: Display Process
//
// Description: Sets the words on the display to be the default display
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: display_1
//          display_2
//          display_3
//          display_4
//          posL1
//          posL2
//          posL3
//          posL4
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void setDefaultMonitor(void){
  display_1 = "NCSU";
  posL1 = THREE;
  display_2 = "WOLFPACK";
  posL2 = ONE;
  display_3 = "ECE306";
  posL3 = TWO;
  display_4 = "D Bangera";
  posL4 = ONE;
  Display_Process();
}

/*===========================================================================
// Function name: setSpecificLCD
//
// Description: changes the words on the display to display what is passed in
// 
// Passed: char * words1
//         char * words2
//         char * words3
//         char * words4
// Locals: None
// Returned: None
// Globals: display_1
//          display_2
//          display_3
//          display_4
//          posL1
//          posL2
//          posL3
//          posL4
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void setSpecificLCD(char * words1, char * words2, char * words3, char * words4){
  display_1 = words1;
  posL1 = START;
  display_2 = words2;
  posL2 = START;
  display_3 = words3;
  posL3 = START;
  display_4 = words4;
  posL4 = START;
  Display_Process();
}

/*===========================================================================
// Function name: charToHex
//
// Description: changes the char to a number.
// 
// Passed: char countChar[]
// Locals: numNum
//         length
//         i
//         temp
//         unitPlace
//         walk
// Returned: unsigned int numNum
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
unsigned int charToInt(char countChar[]){
  unsigned int numNum=START;
  unsigned int length = strlen(countChar);
  for(int i=START; i<length;i++){
    if(countChar[i] == '\0') break;
    unsigned int temp = countChar[i]-'0';
    unsigned int unitPlace = ONE;
    for(int walk=length-i;walk>ONE;walk--){
      unitPlace *= TEN;
    }
    numNum += temp*unitPlace;
  }
  return numNum;
}

/*===========================================================================
// Function name: itoa
//
// Description: changes the int to a char *
// 
// Passed: int value
//         char * result
//         int base
// Locals: char *ptr
//         char *ptr1
//         char *tmp_char
//         int tmp_value
// Returned: char * result
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
char * itoa(int value, char* result, int base) {
  // check that the base if valid
  if (base < TWO || base > MAXBASE) { *result = '\0'; return result; }
  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;
  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );
  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}