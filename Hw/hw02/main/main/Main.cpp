#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "Event.h"
#include "Period.h"
#include "Game.h"

using namespace std;

int main() {
    ifstream input("2012_small.txt");
    ofstream output("2012_small_output.txt");
    vector<Period> periods;

    while (input.good()) {
        Period period;
        period.parsePeriod(input);
        periods.push_back(period);
    }
    for (Period period : periods) {
        period.outputPeriod(output);
    }

    input.close();
    output.close();
    return 0;
}
