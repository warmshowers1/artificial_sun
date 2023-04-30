#include "Timestamp.h"

// Constructors
Timestamp::Timestamp(uint8_t hour, uint8_t minute){
    this->hour_ = hour % 24;
    this->minute_ = minute % 60;
    this->day_seconds_ = (uint32_t(this->hour_)*3600) + (this->minute_*60);
}
Timestamp::Timestamp(uint32_t seconds){
    this->hour_ = uint8_t((seconds/3600) % 24);
    this->minute_ = uint8_t((seconds/60) % 60);
    this->day_seconds_ = seconds % 86400; //86400 seconds per 24 hrs
}

// Getters
uint8_t Timestamp::getHour() const{
    return this->hour_;
}
uint8_t Timestamp::getMinute() const{
    return this->minute_;
}
uint32_t Timestamp::getDaySeconds() const{
    return this->day_seconds_;
}

// Setters
void Timestamp::setHour(uint8_t hour){
    this->hour_ = hour % 24;
    this->day_seconds_ = (uint32_t(this->hour_)*3600) + (this->minute_*60);
}
void Timestamp::setMinute(uint8_t minute){
    this->minute_= minute % 60;
    this->day_seconds_ = (uint32_t(this->hour_)*3600) + (this->minute_*60);
}
void Timestamp::setDaySeconds(uint32_t seconds){
    this->hour_ = uint8_t((seconds/3600) % 24);
    this->minute_ = uint8_t((seconds/60) % 60);
    this->day_seconds_ = seconds % 86400;
}

// Operators
bool Timestamp::operator==(Timestamp right) const{
    return day_seconds_ == right.getDaySeconds();
}
bool Timestamp::operator!=(Timestamp right) const{
    return day_seconds_ != right.getDaySeconds();
}
bool Timestamp::operator>(Timestamp right) const{
    return day_seconds_ > right.getDaySeconds();
}
bool Timestamp::operator<(Timestamp right) const{
    return day_seconds_ < right.getDaySeconds();
}
bool Timestamp::operator>=(Timestamp right) const{
    return day_seconds_ >= right.getDaySeconds();
}
bool Timestamp::operator<=(Timestamp right) const{
    return day_seconds_ <= right.getDaySeconds();
}

void Timestamp::print() const {
    Serial.print("Timestamp <");
    if(this->hour_ < 10){
        Serial.print("0");
        Serial.print(this->hour_);
    }
    else{
        Serial.print(this->hour_);
    }
    Serial.print(":");
    if(this->minute_ < 10){
        Serial.print("0");
        Serial.print(this->minute_);
    }
    else{
        Serial.print(this->minute_);
    }
    Serial.print(" (");
    Serial.print(this->day_seconds_);
    Serial.println(")>");
}
