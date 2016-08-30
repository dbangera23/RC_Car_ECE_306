//******************************************************************************
//
//  Description: This file contains the interrupt code
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

//Global Variables
extern volatile unsigned int count;
extern volatile unsigned int count2;
extern volatile bool countdown;
extern volatile unsigned int countTimer;
extern volatile bool startWaiting;
extern volatile bool startWaiting2;
volatile bool switch1DB = false;
volatile bool switch2DB = false;
volatile bool switch1;
volatile bool switch2;
volatile unsigned int SW1DBCount;
volatile unsigned int SW2DBCount;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Channel;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
volatile bool read=false;

//------------------------------------------------------------------------------

/*===========================================================================
// Function name: Timer0_A0_ISR
//
// Description: Interrupt handler for a A0 timer. also handles part of the
//              debounces for switches
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: count
//          startWaiting
//          switch1DBCount
//          switch1
//          switch1DB
//          switch2DBCount
//          switch2
//          switch2DB
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
// TimerB0 0 Interrupt handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  TA0CCR0 += TA0CCR0_INTERVAL;
  if(startWaiting){
    count++;
  }
  if(startWaiting2){
    count2++;
  }
  if(countdown){
    countTimer--;
    if(countTimer==START) 
      countdown = false;
  }
  if(switch1){
    SW1DBCount++;
    if(SW1DBCount > DBOUNCESlEEP)
      switch1DB = false;
  }
  if(switch2){
    SW2DBCount++;
    if(SW2DBCount > DBOUNCESlEEP)
      switch2DB = false;
  }
}
  
/*===========================================================================
// Function name: Timer0_A0_ISR
//
// Description: Interrupt handler port 4 interrupts. switches and debounces
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: switch1DBCount
//          switch1
//          switch1DB
//          switch2DBCount
//          switch2
//          switch2DB
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
#pragma vector = PORT4_VECTOR
__interrupt void Port4_ISR(void){
  if((P4IFG & SW1) && (!switch1DB)){
      SW1DBCount = START;
      switch1DB = true;
      switch1 = true;
      PJOUT ^= LED1;
      P4IFG &= ~SW1;
  }
  if((P4IFG & SW2) && (!switch2DB)){
      SW2DBCount = START;
      switch2DB = true;
      switch2 = true;
      PJOUT ^= LED2;
      P4IFG &= ~SW2;
  }
}

/*===========================================================================
// Function name: ADC10_ISR
//
// Description: Interrupt handler ADC. 
// 
// Passed: None
// Locals: None
// Returned: None
// Globals: ADC_Channel
//          ADC_Right_Detect
//          ADC_Left_Detect
//          ADC_Thumb
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,TWELVE)) {
    case START: break; // No interrupt
    case TWO: break; // conversion result overflow
    case FOUR: break; // conversion time overflow
    case SIX: break; // ADC10HI
    case EIGHT: break; // ADC10LO
    case TEN: break; // ADC10IN
    case TWELVE:
      ADC10CTL0 &= ~ADC10ENC;
      switch(ADC_Channel++){
        case ADC_R_DETECT:
          ADC10MCTL0 = ADC10INCH_1;
          ADC_Right_Detect = ADC10MEM0; // Channel A3
          break;
        case ADC_L_DETECT:
          ADC10MCTL0 = ADC10INCH_3;
          ADC_Left_Detect = ADC10MEM0; // Channel A3
          break;
        case ADC_THUMB:
          ADC10MCTL0 = ADC10INCH_0;
          ADC_Thumb = ADC10MEM0; // Channel A3
          ADC_Channel = CLEAR;
          break;
      default: break;
      }
    default: break;
  }
}

/*===========================================================================
// Function name: USCI_A1_ISR
//
// Description: Interrupt handler USCI_A1. 
// 
// Passed: None
// Locals: unsigned int temp
// Returned: None
// Globals: usb_rx_ring_wr
//          USB_Char_Rx[]
//          ADC_Left_Detect
//          ADC_Thumb
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
#pragma vector=USCI_A1_VECTOR 
__interrupt void USCI_A1_ISR(void) {
  unsigned int temp;
  switch(__even_in_range(UCA1IV,EIGHT)) {
    case START: // Vector 0: No interrupts
      break;
    case TWO: // Vector 2: UCRXIFG
      temp = usb_rx_ring_wr;
      USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
      if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr = START; // Circular buffer back to beginning
        read = true;
      }
      break;
    case FOUR: // Vector 4: UCTXIFG
      break;
    case SIX: // Vector 6: UCSTTIFG
      break;
    case EIGHT: // Vector 8: UCTXCPTIFG
      break;
  default: break;
  }
}