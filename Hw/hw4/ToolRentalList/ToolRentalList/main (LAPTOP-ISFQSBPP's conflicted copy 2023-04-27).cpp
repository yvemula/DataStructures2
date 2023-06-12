#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "customer.h"
#include "inventory.h"

using namespace std;

// Function to read the inventory file and populate the inventory list
void inventoryFile(string filename, list<Inventory>& inventoryList)
{
    ifstream file(filename);
    if (!file) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Parse the line
        string id, description;
        int quantity;
        if (line.length() >= 8 && line[0] == 'T' && isdigit(line[1]) && isdigit(line[2]) &&
            isdigit(line[3]) && isdigit(line[4]) && isspace(line[5])) {
            id = line.substr(0, 5);
            quantity = stoi(line.substr(6, 1));
            description = line.substr(8);
        }
        else {
            cerr << "Invalid inventory ID " << line.substr(0, 5) << " found in the inventory file." << endl;
            continue;
        }

        // Add the item to the inventory list
        inventoryList.push_back(Inventory(id, quantity, description));
        
    }

    file.close();
}

// Function to read the customer file and populate the customer list
void CustomerFile(string filename, list<Customer>& customerList, list<Inventory>& inventoryList)
{
    ifstream file(filename);
    if (!file) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Parse the line
        string id, action, inventoryId, name;
        int timestamp, quantity;
        if (line.length() >= 23 && line[0] == 'C' && isdigit(line[1]) && isdigit(line[2]) &&
            isdigit(line[3]) && isdigit(line[4]) && isspace(line[5])) {
            id = line.substr(0, 5);
            action = line.substr(6, 4);
            timestamp = stoi(line.substr(11, 4));
            quantity = stoi(line.substr(16, 1));
            inventoryId = line.substr(18, 5);
            name = line.substr(24);
        }
        else {
            cerr << "Invalid customer information found for ID " << line.substr(0, 5) << " in the customer file." << endl;
            continue;
        }

        // Find the customer in the customer list or add a new customer if not found
        auto customer = find_if(customerList.begin(), customerList.end(),
            [&](const Customer& c) { return c.getId() == id; });
        if (customer == customerList.end()) {
            customerList.push_back(Customer(id, name));
            customer = --customerList.end();
        }

        // Find the item in the inventory list
        auto item = find_if(inventoryList.begin(), inventoryList.end(),
            [&](const Inventory& i) { return i.getId() == inventoryId; });
        if (item == inventoryList.end()) {
            cerr << "Customer " << id << " requested item " << inventoryId
                << " which is not in the inventory." << endl;
            continue;
        }

        // Rent or return the item
        if (action == "rent") {
            // Check if the requested quantity is available
            if (item->getAvailableQuantity() >= quantity) {
                // Rent the item to the customer
                item->rent(quantity);
                customer->rentItem(*item, quantity);
            }
            else {
                cerr << "Customer " << id << " requested " << quantity << " of item " << inventoryId
                    << " but only " << item->getAvailableQuantity() << " are available." << endl;
            }
        }
        else if (action == "return") {
            customer->returnItem(*item, quantity);
        }
        else {
            cerr << "Invalid action " << action << " found for customer " << id << " in the customer file." << endl;
            continue;
        }
    }

    file.close();
}

int main(int argc,char* argv[])
{
    if (argc != 6) {
        cerr << "Invalid command line arguments." << endl;
    }
    list<Customer> customerList;
    list<Inventory> inventoryList;
   inventoryFile("inventory_small.txt", inventoryList);
   CustomerFile("customer_small.txt", customerList, inventoryList);

    

    

    return 0;
}