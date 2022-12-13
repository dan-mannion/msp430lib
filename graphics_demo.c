#include "msp430lib.h"

struct LCD{
	char control_port;
	char chip_select_pin;
	char write_enable_pin;
	char data_command_select;
	char data_bus_port;
};

struct LCD lcdInit(){
	//Initialises and returns a lcd struct
	struct LCD lcd; 
	lcd.control_port = PORT1;
	lcd.chip_select_pin = 8;
	lcd.write_enable_pin = 7;
	lcd.data_command_select = 6;
	lcd.data_bus_port = PORT2;	
	return lcd;
}

void lcdWriteCommand(struct LCD *lcd, unsigned char cmd){
	//Inidicate to chip we want to write
	writePinOutput(lcd->control_port, lcd->write_enable_pin, LOW);
	//Indicate the data to be sent is a command
	writePinOutput(lcd->control_port, lcd->data_command_select, LOW);
	//Select chip
	writePinOutput(lcd->control_port, lcd->chip_select_pin, LOW);
	//Write to datalines
	P2OUT = cmd;
	// INdicate data writte
	writePinOutput(lcd->control_port, lcd->write_enable_pin, HIGH);
	//Wait for chip to read command
	delayMillisecondTimer1(10);
	//Signal end of transmission
	writePinOutput(lcd->control_port, lcd->chip_select_pin, HIGH);
	
	

}
void main(){
	systemInit();

	struct LCD lcd;

	unsigned char cmd_DISPON = (unsigned char)0x00101001;
	unsigned char cmd_DISPOFF = (unsigned char) 0x00101000;
	
	int n;	
	while(1){
		lcdWriteCommand(&lcd, cmd_DISPON);
		for(n=0;n<6;n++)
			delayMillisecondTimer1(500);
		lcdWriteCommand(&lcd, cmd_DISPOFF);
		for(n=0;n<6;n++)
			delayMillisecondTimer1(500);
	}

	/*setPinMode(1, 0, OUTPUT);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, LOW);
		for(i=0;i<delay;i++){;}
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,HIGH);
		for(i=0;i<delay;i++){;}
	}
	*/
}
