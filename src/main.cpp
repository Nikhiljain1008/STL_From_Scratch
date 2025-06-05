#include "../include/vector.hpp"
#include <string>

using namespace std;

int main() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.print(); // [ 10 20 30 ]

    v.pop_back();
    v.print(); // [ 10 20 ]

    Vector<int> v2 = std::move(v); // test move constructor
    v2.print(); // [ 10 20 ]
    v.print();  // [ ] (empty after move)

    Vector<string> svec;
    svec.push_back("Hello");
    svec.push_back("World");
    svec.print(); // [ Hello World ]

    return 0;
}
