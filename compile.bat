msp430-elf-gcc -mmcu=msp430g2553 -L C:\ti\msp430-gcc\include -I C:\ti\msp430-gcc\include obj\system.o obj\watchdog.o obj\gpio.o obj\uart.o %1 -o %~dpn1.o
