#include "customer.h"
std::list<Customer> customers;
// Constructor implementation
Customer::Customer(const std::string& id, const std::string& name) : id(id), name(name) {}

// Getter implementations
std::string Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

// Item rental/returning implementation
void Customer::rentItem(Inventory& item, int quantity) {
    item.rent(quantity);
    rentedItems.push_back(item);
}

void Customer::returnItem(Inventory& item, int quantity) {
    item.returnItem(quantity);
    auto it = std::find(rentedItems.begin(), rentedItems.end(), item);
    if (it != rentedItems.end()) {
        rentedItems.erase(it);
    }
}

// Getter implementation for rented items
std::list<Inventory>& Customer::getRentedItems() {
    return rentedItems;
}
// Destructor implementation




