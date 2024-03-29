#ifndef UART_H
#define UART_H
#include <msp430.h>
#include "macros.h"
#include "gpio.h"
#include "watchdog.h"

void uartInit();
void uartInit16MHz();
void uartPrintln(char *str_p);
int uartCharReceived();
char uartReadChar();
void uartWriteChar(char c);
void uartEnterTXOnlyMode();
#endif
