#include "msp430lib.h"

void main(){
	int i;
	int delay = 10000;
	systemInit();
	timerInit();
	
	setPinMode(1, 0, OUTPUT);
	setPinFunction(1,0,SEL_IO);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, HIGH);

		timerStartMillisecond(500);
		while(timerIsFinished()==0){;}
		
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,LOW);

		timerStartMillisecond(500);
		while(timerIsFinished()==0){;}
		
	}
}
