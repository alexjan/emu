#include <htc.h>
#include "delay.h"
//Functions for clk = 4MHz (1 instruction = 1 uS)


void delay10Us(unsigned char count) {
    count--;
//        delayUs();
    while (count--) {
        delayUs();
        delayUs();
        delayUs();
    }
}

void delayMs(unsigned char countMs) {
    countMs--;
    do {
        delay10Us(99);
        delayUs();
        delayUs();
    } while (countMs--);
}

void delayS(unsigned char countS) {
    unsigned char cnt;
    countS--;
    do{
        cnt = 10;
        while (cnt--) delayMs(100);
    }
    while(countS--);
    
}
