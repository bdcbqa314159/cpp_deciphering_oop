#include <iostream>
#include <cstring>

using std::cout, std::endl, std::string;

class Person
{
private:
    string firstName;
    string lastName;
    char middleInitial = '\0';
    char *title = nullptr;

protected:
    void modifyTitle(const string &);

public:
    Person() = default;
    Person(const string &, const string &, char, const char *);
    Person(const Person &);
    virtual ~Person();

    const string &getFirstName() const { return firstName; }
    const string &getLastName() const { return lastName; }
    const char *getTitle() const { return title; }
    char getMiddleInitial() const { return middleInitial; }

    virtual void print() const;
    virtual void isA() const;

    Person &operator=(const Person &);
    bool operator==(const Person &);
    Person &operator+(const string &);
    friend Person &operator+(const string &, Person &);
};

Person::Person(const string &fn, const string &ln, char mi, const char *t) : firstName(fn), lastName(ln), middleInitial(mi)
{
    title = new char[strlen(t) + 1];
    strcpy(title, t);
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial)
{
    title = new char[strlen(p.title) + 1];
    strcpy(title, p.title);
}

Person::~Person()
{
    delete title;
}

Person &Person::operator=(const Person &p)
{
    if (this != &p)
    {
        delete title;

        firstName = p.firstName;
        lastName = p.lastName;
        middleInitial = p.middleInitial;

        title = new char[strlen(p.title) + 1];
        strcpy(title, p.title);
    }

    return *this;
}

bool Person::operator==(const Person &p)
{
    if (this == &p)
        return true;
    else if ((!firstName.compare(p.firstName)) && (!lastName.compare(p.lastName)) && (!strcmp(title, p.title)) && (middleInitial == p.middleInitial))
        return true;
    else
        return false;
}

Person &Person::operator+(const string &t)
{
    modifyTitle(t);
    return *this;
}

Person &operator+(const string &t, Person &p)
{
    p.modifyTitle(t);
    return p;
}

void Person::modifyTitle(const string &newTitle)
{
    delete title;
    title = new char[strlen(newTitle.c_str()) + 1];
    strcpy(title, newTitle.c_str());
}

void Person::print() const
{
    if (title)
        cout << title << " ";
    if (!firstName.empty())
        cout << firstName << " ";
    else
        cout << "No first name \n";

    if (middleInitial != '\0')
        cout << middleInitial << ". ";

    if (!lastName.empty())
        cout << lastName << " ";
    else
        cout << "No last name \n";
    cout << "\n";
}

void Person::isA() const
{
    cout << "Person" << endl;
}

int main()
{
    Person p1;
    Person p2("Gabby", "Doone", 'A', "Miss");
    Person p3("Renee", "Alexander", 'Z', "Dr.");

    p1.print();
    p2.print();
    p3.print();

    p1 = p2;
    p1.print();

    p2 = "Ms." + p2;
    p2.print();

    p1 = p2 = p3;
    p2.print();
    p1.print();

    if (p2 == p2)
        cout << "Same people" << endl;

    if (p1 == p3)
        cout << "Same people" << endl;

    return 0;
}