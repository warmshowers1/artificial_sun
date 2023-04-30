#include <Wire.h>
#include <RTClib.h>
#include "Timestamp.h"

RTC_DS1307 RTC;

const bool debug = true; // Switch to true if printing to console is desirable

const char ledPin = 3;
unsigned char pinOut = 0;
const uint32_t secondsInDay = uint32_t(60)*60*24;
const char alarmPeriod = 30; // Minutes to get to full intensity

// The below variables are arbitrary and
// should be determined by the user
const char alarmHour = 07; // Wake up hour
const char alarmMinute = 30; // Wake up minute

uint32_t now, alarmTime = (uint32_t(alarmHour)*60*60) + (alarmMinute*60);
uint32_t alarmTimePlusPeriod = alarmTime + (alarmPeriod*60);

void setup() {
    Serial.begin(9600);
    Wire.begin();
    if(RTC.begin()){
        Serial.println("RTC Begins...");
    }
    else{
        Serial.println("RTC Hasn't Begun?");
    }

    // Check if RTC module is running
    while (! RTC.isrunning()) {
        Serial.println("RTC is NOT running!");
        delay(10);
    }

    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("Time set");

    pinMode(ledPin, OUTPUT);
}

void loop() {
	now = RTC.now().unixtime() % secondsInDay;

    if(now >= alarmTime && now < alarmTimePlusPeriod){
        pinOut = map(now, alarmTime, alarmTimePlusPeriod, 30, 255);
    }
    else if(now >= alarmTimePlusPeriod){
        pinOut = 255;
    }
    analogWrite(ledPin, pinOut);
    
    if(debug){
        Serial.print(RTC.now().unixtime());
        Serial.print(" - (");
        Serial.print(RTC.now().timestamp());
        Serial.println(")");
        Serial.print(alarmTime);
        Serial.print(" - ");
        Serial.println(alarmTimePlusPeriod);
        Serial.println(now);
        Serial.println(pinOut);
        Serial.println("-----------------------");
    }
    
	delay(1000);
}
