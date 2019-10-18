#include <math.h>
int hourPins[5] = {0,1,2,3,4};
int minutePins[6] = {5,6,7,8,9,10};
int secondPins[6] = {11,12,24,25,26,27};
int htime = 17;
int mtime = 03;
long stime = 00;
unsigned int loopStart = 0;
unsigned int elapsedTime = 0;

void setup() {
  //init serial
  Serial.begin(9600);
  //pin 0-12 output
  for(int i=0;i<=12;i++){
    pinMode(i, OUTPUT);
  }
  //pin 24-27 output
  for(int i=24;i<=27;i++){
    pinMode(i, OUTPUT);
  }

  //pin 0-12 high then low
  for(int i=0;i<=12;i++){
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
  //pin 24-27 high then low
  for(int i=24;i<=27;i++){
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
}

void loop() {
  if(millis()-loopStart>=(1000-(elapsedTime%1000))){//check if more than a second has elapsed
    //offset actual start time to when it should of started
    //this is to prevent the acumulation of partial seconds that can add up to add extra skips

    //calculate and save time elapsed since this might be 
    //dramatically more than 1 second if serial handling delayed us
    elapsedTime = millis()-loopStart;
    loopStart = millis();
    
    stime =+ elapsedTime/1000.0;
    if(stime>59){
      mtime += stime/60;
      stime= stime - (stime/60);
      if(mtime>59){
        mtime= mtime-60; //i dont think I need to handle jumps of more than a few min
        htime++;
        if(htime>23){
          htime=0;
        }
      }
    }
    //delay(999);
    
    int TempTime = htime;
    for(int i = 4; i>=0; i--){
      if((pow(2,i))<=TempTime){
        TempTime=TempTime-(pow(2,i));
        digitalWrite(hourPins[i], HIGH);
      }else{
        digitalWrite(hourPins[i], LOW);
      }
    }
  
    TempTime = mtime;
    for(int i = 5; i>=0; i--){
      if((pow(2,i))<=TempTime){
        TempTime=TempTime-(pow(2,i));
        digitalWrite(minutePins[i], HIGH);
      }else{
        digitalWrite(minutePins[i], LOW);
      }
    }
  
    TempTime = stime;//remember stime (seconds) is fractional to prevent drift over time
    for(int i = 5; i>=0; i--){
      if((pow(2,i))<=TempTime){
        TempTime=TempTime-(pow(2,i));
        digitalWrite(secondPins[i], HIGH);
      }else{
        digitalWrite(secondPins[i], LOW);
      }
    }//end seconds display loop
  }//end time elapsed if statement
}//end loop

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
