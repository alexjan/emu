#include<htc.h>
#include"key.h"
#include"delay.h"

extern bit press_buttom, scan;
extern unsigned char Char;

unsigned char scanch(void) {
    unsigned char scancode;
    if (!keyOk) {
        if (!keyUp)scancode = 'H';
        else if (!keyDown)scancode = 'L';
        else scancode = 'Y';
    } else if (!keyUp)scancode = 'U';
    else if (!keyDown)scancode = 'D';
    else scancode = 'N';
    return scancode;

}

unsigned char getch(void) {
    static unsigned char tempch;
    scan = true;
    do {
        Char = false;
        while (!Char);
        tempch = Char;
        Char = false;
        while (!Char);
    } while (Char != tempch);
    scan = false;
    return Char;
}

unsigned char get(void) {
    unsigned char tmpch, count = 5;
    tmpch = getch();
    if (tmpch == 'N');
    else {
        while (--count) {
            if (tmpch != getch())break;
        }
    }
    return tmpch;
}
