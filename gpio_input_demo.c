#include "msp430lib.h"
void main(){
	systemInit();
	setPinMode(PORT1, 0, OUTPUT);
	setPinMode(PORT1, 3, INPUT_PULLUP);
	while(1){
	if(readPin(PORT1, 3))
		writePinOutput(PORT1, 0, LOW);
	else
		writePinOutput(PORT1, 0, HIGH);
	}
}
