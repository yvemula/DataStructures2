#include "Period.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

void Period::parsePeriod(ifstream& input) {
    string line;
    getline(input, line);
    int index = 7;
    // parse number
    while (line[index] != '\0') {
        number *= 10;
        number += line[index] - '0';
        index++;
    }
    while (getline(input, line)) {
        if (line.find("PERIOD") != string::npos) {
            break;
        }
        Event event;
        event.parseEvent(input);
        events.push_back(event);
    }
}

void Period::outputPeriod(ofstream& output) {
    output << "Period " << number << endl;
    sort(events.begin(), events.end(), [](Event a, Event b) { return a.getTime() < b.getTime(); });
    for (Event event : events) {
        event.outputEvent(output);
    }
}

int Period::getNumber() const {
    return number;
}

vector<Event> Period::getEvents() const {
    return events;
}
