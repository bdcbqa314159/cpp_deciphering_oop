#include <iostream>
using std::cout, std::cin, std::endl, std::string;

class Student;

class Person
{
private:
    string name, title;

public:
    Person() = default;
    Person(const string &, const string &);
    Person(const Student &);
    const string &getTitle() const { return title; }
};

class Student : public Person
{
private:
    float gpa{};

public:
    Student() = default;
    Student(const string &, const string &, float);
    Student(const Student &);
    float getGpa() const { return gpa; }
};

class GradStudent final : public Student
{
};

int main()
{
    Person p1("Cyrus Bond", "Mr.");
    Student *s1 = new Student("Anne Lin", "Ms.", 4.0);
    cout << p1.getTitle() << " " << s1->getTitle();
    cout << s1->getGpa() << endl;
    delete s1;

    return 0;
}

Person::Person(const string &name, const string &title) : name(name), title(title) {}
Person::Person(const Student &s) : name(s.name), title(s.title) {}

Student::Student(const string &name, const string &title, float gpa) : Person(name, title), gpa(gpa) {}
Student::Student(const Student &s) : Person(s), gpa(s.gpa) {}