#include <LiquidCrystal.h>
#include "pitches.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonPin = 7;
bool previousState = false;

const int wordButtonPin = 6;
bool previousWordState = false;

long timeSinceLastChange = 0;
String code = "";

String decoded = "";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  timeSinceLastChange = millis();

  pinMode(buttonPin, INPUT);
  pinMode(wordButtonPin, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  if(code.length() > 16){
    lcd.setCursor(0,0);
    code = code.substring(code.length()-1, code.length());
    lcd.print("                                      ");
  }
  lcd.setCursor(0,0);
  lcd.print(code);

  if(digitalRead(buttonPin) == HIGH){
    if(previousState == false){
      timeSinceLastChange = millis();
    }
    previousState = true;
  }
  else{
    if(previousState == true){
      if(millis()-timeSinceLastChange > 300){
        code += "-";
      }
      else{
        code += ".";
      }
      timeSinceLastChange = millis();
    }
    previousState = false;
  }

  //----
  if(digitalRead(wordButtonPin) == HIGH){
    if(previousWordState == false){
      decoded += interpret(code);
      code = "";
      lcd.setCursor(0,0);
      lcd.print("                   ");
      lcd.setCursor(0,1);
      lcd.print("                   ");
      lcd.setCursor(0,1);
      lcd.print(decoded);
    }
    previousWordState = true;
  }
  else{
    previousWordState = false;
  }


}

String interpret(String code){
  return "_";
}





