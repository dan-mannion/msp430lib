#include "msp430lib.h"
#include "lcd.h"
void main(){
	systemInit();

	char control_port = PORT1;
	char write_enable_pin = 7;//Originall 1.4
	char data_cmd_sel = 6;//Originally 1.3
	char data_port = PORT2;
	struct LCD lcd = lcdInit(control_port, write_enable_pin, data_cmd_sel, data_port);

	delayMillisecondTimer1(500);
	lcdDisplayOn(&lcd);
	//lcdClearScreen(&lcd);
	int r,c;
	char r1[] = {0,0,50,50};
	char r2[] = {50,50,100,100};
	char red[] = {10,10,10};
	char green[] = {10,20,10};
	char blue[] = {10,30,10};
	char brown[] = {10,40,10};
	char black[] = {0,0,0};
	char *colours[] = {black, red, green, blue, brown};//Need to double check this is working properly. Not sure on syntax.

	while(1){
		for(c=0;c<5;c++){
			lcdDrawRectangle(&lcd, r1[0],r1[1],r1[2],r1[3], colours[c][0],colours[c][1],colours[c][2]);
			delayMillisecondTimer1(500);
		}

	}
}
