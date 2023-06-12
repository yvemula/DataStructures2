#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cstring>

using namespace std;

int main() {
    int choice;
    float number;
    bool isRunning = true;

    while (isRunning) {
        cout << "Choose an option:\n";
        cout << "1 - Find Cosines\n";
        cout << "2 - Find Logarithms\n";
        cout << "3 - Convert between Decimal and Hexadecimal\n";
        cout << "4 - Change the format of a cstring date\n";
        cout << "0 - Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            int cosineChoice;
            cout << "1 - Cosine\n";
            cout << "2 - Arc cosine\n";
            cout << "3 - Hyperbolic cosine\n";
            cin >> cosineChoice;
            cout << "Enter a number in radians: ";
            cin >> number;
            cout << fixed << setprecision(3);
            if (cosineChoice == 1) {
                cout << "cos(" << number << ") = " << cos(number) << endl;
            }
            else if (cosineChoice == 2) {
                cout << "acos(" << number << ") = " << acos(number) << endl;
            }
            else if (cosineChoice == 3) {
                cout << "cosh(" << number << ") = " << cosh(number) << endl;
            }
            break;
        }
        case 2: {
            int logChoice;
            cout << "1 - Common logarithm\n";
            cout << "2 - Natural logarithm\n";
            cin >> logChoice;
            cout << "Enter a positive number: ";
            cin >> number;
            cout << showpos << fixed << setprecision(3);
            if (logChoice == 1) {
                cout << "log10(" << number << ") = " << log10(number) << endl;
            }
            else if (logChoice == 2) {
                cout << "ln(" << number << ") = " << log(number) << endl;
            }
            break;
        }
        case 3: {
            int conversionChoice;
            bool useLowercase;
            cout << "1 - Convert Decimal to Hexadecimal\n";
            cout << "2 - Convert Hexadecimal to Decimal\n";
            cin >> conversionChoice;
            if (conversionChoice == 1) {
                int decimal;
                cout << "Use lowercase letters (true/false): ";
                cin >> boolalpha >> useLowercase;
                cout << "Enter a decimal number: ";
                cin >> decimal;
                cout << "0x" << (useLowercase ? nouppercase : uppercase) << hex << decimal << endl;
            }
            else if (conversionChoice == 2) {
                string hexNumber;
                cout << "Enter a hexadecimal number: ";
                cin >> hexNumber;
                unsigned int decimal = stoul(hexNumber, nullptr, 16);
                cout << "Decimal value: " << dec << decimal << endl;
            }
            break;
        }
        case 4: {
            char cstrDate[11], newDate[11];
            cout << "Enter a date in mm/dd/yyyy format: ";
            cin >> cstrDate;
            char* month = strtok(cstrDate, "/");
            char* day = strtok(NULL, "/");
            char* year = strtok(NULL, "/");
            sprintf(newDate, "%s-%s-%s", month, day, year);
            cout << "New date format: " << newDate << endl;
            break;
        }
        case 0: {
            isRunning = false;
            break;
        }
        default: {
            cout << "Invalid choice!" << endl;
        }
        }
    }

    return 0;
}
