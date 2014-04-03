#define false 0
#define true 1
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
