
#include "delay.h"
#include "lcd.h"
#include "key.h"

#define false 0
#define true 1
#define timer0

#define RSpin RB1       // RB.1(7) - pin.4 LCD
#define RnWpin RB2      // RB.2(8) - pin.5 LCD
#define Epin RB3        // RB.3(9) - pin.6 LCD

void timerIni(void);
void portIni(void);


