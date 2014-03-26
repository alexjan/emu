#include <htc.h>
#include "delay.h"
//Functions for clk = 4MHz (1 instruction = 1 uS)

bit stop;

void delay10Us(unsigned char countUs){
        while(cnt--);
}

void delayMs(unsigned char countMs){
	while(countMs--) delay10Us(100);
}

void dealayS(unsigned int countS){
	while(countS--) delayUs(1000);
}
