#include <htc.h>
#include "delay.h"
#include "lcd.h"
//#include <htc.h>
#include "main.h"

#define lcdFillingEdge() (Epin=true , Epin=false)

extern bit blink;

/*                                         *//*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
const unsigned char Kyrilica[] = {						 															\
					/* 0 */ 0x41, 0xA0, 0x42, 0xA1, 0xE0, 0x45, 0xA3, 0xA4, 0xA5, 0xA6, 0x4B, 0xA7, 0x4D, 0x48, 0x4F,                                             \
					/* 1 */ 0xA8, 0x50, 0x43, 0x54, 0xA9, 0xAA, 0x58, 0xE1, 0xAB, 0xAC, 0xE2, 0xAD, 0xAE, 0x62, 0xAF, 0xB0,                                             \
					/* 2 */ 0xB1, 0x61, 0xB2, 0xB3, 0xB4, 0xE3, 0x65, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD,                                             \
					/* 3 */ 0x6F, 0xBE, 0x70, 0x63, 0xBF, 0x79, 0xE4, 0x78, 0xE5, 0xC0, 0xC1, 0xE6, 0xC2, 0xC3, 0xC4, 0xC5,                                             \
					/* 4 */ 0xC6, 0xC7
};

/*                                    *//* 0	 ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?
                                         * 1	 ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?
                                         * 2	 ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?
                                         * 3	 ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?    ?
                                         * 4	 ?    ?                                                                          */

void lcdIni(void) {
    Epin = false;
    RSpin = false;
    RnWpin = false;
    // first step pause 15mS
    //----------------------------------
    delayMs(16);
    //----------------------------------
    // second step set 0x03 & wait 4.1mS
    //----------------------------------
    lcdDataLO(0x03);
    lcdFillingEdge();
    delayMs(5);
    //----------------------------------
    //theird step set 0x03 & wait 100uS
    //----------------------------------
    lcdFillingEdge();
    delay10Us(100);
    //----------------------------------
    // next step set 0x03 $ wait 40uS
    //----------------------------------
    lcdFillingEdge();
    delay10Us(4);
    //----------------------------------

    // next set 0x02 & wait 40uS
    //----------------------------------
    lcdDataLO(0x02);
    lcdFillingEdge();
    delay10Us(4);
    //----------------------------------
    LcdWR(FunctionSet & DataLenght4b & Num2lStr & Size5x7, Command);
    LcdWR(DispControl & DisplOn & CursLineOff & CursSquOff, Command);
    LcdWR(ModeSet & IncCount & ShiftDis, Command);
    LcdWR(DispCursShift & CursorShift & RightShift, Command);
    ClrScrn();
    LcdWR(SetAdressDDRAM & 0x80, Command);
    delayMs(2);
    //----------------------------------
}

void LcdWR(unsigned char DataVar, unsigned char mode) {
    RSpin = mode;
    RnWpin = false;
    lcdDataHI(DataVar);
    lcdFillingEdge();
    lcdDataLO(DataVar);
    lcdFillingEdge();
    delay10Us(4);
}

unsigned char lcdReadByte(void) {

}

void SetAdr(unsigned char adr) {
    //     unsigned char Adres;
    //     CharPos = adr;
    // if adr = 8 (0b00001000)
    CharPos = adr | 0x10; //0001SAAAB
    CharPos &= 0xF8; //0001S000B
    CharPos <<= 3; //1S000000B
    CharPos |= adr & 0x07; //1S000AAAB
    LcdWR(CharPos, Command); //
    CharPos = adr;
    return;
}

void putch(unsigned char Char) {
    if (Char == '\n') {
        if (CharPos <= 8) CharPos = 8;
        else CharPos = 0;
        SetAdr(CharPos);
    } else {
        if (Char > 0x7F) Char = Kyrilica[Char - 0xC0];
        LcdWR(Char, Data);
        switch (++CharPos) {
            case 8: SetAdr(8);
                break;
            case 16: SetAdr(0);
                CharPos = 0;
                break;
            default:;
        }

    }
}

void ClrScrn(void) {
    LcdWR(ClrScreen, Command);
    CharPos = 0;
    delayMs(5);
}

void putBCD(unsigned char varBCD) {
    putch(((varBCD >> 4) & 0x0F) + 0x30);
    putch((varBCD & 0x0F) + 0x30);
    return;
}

void putBCDint(unsigned int VarBCDint) {
    //    if (VarBCDint & 0xF000)putch((unsigned char) ((VarBCDint >> 12) & 0x0F) + '0');
    //    else putch(' ');

    putch((unsigned char) ((VarBCDint >> 12) & 0x0F) + '0');
    putch((unsigned char) ((VarBCDint >> 8) & 0x0F) + '0');
    putch(',');
    putch((((unsigned char) VarBCDint >> 4) & 0x0F) + '0');
    putch(((unsigned char) VarBCDint & 0x0F) + '0');
}

unsigned int HexBcd(unsigned int dat) {
    unsigned int tmpvar = 0;
    unsigned char cnt = 0;
    while (dat) {
        tmpvar <<= 4;
        tmpvar |= (dat % 10);
        dat /= 10;
        cnt++;
    }
    return tmpvar;
}

void putst(unsigned char *string) {
    do {
        putch(*(string++));
    } while (*string != '\n');
    putch('\n');
}

void printD(unsigned int num) {
    SetAdr(11);
    putBCDint(HexBcd(num));
    return;
}

