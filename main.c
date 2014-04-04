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
    commandStart,          \
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
    lcdIni();
    
    RunInit = false;

/******************************************************************************/

    if (nPOR) {
        if (nBOR) {
            if (!nTO) {
                if (nPD) {
                    RunInit = true; // WDT Reset
                    // Here Set error.....
                } else; // WDT Wake-up "Nothing"
            }
        } else {
            RunInit = true; //Brown-out Reset
        }
    } else if (!nTO || !nPD) {
        RunInit = true; //Power-on Reset
    }
/******************************************************************************/    
    ei();

    while (true) {

        /*************************** System Timer *****************************/

        if (Count200uS > 50) {
            if (Count10mS++ > 100) {
	    	
	    	}Count10mS = 0;
            }
            CLRWDT();
            Count200uS = 0;
        }

        /************* System timer END ***************************************/

        /************ Unload Buffer ****************************************/

        if (commandStart) {
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
                    commandStart = false;
                }
            }
        }

        /*********** End Block ************************************************/
    }


void interrupt MyInt(void) {
    if (T0IE && T0IF) {
        
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
