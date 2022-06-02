#include "msp430lib.h"

void main(){
	int i;
	int delay = 10;
	systemInit();
	timerInit();
	
	setPinMode(1, 0, OUTPUT);
	setPinFunction(1,0,SEL_IO);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, HIGH);

		//timerStartMicrosecond(delay);
		//while(timerIsFinished()==0){;}
		delayMicrosecond(delay);
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,LOW);

		timerStartMicrosecond(delay);
		while(timerIsFinished()==0){;}
		
	}
}
