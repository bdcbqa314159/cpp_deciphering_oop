#include <iostream>
#include "Person.hpp"

using std::cout;
using std::endl;

constexpr int MAX = 3;

int main()
{
    Person *people[MAX] = {};
    people[0] = new Person("Giselle", "LeBrun", 'R', "Ms.");
    people[1] = new Person("Zack", "Moon", 'R', "Dr.");
    people[2] = new Person("Gabby", "Doone", 'A', "Dr.");

    for (auto *individual : people)
        individual->print();

    for (auto *individual : people)
        delete individual;

    return 0;
}