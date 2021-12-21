msp430-elf-gcc -c -mmcu=msp430g2553 -L C:\ti\msp430-gcc\include -I C:\ti\msp430-gcc\include %1 -o %~dpn1.o
move %~dpn1.o obj/
