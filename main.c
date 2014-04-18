#include <htc.h>
#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_ON & LVP_OFF);

bit stop, editdig1, editdig2, editdig3, editdig4, editdig5, editdig6;
bit key_mode, edit, blink, digit1, digit2, digit3, digit4, mode1, mode2;
unsigned char cnt, var;
unsigned int bufferL, bufferG, cena;
extern const unsigned char Kyrilica[];

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();
    digit1 = true;
    digit2 = true;
    digit3 = true;
    digit4 = true;
    mode1 = false;
    mode2 = true;
    edit = false;
    //    putst("Эмулятор\n");
    //    putst("ver 1.00\n");
    SetAdr(0);
    putst("Набор[л]\n");
    while (true) {
        if (!edit) {
            switch (getch()){
                case 'Y':
                edit = true;
                digit1 = false;
                break;
                default:;
            }
        }

        while (!digit1) {
            switch (getch()) {
                case'U':
                    bufferL++;
                    break;
                case 'D':
                    digit1 = true;
                    digit2 = false;
                    break;
                default:
                    digit1 = true;
                    edit = false;
            }
        }
        //        while (!digit2) {
        //            switch (getch()) {
        //                case'U':
        //                    bufferL += 10;
        //                    break;
        //                case 'D':
        //                    digit2 = true;
        //                    digit3 = false;
        //                    break;
        //                default:
        //                    digit2 = true;
        //                    edit = false;
        //            }
        //        }
        //        while (!digit3) {
        //            switch (getch()) {
        //                case'U':
        //                    bufferL += 100;
        //                    break;
        //                case 'D':
        //                    digit3 = true;
        //                    digit4 = false;
        //                    break;
        //                default:
        //                    digit3 = true;
        //                    edit = false;
        //            }
        //        }
        //        while (!digit4) {
        //            switch (getch()) {
        //                case'U':
        //                    bufferL += 1000;
        //                    break;
        //                case 'D':
        //                    digit4 = true;
        //                    //                        digit5 = false;
        //                    break;
        //                default:
        //                    digit4 = true;
        //                    edit = false;
        //            }
        //
        //        }
    }
}

void interrupt my_funct_int(void) {
    static unsigned int tim;
    if (T0IE && T0IF) {
        if (!tim--) {
            blink = !blink;
            //            if (editdig1) {
            SetAdr(11);
            putBCDint(HexBcd(bufferL));
            //            }
            tim = 2000;
        }
        TMR0 = 90;
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
