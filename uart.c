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
void main(){
	stopWatchdogTimer();	
	uartInit();	
	while(1){
		//if(UCA0STAT && UCBUSY){
			UCA0TXBUF = 'x';	
		//}
	}
	
}
