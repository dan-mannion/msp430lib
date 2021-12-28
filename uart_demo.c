#include "uart.h"

void main(){
	stopWatchdogTimer();	
	uartInit();	
	char str[] = "hello world";
	uartPrintln(&str[0]);
	while(1){
		//uartWriteChar('X');
	}
	
}
