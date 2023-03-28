//#include <TimeLib.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  int beg = RTC.begin();
  if(beg){
    Serial.println("RTC Begins...");
  }
  else{
    Serial.println("RTC Hasn't Begun?");
  }
  /*
  while (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    delay(10);
  }
  */
  /*
  if(RTC.isrunning()){
    Serial.println("RTC *is* Running!");
  }
  else{
    Serial.println("RTC is not Running?");
  }
  */
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
//  Serial.println("Time set");

  pinMode(3, OUTPUT);
}

void loop() {
  DateTime now = RTC.now();

  uint8_t sec = now.second();

  if(sec >= 0 && sec < 15){
    Serial.println(0);
  }
  else if(sec >= 15 && sec){
    Serial.println(map(sec, 0, 59, 0, 255));
  }
  else{
    Serial.println(127);
  }

  Serial.println(now.timestamp());
  delay(1000);
}
