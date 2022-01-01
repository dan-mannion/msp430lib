#include "gpio.h"
#include <msp430.h>
void writePinOutput(int port, int pin, int state){
	volatile unsigned char *port_ptr = (port==PORT1)?&P1OUT:&P2OUT;
	if(state==HIGH)
		bis(*port_ptr, 1<<pin);
	else
		bic(*port_ptr, 1<<pin);

}
void writeCharToPortOutput(int port, char value){
	volatile unsigned char *port_ptr = (port==PORT1)?&P1OUT:&P2OUT;
	*port_ptr = value; 
}
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
			bic(P1SEL, 1<<pin);
			bic(P1SEL2, 1<<pin);
			break;
		case(1):
			bis(P1SEL, 1<<pin);
			bic(P1SEL2, 1<<pin);
			break;
		case(2):
			bic(P1SEL, 1<<pin);
			bis(P1SEL2, 1<<pin);
			break;
		case(3):
			bis(P1SEL, 1<<pin);
			bis(P1SEL2, 1<<pin);
			break;
	}
}
void setPort2Function(int pin, int func){
	if(func&&(1<<0))
		bis(P1SEL,1<< pin);
	else
		bic(P1SEL, 1<<pin);

	if(func&&(1<<1))
		bis(P2SEL2,1<<pin);
	else
		bic(P2SEL2, 1<<pin);
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

