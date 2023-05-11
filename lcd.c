#include "lcd.h"
#include "gpio.h"
#include "timer.h"
struct LCD lcdInit(char control_port, char write_enable, char data_cmd_sel, char data_port){
	//Initialises and returns a lcd struct
	struct LCD lcd; 
	lcd.control_port = control_port;
	lcd.chip_select_pin = 5;
	lcd.write_enable_pin = write_enable;
	lcd.data_command_select_pin = data_cmd_sel;
	lcd.data_bus_port = data_port;	
	
	//Initilise gpio pins. 
	setPinMode(lcd.control_port, lcd.chip_select_pin, OUTPUT);
	writePinOutput(lcd.control_port, lcd.chip_select_pin, LOW);
	setPinMode(lcd.control_port, lcd.write_enable_pin, OUTPUT);
	writePinOutput(lcd.control_port, lcd.write_enable_pin, HIGH);
	setPinMode(lcd.control_port, lcd.data_command_select_pin, OUTPUT);
	writePinOutput(lcd.control_port, lcd.data_command_select_pin, HIGH);

	//Initialise data pins
	int n=0;
	for (n=0;n<8;n++){
		selectPinFunction(lcd.data_bus_port, n, SEL_IO);
		setPinMode(lcd.data_bus_port, n, OUTPUT);
	}	
	writeCharToPortOutput(lcd.data_bus_port, 0);

	return lcd;
}

void lcdWriteCommand(struct LCD *lcd, unsigned char cmd){
	//Indicate the data to be sent is a command
	writePinOutput(lcd->control_port, lcd->data_command_select_pin, LOW);
	//Inidicate to chip we want to write
	writePinOutput(lcd->control_port, lcd->write_enable_pin, LOW);
	//Select chip
	//writePinOutput(lcd->control_port, lcd->chip_select_pin, LOW);
	//Write to datalines
	writeCharToPortOutput(lcd->data_bus_port, cmd);
	//delayMillisecondTimer1(500);
	// INdicate data writte
	writePinOutput(lcd->control_port, lcd->write_enable_pin, HIGH);
	//Wait for chip to read command
	//delayMillisecondTimer1(1);
	//Signal end of transmission
	//writePinOutput(lcd->control_port, lcd->chip_select_pin, HIGH);
	writePinOutput(lcd->control_port, lcd->write_enable_pin, HIGH);
	writePinOutput(lcd->control_port, lcd->data_command_select_pin, HIGH);
}
void lcdWriteData(struct LCD *lcd, unsigned char cmd){
	//Indicate the data to be sent is a command
	writePinOutput(lcd->control_port, lcd->data_command_select_pin, HIGH);
	//Inidicate to chip we want to write
	writePinOutput(lcd->control_port, lcd->write_enable_pin, LOW);
	//Select chip
	//writePinOutput(lcd->control_port, lcd->chip_select_pin, LOW);
	//Write to datalines
	writeCharToPortOutput(lcd->data_bus_port, cmd);
	//delayMillisecondTimer1(250);
	// INdicate data writte
	writePinOutput(lcd->control_port, lcd->write_enable_pin, HIGH);
	//Wait for chip to read command
	//delayMillisecondTimer1(250);
	//Signal end of transmission
	//writePinOutput(lcd->control_port, lcd->chip_select_pin, HIGH);
}
void lcdSetColumns(struct LCD *lcd, char start, char end){
	lcdWriteCommand(lcd, cmd_CASET);	
	lcdWriteData(lcd, 0);//Upper 8 bits always set to 0 as max value is 127
	lcdWriteData(lcd, start); //Lower 8 bits are set according to the parameter
	lcdWriteData(lcd, 0);
	lcdWriteData(lcd, end);
}
void lcdSetRows(struct LCD *lcd, char start, char end){
	lcdWriteCommand(lcd, cmd_RASET);	
	lcdWriteData(lcd, 0);//Upper 8 bits always set to 0 as max value is 127
	lcdWriteData(lcd, start); //Lower 8 bits are set according to the parameter
	lcdWriteData(lcd, 0);
	lcdWriteData(lcd, end);
}
void lcdDisplayOn(struct LCD *lcd){
	lcdWriteCommand(lcd, cmd_SLPOUT);
	lcdWriteCommand(lcd, cmd_DISPON);
	lcdWriteCommand(lcd, cmd_COLMOD);
	lcdWriteData(lcd, opt_RGB565);
}
void lcdDrawRectangle(struct LCD *lcd, char xstart, char ystart, char xend, char yend, char red, char green, char blue){
	lcdSetColumns(lcd, ystart, yend);
	lcdSetRows(lcd, xstart, xend);	
	char x,y;
	char pixel_upper_byte;
	char pixel_lower_byte;
	//colour[0] = 0; colour[1]=0;colour[2]=31;
	char ru, gu, gl,bl;
	ru = ((red&0x1f)<<3)&(0xf8);
			gu = ((green&0x38)>>3)&(0x07);
			gl = ((green&0x07)<<3)&(0xE0);
			bl = (blue&0x1f);	
			pixel_upper_byte = ru|gu;	
			pixel_lower_byte = gl|bl;

	lcdWriteCommand(lcd, cmd_WRITERAM);
	for (y=ystart; y<=yend;y++){
		for(x=xstart;x<=xend;x++){
						/*pixel_upper_byte = (blue<<3)|(green>>3);
			pixel_lower_byte = (green<<5)|(red);*/
			lcdWriteData(lcd, pixel_upper_byte);
			lcdWriteData(lcd, pixel_lower_byte);
		}
	}
}
void lcdClearScreen(struct LCD *lcd){
	lcdDrawRectangle(lcd, 0,0,127,127,0,0,0);
}


