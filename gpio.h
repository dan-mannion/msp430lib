#ifndef GPIO_H
#define GPIO_H
#include <msp430.h>
#include "macros.h"
#define OUTPUT 0
#define INPUT 1
#define PORT1 1
#define PORT2 2
#define HIGH 1
#define LOW 0
void setPinMode(int port, int pin, int state); 
void setPinFunction(int port, int pin, int func);
void writePinOutput(int port, int pin, int state);
void writeCharToPortOutput(int port, char value);
#endif
