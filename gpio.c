#include "gpio.h"
#include <msp430.h>

void setPinMode(int port, int pin, int state){
	switch(state){
		case OUTPUT:
			switch(port){
				case(1):
					P1DIR |= 1<<pin;
					break;
				case(2):
					P2DIR |= 1<<pin;
					break;
			}	
			break;
		case INPUT:
			switch(port){
				case(1):
					P1DIR &= ~(1<<pin);
					break;
				case(2):
					P2DIR &= ~(1<<pin);
					break;
			}
			break;
	}
}
void setPort1Function(int pin, int func){
	switch(func){
		case(0):
			bic(P1SEL, pin);
			bic(P1SEL2, pin);
			break;
		case(1):
			bis(P1SEL, pin);
			bic(P1SEL2, pin);
			break;
		case(2):
			bic(P1SEL, pin);
			bis(P1SEL2,pin);
			break;
		case(3):
			bis(P1SEL, pin);
			bis(P1SEL2, pin);
			break;
	}
}
void setPort2Function(int pin, int func){
	if(func&&(1<<0))
		bis(P1SEL,pin);
	else
		bic(P1SEL, pin);

	if(func&&(1<<1))
		bis(P2SEL2,pin);
	else
		bic(P2SEL2,pin);
}
void setPinFunction(int port, int pin, int func){
	switch(port){
		case(1):
			setPort1Function(pin, func);
			break;
		case(2):
			setPort2Function(pin, func);
			break;
	}	
}

