#pragma once
#include <iostream>
#include <iomanip>
#include <utility>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

class Person
{
private:
    class PersonImpl;
    PersonImpl *pImpl;

protected:
    void modifyTitle(const string &);

public:
    Person();
    Person(const string &, const string &, char, const string &);
    Person(const Person &);
    virtual ~Person();

    const string &getFirstName() const;
    const string &getLastName() const;
    const string &getTitle() const;
    char getMiddleInitial() const;

    virtual void print() const;
    virtual void isA() const;
    virtual void greeting(const string &) const;

    Person &operator=(const Person &);
};