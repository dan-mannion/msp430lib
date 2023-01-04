#include "msp430lib.h"
#include "lcd.h"
void main(){
	systemInit();

	struct LCD lcd = lcdInit();

	delayMillisecondTimer1(500);
	lcdDisplayOn(&lcd);
	lcdClearScreen(&lcd);
	int r,c;
	char r1[] = {0,0,10,10};
	char r2[] = {50,50,100,100};
	char red[] = {31,0,0};
	char green[] = {0,31,0};
	char blue[] = {0,0,31};
	char brown[] = {26,32,5};
	char *colours[] = {red, green, blue};//Need to double check this is working properly. Not sure on syntax.

	while(1){
		for(c=0;c<3;c++){
			lcdDrawRectangle(&lcd, r1[0],r1[1],r1[2],r1[3], (colours[c]));
			delayMillisecondTimer1(500);
			lcdDrawRectangle(&lcd, r2[0],r2[1],r2[2],r2[3], (colours[c]));
			delayMillisecondTimer1(500);
		}

	}
}
