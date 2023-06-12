#include "inventory.h"
std::list<Inventory> inventory;
// Constructor implementation
Inventory::Inventory(const std::string& id, int quantity, const std::string& description)
    : id(id), quantity(quantity), description(description), rentedQuantity(0) {}

// Getter implementations
std::string Inventory::getId() const {

    return id;
}

int Inventory::getQuantity() const {

    return quantity;
}

int Inventory::getRentedQuantity()const {
    return rentedQuantity;
}

std::string Inventory::getDescription() const {
    return description;
}

int Inventory::getAvailableQuantity() const {
    return quantity - rentedQuantity;
}

// Item rental/returning implementation
void Inventory::rent(int quantity) {
    rentedQuantity += quantity;
}

void Inventory::returnItem(int quantity) {
    rentedQuantity -= quantity;
}

// Equality operator implementation for finding an item in a list
bool Inventory::operator==(const Inventory& other) const {
    return id == other.id;
}

