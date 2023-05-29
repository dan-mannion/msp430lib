#include "system.h"
#include "gpio.h"

void main(){
	systemInit16MHz();
	setPinMode(PORT1, 4, OUTPUT);
	setPinFunction(PORT1, 4, 1);
	while(1){;}
}
