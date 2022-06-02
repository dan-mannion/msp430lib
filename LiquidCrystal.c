#include "LiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"
//DM remove arduino.h and add required includes: gpio, timers. 
struct LiquidCrystal{
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
  

  void setRowOffsets(struct LiquidCrystal *lcd, int row1, int row2, int row3, int row4);
  void createChar(struct LiquidCrystal *lcd, uint8_t, uint8_t[]);
  void setCursor(struct LiquidCrystal *lcd, uint8_t, uint8_t); 
  size_t write(struct LiquidCrystal *lcd, uint8_t);
  void command(struct LiquidCrystal *lcd, uint8_t);
  
  void send(struct LiquidCrystal *lcd, uint8_t, uint8_t);
  void write4bits(struct LiquidCrystal *lcd,uint8_t);
  void pulseEnable(struct LiquidCrystal *lcd);


// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that it's in that state when a sketch starts (and the
// LiquidCrystal constructor is called).


struct LiquidCrystal liquidCrystalInit(uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3){

  struct LiquidCrystal lcd = LiquidCrystal;
  lcd._rs_pin = rs;
  lcd._rw_pin = rw;
  lcd._enable_pin = enable;
  
  lcd._data_pins[0] = d0;
  lcd._data_pins[1] = d1;
  lcd._data_pins[2] = d2;
  lcd._data_pins[3] = d3; 

  //Settings TODO: check these are correct for teh 
  lcd._displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  begin(16, 1);  

  return lcd;
}

void begin(struct LiquidCrystal *lcd, uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (lines > 1) {
    lcd->_displayfunction |= LCD_2LINE;
  }
  lcd->_numlines = lines;

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);  

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    lcd->_displayfunction |= LCD_5x10DOTS;
  }

  pinMode(lcd->_rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (_rw_pin != 255) { 
    pinMode(lcd->_rw_pin, OUTPUT);
  }
  pinMode(lcd->_enable_pin, OUTPUT);
  
  // Do these once, instead of every time a character is drawn for speed reasons.
  for (int i=0; i<((lcd->_displayfunction & LCD_8BITMODE) ? 8 : 4); ++i)
  {
    pinMode(lcd->_data_pins[i], OUTPUT);
   } 

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40 ms after power rises above 2.7 V
  // before sending commands. Arduino can turn on way before 4.5 V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(lcd->_rs_pin, LOW);
  digitalWrite(lcd->_enable_pin, LOW);
  if (lcd->_rw_pin != 255) { 
    digitalWrite(lcd->_rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (lcd->_displayfunction & LCD_8BITMODE)) {
    // this is according to the Hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    delayMicroseconds(150);

    // finally, set to 4-bit interface
    write4bits(0x02); 
  } else {
    // this is according to the Hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(LCD_FUNCTIONSET | lcd->_displayfunction);
    delayMicroseconds(4500);  // wait more than 4.1 ms

    // second try
    command(LCD_FUNCTIONSET | lcd->_displayfunction);
    delayMicroseconds(150);

    // third go
    command(LCD_FUNCTIONSET | lcd->_displayfunction);
  }

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | lcd->_displayfunction);  

  // turn the display on with no cursor or blinking default
  lcd->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display();

  // clear it off
  clear();

  // Initialize to default text direction (for romance languages)
  lcd->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(LCD_ENTRYMODESET | lcd->_displaymode);

}

void setRowOffsets(struct LiquidCrystal *lcd, int row0, int row1, int row2, int row3)
{
  lcd->_row_offsets[0] = row0;
  lcd->_row_offsets[1] = row1;
  lcd->_row_offsets[2] = row2;
  lcd->_row_offsets[3] = row3;
}

/********** high level commands, for the user! */
void clear(struct LiquidCrystal *lcd)
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void home(struct LiquidCrystal *lcd)
{
  command(LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void setCursor(struct LiquidCrystal *lcd, uint8_t col, uint8_t row)
{
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/ 0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/ 0
  }
  
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
void noDisplay(struct LiquidCrystal *lcd) {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void display(struct LiquidCrystal *lcd) {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void noCursor(struct LiquidCrystal *lcd) {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor(struct LiquidCrystal *lcd) {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void noBlink(struct LiquidCrystal *lcd) {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink(struct LiquidCrystal *lcd) {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(struct LiquidCrystal *lcd) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(struct LiquidCrystal *lcd) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(struct LiquidCrystal *lcd) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(struct LiquidCrystal *lcd) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(struct LiquidCrystal *lcd) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(struct LiquidCrystal *lcd) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(struct LiquidCrystal *lcd, uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

void command(struct LiquidCrystal *lcd, uint8_t value) {
  send(value, LOW);
}

size_t write(struct LiquidCrystal *lcd, uint8_t value) {
  send(value, HIGH);
  return 1; // assume success
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void send(struct LiquidCrystal *lcd, uint8_t value, uint8_t mode) {
  digitalWrite(_rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    digitalWrite(_rw_pin, LOW);
  }
  
  if (_displayfunction & LCD_8BITMODE) {
    write8bits(value); 
  } else {
    write4bits(value>>4);
    write4bits(value);
  }
}

void pulseEnable(struct LiquidCrystal *lcd) {
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);    
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450 ns
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100);   // commands need >37 us to settle
}

void write4bits(struct LiquidCrystal *lcd, uint8_t value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }

  pulseEnable();
}

