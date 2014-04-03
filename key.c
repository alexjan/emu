#include<htc.h>
#include"key.h"
#include"delay.h"

extern bit key_mode;

unsigned char scanch(void) {
    unsigned char scancode;
    switch((PORTB >> 3) & 7){
        case 0b011 : scancode = 'Y';
        break;
        case 0b110 : scancode = 'D';
        break;
        case 0b101 : scancode ='U';
        break;
        case 0b100 : scancode = 'L';
        break;
        case 0b001 : scancode ='H';
        break;        
        default : scancode ='N';
    }
    return scancode;

}

unsigned char getch(void) {
    static unsigned char Char;
    unsigned char  countscan = 10;
    Char = scanch();
    delayMs(10);
    while ((Char == scanch()) && countscan--)delayMs(100);
    if(!countscan)key_mode = true;
    return Char;
}
