#include <Wire.h>
#include <RTClib.h>

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

class Timestamp{
    private:
        char hour;
        char minute;
        uint32_t day_seconds; // Seconds in the day, should max out at 86399

    public:
        // Constructors
        Timestamp(char hour){
            this->hour = hour;
            this->minute = 0;
            this->day_seconds = (uint32_t(this->hour)*60*60) + (this->minute*60);
        }
        Timestamp(char hour, char minute){
            this->hour = hour;
            this->minute = minute;
            this->day_seconds = (uint32_t(this->hour)*60*60) + (this->minute*60);
        }
        Timestamp(uint32_t seconds){
            this->hour = char((seconds/60)/60);
            this->minute = (seconds - (this->hour*60*60))/60;
            this->day_seconds = seconds;
        }
        // Getters
        char getHour(){
            return this->hour;
        }
        char getMinute(){
            return this->minute;
        }
        uint32_t getDaySeconds(){
            return this->day_seconds;
        }
        // Operators
        bool operator==(Timestamp right){
            return day_seconds == right.getDaySeconds();
        }
        bool operator>(Timestamp right){
            return day_seconds > right.getDaySeconds();
        }
        bool operator<(Timestamp right){
            return day_seconds < right.getDaySeconds();
        }
        bool operator>=(Timestamp right){
            return day_seconds >= right.getDaySeconds();
        }
        bool operator<=(Timestamp right){
            return day_seconds <= right.getDaySeconds();
        }
};

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
    }
    
	delay(1000);
}
