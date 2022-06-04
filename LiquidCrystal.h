#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include <inttypes.h>
#include <msp430.h>
#include "macros.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


  struct LiquidCrystal{
  uint8_t _pin_port;
  uint8_t _rs_pin; // LOW: command. HIGH: character.
  uint8_t _rw_pin; // LOW: write to LCD. HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[4];

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines;
  uint8_t _row_offsets[4];
};

  struct LiquidCrystal liquidCrystalInit(int _pin_port, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    
  void lcdBegin(struct LiquidCrystal *lcd, uint8_t cols, uint8_t rows, uint8_t charsize);
  void lcdPrint(struct LiquidCrystal *lcd, char *str_p);

  void lcdClear(struct LiquidCrystal *lcd);
  void lcdHome(struct LiquidCrystal *lcd);

  void lcdNoDisplay(struct LiquidCrystal *lcd);
  void lcdDisplay(struct LiquidCrystal *lcd);
  void lcdNoBlink(struct LiquidCrystal *lcd);
  void lcdBlink(struct LiquidCrystal *lcd);
  void lcdNoCursor(struct LiquidCrystal *lcd);
  void lcdCursor(struct LiquidCrystal *lcd);
  void lcdScrollDisplayLeft(struct LiquidCrystal *lcd);
  void lcdScrollDisplayRight(struct LiquidCrystal *lcd);
  void lcdLeftToRight(struct LiquidCrystal *lcd);
  void lcdRightToLeft(struct LiquidCrystal *lcd);
  void lcdAutoscroll(struct LiquidCrystal *lcd);
  void lcdNoAutoscroll(struct LiquidCrystal *lcd);



#endif
