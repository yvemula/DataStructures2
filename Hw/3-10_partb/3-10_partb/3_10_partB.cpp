#include <string>
#include <iostream>

int main() {
    const int ARRAY_SIZE = 3;
    std::string strings[ARRAY_SIZE];

    // Fill the array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::getline(std::cin, strings[i]);
    }

    // Process the strings
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::string s = strings[i];

        // Check if ends with "es"
        if (s.size() >= 2 && s.substr(s.size() - 2, 2) == "es") {
            std::cout << s << "\n";
        }

        // Check if begins with "yan"
        else if (s.substr(0, 3) == "yan") {
            std::cout << s << "\n";
        }
    }

    return 0;
}
