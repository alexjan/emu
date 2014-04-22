#include <htc.h>
#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_ON & LVP_OFF);

bit scan;
bit press_buttom, edit, blink;
unsigned char cnt, var;
unsigned int bufferL, bufferG, cena;
extern const unsigned char Kyrilica[];
unsigned char Char;

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();

    //    putst("Эмулятор\n");
    //    putst("ver 1.00\n");
    SetAdr(0);
    putst("Набор[л]\n");
    while (true) {
        var = get();
        if (var == 'Y') {
            bufferL += 25;
        };
        printD(bufferL);
    }
}

void interrupt my_funct_int(void) {
    static unsigned char tim, tim_l;
    if (T0IE && T0IF) {
        if (!tim--) {
            if (!tim_l--) {
                blink = true; //!blink;
                tim_l = 25;
            }
            if (scan)Char = scanch();
            tim = 99;
        }
        TMR0 = 87;
        T0IF = false;
        return;
    }
}

void portIni(void) {
    PORTA = 0b11111111;
    TRISA = 0b11111111;
    //        |||||||+--> 17 pin --> Data4 (11)
    //        ||||||+---> 18 pin --> Data5 (12)
    //        |||||+---->  1 pin --> Data6 (13)
    //        ||||+----->  2 pin --> Data7 (14)
    //        |||+------>  3 pin
    //        ||+------->  4 pin
    //        |+--------> 15 pin
    //        +---------> 16 pin

    PORTB = 0b00000001;
    TRISB = 0b00000001;
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
    OPTION_REG &= 0b01011111;
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
