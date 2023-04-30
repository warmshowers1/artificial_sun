#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include<stdint.h>
#include<Arduino.h>

class Timestamp{
    private:
        uint8_t hour_;
        uint8_t minute_;
        uint32_t day_seconds_; // Seconds in the day, should max out at 86399

    public:
        Timestamp(uint8_t, uint8_t);
        Timestamp(uint32_t);
        uint8_t getHour() const;
        uint8_t getMinute() const;
        uint32_t getDaySeconds() const;
        void setHour(uint8_t);
        void setMinute(uint8_t);
        void setDaySeconds(uint32_t);
        bool operator==(Timestamp right) const;
        bool operator!=(Timestamp right) const;
        bool operator>(Timestamp right) const;
        bool operator<(Timestamp right) const;
        bool operator>=(Timestamp right) const;
        bool operator<=(Timestamp right) const;
        void print() const;
};

#endif
