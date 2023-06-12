#include <iostream>
using namespace std;
int main(int argc, char *argv[]){
int product=1;
for (int i=1; i<argc; i++){
product=product* stoi(argv[i]);
}
cout << "product of integers: " << product << endl;

return 0;
}
