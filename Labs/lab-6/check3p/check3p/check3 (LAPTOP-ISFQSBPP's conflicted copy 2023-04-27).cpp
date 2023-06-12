#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class T>
void print(std::list<T>& data, const std::string& label) {
    std::cout << label << " ";
    typename std::list<T>::iterator itr = data.begin();
    for (itr = data.begin(); itr != data.end(); itr++) {
        std::cout << " " << *itr;
    }
    std::cout << std::endl;
}

template <class T>
// Function to reverse a list in place
void reverse(std::list<T>& data) {
    std::list<T> reversed_list;
    while (!data.empty()) {
        T temp = data.back(); // Get the last element of the original list
        data.pop_back(); // Remove the last element from the original list
        reversed_list.push_back(temp); // Add the last element to the end of the reversed list
    }
    data.insert(data.begin(), reversed_list.begin(), reversed_list.end()); // Copy the reversed list to the original list
}



int main() {

    std::list<int> data;

    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);

    print(data, "before:");

    reverse(data);

    print(data, "after: ");

    std::list<std::string> data2;

    data2.push_back("apple");

    data2.push_back("banana");

    data2.push_back("carrot");

    data2.push_back("date");

    print(data2, "before:");

    reverse(data2);

    print(data2, "after: ");

}