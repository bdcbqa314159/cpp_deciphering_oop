#include <iostream>

using std::cout, std::endl, std::string;

class Person
{
private:
    string name, title;

public:
    Person() = default;
    ~Person() = default;

    Person(const string &n, const string &t) : name(n), title(t) {}
    virtual void print() const
    {
        cout << "title: " << title << " name: " << name << "\n";
    }
};

class Student : public Person
{
private:
    float gpa{};

public:
    Student() = default;
    ~Student() = default;

    Student(const string &n, const string &t, float avg) : Person(n, t), gpa(avg) {}
    void print() const override
    {
        Person::print();
        cout << "gpa: " << gpa << "\n";
    }
};

int main()
{
    Person tom("Tom", "Dr.");
    Student pete("Pete", "None", 3.4);

    tom.print();
    pete.print();

    return 0;
}