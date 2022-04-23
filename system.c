#include "watchdog.h"
#include "clocks.h"

void systemInit(){
	stopWatchdogTimer();
	clocksInit();
}
