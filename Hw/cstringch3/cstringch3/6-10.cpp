#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>

int main() {
    int choice;

    // Print the menu
    std::cout << "Menu\n";
    std::cout << "1. Cosine\n";
    std::cout << "2. Logarithms\n";
    std::cout << "3. Decimal and Hexadecimal conversion\n";
    std::cout << "4. Cstring date format change\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Use a switch to respond to the user's menu choice
    switch (choice) {
    case 1: {
        int schoice;
        double number;
        // Submenu for cosine options
        std::cout << "1. Cosine\n";
        std::cout << "2. Arc cosine\n";
        std::cout << "3. Hyperbolic cosine\n";
        std::cout << "Enter your choice: ";
        std::cin >> schoice;
        std::cout << "Enter a number: ";
        std::cin >> number;

        // Set the precision of output
        std::cout << std::fixed << std::setprecision(3);  // Use 'fixed' floating-point notation and set precision to 3 decimal places
        switch (schoice) {
        case 1:
            std::cout << cos(number) << '\n'; // Compute cosine using cmath library
            break;
        case 2:
            std::cout << acos(number) << '\n'; // Compute arc cosine using cmath library
            break;
        case 3:
            std::cout << cosh(number) << '\n'; // Compute hyperbolic cosine using cmath library
            break;
        }
        break;
    }
    case 2: {
        int schoice;
        double number;
        std::cout << "1. Common Logarithm (log10)\n";
        std::cout << "2. Natural Logarithm (ln)\n";
        std::cout << "Enter your choice: ";
        std::cin >> schoice;
        std::cout << "Enter a number: ";
        std::cin >> number;

        std::cout << std::showpos << std::fixed << std::setprecision(3); // Enable showing the '+' sign for positive numbers
        switch (schoice) {
        case 1:
            std::cout << log10(number) << '\n'; // Compute common logarithm (base 10)
            break;
        case 2:
            std::cout << log(number) << '\n'; // Compute natural logarithm (base e)
            break;
        }
        break;
    }
    case 3: {
        int schoice;
        bool lowercase;
        std::cout << "1. Decimal to Hexadecimal\n";
        std::cout << "2. Hexadecimal to Decimal\n";
        std::cout << "Enter your choice: ";
        std::cin >> schoice;
        if (schoice == 1) {
            std::cout << "Do you want to use lowercase? (1 for yes, 0 for no): ";
            std::cin >> lowercase;
        }
        std::cout << std::setbase(schoice == 1 ? 10 : 16); // Change the base of input according to user's choice
        int number;
        std::cout << "Enter a number: ";
        std::cin >> number;
        std::cout << std::showbase; // Show the base of output number
        if (lowercase) std::cout << std::nouppercase; // Use lowercase if user chose so
        std::cout << std::setbase(schoice == 1 ? 16 : 10); // Change the base of output according to user's choice
        std::cout << number << '\n';
        break;
    }
    case 4: {
        char date[11];
        std::cout << "Enter date (mm/dd/yyyy): ";
        std::cin >> date;
        char* tk = strtok(date, "/"); // Use strtok to split the string
        std::string new_date = tk; // First token (month)
        while ((tk = strtok(NULL, "/")) != NULL) { // While there are more tokens
            new_date += "-"; // Append the separator
            new_date += tk; // Append the next token
        }
        std::cout << new_date << '\n'; // Print the newly formatted date
        break;
    }
    }

    return 0;
}

//Depending on the user's choice, the program can compute
//various types of cosine, logarithms, convert numbers between decimal 
//and hexadecimal formats, or manipulate dates formatted as cstrings. 
//For instance, if a user picks to compute cosines, the program asks
//whether they want to find the cosine, arc cosine, or hyperbolic cosine 
//of a number they input. Likewise, for date manipulation, it allows users
//to input a date in the "mm/dd/yyyy" format and converts it to the "mm-dd-yyyy" 
//format using cstring functions.