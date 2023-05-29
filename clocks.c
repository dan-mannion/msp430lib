#include "clocks.h"

void clocksInit(){
	//Set DCO to 1MHz
	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    	DCOCTL = CALDCO_1MHZ;

}
void clocksInit16MHz(){
  	BCSCTL1 = CALBC1_16MHZ;                    // Set DCO
    	DCOCTL = CALDCO_16MHZ;
}
