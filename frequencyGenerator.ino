#include <LiquidCrystal.h>
#include <RotaryEncoder.h>

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

/*
    Encoder pins are 2 and 3
*/

// const int A0 = A0;
const int enc_pin1 = 2;                   // DT on encoder
const int enc_pin2 = 3;                   // CLK on encoder
RotaryEncoder rotenc(enc_pin1, enc_pin2); // LatchMode::FOUR0 ???
// RotaryEncoder::LatchMode::TWO03);
// RotaryLatchMode::FOUR0);

// For some reason when set in 4-bit mode, it uses pins d4-d7
// instead of the presumed; d0-d3 ...
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int dtime = 100;

char buff_1[16];
bool button_pressed = false;
int iter = 0;
int foo = 0;

void checkPosition() {
    rotenc.tick(); // just call tick() to check the state.
}

int pos = 0;
char buff[16];

void setup() {
    Serial.begin(115200);
    while (!Serial) {
    }
    Serial.println("I am running");

    // Setup the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // clear and setup first line.
    lcd.clear();
    sprintf(buff, "pos: %d", pos);
    lcd.print(buff);

    // Setup encoder interrupts:
    attachInterrupt(digitalPinToInterrupt(enc_pin1), checkPosition, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enc_pin2), checkPosition, CHANGE);

    // Setup push button.
    // XXX button pulls high: KY-040 Rotary Encoder Module
    // https://www.amazon.com/gp/product/B06XQTHDRR/
    pinMode(A0, INPUT_PULLUP);
}

const long MAX_POS = 32;
const long MIN_POS = -32;

void checkPositionLimits() {
    if (pos < MIN_POS) {
        rotenc.setPosition(MIN_POS);
        pos = MIN_POS;
    }
    if (pos > MAX_POS) {
        rotenc.setPosition(MAX_POS);
        pos = MAX_POS;
    }
}

void loop() {

    long newPos = rotenc.getPosition();
    if (newPos != pos) {
        lcd.clear();
        pos = newPos;
        checkPositionLimits();
        sprintf(buff, "pos: %d", pos); // Probably should be sprintfn?
        lcd.print(buff);

        // sprintf(buff_1, "ms: %d", rotenc.getMillisBetweenRotations());
        // lcd.setCursor(0, 1);
        // lcd.print(buff_1);
    }
    int button_state = digitalRead(A0);
    if (button_state == LOW) {
        Serial.print("Button state is low, button_pressed ");
        Serial.println(button_pressed ? "ON" : "OFF");
        if (button_pressed) {
            Serial.print("Button is pressed, setting to FALSE - ");
            button_pressed = false;
            Serial.println(iter);
        } else {
            Serial.print("Button is not pressed, setting to TRUE - ");
            button_pressed = true;
            Serial.println(iter);
        }
        Serial.println("I am about to sleep");
    }
    iter++;
    // XXX this sprintf is corrupting the stack vars.
    // sprintf(buff_1, "b: %-13s", button_pressed ? "ON" : "OFF");
    // lcd.setCursor(0, 1);
    // lcd.print(buff_1);
    delay(dtime);
}
