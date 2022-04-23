#ifndef TIMER_H
#define TIEMR_H
#include <msp430.h>
#include "macros.h"
void timerInit();
void timerStartMillisecond();
int timerIsFinished();
void timerHalt();
#endif
