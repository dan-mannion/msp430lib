msp430-elf-objcopy -O ihex %1 %~dpn1.hex -v    
MSP430Flasher -n msp430g2553 -i DETECT -z [vcc] -w %~dpn1.hex
