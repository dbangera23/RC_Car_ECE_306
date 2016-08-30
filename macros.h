//******************************************************************************
//
//  Description: This file contains the macros code
//
//
//  Dean Bangera
//  Fall 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define NEVER                   (0)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CSLOCK               (0x01) // Any incorrect password locks registers
#define MAINLOOPDONE          (250)
#define CLOCKINIT              (50)
// MOTORS
#define DUTY_START           0x0001
#define DUTY_CLEAR           0x0000
#define HALF_DUTY            0x001F
#define ONE_DUTY             0X0001
#define THIRTY_DUTY          0x0007
#define FULL_DUTY            0x03FF
#define TWO                     (2)
// LCD
#define LCD_HOME_L1	        0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0
#define MAXBASE                 (32)
// SWTICH
#define DBOUNCESlEEP            40
#define SHAPESLEEP              250
// SHAPES
#define CIRCLE                  (0)
#define FIGURE8                 (1)
#define TRIANGLE                (2)
#define START                   (0)
#define ONE                     (1)
#define CIRCLEEND               (27)
#define SHAPEBIAS               (2)
#define TRIANGLE_LOOP           (3)
#define TRIANGLE_TURN           (10)
#define WHEEL_BIAS              (2)
#define TRIANGLE_BIAS           (1)
#define STRAIGHT_SEC            (6)
#define STRAIGHT_TWOSEC         (14)
// INIT
#define DISPLINESIZE            (11)
// Pins
#define CLEAR                   (0x00)
//Port 1 Pins
#define V_DETECT_R              (0x01)
#define V_DETECT_L              (0x02)
#define IR_LED                  (0x04)
#define V_THUMB                 (0x08)
#define SPI_CS_LCD              (0x10)
#define SA0_LCD                 (0x20)
#define SPI_SIMO                (0x40)
#define SPI_SOMI                (0x80)
#define SIMO_B                  (0x40)
#define SOMI_B                  (0x80)

//Port 2 Pins
#define USB_TXD                 (0x01)
#define USB_RXD                 (0x02)
#define SPI_SCK                 (0x04)
#define UNKNOWN23               (0x08)
#define UNKNOWN24               (0x10)
#define CPU_TXD                 (0x20)
#define CPU_RXD                 (0x40)
#define UNKNOWN27               (0x80)

//Port 3 Pins
#define X                       (0x01)
#define Y                       (0x02)
#define ZPIN                    (0x04)
#define LCD_BACKLITE            (0x08)
#define USE_R_FORWARD           (0x00)
#define USE_SMCLK               (0x01)
#define SET_SMCLK               (0x10)
#define R_FORWARD               (0x10)
#define R_REVERSE               (0x20)
#define L_FORWARD               (0x40)
#define L_REVERSE               (0x80)

//Port 4 Pins
#define SW1                     (0x01)
#define SW2                     (0x02)

//Port J Pins
#define IOT_FACTORY             (0x01)
#define IOT_WAKEUP              (0x02)
#define IOT_STA_MINIAP          (0x04)
#define RESET                   (0x08)
#define XINR                    (0x10) // XINR
#define XOUTR                   (0x20) // XOUTR
#define CLEAR_REGISTER          (0X0000)

// Clock
#define FLLN_BITS               (0x03ffu)
#define FLLN_255                (0x00ffu)

// Timers
#define TA0CCR0_INTERVAL        (2500)
#define HALF_SECOND             (100)
#define FULL_SECOND             (200)
#define FIVE_SECONDS            (1000)
#define TWO_SECONDS             (400)
#define QUARTER_SECOND          (50)
#define LCD_WAIT                (40)

// Function
#define FUNCTIONNUM             (6)
#define DEMO3                   (0)
#define DEMO4                   (1)
#define DEMO5                   (2)
#define DEMO6                   (4)
#define DEMO8                   (6)
#define HW8                     (3)
#define HW9                     (5)
#define TURNONE                 (17)
#define DEMO8TIME               (14000)
#define BACK                    (1000)
//ADC
#define ADC_R_DETECT            (1)
#define ADC_L_DETECT            (2)
#define ADC_THUMB               (3)
#define THREE                   (3)
#define FOUR                    (4)
#define FIVE                    (5)
#define SIX                     (6)
#define SEVEN                   (7)
#define EIGHT                   (8)
#define NINE                    (9)
#define TEN                     (10)
#define ELEVEN                  (11)
#define TWELVE                  (12)

//SERIAL
#define BR_INTERVAL_FAST        (4)    //4
#define BR_INTERVAL_SLOW        (52)     //52
#define SLOWBAUDCONFIG          (0x5551)        //0X4911
#define FASTBAUDCONFIG          (0x4911)
#define SMALL_RING_SIZE         (16)
#define LARGE_RING_SIZE         (32)

//Homework 9 Menu
#define ADC_MENU3_1             (341)
#define ADC_MENU3_2             (682)
#define RES_MENU10_1            (102)
#define RES_MENU10_2            (204)
#define RES_MENU10_3            (306)
#define RES_MENU10_4            (408)
#define RES_MENU10_5            (510)
#define RES_MENU10_6            (612)
#define RES_MENU10_7            (714)
#define RES_MENU10_8            (816)
#define RES_MENU10_9            (918)
#define SONG_CHANGE_MIN         (100)