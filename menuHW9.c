//******************************************************************************
//
//  Description: This file contains the HW9 Menu code
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
// Function name: ResistorMenu
//
// Description: Set up the menu for the Resistors
// 
// Passed: None
// Locals: unsigned int thumbPosition
//         unsigned int oldPosition
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void ResistorMenu(void){
  unsigned int oldPosition = START;
  while(ALWAYS){
    unsigned int thumbPosition = ReadSensor(ADC_THUMB);
    if(thumbPosition == oldPosition)
      continue;
    oldPosition = thumbPosition;
    waitForTimer(LCD_WAIT);
    if(thumbPosition<RES_MENU10_1){
      setResistorLCD("Black","0");
    }else if(thumbPosition<RES_MENU10_2){
      setResistorLCD("Brown","1");
    }else if(thumbPosition<RES_MENU10_3){
      setResistorLCD("Red","2");
    }else if(thumbPosition<RES_MENU10_4){
      setResistorLCD("Orange","3");
    }else if(thumbPosition<RES_MENU10_5){
      setResistorLCD("Yellow","4");
    }else if(thumbPosition<RES_MENU10_6){
      setResistorLCD("Green","5");
    }else if(thumbPosition<RES_MENU10_7){
      setResistorLCD("Blue","6");
    }else if(thumbPosition<RES_MENU10_8){
      setResistorLCD("Violet","7");
    }else if(thumbPosition<RES_MENU10_9){
      setResistorLCD("Grey","8");
    }else{
      setResistorLCD("White","9");
    }
    if(Switch_2_Read()){
      return;
    }
  }
}

/*===========================================================================
// Function name: setResistorLCD
//
// Description: Print out the value for the Resistor menu
// 
// Passed: char * color
//         char * value
// Locals: None
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void setResistorLCD(char * color, char * value){
  setSpecificLCD("Color",color,"Value",value);
}

/*===========================================================================
// Function name: ShapeMenu
//
// Description: Set up the menu for shapes
// 
// Passed: None
// Locals: unsigned int thumbPosition
//         unsigned int oldPosition
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void ShapeMenu(void){
  lcd_BIG_mid();
  char * shapes[] = {nothing,"Circle","Square","Triangle","Octagon","Pentagon","Hexagon","Cube","Oval","Sphere","Cylinder",nothing};
  unsigned int OldPosition = START;
  while(ALWAYS){
    unsigned int thumbPosition = ReadSensor(ADC_THUMB);
    if(thumbPosition == OldPosition)
      continue;
    OldPosition = thumbPosition;
    waitForTimer(LCD_WAIT);
    if(thumbPosition<RES_MENU10_1){
      setSpecificLCD(shapes[START],shapes[ONE],shapes[TWO],nothing);
    }else if(thumbPosition<RES_MENU10_2){
      setSpecificLCD(shapes[ONE],shapes[TWO],shapes[THREE],nothing);
    }else if(thumbPosition<RES_MENU10_3){
      setSpecificLCD(shapes[TWO],shapes[THREE],shapes[FOUR],nothing);
    }else if(thumbPosition<RES_MENU10_4){
      setSpecificLCD(shapes[THREE],shapes[FOUR],shapes[FIVE],nothing);
    }else if(thumbPosition<RES_MENU10_5){
      setSpecificLCD(shapes[FOUR],shapes[FIVE],shapes[SIX],nothing);
    }else if(thumbPosition<RES_MENU10_6){
      setSpecificLCD(shapes[FIVE],shapes[SIX],shapes[SEVEN],nothing);
    }else if(thumbPosition<RES_MENU10_7){
      setSpecificLCD(shapes[SIX],shapes[SEVEN],shapes[EIGHT],nothing);
    }else if(thumbPosition<RES_MENU10_8){
      setSpecificLCD(shapes[SEVEN],shapes[EIGHT],shapes[NINE],nothing);
    }else if(thumbPosition<RES_MENU10_9){
      setSpecificLCD(shapes[EIGHT],shapes[NINE],shapes[TEN],nothing);
    }else{
      setSpecificLCD(shapes[NINE],shapes[TEN],shapes[ELEVEN],nothing);
    }
    if(Switch_2_Read()){
      lcd_4line();
      return;
     }
  }
}

/*===========================================================================
// Function name: SongMenu
//
// Description: Set up the menu for the Song
// 
// Passed: None
// Locals: char song[]
//         unsigned int walk
//         unsigned int OldPosition
//         bool heading
//         unsigned int difference
// Returned: None
// Globals: None
//          
//
// Author: Dean Bangera
// Date: Fall 2015
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//===========================================================================*/
void SongMenu(void){
  char song[] = "We're the Red and White from State And we know we are the best. A hand behind our back, We can take on all the rest. Come over the hill, Carolina. Devils and Deacs stand in line. The Red and White from N.C. State. Go State!";
  lcd_BIG_mid();
  unsigned int walk = START;
  unsigned int OldPosition = ReadSensor(ADC_THUMB);
  bool heading = true;
  setSpecificLCD("Red","W","White",nothing);
  while(ALWAYS){
    waitForTimer(LCD_WAIT);
    unsigned int thumbPosition = ReadSensor(ADC_THUMB);
    if(thumbPosition < OldPosition){
      unsigned int difference = OldPosition - thumbPosition;
      if(difference < SONG_CHANGE_MIN){
        continue;
      }else if(difference >= SONG_CHANGE_MIN){
        walk++;
      }
      heading = !heading;
      char temp[] = {song[walk], '\0'};
      switch (heading){
      case false:
        setSpecificLCD("White", temp, "Red",nothing);
        break;
      case true:
        setSpecificLCD("Red", temp, "White",nothing);
        break;
      default:
        break;
      }
      OldPosition = thumbPosition;
    } else if(thumbPosition > OldPosition){
      OldPosition = thumbPosition;
    }
    if(Switch_2_Read()){
      lcd_4line();
      return;
    }
  }
}