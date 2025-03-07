#include <iostream>
#include <iomanip>
#include "Person.hpp"

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

class Person::PersonImpl
{
private:
    string firstName, lastName;
    char middleInitial = '\0';
    string title;

public:
    PersonImpl() = default;
    PersonImpl(const string &, const string &, char, const string &);
    PersonImpl(const PersonImpl &) = default;
    virtual ~PersonImpl() = default;

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const string &getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    void modifyTitle(const string &);

    virtual void print() const;
    virtual void isA() const { cout << "Person\n"; }
    virtual void greeting(const string &msg) const { cout << msg << endl; }

    PersonImpl &operator=(const PersonImpl &);
};

Person::PersonImpl::PersonImpl(const string &fn, const string &ln, char mi, const string &t) : firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

void Person::PersonImpl::modifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::PersonImpl::print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". ";
    cout << lastName << endl;
}

Person::PersonImpl &Person::PersonImpl::operator=(const PersonImpl &p)
{

    if (this != &p)
    {
        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;
        title = p.title;
    }
    return *this;
}

Person::Person() : pImpl(new PersonImpl())
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : pImpl(new PersonImpl(fn, ln, mi, t))
{
}

Person::Person(const Person &p) : pImpl(new PersonImpl(*(p.pImpl)))
{
}

Person::~Person()
{
    delete pImpl;
}

const string &Person::getFirstName() const
{
    return pImpl->getFirstName();
}

const string &Person::getLastName() const
{
    return pImpl->getLastName();
}

const string &Person::getTitle() const
{
    return pImpl->getTitle();
}

char Person::getMiddleInitial() const
{
    return pImpl->getMiddleInitial();
}

void Person::modifyTitle(const string &newTitle)
{
    pImpl->modifyTitle(newTitle); // delegate to implementation
}

void Person::print() const
{
    pImpl->print(); // delegate to implementation
}

void Person::isA() const
{
    pImpl->isA(); // delegate to implementation
}

void Person::greeting(const string &msg) const
{
    pImpl->greeting(msg); // delegate to implementation
}

Person &Person::operator=(const Person &p)
{
    pImpl->operator=(*(p.pImpl));
    return *this;
}