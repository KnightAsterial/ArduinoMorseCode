int sensor = -99; //change this to the board value
int state = LOW;
int val = 0;

long timeSinceLastChangeIR = 0;
bool previousStateIR = false;
String codedString = "";

void setup() {
  timeSinceLastChangeIR = millis();
  pinMode(sensor, INPUT);

}

void loop() {
  val = digitalRead(sensor);
  if(val == HIGH){
    if(previousStateIR == false){
      timeSinceLastChangeIR = millis();
    }
    previousStateIR = true;
  }
  else{
    if(previousStateIR == true){
      if(millis()-timeSinceLastChangeIR > 300){
        codedString += "-";
      }
      else{
        codedString += ".";
      }
      timeSinceLastChangeIR = millis();
    }
    previousStateIR = false;
  }
  //codedString stores all of the data 
  //just need to convert and output to the LCD

}
