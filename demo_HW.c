//******************************************************************************
//
//  Description: This file contains the HW Demo code
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

extern char * nothing;
/*===========================================================================
// Function name: runDemoHW8
//
// Description: Runs the demo for HW9
// 
// Passed: None
// Locals: demoSW1
//         demoSW2
// Returned: None
// Globals: nothing
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemoHW8(void){
  char * demoSW1 = "115200";
  char * demoSW2 = "9600";
  init_eUART_A();
  setDefaultMonitor();
  waitForTimer(FIVE_SECONDS);
  setSpecificLCD(nothing,nothing,"Baud",demoSW2);
  while(ALWAYS){
    if(Switch_1_Read()){            
      setBaudRate(true);
      setSpecificLCD(nothing,nothing,"Baud",demoSW1);
      waitForTimer(TWO_SECONDS);
      clearBufferRX();
      sendData("NCSU  #1");
      waitForTimer(HALF_SECOND);
      setSpecificLCD(receiveData(),nothing,"Baud",demoSW1);
    }
    if(Switch_2_Read()){
      setBaudRate(false);
      setSpecificLCD(nothing,nothing,"Baud",demoSW2);
      waitForTimer(TWO_SECONDS);
      clearBufferRX();
      sendData("NCSU  #1");
      waitForTimer(HALF_SECOND);
      setSpecificLCD(receiveData(),nothing,"Baud",demoSW2);
    }
  }  
}

/*===========================================================================
// Function name: runDemoHW9
//
// Description: Runs the demo for HW 9
// 
// Passed: None
// Locals: char Resistor[]
//         char Shapes[]
//         char Song[]
//         unsigned int currentMenu
//         unsigned int thumbPosition
// Returned: None
// Globals: nothing
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemoHW9(void){
  char Resistor[] = "->Resistors";
  char Shapes[] = "->Shapes";
  char Song[] = "->Song";
  unsigned int currentMenu;
  while(ALWAYS){
    unsigned int thumbPosition = ReadSensor(ADC_THUMB);
    waitForTimer(LCD_WAIT);
    if(thumbPosition<ADC_MENU3_1){
        setSpecificLCD(Resistor,&Shapes[TWO],&Song[TWO],nothing);
        currentMenu = ONE;
    }else if(thumbPosition<ADC_MENU3_2){
        setSpecificLCD(&Resistor[TWO],Shapes,&Song[TWO],nothing);
        currentMenu = TWO;
    }else{
        setSpecificLCD(&Resistor[TWO],&Shapes[TWO],Song,nothing);
        currentMenu = THREE;
    }
    if(Switch_1_Read()){
      switch (currentMenu){
      case ONE:
        ResistorMenu();
        break;
      case TWO:
        ShapeMenu();
        break;
      case THREE:
        SongMenu();
        break;
      default:
        break;
      }
    }
    if(Switch_2_Read()){
      setSpecificLCD("Select","Function:",currentFunction(),"");
      return;
    }
  }
}