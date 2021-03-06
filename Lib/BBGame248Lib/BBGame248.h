
//========== BBGAME248 HARDWARE LIBARY ==========

// Date: May 14, 2019


#ifndef LIBHARDWARE_H
#define LIBHARDWARE_H

#include <Arduino.h>

class GameBoard
{
public:
  void CheckID();
  bool IsCorrectGameID();
  void WriteGameID();
};

#define EEPROM_ID       0 /*length 7*/
#define EEPROM_RNDSEED  7
#define EEPROM_GAMEMODE 8
#define EEPROM_MSGINDEX 9
#define EEPROM_MSGSPEED 10



//---------- DISPLAY CLASS ----------

// Purpose: To abstract the BBGame114 LED matrix as a display, 
// with methods/functions to Clear the display, draw a dot,
// draw horizontal or vertical lines and draw text.


class Display
{
public:
  void Setup(byte _numCols, byte _numRows);
  void Clear();
  static byte MakeBit(byte y);
  byte SetPixel(byte x, byte y, byte c = 1);
  void SetColumnByte(byte x, byte bits);
  void vLine(byte x, byte y1 = 255, byte y2 = 255);
  void hLine(byte y, byte x1 = 255, byte x2 = 255);
  void hShift(signed char dir = -1, bool wrap = false);
  void vShift(signed char dir = -1, bool wrap = false);
  byte numCols;
  byte numRows;

private:
    void SetupTimedRefresh();
    void hShiftRow(byte row, signed char dir, bool wrap);
};

#define ON  1
#define OFF 0


//---------- BUTTONS CLASS ----------

// Purpose: To simplify the use of the pushbuttons on the 
// BBGame114 board. The BtnPressed() method/function only 
// returns true one time after a buttons is pressed, and it 
// is not reset until the button is released.


#define BTN1 0
#define BTN2 1
#define BTN3 3
#define BTN4 2

class Buttons
{
public:
    void Setup();
    bool BtnPressed(byte i);
    bool BtnDown(byte i);
    bool AnyBtnDown();
    byte WaitAnyBtnPressed();
private:
  bool btnDown[4];
  bool btnWasNotPressed[4];
  void ReadButtons();
};


//---------- SOUND CLASS ----------

// Purpose: To output sound tones through the piezoelectric
// speaker on the the BBGame114 board.


#define SNDPIN 5

class Sound
{
public:
    void Setup();
    void Update(int counter);
    void StartSound(byte _tone, byte _duration, bool _noisy = false);
private:
  byte tone;
  byte duration;
  bool noisy;
};


//---------- TEXTDISPLAY CLASS ----------

// Purpose: To draw alphanumeric characters and punctuation on the
// BBGame114 display.


class TextDisplay
{
public:
  TextDisplay(Display& _display);
  
  void DisplayText(String s, int pos = 0);
  void DisplayTextCentered(String s);
  void ScrollText(String s, int counter);
  int GetWidth(String s);
  int getScrollWidth(String s);

private:
  Display& display;
  void GetCharPixelData(char c, byte *np, byte const **p);
};


#endif //LIBHARDWARE_H

