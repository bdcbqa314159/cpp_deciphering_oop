#include <iostream>
#include <iomanip>
#include "Person.hpp"

using std::cout;
using std::endl;
using std::string;

Person::Person(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")
{
}

Person &Person::operator=(const Person &p)
{
    if (this != &p)
    {
        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;
        title = p.title;
        greeting = p.greeting;
    }
    return *this;
}

Person::~Person()
{
    cout << "Person destructor" << endl;
}

void Person::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::setGreeting(const string &newGreeting)
{
    greeting = newGreeting;
}

void Person::print() const
{
    cout << title << " " << firstName << " " << lastName << endl;
}
