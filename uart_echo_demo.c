#include "uart.h"

void main(){
	stopWatchdogTimer();	
	uartInit16MHz();	
	char resp = 'X';
	uartWriteChar(resp);
	while(1){
		if(uartCharReceived()){
			resp = uartReadChar();
			uartWriteChar(resp);
		}
	}
	
}
