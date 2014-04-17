#include<htc.h>
#include"key.h"
#include"delay.h"

extern bit key_mode;

unsigned char scanch(void) {
    unsigned char scancode;
    scancode = 7;
    keyUp ? scancode |= 4 :  scancode &= 3;
    keyDown ? scancode |= 2 :  scancode &= 5;
    keyOk ? scancode |= 1 :  scancode &= 6;
       
    switch(scancode){
        case 0b110 : scancode = 'Y';
        break;
        case 0b101 : scancode = 'D';
        break;
        case 0b011 : scancode ='U';
        break;
        case 0b001 : scancode = 'L';
        break;
        case 0b100 : scancode ='H';
        break;        
        default : scancode ='N';
    }
    return scancode;

}

unsigned char getch(void) {
    static unsigned char Char;
    unsigned char  countscan = 20;
    Char = scanch();
    delayMs(10);
    while ((Char == scanch()) && countscan--)delayMs(100);
    if(!countscan)key_mode = true;
    return Char;
}
