#include "rand.h"
char RAND_SEED;
void initRand(){
	//timerInitMicrosecond();
	//delayMicrosecond(1000);
	//RAND_SEED = TAR*UCA0RXBUF*UCA0TXBUF; //Seed taken from timer count
	//RAND_SEED = (char) *((int *)767);
	//RAND_SEED = IFG2;
	
	bis(TACTL, MC1);
	RAND_SEED = TAR;
}
char randomChar(){
	RAND_SEED = 61*RAND_SEED+1;
	return RAND_SEED;
}

