#include "uart.h"

void main(){
	stopWatchdogTimer();	
	uartInit();	
	uartEnterTXOnlyMode();
	char str[] = "hello world";
	uartPrintln(&str[0]);
	while(1){
		//uartWriteChar('X');
	}
	
}
