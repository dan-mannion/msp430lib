#ifndef TIMER_H
#define TIMER_H
#include <msp430.h>
#include "macros.h"
void timer0Init();
void timer0InitMicrosecond();
void timer0StartMillisecond();
void timer0StartMicrosecond();
int timer0IsFinished();
void timer0Halt();
void delayMillisecondTimer0(int duration);
void delayMicrosecondTimer0(int duration);

void timer1Init();
void timer1InitMicrosecond();
void timer1StartMillisecond();
void timer1StartMicrosecond();
int timer1IsFinished();
void timer1Halt();
void delayMillisecondTimer1(int duration);
void delayMicrosecondTimer1(int duration);
#endif
