#pragma once
#ifndef EVENT_H
#define EVENT_H
#include "Game.h"

#include <string>
using namespace std;

class Event {
private:
    int time;
    string team;
    bool isGoal;
    string player;
    string assists;
    int penaltyTime;
    string penaltyType;
public:
    Event() : time(0), team(""), isGoal(false), player(""), assists(""), penaltyTime(0), penaltyType("") {}
    ~Event() {}
    void parseEvent(ifstream& input);
    void outputEvent(ofstream& output);
    int getTime() const;
    string getTeam() const;
    bool getIsGoal() const;
    string getPlayer() const;
    string getAssists() const;
    int getPenaltyTime() const;
    string getPenaltyType() const;
};

#endif
