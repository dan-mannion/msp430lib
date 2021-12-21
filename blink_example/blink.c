//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.2
//
//  Description; Toggle P1.2 by xor'ing P1.2 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.2|-->LED
//
//  Texas Instruments, In0
//  July 2011
//***************************************************************************************

#include <msp430.h>				

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= 1<<6;	

	//P1OUT = P1OUT&&(!1);	// Set P1.2 to output direction

	P1OUT |= 1<<6;

	/*for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization

		P1OUT ^= 0x01;				// Toggle P1.2 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}*/
}
