#include "delay.h"
#include "lcd.h"
//#include <htc.h>
#include "main.h"


							 /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
unsigned char const Kyrilica[]={						 															\
					/* 0 */		0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,\
					/* 1 */		0xA8,0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,\
					/* 2 */		0xB1,0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,\
					/* 3 */		0x6F,0xBE,0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,\
					/* 4 */		0xC6,0xC7};
					/* 0	   	À    Á    Â    Ã    Ä    Å    Æ    Ç    È    É    Ê    Ë    Ì    Í    Î
					 * 1	  	Ï    Ð    Ñ    Ò    Ó    Ô    Õ    Ö    ×    Ø    Ù    Ú    Û    Ü    Ý    Þ
					 * 2	   	ß    à    á    â    ã    ä    å    æ    ç    è    é    ê    ë    ì    í
					 * 3	 	î    ï    ð    ñ    ò    ó    ô    õ    ö    ÷    ø    ù    ú    û    ü    ý
					 * 4	 	þ    ÿ                                                                          */




void lcdIni(void) {
    Epin = false;
    RSpin = false;
    RnWpin = false;
    // first step pause 15mS
    delayMs(15);
    // second step set 0x03 & wait 4.1mS
    lcdDataHI(0x38);
    lcdFillingEdge();
    delayMs(5);
    //theird step set 0x03 & wait 100uS
    lcdFillingEdge();
    delayMs(1);
    // next step set 0x03 $ wait 40uS
    lcdFillingEdge();
    delay40uS();
    // next set 0x02 & wait 40uS
    lcdDataHI(0x28);
    lcdFillingEdge();
    delay40uS();
    // next set 0x02
    LcdWR(0x28,Command);
    LcdWR(0x06,Command);
    LcdWR(0x0E,Command);
    LcdWR(0x01,Command);
    delayMs(2);
}

void LcdWR(unsigned char DataVar, unsigned char mode) {
    RSpin = mode;
    RnWpin = false;
    lcdDataHI(DataVar);
    lcdFillingEdge();
    lcdDataLO(DataVar);
    lcdFillingEdge();
    delay40uS();
}

unsigned char lcdReadByte(void) {

}
void SetAdr (unsigned char adr){
//     unsigned char Adres;
//     CharPos = adr;
    CharPos = adr | 0x20;                         //001SAAAAB
    CharPos &= 0xF0;                              //001S0000B
    CharPos <<= 2;                                //1S000000B
    CharPos |= adr & 0x0F;                        //1S00AAAAB
    LcdWR(CharPos,Command);                       //
    CharPos = adr;
}


void putch(unsigned char Char) {
    if (Char == '\n') {
        if(CharPos < 16) CharPos = 16;
        else CharPos = 0;
        SetAdr(CharPos);
    }
	else {
        if (Char > 0x7F) Char = Kyrilica[Char - 0xC0];
		LcdWR(Char, Data);
        switch(++CharPos){
            case 16 : SetAdr(16);
                break;
            case 32 : SetAdr(0);
                      CharPos = 0;
                break;
            default : ;
        }

	}
}
