//******************************************************************************
//
//  Description: This file contains the serial communication code
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

volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_tx_ring_rd;
char received[SMALL_RING_SIZE];
extern volatile bool read;


/*===========================================================================
// Function name: init_eUART_A
//
// Description: Set up all the code to initialize the Serialize comm on A1
// 
// Passed: None
// Locals: unsigned int i
// Returned: None
// Globals: USB_Char_Rx
//          usb_rx_ring_wr
//          usb_rx_ring_rd
//          usb_tx_ring_wr
//          usb_rx_ring_rd
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void init_eUART_A(void){
  int i;
  for(i=START; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = CLEAR; // USB Rx Buffer
  }
  usb_rx_ring_wr = START;
  usb_rx_ring_rd = START;
  for(i=START; i<SMALL_RING_SIZE; i++){ // May not use this
    USB_Char_Tx[i] = CLEAR; // USB Tx Buffer
  }
  usb_tx_ring_wr = START;
  usb_tx_ring_rd = START;
  
  UCA1CTLW0 = CLEAR;
  UCA1CTLW0 |= UCSSEL__SMCLK;         //Select Clock source, SMCLK
  
  UCA1CTLW0 |= UCSWRST;         //Set RESET flag
    
  UCA1CTL1 &= ~UCSWRST;        //Clear reset flag
  UCA1IE |= UCRXIE;             //Enable the RX interrupt
}

/*===========================================================================
// Function name: setBaudRate
//
// Description: Setting a baud rate with an option to set it to fast and slow
//              fast = 115200, slow = 9600
// 
// Passed: bool fast
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void setBaudRate(bool fast){
  if(fast){       //Set fast baud rate
    UCA1BRW =BR_INTERVAL_FAST;
    UCA1MCTLW = FASTBAUDCONFIG;   
  }else{//Set fast baud rate
    UCA1BRW = BR_INTERVAL_SLOW;
    UCA1MCTLW = SLOWBAUDCONFIG;
  }
}

/*===========================================================================
// Function name: sendData
//
// Description: Handles the sending of data out of the tx port
// 
// Passed: message
// Locals: None
// Returned: None
// Globals: usb_rx_ring_wr
//          usb_tx_ring_rd
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void sendData(char* message){
  usb_rx_ring_wr = START;
  for (usb_tx_ring_rd = START; usb_tx_ring_rd < SMALL_RING_SIZE; usb_tx_ring_rd++){ 
   waitForTimer(TEN);
   UCA1TXBUF = message[usb_tx_ring_rd];
  }
}

/*===========================================================================
// Function name: receiveData
//
// Description: This function handles the receiving of data
// 
// Passed: None
// Locals: unsigned int i
// Returned: char *
// Globals: USB_Char_Rx
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
char * receiveData(void){
  if(read){
    read = false;
    unsigned int temp = usb_rx_ring_rd;                         //Using a temp since two volatiles can't be used at the same time.
    int difference = usb_rx_ring_wr - temp;
    if(difference<=START)
      difference = SMALL_RING_SIZE-temp+usb_rx_ring_wr;
    unsigned int i;
    for(i = START; i < difference; i++) {
        received[i] = USB_Char_Rx[usb_rx_ring_rd++];
        if(usb_rx_ring_rd >= SMALL_RING_SIZE)
          usb_rx_ring_rd = START;
    }
    received[i] = '\n';
  }
  return received;
}

/*===========================================================================
// Function name: clearBufferRx
//
// Description: This handles clearing the receive buffer to make sure nothing
//              is overwritten
// 
// Passed: None
// Locals: i
// Returned: None
// Globals: USB_Char_Rx
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void clearBufferRX(void){
  for(int i =START;i < SMALL_RING_SIZE; i++){
     USB_Char_Rx[i] = CLEAR; 
     received[i] = CLEAR;
  }
}