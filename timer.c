#include "timer.h"
#include "uart.h"

void stopTimer(){
	bic(TACTL, MC0);
	bic(TACTL, MC1);
}
void timerHalt(){stopTimer();}
void resetTimerCount(){
	TAR = 0;
}
void resetTimer(){
	bis(TACTL, TACLR);
	resetTimerCount();
}

void resetFlag(){
	bic(TACTL, TAIFG);
}
int timerFlagRaised(){
	if(TACTL&(TAIFG))
		return 1;
	else
		return 0;

}
void setAlarmValue(int count){
	TACCR0 = count;
}
void resetAlarmFlag(){
	bic(TACCTL0, CCIFG);
}
int alarmFlagRaised(){
	if(TACCTL0&(OUT))
		return 1;
	else
		return 0;
}
void startTimer(){
	bis(TACTL, MC0);
}
void timerInit(){
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
void timerInitMicrosecond(){
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
void timerStartMillisecond(int duration){
	timerInit();
	setAlarmValue(duration*125);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer();
}
void timerStartMicrosecond(int duration){
	timerInitMicrosecond();
	setAlarmValue(duration);	//when smclk is at 1meghz and div set to 8 then 125 counts=1millisecond	
	startTimer();
}
int timerIsFinished(){
	if(timerFlagRaised()){
		stopTimer();
		return 1;
	}else{
		return 0;
	}
}
void delayMillisecond(int duration){
	timerStartMillisecond(duration);
	while(!timerIsFinished()){;}
}
void delayMicrosecond(int duration){
	timerStartMicrosecond(duration);
	while(!timerIsFinished()){;}
}
