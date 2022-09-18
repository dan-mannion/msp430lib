#include "msp430lib.h"

void main(){
	int i;
	int delay = 10000;
	systemInit();
	timer1Init();
	
	setPinMode(1, 0, OUTPUT);
	setPinFunction(1,0,SEL_IO);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, HIGH);

		timer1StartMillisecond(500);
		while(timer1IsFinished()==0){;}
		
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,LOW);

		timer1StartMillisecond(500);
		while(timer1IsFinished()==0){;}
		
	}
}
