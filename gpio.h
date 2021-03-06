#ifndef GPIO_H
#define GPIO_H
#include <msp430.h>
#include "macros.h"
#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define INPUT_PULLDOWN 3
#define PORT1 1
#define PORT2 2
#define HIGH 1
#define LOW 0
#define SEL_IO 0
#define SEL_UART 1
void selectPinFunction(int port, int pin, int function);
void setPinMode(int port, int pin, int state); 
void setPinFunction(int port, int pin, int func);
void writePinOutput(int port, int pin, int state);
void writeCharToPortOutput(int port, char value);
int readPin(int port, int pin);
#endif
