#ifndef INVENTORY_H
#define INVENTORY_H
#include <list>
#include <string>
using namespace std;

class Inventory {
public:

    Inventory(const std::string& id, int quantity, const std::string& description);

    std::string getId() const;
    std::string getDescription() const;
    int getQuantity() const;
    int getRentedQuantity() const;
    int getAvailableQuantity() const;
    void rent(int quantity);
    void returnItem(int quantity);

    bool operator==(const Inventory& other) const;

private:
    std::string id;
    std::string description;
    list<string>inventory;
    int quantity;
    int rentedQuantity;
};

#endif // INVENTORY_H
