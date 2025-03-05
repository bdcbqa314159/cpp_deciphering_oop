#include "Person.hpp"
#include <utility>

using std::cout, std::endl, std::setprecision, std::string, std::to_string, std::move;

Person::Person(const string &fn, const string &ln, char mi, const char *t) : firstName(fn), lastName(ln), middleInitial(mi)
{
    title = new char[strlen(t) + 1];
    strcpy(title, t);
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial)
{
    cout << "Person copy constructor\n";
    title = new char[strlen(p.title) + 1];
    strcpy(title, p.title);
}

Person::Person(Person &&p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
{
    cout << "Person move copy constructor\n";
    p.firstName.clear();
    p.lastName.clear();
    p.middleInitial = '\0';
    p.title = nullptr;
}

Person::~Person()
{
    cout << "Person destructor\n";
    delete[] title;
}

void Person::modifyTitle(const string &newTitle)
{
    delete title;
    title = new char[strlen(newTitle.c_str()) + 1];
    strcpy(title, newTitle.c_str());
}

const string &Person::setLastName(const string &ln)
{
    lastName = ln;
    return lastName;
}

void Person::print() const
{
    if (title)
        cout << title << " ";
    if (!firstName.empty())
        cout << firstName << " ";
    else
        cout << "No first name ";
    if (middleInitial != '\0')
        cout << middleInitial << ". ";
    if (!lastName.empty())
        cout << lastName << " ";
    else
        cout << "No last name ";
}

void Person::isA() const
{
    cout << "Person\n";
}

void Person::greeting(const string &msg) const
{
    cout << msg << endl;
}

Person &Person::operator=(const Person &p)
{
    cout << "person assignement operator\n";

    if (this != &p)
    {
        delete[] title;
        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;
        title = new char[strlen(p.title) + 1];
        strcpy(title, p.title);
    }

    return *this;
}

Person &Person::operator=(Person &&p)
{
    cout << "person assignement operator\n";

    if (this != &p)
    {
        delete[] title;
        firstName = p.firstName;
        p.firstName.clear();
        lastName = p.lastName;
        p.lastName.clear();
        middleInitial = p.middleInitial;
        p.middleInitial = '\0';
        title = p.title;
        p.title = nullptr;
    }

    return *this;
}