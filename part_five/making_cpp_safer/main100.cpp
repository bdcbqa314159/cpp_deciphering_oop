#include <iostream>
#include <memory>
#include "Person.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

int main()
{
    unique_ptr<int> p1(new int(100));

    cout << *p1 << endl;

    unique_ptr<Person> pers1(new Person("Renee", "Alexander", 'K', "Dr."));
    (*pers1).print();

    unique_ptr<Person> pers2;
    pers2 = std::move(pers1);
    pers2->print();

    auto pers3 = make_unique<Person>("Giselle", "LeBrun", 'R', "Ms.");
    pers3->print();

    return 0;
}