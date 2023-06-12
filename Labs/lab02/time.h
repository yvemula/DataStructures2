// time.h.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

class Time {
    private:
        int hour;
        int minute;
        int second;

    public:
        Time(); 
        Time(int h, int m, int s); 

        int getHour() const;
        int getMinute() const;
        int getSecond() const;

        void setHour(int h);
        void setMinute(int m);
        void setSecond(int s);

        void PrintAMPM() const;
    };

    bool IsEarlierThan(const Time& t1, const Time& t2);
