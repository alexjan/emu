#include<htc.h>
#include"key.h"
#include"delay.h"

extern bit key_mode;

unsigned char scanch(void) {
    unsigned char scancode;
    if (!keyOk) {
        if (!keyUp)scancode = 'H';
        else if (!keyDown)scancode = 'L';
        else scancode = 'Y';
    }
    else if (!keyUp)scancode = 'U';
    else if (!keyDown)scancode = 'D';
    else scancode = 'N';
    return scancode;

}

unsigned char getch(void) {
    static unsigned char Char;
    unsigned char countscan = 5;
    key_mode = false;
    Char = scanch();
    delayMs(10);
    while ((Char == scanch()) && countscan--)delayMs(20);
    if(!countscan)key_mode = true;
    return Char;
}
