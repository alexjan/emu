#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_ON & LVP_OFF);

extern bit stop;

void main(void) {
//    di();
    portIni();
//    timerIni();
//    ei();
//    lcdIni();
//    delay10Us();
    delay10Us(0);
    delay10Us(1);
    delay10Us(2);
    delay10Us(3);
    delay10Us(4);
    delay10Us(5);
    delay10Us(6);
    delay10Us(7);
    delay10Us(8);
    delay10Us(9);
    delay10Us(200);
    
    delayS(1);

    delayS(2);






    
    while (true){
        CLRWDT();
        delayMs(200);
        putch('1');
    }
}

void interrupt my_funct_int(void) {
    if (T0IE && T0IF) {
        if (next--) stop = false;
        TMR0 = 55;
        T0IF = false;
        return;
    }
}

void portIni(void) {
    PORTA = 0b11110000;
    TRISA = 0b11110000;
    //        |||||||+--> 17 pin --> Data4 (11)
    //        ||||||+---> 18 pin --> Data5 (12)
    //        |||||+---->  1 pin --> Data6 (13)
    //        ||||+----->  2 pin --> Data7 (14)
    //        |||+------>  3 pin
    //        ||+------->  4 pin
    //        |+--------> 15 pin
    //        +---------> 16 pin

    PORTB = 0b11111100;
    TRISB = 0b11111000;
    //        |||||||+-->  6 pin --> RS
    //        ||||||+--->  7 pin --> RnW
    //        |||||+---->  8 pin --> E
    //        |||+------>  9 pin
    //        ||||+-----> 10 pin
    //        ||+-------> 11 pin
    //        |+--------> 12 pin
    //        +---------> 13 pin

    CMCON |= 0x07;
}

void timerIni(void) {

#ifdef timer0

    TMR0 = 55;
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
