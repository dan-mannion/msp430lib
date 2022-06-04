#include "msp430lib.h"
#include "LiquidCrystal.h"

void main(){
	systemInit();
	uartInit();	

	uint8_t rs = 0;
	// we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
	uint8_t rw = 255;
       	uint8_t	en = 1;
	uint8_t d0 = 2;
	uint8_t d1 = 3;
	uint8_t d2 = 4;
	uint8_t d3 = 5;

	struct LiquidCrystal lcd = liquidCrystalInit(PORT2,rs,rw,en,d0,d1,d2,d3);
	begin(&lcd,16,1,LCD_5x8DOTS);
	home(&lcd);
	cursor(&lcd);
	//print("Hello");	
	char str[] = "hello world";
	uartPrintln(&str[0]);
	while(1){
		//uartWriteChar('X');
	}
	
}
