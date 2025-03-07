#include <iostream>
#include <memory>
#include "Person.hpp"

using std::cout; // preferred to: using namespace std;
using std::endl;
using std::shared_ptr;

int main()
{
    shared_ptr<int> p1 = std::make_shared<int>(100);
    // alternative to preferred, above line of code:
    // shared_ptr<int> p1(new int(100));

    shared_ptr<int> p2; // currently uninitialized
    p2 = p1;            // p2 points to the same memory as p1
    cout << *p1 << " " << *p2 << endl;

    shared_ptr<Person> pers1 = std::make_shared<Person>("Gabby", "Doone", 'A', "Miss");
    // alternative to preferred, above line of code:
    // shared_ptr<Person> pers1(new Person("Gabby", "Doone", 'A', "Miss"));

    shared_ptr<Person> pers2 = pers1; // notice we initialize with the valid address

    pers1->print(); // or alternatively use: (*pers1).Print();
    pers2->print();
    pers1->modifyTitle("Dr.");
    pers2->print();

    cout << "Number of references: " << pers1.use_count() << endl;
    return 0;
}