#include <htc.h>
#include "main.h"

__IDLOC(0001);

__CONFIG(FOSC_INTOSCIO &  \
        WDTE_OFF &        \
        PWRTE_ON &        \
        MCLRE_OFF &       \
        BOREN_ON &        \
        LVP_OFF);

extern bit stop;
bit key_mode, RUN;
unsigned int CountLitrs;

bit ModeBlock,             \
    ResBuf,                \
    FullBuf,               \
    uBlockGun,             \
    Rise,                  \
    RunInit,               \
    RDimpuls,              \
    key_mode,              \
    RUN;

volatile unsigned char cnt,                \
                       TimeOutGun,         \
                       Count200uS,         \
                       Count10mS,          \
                       var;

unsigned int Buffer,                       \
             count;

void main(void) {
    di();
    portIni();
    timerIni();
    ei();
    lcdIni();
    while (true) {

        /*************************** System Timer *****************************/

        if (Count200uS > 50) {
            if (Count10mS++ > 100) {
                if (!Start && (!FullBuf || ModeBlock)) {
                    if (TimeOutGun++ > 60) {
                        count = 3500;
                        OGun = true;
                        while (count--);
                        TimeOutGun = 0;
                    }
                } else TimeOutGun = 0;
                Count10mS = 0;
            }
            CLRWDT();
            Count200uS = 0;
        }

        /************* System timer END ***************************************/

        /************** Read & Control GUN ************************************/

        if (uBlockGun) OGun = Start;

        /**************** End Block *******************************************/

        /********** Read Impuls ***********************************************/
        if (Start) ResBuf = true;
        else {
            if (Start) {
                if (RDimpuls) {
                    if (ResBuf) {
                        Buffer = 0xFFFF;
                        ResBuf = false;
                    }
                    Buffer++;
                    FullBuf = true;
                    RDimpuls = false;
                }
            } else RDimpuls = true;
        }

        /************ End Block ***********************************************/

        /************ Control Blocking ****************************************/

        if (!ModeBlock && FullBuf && !Start) {
            if (Rise) {
                if (cnt > WidthImp) {
                    OImpuls = true;
                    cnt = 0;
                    Rise = false;
                }
            } else if (cnt > PauseImp) {
                Rise = true;
                OImpuls = false;
                cnt = 0;
                if (!Buffer--) {
                    uBlockGun = true;
                    FullBuf = false;
                }
            }
        }

        /*********** End Block ************************************************/
    }
}

void interrupt MyInt(void) {
    if (T0IE && T0IF) {
        if (FullBuf) cnt++;
        else cnt = 0;
        Count200uS++;
        TMR0 = 81;
        T0IF = false;
    }
}

void portIni(void) {
    PORTA = 0b11110000;
    TRISA = 0b11110000;
    //        |||||||+--> 17 pin --> Data4 (11)
    //        ||||||+---> 18 pin --> Data5 (12)
    //        |||||+---->  1 pin --> Data6 (13)
    //        ||||+----->  2 pin --> Data7 (14)
    //        |||+------>  3 pin
    //        ||+------->  4 pin
    //        |+--------> 15 pin
    //        +---------> 16 pin

    PORTB = 0b11111000;
    TRISB = 0b11111000;
    //        |||||||+-->  6 pin --> RS     (4)
    //        ||||||+--->  7 pin --> RnW    (5)
    //        |||||+---->  8 pin --> E      (6)
    //        |||+------>  9 pin
    //        ||||+-----> 10 pin
    //        ||+-------> 11 pin
    //        |+--------> 12 pin
    //        +---------> 13 pin
    nRBPU = false;
    CMCON |= 0x07;
}

void timerIni(void) {
    TMR0 = 150;
    T0IE = true;
    T0IF = false;
    StartT0();
}
