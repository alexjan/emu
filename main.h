#include "delay.h"
#include "lcd.h"
#include "key.h"

#define false 0
#define true 1

#define timer0
#define WaitForNext     20           // Wait for next otpusk in Second
#define WidthImp        10           // x 200 uS - now 2mS
#define PauseImp        10           // x 200 uS - now 2mS (F = 250Hz -> 150 l/min)

#define RSpin           PORTBbits.RB0       // ->  6  -  control LCD RS
#define RnWpin          PORTBbits.RB1       // ->  7  -  control LCD R/nW
#define Epin            PORTBbits.RB2       // ->  8  -  control LCD E
#define KeyDown         PORTBbits.RB3       // ->  9  -  Key Buttom [down]
#define KeyUp           PORTBbits.RB4       // ->  10 -  Key Buttom [Up]
#define KeyOk           PORTBbits.RB5       // ->  11 -  Key Buttom [OK]
#define ICSPdat         PORTBbits.RB6       // ->  12 -  ICSP Data
#define ICSPclk         PORTBbits.RB7       // ->  13 -  ICSP CLK
#define DB4             PORTAbits.RA0       // ->  17 -  LCD data bus
#define DB5             PORTAbits.RA1       // ->  18 -  LCD data bus
#define DB6             PORTAbits.RA2       // ->  1  -  LCD data bus
#define DB7             PORTAbits.RA3       // ->  2  -  LCD data bus
#define OImpuls         PORTAbits.RA4       // ->  3  -
#define Vpp             PORTAbits.RA5       // ->  4  -
#define OGun            PORTAbits.RA6       // ->  15 -
#define Start           PORTAbits.RA7       // ->  16 -

#define RunTimer0       T0CS = false;    //Clock Select system CLK

void timerIni(void);
void portIni(void);
