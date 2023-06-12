// time.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "time.h"

Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::setHour(int h) {
    hour = h;
}

void Time::setMinute(int m) {
    minute = m;
}

void Time::setSecond(int s) {
    second = s;
}

void Time::PrintAMPM() const {
    std::string ampm;
    if (getHour() >= 12) {
        ampm = " pm";
    }
    else {
        ampm = " am";
    }
    if (getHour() == 0 || getHour() == 12) {
        std::cout << 12 << ":";
    }
    else {
        std::cout << getHour() % 12 << ":";
    }

    if (getMinute() < 10) {
        std::cout << "0";
    }
    std::cout << getMinute() << ":";
    if (getSecond() < 10) {
        std::cout << "0";
    }
    std::cout << getSecond() << ampm << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
    if (t1.getHour() < t2.getHour()) {
        return true;
    }
    else if (t1.getHour() > t2.getHour()) {
        return false;
    }
    else if (t1.getMinute() < t2.getMinute()) {
        return true;
    }
    else if (t1.getMinute() > t2.getMinute()) {
        return false;
    }
    else if (t1.getSecond() < t2.getSecond()) {
        return true;
    }
    else {
        return false;
    }
}