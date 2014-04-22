#include "delay.h"


//#define delay40uS() delay10Us;delay10Us;delay10Us;delay10Us
#define lcdDataLO(n) (PORTB &= 0x0F,PORTB |= (n) << 4)
#define lcdDataHI(n) (PORTB &= 0x0F,PORTB |= (n) & 0xF0)


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
void SetAdr(unsigned char);
unsigned char lcdReadByte(void);
static unsigned char CharPos;
void putch(unsigned char);
void putst(unsigned char *);
unsigned char HB(unsigned char); // Hex --> BCD char
unsigned int HexBcd(unsigned int);
void putBCD(unsigned char);
void putBCDint(unsigned int);
void ClrScrn(void);
void printD(unsigned int);

