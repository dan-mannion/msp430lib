#include "uart.h"
void uartPause(){
	bis(UCA0CTL1, UCSWRST);
}
void uartStart(){
	bic(UCA0CTL1, UCSWRST);
}
void uartInitClock(){
	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    	DCOCTL = CALDCO_1MHZ;
	bis(UCA0CTL1, UCSSEL_2);
}
void uartInit(){
	uartPause();
	uartInitClock();
	
	//Set baud rate to 9600
	bic(UCA0MCTL, UCOS16);
	UCA0BR0 = 104;
	UCA0BR1 = 0;

	UCA0MCTL = UCBRS0;//Sets modulation type to 0

	//bis(P1SEL2, BIT2);	
	setPinFunction(PORT1, 2, 2);
	uartStart();
}
int uartBusy(){
 if(UCA0STAT && UCBUSY)
	 return 1;
 else
	 return 0;
}
void uartWriteChar(char c){
	if(!uartBusy()){
		UCA0TXBUF = c;	
	}

	
}
void uartPrintln(char *str_p, int len){
	int n = 0;
	for(n;n<len;n++){
		uartWriteChar(*(str_p+n));
	}	
	uartWriteChar('\n');
}
void main(){
	stopWatchdogTimer();	
	uartInit();	
	while(1){
		uartWriteChar('X');
	}
	
}
