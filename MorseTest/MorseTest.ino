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

  if(decoded == "AFRICA"){
    playSong();
    decoded = "";
    code = "";
    lcd.setCursor(0,1);
    lcd.print("                   ");
  }
}

String interpret(String code){
  if(code == ".-"){
    return "A";
  }
  else if (code == "..-."){
    return "F";
  }
  else if (code == ".-."){
    return "R";
  }
  else if (code == ".."){
    return "I";
  }
  else if (code == "-.-."){
    return "C";
  }
  else{
    return "_";
  }
}


void playSong(){ 
    // notes in the melody:
    int melody[] = {
     //DIFFERENT SONG BELOW
     // NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4

   
     //BEGIN AFRICA
     NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4,
     NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4,
     NOTE_C5, 0,
     NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
     NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4,
     NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4,
     NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4,
     NOTE_D4, 0,
     NOTE_D4,NOTE_C4, NOTE_F4, 
     //START REPEAT
     0, NOTE_G4, NOTE_G4, NOTE_G4,
     NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4,
     NOTE_C5, 0, NOTE_E4,
     NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
     NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4,
     NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4,
     NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, 
     NOTE_D4, 0, 
     NOTE_D4, NOTE_C4, NOTE_F4,
     0, NOTE_G4, NOTE_G4, NOTE_G4,
     NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4,
     NOTE_C5, NOTE_E4, NOTE_E4,
     NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
     NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_D4,
     NOTE_D4, NOTE_C4, NOTE_D4, NOTE_C4,
     NOTE_E4, NOTE_D4, NOTE_C4,
     NOTE_D4, 0,
     NOTE_D4, NOTE_C4, NOTE_F4,
     0, NOTE_G4, NOTE_G4, NOTE_G4,
     NOTE_G4, NOTE_G4, NOTE_A4, NOTE_B4,
     NOTE_C5, 0,
     NOTE_E5, NOTE_E5, NOTE_F5, NOTE_G5,
     NOTE_G5, NOTE_F5, NOTE_F5,NOTE_E5, NOTE_F5,
     NOTE_F5,
     0,
     0,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_A5,
     NOTE_A5,
     0, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_A5, 
     NOTE_A5,
     0, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_A5,
     NOTE_A5,
     0, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
     NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_A5,
     NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
     NOTE_A5, NOTE_A5, NOTE_AS5, NOTE_A5,
     NOTE_G5, 0,
     NOTE_D5, NOTE_D5, NOTE_D5,
     NOTE_D5, NOTE_C5, NOTE_F5,
     NOTE_F5,
     0,
     NOTE_D5, NOTE_D5, NOTE_D5,
     NOTE_D5, NOTE_C5, NOTE_F5,
     NOTE_F5, 0, //END REPEAT
     NOTE_D4,
     NOTE_D4, NOTE_C4, NOTE_F4,
     NOTE_F4,
     0
     
     
     
    };
    
    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
      2, 1, 1, 4,
      2, 2, 2, 2,
      4, 4,
      2, 2, 2, 2,
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 1, 1, 2,
      4, 4,
      2, 2, 4,
      //START REPEAT
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 2, 2,
      2, 2, 2, 2,
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 1, 1, 2,
      4, 4,
      2, 2, 4,
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 2, 2,
      1, 1, 2, 2, 2,
      2, 2, 1, 1, 2,
      2, 2, 2, 2,
      4, 2, 2,
      4, 4,
      2, 2, 4,
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 4,
      2, 2, 2, 2,
      2, 2, 1, 1, 2,
      8,
      8,
      8,
      2, 1, 1, 2, 2,
      2, 2, 1, 1, 2,
      6, 2,
      8,
      2, 2, 1, 1, 1, 1,
      2, 2, 2, 2,
      3, 1, 2, 2,
      8,
      2, 2, 2, 2,
      4, 2, 2,
      6, 2,
      8,
      2, 1, 1, 2, 2,
      2, 2, 2, 2,
      2, 2, 2, 2,
      4, 1, 1, 2,
      4, 1, 1, 2,
      6, 2,
      3, 1, 4,
      2, 2, 4,
      8,
      8,
      3, 1, 4,
      2, 2, 4,
      8,
      8,
      8,
      2, 2, 4,
      8,
      8
      
      
    };
    
    for (int thisNote = 0; thisNote < 201; thisNote++) {
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 120* noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
}

