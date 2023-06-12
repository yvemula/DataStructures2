#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <list>
#include "inventory.h"
using namespace std;
class Customer {
public:

    Customer(const std::string& id, const std::string& name);
    std::string getId() const;
    std::string getName() const;
    std::list<Inventory>& getRentedItems();
    void rentItem(Inventory& item, int quantity);
    void returnItem(Inventory& item, int quantity);

private:
    std::string id;
    std::string name;
    std::list<std::string> rentedItems;
};

#endif // CUSTOMER_H
