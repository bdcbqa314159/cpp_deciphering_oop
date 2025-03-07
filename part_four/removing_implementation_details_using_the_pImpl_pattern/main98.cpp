#include <iostream>
#include "Person.hpp"

using std::cout; // preferred to: using namespace std;
using std::endl;

template <class Type>
class SmartPointer
{
private:
    Type *pointer = nullptr; // in-class initialization
public:
    SmartPointer(Type *ptr = nullptr) : pointer(ptr) {} // handles default constructor case as well
    virtual ~SmartPointer()
    {
        cout << "SmartPtr Destructor" << endl;
        delete pointer;
    }
    Type *operator->() { return pointer; }
    Type &operator*() { return *pointer; }
};

int main()
{
    SmartPointer<int> p1(new int());
    SmartPointer<Person> pers1(new Person("Renee", "Alexander", 'K', "Dr."));

    *p1 = 100;
    cout << *p1 << endl;
    (*pers1).print(); // or use: pers1->Print();

    return 0;
}