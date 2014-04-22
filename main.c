#include <htc.h>
#include "main.h"

__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & BOREN_ON & LVP_OFF);

bit scan;
bit press_buttom, edit, blink;
unsigned char cnt, cnt1, cnt2, var, rotate;
unsigned short long bufferL, mask;
extern const unsigned char Kyrilica[];
unsigned char Char;

union {

    struct {
        unsigned D1 : 1;
        unsigned D2 : 1;
        unsigned D3 : 1;
        unsigned D4 : 1;
        unsigned D5 : 1;
        unsigned D6 : 1;
        unsigned top : 1;
    } bits;
    unsigned char byte;
} mode;

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();
    mode.byte = 0xFF;
    //    putst("Эмулятор\n");
    //    putst("ver 1.00\n");
    SetAdr(0);
    putst("Набор[л]\n");
    while (true) {
        switch (get()) {
            case'U':
                break;
            case'D':;
                break;
            case'Y':
                //                if (bufferL); // RUN out buffer;
                //                else {
                edit = true;
                mode.byte = 0xFE;
                mask = 0xFFFFF0;
                rotate = 0;
                cnt = 0;
                //                }
                break;
            default:;
        }
        if (edit) {
            switch (get()) {
                case'U':
                    if (++cnt > 9)cnt = 0;
                    bufferL &= mask;
                    bufferL |= (unsigned short long) cnt << rotate;
                    blink = true;
                    printD(bufferL);
                    break;
                case'D':
                    mode.byte = (mode.byte << 1) + 1;
                    if (!mode.bits.top) {
                        mode.byte = 0xFE;
                        mask = 0xFFFFF0;
                        rotate = 0;
                    } else {
                        mask = (mask << 4) + 15;
                        rotate += 4;
                    }
                    cnt = 0;
                    break;
                case'Y':edit = false;
                    mode.byte = 0xFF;
                    cnt = 0;
                    break;
                default:;
            }
        } else {
        }


        printD(bufferL);




        //        //
        //
        //       
        //        if (var == 'D') {
        //            if (++cnt1 > 9)cnt1 = 0;
        //            bufferL &= 0xFF0F;
        //            bufferL |= cnt1 << 4;
        //        };
        //        if (var == 'U') {
        //            if (++cnt2 > 9)cnt2 = 0;
        //            bufferL &= 0xF0FF;
        //            bufferL |= cnt2 << 8;
        //        };

    }
}

void interrupt my_funct_int(void) {
    static unsigned char tim, tim_l;
    if (T0IE && T0IF) {
        if (!tim--) {
            if (!tim_l--) {
                blink = !blink;
                tim_l = 20;
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
