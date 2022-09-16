#include "timer.h"
#include "uart.h"

void stopTimer0(){
	bic(TACTL, MC0);
	bic(TACTL, MC1);
}
void stopTimer1(){
	bic(TA1CTL, MC0);
	bic(TA1CTL, MC1);
}
void timer0Halt(){stopTimer0();}
void timer1Halt(){stopTimer1();}
void resetTimer0Count(){
	TAR = 0;
}
void resetTimer1Count(){
	TA1R = 0;
}
void resetTimer0(){
	bis(TACTL, TACLR);
	resetTimerCount();
}
void resetTimer1(){
	bis(TA1CTL, TACLR);
	resetTimerCount();
}



void resetFlagTimer0(){
	bic(TACTL, TAIFG);
}
void resetFlagTimer1(){
	bic(TA1CTL, TAIFG);
}
int timer0FlagRaised(){
	if(TACTL&(TAIFG))
		return 1;
	else
		return 0;

}
int timer1FlagRaised(){
	if(TA1CTL&(TAIFG))
		return 1;
	else
		return 0;

}
void setAlarmValueTimer0(int count){
	TACCR0 = count;
}
void setAlarmValueTimer1(int count){
	TA1CCR0 = count;
}
void resetAlarmFlagTimer0(){
	bic(TACCTL0, CCIFG);
}
void resetAlarmFlagTimer1(){
	bic(TA1CCTL0, CCIFG);
}
int alarmFlagRaisedTimer0(){
	if(TACCTL0&(OUT))
		return 1;
	else
		return 0;
}
int alarmFlagRaisedTimer1(){
	if(TA1CCTL0&(OUT))
		return 1;
	else
		return 0;
}
void startTimer0(){
	bis(TACTL, MC0);
}
void startTimer1(){
	bis(TA1CTL, MC0);
}

void timer0Init(){
	stopTimer();
	resetTimer();
	resetFlag();
	//select clock source
	bic(TACTL, TASSEL0);
	bis(TACTL, TASSEL1);
	//select clock div
	bis(TACTL, ID0);
	bis(TACTL, ID1);
	//Set output mode for compare unit
	//bis(TACCTL0, OUTMOD0);
}
void timer1Init(){
	stopTimer();
	resetTimer();
	resetFlag();
	//select clock source
	bic(TA1CTL, TASSEL0);
	bis(TA1CTL, TASSEL1);
	//select clock div
	bis(TA1CTL, ID0);
	bis(TA1CTL, ID1);
	//Set output mode for compare unit
	//bis(TACCTL0, OUTMOD0);
}
void timer0InitMicrosecond(){
	stopTimer();
	resetTimer();
	resetFlag();
	//select clock source
	bic(TACTL, TASSEL0);
	bis(TACTL, TASSEL1);
	//select clock div
	bic(TACTL, ID0);
	bic(TACTL, ID1);

}
void timer1InitMicrosecond(){
	stopTimer();
	resetTimer();
	resetFlag();
	//select clock source
	bic(TA1CTL, TASSEL0);
	bis(TA1CTL, TASSEL1);
	//select clock div
	bic(TA1CTL, ID0);
	bic(TA1CTL, ID1);

}
void timer0StartMillisecond(int duration){
	timerInit();
	setAlarmValue(duration*125);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer();
}
void timer1StartMillisecond(int duration){
	timer1Init();
	setAlarmValueTimer1(duration*125);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer1();
}
void timer0StartMicrosecond(int duration){
	timerInitMicrosecond();
	setAlarmValue(duration);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer();
}
void timer1StartMicrosecond(int duration){
	timer1InitMicrosecond();
	setAlarmValueTimer1(duration);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer1();
}
int timer0IsFinished(){
	if(timerFlagRaised()){
		stopTimer();
		return 1;
	}else{
		return 0;
	}
}
int timer1IsFinished(){
	if(timer1FlagRaised()){
		stopTimer1();
		return 1;
	}else{
		return 0;
	}
}
void delayMillisecondTimer0(int duration){
	timerStartMillisecond(duration);
	while(!timerIsFinished()){;}
}
void delayMillisecondTimer1(int duration){
	timer1StartMillisecond(duration);
	while(!timer1IsFinished()){;}
}
void delayMicrosecondTimer0(int duration){
	timerStartMicrosecond(duration);
	while(!timerIsFinished()){;}
}
void delayMicrosecondTimer1(int duration){
	timer1StartMicrosecond(duration);
	while(!timer1IsFinished()){;}
}
