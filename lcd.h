#ifndef LCD_H
#define LCD_H

#define cmd_DISPON  0x29
#define cmd_DISPOFF  0x28
#define cmd_WRITERAM 0x2c
#define cmd_INVON 0x21
#define cmd_INVOFF 0x20
#define cmd_SLPOUT 0x11
#define cmd_COLMOD 0x3a
#define opt_RGB565 0x05
#define cmd_CASET 0x2a
#define cmd_RASET 0x2b

struct LCD{
	char control_port;
	char chip_select_pin;
	char write_enable_pin;
	char data_command_select_pin;
	char data_bus_port;
};


struct LCD lcdInit();
void lcdDisplayOn(struct LCD *lcd);
void lcdDrawRectangle(struct LCD *lcd, char xstart, char ystart, char xend, char yend, char colour[]);
void lcdClearScreen(struct LCD *lcd);

#endif