#include <LiquidCrystal.h>
#include "pitches.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonPin = 7;
int numClicks = 0;
bool previousState = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time:");
  lcd.setCursor(0,1);
  lcd.print("NumClicks:");

  pinMode(buttonPin, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  lcd.setCursor(6,0);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  lcd.setCursor(11, 1);
  lcd.print(numClicks);

  if(digitalRead(buttonPin) == HIGH){
    if(previousState == false){
      numClicks += 1;
    }
    previousState = true;
  }
  else{
    previousState = false;
  }

  
}



