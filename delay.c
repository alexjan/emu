#include <htc.h>
#include "delay.h"
//Functions for clk = 4MHz (1 instruction = 1 uS)

bit stop;

void delay10Us(unsigned char count){
    count--;
//    delayUs();
    while(count--){
        delayUs();
        delayUs();
        delayUs();
    }
}

void delayMs(unsigned char countMs){
   
//    
}

void delayS(unsigned char countS){
	while(--countS) delayMs(1000);
}
