#ifndef UART_H
#define UART_H
#include <msp430.h>
#include "macros.h"
#include "gpio.h"
#include "watchdog.h"

void uartPuase();
void uartStart();
void uartInit();
void uartWriteChar(char c);
#endif
