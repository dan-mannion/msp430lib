#include "msp430lib.h"

struct LCD{
	char control_port;
	char chip_select_pin;
	char write_enable_pin;
	char data_command_select_pin;
	char data_bus_port;
};

struct LCD lcdInit(){
	//Initialises and returns a lcd struct
	struct LCD lcd; 
	lcd.control_port = PORT1;
	lcd.chip_select_pin = 5;
	lcd.write_enable_pin = 4;
	lcd.data_command_select_pin = 3;
	lcd.data_bus_port = PORT2;	
	
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
void main(){
	systemInit();

	struct LCD lcd = lcdInit();

	unsigned char cmd_DISPON = (unsigned char) 0x29;
	unsigned char cmd_DISPOFF = (unsigned char) 0x28;
	unsigned char cmd_WRITERAM = (unsigned char) 0x2c;
	unsigned char cmd_INVON = (unsigned char) 0x21;
	unsigned char cmd_INVOFF = (unsigned char) 0x20;
	unsigned char cmd_SLPOUT = (unsigned char) 0x11;
	unsigned char cmd_COLMOD = 0x3a;
	
		//writePinOutput(lcd.control_port, lcd.chip_select_pin, HIGH);
		//delayMillisecondTimer1(500);
		writePinOutput(lcd.control_port, lcd.chip_select_pin, LOW);
		delayMillisecondTimer1(500);
		lcdWriteCommand(&lcd, cmd_SLPOUT);
		lcdWriteCommand(&lcd, cmd_DISPON);
		lcdWriteCommand(&lcd, cmd_COLMOD);
		lcdWriteData(&lcd, 0x03);
		lcdWriteCommand(&lcd, cmd_WRITERAM);
	int n;
	while(1){
		/*lcdWriteCommand(&lcd, cmd_DISPON);
		for(n=0;n<2;n++)
			delayMillisecondTimer1(500);
		lcdWriteCommand(&lcd, cmd_DISPOFF);
		for(n=0;n<2;n++)
			delayMillisecondTimer1(500);
		*/	
		//lcdWriteCommand(&lcd, cmd_WRITERAM);
		for(n=0;n<0xff;n++){
		lcdWriteData(&lcd, 0xaa);
		lcdWriteData(&lcd, 0x11);
		lcdWriteData(&lcd, 0xff);
		lcdWriteData(&lcd, 0x5c);
		lcdWriteData(&lcd, 0x31);
		}
		for(n=0;n<0xcc;n++){
			lcdWriteData(&lcd, 0xff);
		}
	//	lcdWriteCommand(&lcd, cmd_DISPOFF);
			
	}
}
