#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonPin = 7;
bool previousState = false;
int timeSinceLastChange = 0;
String code = "";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  timeSinceLastChange = millis();

  pinMode(buttonPin, INPUT);
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

  
}



