#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Period.h"
using namespace std;

class Game {
private:
    string date;
    string awayTeam;
    string homeTeam;
    vector<Period> periods;
    int awayScore;
    int homeScore;
public:
    Game() : date(""), awayTeam(""), homeTeam(""), periods(), awayScore(0), homeScore(0) {}
    ~Game() {}
    void parseGame(ifstream& input);
    void outputGame(ofstream& output);
    string getDate() const;
    string getAwayTeam() const;
    string getHomeTeam() const;
    vector<Period> getPeriods() const;
    int getAwayScore() const;
    int getHomeScore() const;
};

#endif
