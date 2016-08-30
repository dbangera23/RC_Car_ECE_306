//******************************************************************************
//
//  Description: This file contains the code to demos for the projects
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

// Global Variable
extern int currFunctionNum;
extern volatile unsigned int LThreshold;
extern volatile unsigned int RThreshold;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern char *display_1;
extern char posL1;
extern volatile bool read;
char * straight = "Straight";
char * forward = "Forward";
char * reverse = "Reverse";
char * nothing = "";
extern volatile bool countdown;

//------------------------------------------------------------------------------

/*===========================================================================
// Function name: runDemo
//
// Description: Figures out which demo was selected and runs it
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
void runDemo(void){
  switch (currFunctionNum){
  case DEMO3:
    runDemo3();
    break;
  case DEMO4:
    runDemo4();
    break;
  case DEMO5:
    runDemo5();
    break;
  case HW8:
    runDemoHW8();
    break;
  case DEMO6:
    runDemo6();
    break;
  case HW9:
    runDemoHW9();
    break;
  case DEMO8:
    runDemo8();
    break;
  default:
    break;
  }
}

/*===========================================================================
// Function name: runDemo3
//
// Description: Runs the demo for project 3
// 
// Passed: None
// Locals: unsigned int shape
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemo3(void){
  unsigned int shape = START;
  while(ALWAYS){
    if(Switch_1_Read()){
      shape++;
      if(shape>TRIANGLE)
        shape=START;
    }
    if(Switch_2_Read())
      runShape(shape);
  }
}

/*===========================================================================
// Function name: runDemo4
//
// Description: Runs the demo for project 4
// 
// Passed: None
// Locals: walk
// Returned: None
// Globals: nothing
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemo4(void){
  setSpecificLCD(straight,forward,nothing,nothing);
  runStraight(STRAIGHT_SEC,true);
  waitForTimer(HALF_SECOND);
  setSpecificLCD(straight,reverse,nothing,nothing);
  runStraight(STRAIGHT_TWOSEC,false);
  waitForTimer(HALF_SECOND);
  setSpecificLCD(straight,forward,nothing,nothing);
  runStraight(STRAIGHT_SEC,true);
  waitForTimer(HALF_SECOND);
  setSpecificLCD("Spin","Right",nothing,nothing);
  for(int walk = START; walk < TURNONE; walk++)
    spinR();
  stopMotors();
  waitForTimer(HALF_SECOND);
  setSpecificLCD("Spin","Left",nothing,nothing);
  for(int walk = START; walk < TURNONE; walk++)
    spinL();
  stopMotors();
  setDefaultMonitor();
}

/*===========================================================================
// Function name: runDemo5
//
// Description: Runs the demo for project 5
// 
// Passed: None
// Locals: walk
//         time
// Returned: None
// Globals: RThreshold
//          LThreshold
//          nothing
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemo5(void){
  CalibrateSensor();            //Sensor Calibration
  
  setSpecificLCD("Set","Car","For","Demo");
  while(!Switch_1_Read()){}  
   
  setSpecificLCD(straight,forward,"Till","Black");
  P1OUT |= IR_LED;              //Turn on IR LED
  runStraightForever(true);
  while((ReadSensor(ADC_R_DETECT) < RThreshold) || (ReadSensor(ADC_L_DETECT) < LThreshold)){}            //Run till we hit a black line
  stopMotors();
  
  waitForTimer(HALF_SECOND);
  
  setSpecificLCD(straight,reverse,"Till","Black");
  runStraightForever(false);
  startTimer();                 //Start timer and run backwards till we see a line
  waitForTimer(HALF_SECOND);
  while((ReadSensor(ADC_R_DETECT) < RThreshold) || (ReadSensor(ADC_L_DETECT) < LThreshold)){}
  stopMotors();
  unsigned int time = stopTimer();
  P1OUT &= ~IR_LED;
  waitForTimer(HALF_SECOND);
  
  setSpecificLCD(straight,forward,"Halfway",nothing);
  time = time >> ONE;                   //Bit shifting to divide by 2
  runStraightTillTime(time, true);
  waitForTimer(HALF_SECOND);
  
  setSpecificLCD("Spin","Right",nothing,nothing);
 for(int walk = START; walk < TURNONE; walk++)
    spinR();
 for(int walk = START; walk < TURNONE; walk++)
    spinR();
  
  setSpecificLCD("Spin","Left",nothing,nothing);
  for(int walk = START; walk < TURNONE; walk++)
    spinL();
  for(int walk = START; walk < TURNONE; walk++)
    spinL();
  for(int walk = START; walk < TURNONE; walk++)
    spinL();
  stopMotors();
}



/*===========================================================================
// Function name: runDemo6
//
// Description: Runs the demo for Project 6
// 
// Passed: None
// Locals: countChar
//         demo6count
// Returned: None
// Globals: display_1
//          posL1
//          nothing
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemo6(void){
  init_eUART_A();
  setBaudRate(false);
  setSpecificLCD("Press","SW1","To","Start");
  while(ALWAYS){
    if(Switch_1_Read()){
      setSpecificLCD("1",nothing,nothing,nothing);
      Display_Process();
      sendData("1");
    }
    waitForTimer(QUARTER_SECOND);
    if(!read){
      continue;
    }
    char * countChar = receiveData();
    unsigned int demo6count = charToInt(countChar);
    if(demo6count>START){
      demo6count++;
      itoa(demo6count,countChar,TEN);
      setSpecificLCD(countChar,nothing,nothing,nothing);
      Display_Process();
      waitForTimer(HALF_SECOND);
      sendData(countChar);
    }
  }
}

/*===========================================================================
// Function name: runDemo8
//
// Description: Runs the demo for Project 8
// 
// Passed: None
// Locals: WALK
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void runDemo8(void){
  CalibrateSensor();
  setSpecificLCD("Place On","Right","Side of","Line");
  while(!Switch_1_Read()){}
  waitForTimer(FULL_SECOND);
  runOnLine(START);
  stopMotors();
  waitForTimer(TWO_SECONDS);
  for(unsigned int walk=START;walk<SIX;walk++){
    P3OUT &= ~L_FORWARD;
    waitForTimer(FOUR);
    spinL();
  }
  runStraight(START, true);
  runOnLine(BACK);
  stopMotors();
  setDefaultMonitor();
}