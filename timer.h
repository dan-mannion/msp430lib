#ifndef TIMER_H
#define TIEMR_H
#include <msp430.h>
#include "macros.h"
void timerInit();
void timerInitMicrosecond();
void timerStartMillisecond();
void timerStartMicrosecond();
int timerIsFinished();
void timerHalt();
void delayMillisecond(int duration);
void delayMicrosecond(int duration);
#endif
