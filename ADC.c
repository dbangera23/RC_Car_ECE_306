//******************************************************************************
//
//  Description: This file contains the ADC code
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
volatile unsigned int ADC_Channel;
volatile bool ADCRead;

/*===========================================================================
// Function name: Init_ADC
//
// Description: Set up the ADC to start reading from sensors and thumb
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
void Init_ADC(void){
ADC10CTL0 = CLEAR; // Clear ADC10CTL0
ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
ADC10CTL0 &= ~ADC10MSC; // Single Sequence
ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled

ADC10CTL1 = CLEAR; // Clear ADC10CTL1
ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
ADC10CTL1 |= ADC10SSEL_0; // MODCLK
ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion

ADC10CTL2 = CLEAR; // Clear ADC10CTL2
ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
ADC10CTL2 |= ADC10RES; // 10-bit resolution
ADC10CTL2 &= ~ADC10DF; // Binary unsigned
ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps

ADC10MCTL0 = CLEAR; // Clear ADC10MCTL0
ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

/*===========================================================================
// Function name: ADC_Process
//
// Description: Ping the ADC system to do a read
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
void ADC_Process(){
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
}