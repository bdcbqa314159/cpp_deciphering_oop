#pragma once
#include <iostream>
#include <iomanip>
#include <utility>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

class Person
{
private:
    string firstName, lastName;
    char middleInitial = '\0';
    char *title = nullptr;

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, char, const char *);
    Person(const Person &);
    Person(Person &&);
    virtual ~Person();

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const char *getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    const string &setLastName(const string &);

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;

    Person &operator=(const Person &);
    Person &operator=(Person &&);
};