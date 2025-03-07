#pragma once
#include <iostream>

using std::string;

class Person
{
private:
    string firstName;
    string lastName;
    char middleInitial = '\0';
    string title;
    string greeting;

public:
    Person() = default;
    Person(const string &, const string &, char, const string &);

    Person &operator=(const Person &);
    virtual ~Person();
    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }
    void modifyTitle(const string &);
    void setGreeting(const string &);
    virtual const string &speak() { return greeting; }
    virtual void print() const;
};