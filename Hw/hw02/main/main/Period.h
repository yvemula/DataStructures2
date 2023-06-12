#ifndef PERIOD_H
#define PERIOD_H
#include <vector>
#include "Event.h"
using namespace std;

class Period {
private:
    int number;
    vector<Event> events;

public:
    Period() : number(0), events() {}
    ~Period() {}
    void parsePeriod(ifstream& input);
    void outputPeriod(ofstream& output);
    int getNumber() const;
    vector<Event> getEvents() const;
};
#endif
