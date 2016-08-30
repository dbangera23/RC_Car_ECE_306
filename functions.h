//******************************************************************************
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

// required includes for operations
#include <stdbool.h>
#include <string.h>

// Function prototypes main
void main(void);

//Init
void Init_Conditions(void);

// Timers
void Init_Timers(void);
void waitForTimer(unsigned int UpTo);
void startTimer(void);
unsigned int stopTimer(void);
void startCountdown(unsigned int time);

// Function prototypes clocks
void Init_Clocks(void);
void five_msec_sleep(unsigned int fivemsec);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes timers
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char clock_state);
void Init_Port4(void);
void Init_PortJ(bool LED);

// Function prototypes Motors
void stopMotors(void);
bool setDutyL(unsigned int DutyPercent);
bool setDutyR(unsigned int DutyPercent);
void runMotorsForward(void);
void runMotorsReverse(void);
void spinR(void);
void spinL(void);
void stopMotorsR(void);
void stopMotorsL(void);

// Function prototypes Shapes
void runShape(unsigned int shape);
void runCircleL(void);
void runCircleR(void);
void runFigure8(void);
void runTriangle();
void runStraight(int bias,bool forward);
void runTriangleTurn(int bias);
void runStraightTillTime(unsigned int time, bool forward);
void runStraightForever(bool forward);
void runOnLine(unsigned int bias);

// Function prototypes LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void Display_Process(void);
void setDefaultMonitor(void);
void setSpecificLCD(char * words1, char * words2, char * words3, char * words4);
char* itoa(int value, char* result, int base);
unsigned int charToInt(char numChar[]);

// Function prototypes LED
void Init_LEDs(void);

// Function prototypes SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Function prototypes Switches
void Init_Switches(void);
void switch_control(void);
void Switches_Process_Main(void);
bool Switch_1_Read(void);
bool Switch_2_Read(void);

// Function prototypes function
void iterateFunction(void);
char * currentFunction(void);

// Function prototypes demo
void runDemo(void);
void runDemo3(void);
void runDemo4(void);
void runDemo5(void);
void runDemoHW8(void);
void runDemo6(void);
void runDemoHW9(void);
void runDemo8(void);

// Function Prototypes ADC
void ADC_Process(void);
void Init_ADC(void);

// Function Prototypes Sensors
void CalibrateSensor(void);
unsigned int ReadSensor(unsigned int ADC);

//Function Prototypes UART
void init_eUART_A(void);
void setBaudRate(bool fast);
void sendData(char* message);
char * receiveData(void);
void clearBufferRX(void);

//Function Prototypes HW9Menu
void ResistorMenu(void);
void setResistorLCD(char * color, char * value);
void ShapeMenu(void);
void SongMenu(void);