#include "rand.h"
char RAND_ISINIT;
char RAND_SEED;

void initTempSensorADC(){
	// Choose temperature sensor
	bis(ADC10CTL1,INCH1);
	bis(ADC10CTL1, INCH3);
}
void ADCOn(){
	bis(ADC10CTL0, ADC10ON);
	bis(ADC10CTL0, ENC);
}
void ADCOff(){
	bic(ADC10CTL0, ADC10ON);
	bic(ADC10CTL0, ENC);
}
char ADCFlagRaised(){
	if(ADC10CTL0 & ADC10IFG)
		return 1;
	else
		return 0;
}
char triggerReadingTempSensor(){
	char val;
	bis(ADC10CTL0, ADC10SC);
	while(!ADCFlagRaised()){
		;
	}
	
	val = ADC10MEM;
	return val;
}
void initRand(){
	initTempSensorADC();
	ADCOn();	
	RAND_SEED = triggerReadingTempSensor();
	ADCOff();

	RAND_ISINIT = 1;
}
char randomChar(){
	if(RAND_ISINIT==0){
		initRand();
	}
	RAND_SEED = 61*RAND_SEED+1;
	return RAND_SEED;
}

