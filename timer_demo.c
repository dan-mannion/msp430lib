#include "msp430lib.h"

void main(){
	int i;
	int delay = 100;
	systemInit();
	timer0Init();
	
	setPinMode(1, 0, OUTPUT);
	setPinFunction(1,0,SEL_IO);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, HIGH);

		timer0StartMillisecond(delay);
		while(timer0IsFinished()==0){;}
		
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,LOW);

		timer0StartMillisecond(500);
		while(timer0IsFinished()==0){;}
		
	}
}
