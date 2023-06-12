#include "Game.h"
#include <iostream>
#include <fstream>
using namespace std;

void Game::parseGame(ifstream& input) {
    string line;
    getline(input, line);
    date = line;
    getline(input, line);
    awayTeam = line.substr(0, line.find(" at "));
    homeTeam = line.substr(line.find(" at ") + 4);
    while (getline(input, line)) {
        if (line.find("PERIOD") != string::npos) {
            Period period;
            period.parsePeriod(input);
            periods.push_back(period);
        }
        else if (line.find("FINAL") != string::npos) {
            break;
        }
    }
    getline(input, line);
    awayScore = line[0] - '0';
    getline(input, line);
    homeScore = line[0] - '0';
}

void Game::outputGame(ofstream& output) {
    output << date << endl;
    output << awayTeam << " at " << homeTeam << endl;
    for (Period period : periods) {
        period.outputPeriod(output);
    }
    output << "FINAL" << endl;
    output << awayTeam << " " << awayScore << endl;
    output << homeTeam << " " << homeScore << endl;
}

string Game::getDate() const
{
    return string();
}

string Game::getAwayTeam() const
{
    return string();
}

string Game::getHomeTeam() const
{
    return string();
}

vector<Period> Game::getPeriods() const
{
    return vector<Period>();
}

int Game::getAwayScore() const
{
    return 0;
}

int Game::getHomeScore() const
{
    return 0;
}
