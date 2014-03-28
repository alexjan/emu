//#include<htc.h>
//#include "main.h"

#define false 0
#define true 1
#define count1uS() asm("nop")
#define baseMin 5
#define StopT0()  T0CS = true
#define StartT0() T0CS = false
#define delayUs() asm("nop")
#define delay5Us()  delayUs();               \
                    delayUs();               \
                    delayUs();               \
                    delayUs();               \
                    delayUs();


void delay10Us(unsigned char);
void delayMs(unsigned char);
void delayS(unsigned char);

volatile unsigned char next;

