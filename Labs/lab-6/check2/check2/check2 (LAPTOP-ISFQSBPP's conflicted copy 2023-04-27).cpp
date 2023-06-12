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
void reverse(std::list<T>& data) {
    if (data.empty() || data.size() == 1) {
        return;
    }
    T temp = data.back();
    data.pop_back();
    reverse(data);
    data.insert(data.begin(), temp);
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