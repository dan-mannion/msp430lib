#include <msp430.h>				
#include "msp430lib.h"
#define pin 6
void main(void) {
	//WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	stopWatchdogTimer();

	//P1DIR |= 1<<pin;	
	setPinMode(1, pin, OUTPUT);

	//P1OUT = P1OUT&&(!1);	// Set P1.2 to output direction

	P1OUT |= 1<<pin;

	/*for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization

		P1OUT ^= 0x01;				// Toggle P1.2 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}*/
}
