//#include <TimeLib.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const char ledPin = 3;
unsigned char pinOut = 0;

// The below variables are arbitrary and 
// should be determined by the user
const uint32_t secondsInDay = uint32_t(60)*60*24;
const char alarmHour = 22; // Wake up hour
const char alarmMinute = 00; // Wake up minute
const char alarmPeriod = 10; // Minutes to get to full intensity

uint32_t now, alarmTime = (uint32_t(alarmHour)*60*60) + (alarmMinute*60);
const uint32_t alarmTimePlusPeriod = alarmTime + (alarmPeriod*60);

void setup() {
    Serial.begin(9600);
    Wire.begin();
    int rtcBegin = RTC.begin();
    if(rtcBegin){
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
    Serial.println("Time set");

    pinMode(ledPin, OUTPUT);
}

void loop() {
	now = RTC.now().unixtime() % secondsInDay;

    pinOut = map(now, alarmTime, alarmTimePlusPeriod, 0, 255);
    if(now >= alarmTime && now < alarmTimePlusPeriod){
        analogWrite(ledPin, pinOut);
    }
    else if(now >= alarmTimePlusPeriod){
        analogWrite(ledPin, 255);
    }
    
    Serial.println(RTC.now().timestamp());
    Serial.println(pinOut);
    
	delay(1000);
}
