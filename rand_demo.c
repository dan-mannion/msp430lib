#include "uart.h"
#include "rand.h"
#include "timer.h"
#include "mspString.h"
void timerStartContinuous(){
	bis(TACTL, MC1);
};

void main(){
	stopWatchdogTimer();	
	uartInit();	
	
	timerInitMicrosecond();
	char str[] = "hello world";
	uartPrintln(&str[0]);

	initRand();
	char numstr[4];	
	char2ascii(&numstr[0], 231);
	uartPrintln(&numstr[0]);

	char resp;
	while(1){
		if(uartCharReceived()){
			resp = uartReadChar();
			if(resp=='s'){
				initRand();
			}
			char2ascii(&numstr[0], randomChar());
			uartPrintln(&numstr[0]);
		}
	}
}
	

