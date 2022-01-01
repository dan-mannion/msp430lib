#include "msp430lib.h"

void main(){
	int i;
	int delay = 10000;
	systemInit();
	setPinMode(1, 0, OUTPUT);
	setPinMode(1, 6, OUTPUT);
	while(1){
		writePinOutput(1,0, HIGH);
		writePinOutput(1,6, LOW);
		for(i=0;i<delay;i++){;}
		writePinOutput(1,0,LOW);
		writePinOutput(1,6,HIGH);
		for(i=0;i<delay;i++){;}
	}
}
