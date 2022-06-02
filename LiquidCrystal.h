#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include <inttypes.h>

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


struct LiquidCrystal liquidCrystalInit(uint8_t _pin_port, uint8_t rs, uint8_t rw, uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
    
  void begin(struct LiquidCrystal *lcd, uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear(struct LiquidCrystal *lcd);
  void home(struct LiquidCrystal *lcd);

  void noDisplay(struct LiquidCrystal *lcd);
  void display(struct LiquidCrystal *lcd);
  void noBlink(struct LiquidCrystal *lcd);
  void blink(struct LiquidCrystal *lcd);
  void noCursor(struct LiquidCrystal *lcd);
  void cursor(struct LiquidCrystal *lcd);
  void scrollDisplayLeft(struct LiquidCrystal *lcd);
  void scrollDisplayRight(struct LiquidCrystal *lcd);
  void leftToRight(struct LiquidCrystal *lcd);
  void rightToLeft(struct LiquidCrystal *lcd);
  void autoscroll(struct LiquidCrystal *lcd);
  void noAutoscroll(struct LiquidCrystal *lcd);



#endif