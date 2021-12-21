#include <msp430.h>
void stopWatchdogTimer(){
	WDTCTL = WDTPW |WDTHOLD;
}
