#include <htc.h>
#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_ON & LVP_OFF);

bit stop, bshow1, bshow2, bshow3, bshow4;
bit key_mode, edit, edit1, blink;
unsigned char cnt, var;
unsigned int bufferL, bufferG, cena;
extern const unsigned char Kyrilica[];

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();
    bshow1 = true;
    bshow2 = true;
    bshow3 = true;
    bshow4 = true;
    putst("Эмулятор\n");
    putst("ver 1.00\n");
    delayS(1);
    ClrScrn();
    while (true) {
        switch (getch()) {
            case 'U':
                ClrScrn();
                putst("Набор[л]\n");
                SetAdr(10);
                putBCDint(HexBcd(bufferL));
                edit = true;
                bshow1 = false;
                while (edit) {
                    switch (getch()) {
                        case 'U': SetAdr(10);
                            putBCDint(HexBcd(++bufferL));
                            break;
                        case 'D': SetAdr(10);
                            putBCDint(HexBcd(--bufferL));
                            break;
                        case 'Y':
                            edit1 = true;
                            bshow2 = false;
                            bshow1 = true;
                            while (edit1) {
                                switch (getch()) {
                                    case 'U': SetAdr(10);
                                        putBCDint(HexBcd(bufferL+=10));
                                        break;
                                    case 'D': SetAdr(10);
                                        putBCDint(HexBcd(bufferL-=10));
                                        break;
                                    case 'H': edit1 = false;
                                        bshow2 = true;
                                        bshow1 = false;
                                        break;
                                    default:;

                                }


                            }

                        case 'H':
                            ClrScrn();
                            edit = false;
                            break;
                        default:;
                    }
                }
                break;
            case 'D': ClrScrn();
                putst("Набор[Г]\n");
                SetAdr(10);
                putBCDint(HexBcd(bufferG));
                edit = true;
                while (edit) {
                    switch (getch()) {
                        case 'U': bufferG++;
                            SetAdr(10);
                            putBCDint(HexBcd(bufferG));
                            break;
                        case 'D': bufferG--;
                            SetAdr(10);
                            putBCDint(HexBcd(bufferG));
                            break;
                        case 'H':
                            ClrScrn();
                            edit = false;
                            break;
                        default:;
                    }
                }

                break;
            case 'Y': putst("Ok! \n");
                break;
            case 'L':ClrScrn();
                putst("Цена [Г]\n");
                SetAdr(10);
                putBCDint(HexBcd(cena));
                edit = true;
                while (edit) {
                    switch (getch()) {
                        case 'U': cena++;
                            SetAdr(10);
                            putBCDint(HexBcd(cena));
                            break;
                        case 'D': cena--;
                            SetAdr(10);
                            putBCDint(HexBcd(cena));
                            break;
                        case 'H':
                            ClrScrn();
                            edit = false;
                            break;
                        default:;
                    }
                }
                break;
            case 'H':
                putst("Эмулятор\n");
                putst("ver 1.00\n");
                break;
            default:;
        }
    }

}

void interrupt my_funct_int(void) {
    static unsigned int tim;
    if (T0IE && T0IF) {
        if (!tim--) {
            blink = !blink;
            SetAdr(10);
            putBCDint(HexBcd(bufferL));
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
