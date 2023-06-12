#include "Event.h"
#include <fstream>
#include <iomanip>

void Event::parseEvent(ifstream& input) {
    string line;
    getline(input, line);
    int index = 0;
    // parse time
    while (line[index] != ' ') {
        time += line[index] - '0';
        index++;
    }
    index++;
    // parse team
    while (line[index] != ' ') {
        team += line[index];
        index++;
    }
    index++;
    string eventType;
    while (line[index] != ' ') {
        eventType += line[index];
        index++;
    }
    if (eventType == "goal") {
        isGoal = true;
        index++;
        // parse player
        while (line[index] != ' ') {
            player += line[index];
            index++;
        }
        index++;
        // parse assists
        while (line[index] != '\0') {
            assists += line[index];
            index++;
        }
    }
    else if (eventType == "penalty") {
        isGoal = false;
        index++;
        // parse player
        while (line[index] != ' ') {
            player += line[index];
            index++;
        }
        index++;
        // parse penalty time
        string penaltyTimeStr = "";
        while (line[index] != ' ') {
            penaltyTimeStr += line[index];
            index++;
        }
        penaltyTime = stoi(penaltyTimeStr);
        index++;
        // parse penalty type
        while (line[index] != '\0') {
            penaltyType += line[index];
            index++;
        }
    }
}

void Event::outputEvent(ofstream& output) {
    if (isGoal) {
        output << setw(5) << time << setw(10) << team << setw(10) << "goal" << setw(20) << player << setw(20) << assists << endl;
    }
    else {
        output << setw(5) << time << setw(10) << team << setw(10) << "penalty" << setw(20) << player << setw(5) << penaltyTime << setw(20) << penaltyType << endl;
    }
}
