//******************************************************************************
//
//  Description: This file contains the Sensor code
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

//Global Variables
volatile unsigned int ADC_Thumb;
volatile unsigned int ADC_Right_Detect;
volatile unsigned int ADC_Left_Detect;
extern volatile bool ADCRead;
volatile unsigned int LThreshold;
volatile unsigned int RThreshold;

/*===========================================================================
// Function name: CalibrateSensor
//
// Description: Calibrates the sensor to work in the particular environment
// 
// Passed: None
// Locals: RDetectOnWhite
//         LDetectOnWhite
//         RDetectOnBlack
//         LDetectOnBlack
// Returned: None
// Globals: RThreshold
//          LThreshold
//
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void CalibrateSensor(void){
  P1OUT  |= IR_LED; 
  ReadSensor(ADC_R_DETECT);
  waitForTimer(ONE);
  ReadSensor(ADC_L_DETECT);
  waitForTimer(ONE);
 //P1OUT &= ~IR_LED;                                             //Led off, On the black line
 // unsigned int RDetectOffBlack = ReadSensor(ADC_R_DETECT);
 //unsigned int LDetectOffBlack = ReadSensor(ADC_L_DETECT);
  
                                              //LED On, Off the black Line
  setSpecificLCD("Place Off","Black Line","Press","SW1");       //Tell user to place car off the black line
  while(!Switch_1_Read()){}                             //WAIT FOR THE BUTTON PRESS
  
  unsigned int RDetectOnWhite = ReadSensor(ADC_R_DETECT);
  waitForTimer(TWO);

  unsigned int LDetectOnWhite = ReadSensor(ADC_L_DETECT);
   waitForTimer(TWO);

  setSpecificLCD("Place On","Black Line","Press","SW1");        //Tell user to place car on black line
  while(!Switch_1_Read()){}                             //WAIT FOR THE BUTTON PRESS
 
  P1OUT  |= IR_LED;                                             //LED On, On the black Line
  unsigned int RDetectOnBlack = ReadSensor(ADC_R_DETECT);
  waitForTimer(TWO);
  unsigned int LDetectOnBlack = ReadSensor(ADC_L_DETECT);
  waitForTimer(TWO);
  //P1OUT &= ~IR_LED;                                             //Led off, Off the black line
  //unsigned int RDetectOffWhite = ReadSensor(ADC_R_DETECT);
  //unsigned int LDetectOffWhite = ReadSensor(ADC_L_DETECT);
  
  RThreshold = (RDetectOnBlack + RDetectOnWhite)>> ONE;                                                 // Set appropriate thresholds
  LThreshold = (LDetectOnBlack + LDetectOnWhite)>> ONE;
}

/*===========================================================================
// Function name: ReadSensor
//
// Description: Reads the requested sensor values
// 
// Passed: None
// Locals: None
// Returned: unsigned int
// Globals: ADC_Right_Detect
//          ADC_Left_Detect
//          ADC_Thumb
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
unsigned int ReadSensor(unsigned int ADC){
  ADC_Process();
  ADC_Process();
  ADC_Process();
  switch(ADC){
    case ADC_R_DETECT:
      return ADC_Right_Detect;
      break;
    case ADC_L_DETECT:
      return ADC_Left_Detect;
      break;
    case ADC_THUMB:
      return ADC_Thumb;
      break;
  }
  return NEVER;
}
      