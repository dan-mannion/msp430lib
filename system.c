#include "watchdog.h"
#include "clocks.h"

void systemInit(){
	stopWatchdogTimer();
	clocksInit();
}
void systemInit16MHz(){
	stopWatchdogTimer();
	clocksInit16MHz();
}
