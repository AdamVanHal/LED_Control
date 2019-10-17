#include <math.h>
int hourPins[5] = {0,1,2,3,4};
int minutePins[6] = {5,6,7,8,9,10};
int secondPins[6] = {11,12,24,25,26,27};
int htime = 17;
int mtime = 03;
int stime = 00;

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

  TempTime = stime;
  for(int i = 5; i>=0; i--){
    if((pow(2,i))<=TempTime){
      TempTime=TempTime-(pow(2,i));
      digitalWrite(secondPins[i], HIGH);
    }else{
      digitalWrite(secondPins[i], LOW);
    }
  }

  stime ++;
  if(stime>59){
    stime=0;
    mtime++;
    if(mtime>59){
      mtime=0;
      htime++;
      if(htime>23){
        htime=0;
      }
    }
  }
  delay(999);

}
