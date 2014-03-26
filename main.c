#include "main.h"

extern bit stop;

void main(void) {
    di();
    asm("nop");
    delayUs();
    asm("nop");
    delay10Us(1);
    asm("nop");
    delayMs(1);
    asm("nop");
    delayS(1);
    asm("nop");


    portIni();
    timerIni();
    ei();
    lcdIni();
    //	printf("Hello word!\n");

    while (true);
}

void interrupt my_funct_int(void) {
    if (T0IE && T0IF) {
        if (next--) stop = false;
        T0IF = false;
        return;
    }
}

void portIni(void) {
    PORTA = 0b11110000;
    TRISA = 0b11110000;
    //        |||||||+--> 17 pin --> Data4
    //        ||||||+---> 18 pin --> Data5
    //        |||||+---->  1 pin --> Data6
    //        ||||+----->  2 pin --> Data7
    //        |||+------>  3 pin
    //        ||+------->  4 pin
    //        |+--------> 15 pin
    //        +---------> 16 pin

    PORTB = 0b11111000;
    TRISB = 0b11111000;
    //        |||||||+-->  6 pin
    //        ||||||+--->  7 pin --> RS
    //        |||||+---->  8 pin --> R/nW
    //        ||||+----->  9 pin --> E
    //        |||+------> 10 pin
    //        ||+-------> 11 pin
    //        |+--------> 12 pin
    //        +---------> 13 pin

    CMCON |= 0x07;
}

void timerIni(void) {

#ifdef timer0

    TMR0 = 150;
    T0IE = true;
    T0IF = false;
    OPTION_REG &= 0b11011111;
    //              |||||||+--> PS0
    //              ||||||+---> PS1
    //              |||||+----> PS2
    //              ||||+-----> PSA
    //              |||+------> T0SE
    //              ||+-------> T0CS
    //              |+--------> INTEDG
    //              +---------> nRPBU

#endif	

}
