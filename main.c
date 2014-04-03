#include <htc.h>
#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_ON & MCLRE_OFF & BOREN_ON & LVP_OFF);

extern bit stop;
bit key_mode;
unsigned char cnt, var;
extern const unsigned char Kyrilica[];

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();
    putst("Привет всем!\n");
    delayS(3);
    ClrScrn();
    while (true) {
        switch (getch()) {
            case 'U': putst("Up  \n");
                break;
            case 'D': putst("Down\n");
                break;
            case 'Y': putst("Ok! \n");
                break;
            case 'L': putst("LO \n");
                break;
            case 'H': putst("HI \n");
                break;
            default:;
        }
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

    PORTB = 0b11111000;
    TRISB = 0b11111000;
    //        |||||||+-->  6 pin --> RS     (4)
    //        ||||||+--->  7 pin --> RnW    (5)
    //        |||||+---->  8 pin --> E      (6)
    //        |||+------>  9 pin
    //        ||||+-----> 10 pin
    //        ||+-------> 11 pin
    //        |+--------> 12 pin
    //        +---------> 13 pin
    nRBPU = false;
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
