#include "delay.h"


//#define delay40uS() delay10Us;delay10Us;delay10Us;delay10Us
#define lcdDataLO(n) (PORTB = (n) >> 4, DB4 = (n) >> 1,DB5 = (n))
#define lcdDataHI(n) (PORTB = (n),DB4 = (n) >> 6,DB5 = (n) >> 5)


#define RSpin           PORTBbits.RB1       // ->  6  -  control LCD RS
#define RnWpin          PORTBbits.RB2       // ->  7  -  control LCD R/nW
#define Epin            PORTBbits.RB3       // ->  8  -  control LCD E
//#define KeyDown         PORTBbits.RB0       // ->  9  -  Key Buttom [down]
//#define KeyUp           PORTBbits.RB4       // ->  10 -  Key Buttom [Up]
//#define KeyOk           PORTBbits.RB5       // ->  11 -  Key Buttom [OK]
//#define ICSPdat         PORTBbits.RB6       // ->  12 -  ICSP Data
//#define ICSPclk         PORTBbits.RB7       // ->  13 -  ICSP CLK

#define DB4             PORTBbits.RB4       // ->  17 -  LCD data bus
#define DB5             PORTBbits.RB5       // ->  18 -  LCD data bus
#define DB6             PORTBbits.RB6       // ->  1  -  LCD data bus
#define DB7             PORTBbits.RB7       // ->  2  -  LCD data bus
#define OImpuls         PORTAbits.RA4       // ->  3  -
#define Vpp             PORTAbits.RA5       // ->  4  -
#define OGun            PORTAbits.RA6       // ->  15 -
#define Start           PORTAbits.RA7       // ->  16 -

#define empty		0x11

/* List Command for LCD 44780*/

#define ClrScreen   	0x01		// 0b00000001

#define ReturnHome    	0x03		// 0b00000011

#define ModeSet		0x07		// 0b00000111
/* SubCommnads */
#define IncCount 	0xFF		// 0b11111111
#define DecCount 	0xFD		// 0b11111101
#define ShiftEn  	0xFF		// 0b11111111
#define ShiftDis 	0xFE            // 0b11111110

#define DispControl   	0x0F		// 0b00001111
/* SubCommnads */
#define DisplOn		0xFF            // 0b11111111
#define DisplOff	0xF3		// 0b11111011
#define CursLineOn	0xFF		// 0b11111111
#define CursLineOff	0xFD		// 0b11111101
#define CursSquOn	0xFF		// 0b11111111
#define CursSquOff 	0xFE		// 0b11111110

#define DispCursShift 	0x1F		// 0b00011111
/* SubCommnads */
#define ScreenShift   	0xFF		// 0b11111111
#define CursorShift   	0xF7		// 0b11110111
#define RightShift  	0xFF		// 0b11111111
#define LeftShift     	0xFB		// 0b11111011

#define FunctionSet   	0x3F		// 0b00111111
/* SubCommnads */
#define DataLenght8b  	0xFF		// 0b11111111
#define DataLenght4b  	0xEF		// 0b11101111
#define Num2lStr    	0xFF		// 0b11111111
#define NumHiStr	0xF7		// 0b11110111
#define Size5x7		0xFF		// 0b11111111
#define Size5x10    	0xFB            // 0b11111011

#define SetAdressCGRAM 	0x7F		// 0b01111111

#define SetAdressDDRAM 	0xFF		// 0b11111111

#define DispStrAdr1str 	0x80
#define DispStrAdr2str 	0xC0

#define true 		1
#define false 		0

#define Command 	false
#define Data 		true

void lcdIni(void);
//void lcdWriteByte(unsigned char);
void LcdWR(unsigned char, unsigned char);
unsigned char lcdReadByte(void);
static unsigned char CharPos;
void putch(unsigned char);
void putst(unsigned char *);
unsigned int HexBcd(unsigned int);
void PutBCDint(unsigned int);
void ClrScrn(void);

