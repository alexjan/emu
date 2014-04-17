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
    //    timerIni();
    //    lcdIni();
    //    ei();
//    while (true) {
//        lcdDataHI(0x30);
//        delayS(2);
//        lcdDataHI(0xC0);
//        delayS(2);
//    }


    putst("Привет всем!\n");
    while (true) {
        delayMs(250);
        putch('2');
    }
    //    delayS(3);
    //    ClrScrn();
    //    while (true) {
    //        switch (getch()) {
    //            case 'U': putst("Up  \n");
    //                break;
    //            case 'D': putst("Down\n");
    //                break;
    //            case 'Y': putst("Ok! \n");
    //                break;
    //            case 'L': putst("LO \n");
    //                break;
    //            case 'H': putst("HI \n");
    //                break;
    //            default:;
    //        }
    //    }

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
    PORTA = 0b00000000;
    TRISA = 0b00000000;
    //        |||||||+--> 17 pin 
    //        ||||||+---> 18 pin
    //        |||||+---->  1 pin
    //        ||||+----->  2 pin
    //        |||+------>  3 pin
    //        ||+------->  4 pin
    //        |+--------> 15 pin
    //        +---------> 16 pin

    PORTB = 0b00000000;
    TRISB = 0b00000000;
    //        |||||||+-->  6 pin
    //        ||||||+--->  7 pin --> RS     (4)
    //        |||||+---->  8 pin --> RnW    (5)
    //        ||||+----->  9 pin --> E      (6)
    //        |||+------> 10 pin --> Data4 (11)
    //        ||+-------> 11 pin --> Data5 (12)
    //        |+--------> 12 pin --> Data6 (13)
    //        +---------> 13 pin --> Data7 (14)
    nRBPU = false;
    CMCON |= 0x07;
    return;
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
    return;
}
