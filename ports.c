//******************************************************************************
//
//  Description: This file contains the ports initializing code
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

/*===========================================================================
// Function name: Init_Ports
//
// Description: Runs the initialization of all ports with default settings
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
void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_R_FORWARD);
  Init_Port4();
  Init_PortJ(false);
}

/*===========================================================================
// Function name: main
//
// Description: Initialization code for all of port1
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
void Init_Port1(void){
  P1SEL0 = CLEAR;        //Clear SEL0 pins
  P1SEL1 = CLEAR;        //Clear SEL1 pins
  P1DIR  = CLEAR;        //Clear Direction pins
  P1SEL0 |= V_DETECT_R;         //Setting SEL0 pins
  P1SEL0 |= V_DETECT_L;
  P1SEL0 &= ~IR_LED;
  P1SEL0 |= V_THUMB;
  P1SEL0 &= ~SPI_CS_LCD;
  P1SEL0 &= ~SA0_LCD;
  P1SEL0 &= ~SPI_SIMO;
  P1SEL0 &= ~SPI_SOMI;
  P1SEL1 |= V_DETECT_R;         //Setting SEL1 pins
  P1SEL1 |= V_DETECT_L;
  P1SEL1 &= ~IR_LED;
  P1SEL1 |= V_THUMB;
  P1SEL1 &= ~SPI_CS_LCD;
  P1SEL1 &= ~SA0_LCD;
  P1SEL1 |= SPI_SIMO;
  P1SEL1 |= SPI_SOMI;
  P1OUT  &= ~V_DETECT_R;        //Setting  initial value           
  P1OUT  &= ~V_DETECT_L;
  P1OUT  &= ~IR_LED;
  P1OUT  &= ~V_THUMB;
  P1OUT  |= SPI_CS_LCD;         
  P1OUT  &= ~SA0_LCD;
  P1OUT  &= ~SPI_SIMO;
  P1OUT  &= ~SPI_SOMI;
  P1DIR  |= IR_LED;             //Setting Direction pins
  P1DIR  |= SPI_CS_LCD;
  P1DIR  |= SA0_LCD;
  P1REN  |= SPI_SOMI;           //Setting pull up resistor

}

/*===========================================================================
// Function name: Init_Port2
//
// Description: Initializes everything in port 2
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
void Init_Port2(void){
  P2SEL0 = CLEAR;                //Clearing pins to properly initialize
  P2SEL1 = CLEAR;
  P2DIR  = CLEAR;
  P2SEL0 &= ~USB_TXD;           //Setting SEL0 pins
  P2SEL0 &= ~USB_RXD;
  P2SEL0 &= ~SPI_SCK;
  P2SEL0 &= ~UNKNOWN23;
  P2SEL0 &= ~UNKNOWN24;
  P2SEL0 &= ~CPU_TXD;
  P2SEL0 &= ~CPU_RXD;
  P2SEL0 &= ~UNKNOWN27;
  P2SEL1 |= USB_TXD;            //Setting SEL1 pins
  P2SEL1 |= USB_RXD;
  P2SEL1 |= SPI_SCK;
  P2SEL1 &= ~UNKNOWN23;
  P2SEL1 &= ~UNKNOWN24;
  P2SEL1 |= CPU_TXD;
  P2SEL1 |= CPU_RXD;
  P2SEL1 &= ~UNKNOWN27;
  P2OUT  &= ~USB_TXD;           //Setting initial value pin
  P2OUT  &= ~USB_RXD;
  P2OUT  |= SPI_SCK;            
  P2OUT  &= ~UNKNOWN23;
  P2OUT  &= ~UNKNOWN24;
  P2OUT  &= ~CPU_TXD;
  P2OUT  &= ~CPU_RXD;
  P2OUT  &= ~UNKNOWN27;
  P2DIR  &= ~UNKNOWN23;                 //Setting Direction pins
  P2DIR  &= ~UNKNOWN24;
  P2DIR  &= ~UNKNOWN27;
  P2REN  &= ~UNKNOWN23;
  P2REN  &= ~UNKNOWN24;
  P2REN  &= ~UNKNOWN27;            //Setting pull up resistor pin
}

/*===========================================================================
// Function name: Init_Port3
//
// Description: Initializes everything in port 3 with a char argument to specify
//              using the smclk or R_FORWARD
// 
// Passed: char clock_state
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void Init_Port3(char clock_state){
 P3SEL0 = CLEAR; // P3 set as I/0
 P3SEL1 = CLEAR; // P3 set as I/0
 P3DIR = CLEAR; // Set P3 direction to input
  if(clock_state == USE_SMCLK){
     P3SEL0 |= SET_SMCLK;
     P3SEL1 |= SET_SMCLK;
     P3OUT |= SET_SMCLK;
     P3OUT |= SET_SMCLK;
  }
  P3SEL1  &= ~X;                //Setting SEL1 pins
  P3SEL1  &= ~Y;
  P3SEL1  &= ~ZPIN;
  P3SEL1  &= ~LCD_BACKLITE;
  if(clock_state == USE_R_FORWARD)
    P3SEL1  &= ~R_FORWARD;
  P3SEL1  &= ~R_REVERSE;
  P3SEL1  &= ~L_FORWARD;
  P3SEL1  &= ~L_REVERSE;
  P3SEL0  &= ~X;                        //setting SEL0 pins
  P3SEL0  &= ~Y;
  P3SEL0  &= ~ZPIN;
  P3SEL0  &= ~LCD_BACKLITE;
  if(clock_state == USE_R_FORWARD)
    P3SEL0  &= ~R_FORWARD;
  P3SEL0  &= ~R_REVERSE;
  P3SEL0  &= ~L_FORWARD;
  P3SEL0  &= ~L_REVERSE;
  P3DIR |= LCD_BACKLITE;        //Setting Direction pins, NO SEL0 or SEL1 pins
  if(clock_state == USE_R_FORWARD)
    P3DIR |= R_FORWARD;
  P3DIR |= R_REVERSE;
  P3DIR |= L_FORWARD;
  P3DIR |= L_REVERSE;
  P3REN &= ~X;                  //Setting Pull up resistor pins
  P3REN &= ~Y;
  P3REN &= ~ZPIN;
}

/*===========================================================================
// Function name: Init_Port4
//
// Description: Initializes everything in port 4. Sets up interrupt for port 4
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
void Init_Port4(void){
  P4SEL0 = CLEAR;                //Clearing pins to properly initialize
  P4SEL1 = CLEAR;
  P4DIR  = CLEAR;
  P4SEL0 &= ~ SW1;              //settings SEL0 pins
  P4SEL0 &= ~ SW2;
  P4SEL1 &= ~ SW1;              //setting SEL1 pins
  P4SEL1 &= ~ SW2;
  P4OUT |= SW1;                 //Setting Initial value Pins
  P4OUT |= SW2;
  P4REN |= SW1;                 //Setting pull up resistor pins
  P4REN |= SW2;
  P4IES |= SW1; // P4.0 Hi/Lo edge interrupt
  P4IES |= SW2; // P4.0 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // P4 IFG SW1 cleared
  P4IFG &= ~SW2; // P4 IFG SW2 cleared
  // Start / Enable Interrupt
  P4IE |= SW1; // P4.0 SW1 interrupt Enabled
  P4IE |= SW2; // P4.0 SW2 interrupt enabled
}

/*===========================================================================
// Function name: Init_PortJ
//
// Description: Initializes everything in port J. With an argument to specify 
//              Regular operation or LED operation.
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
void Init_PortJ(bool LED){
  PJSEL0 = CLEAR;                //Clearing pins to properly initialize
  PJSEL1 = CLEAR;
  PJDIR  = CLEAR;
  
  if(LED){
    PJSEL0 &= ~LED1; 
    PJSEL1 &= ~LED1; 
    PJOUT &= ~LED1; 
    PJDIR |= LED1;              // Set PJ Pin 1 direction to output 

    PJSEL0 &= ~LED2; 
    PJSEL1 &= ~LED2; 
    PJOUT &= ~LED2; 
    PJDIR |= LED2;              // Set PJ Pin 2 direction to output 

    PJSEL0 &= ~LED3; 
    PJSEL1 &= ~LED3; 
    PJOUT &= ~LED3; 
    PJDIR |= LED3;              // Set PJ Pin 3 direction to output 

    PJSEL0 |= LED5; 
    PJSEL0 |= LED6;
  }
  else{
    PJSEL0 &= ~IOT_FACTORY;           //setting SEL0 pins
    PJSEL0 &= ~IOT_WAKEUP;
    PJSEL0 &= ~IOT_STA_MINIAP;
    
    PJSEL1 &= ~IOT_FACTORY;               //Setting SEL1 pin
    PJSEL1 &= ~IOT_WAKEUP;
    PJSEL1 &= ~IOT_STA_MINIAP;
    
    PJDIR |= IOT_FACTORY;           //setting Direction Pins
    PJDIR |= IOT_WAKEUP;
    PJDIR |= IOT_STA_MINIAP; 
  }
   PJSEL0 &= ~RESET;                    //Setting LED4 to reset
   PJSEL1 &= ~RESET; 
   PJDIR |= RESET;
}