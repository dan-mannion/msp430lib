#include "uart.h"

void main(){
	stopWatchdogTimer();	
	uartInit();	
	char resp = 'X';
	uartWriteChar(resp);
	while(1){
		if(uartCharReceived()){
			resp = uartReadChar();
			uartWriteChar(resp);
		}
	}
	
}
