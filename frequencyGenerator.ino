#include <LiquidCrystal.h>

/**
https://www.arduino.cc/en/Tutorial/LibraryExamples/LiquidCrystalBlink
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:  Controls contrast of letters.
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)
*/

/**
LCD Pins on breadboard:
BB | LCD
20 - VSS
21 - VDD
22 - V0
23 - RS
24 - RW
25 - E
26 - D0
27 - D1
28 - D2
29 - D3
30 - D4
31 - D5
32 - D6
33 - D7
34 - A
35 - K
*/

// const int rs = 12, en = 11, d3 = 6, d2 = 7, d1 = 8, d0 = 9;
const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
// LiquidCrystal lcd(rs, en, d0, d1, d2, d3);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t ii = 0;
char start_char = 'A';
char end_char = 'Z';
int dtime = 500;

void setup() {

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    // lcd.print("hello, world!");
}

void loop() {
    if ((start_char + ii) > end_char) {
        ii = 0;
    }
    lcd.home();
    lcd.print((char)(start_char + ii));
    ii++;
    // Turn on the blinking cursor:
    // lcd.blink();
    delay(dtime);
}
