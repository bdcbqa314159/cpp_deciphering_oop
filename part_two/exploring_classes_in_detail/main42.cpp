#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

class Student;

class Employee
{

private:
    string firstName, lastName;
    float salary{};

public:
    Employee() = default;
    Employee(const Employee &) = default;
    Employee(const string &, const string &, float);
    Employee(const Student &);
    void print();
};

class Student
{
private:
    string firstName, lastName;
    char middleInitial{'\0'};
    float gpa{};
    char *currentCourse = nullptr;

public:
    Student() = default;
    Student(const string &, const string &, char, float, const char *);
    Student(const Student &);
    void cleanUp();
    void print();

    float getGpa() const;
    const string &getFirstName() const;
    const string &getLastName() const;
};

int main()
{
    Student s1("Giselle", "LeBrun", 'A', 3.5, "C++");
    Employee e1(s1);
    e1.print();
    s1.cleanUp();
    return 0;
}

Employee::Employee(const string &fn, const string &ln, float money)
{
    this->firstName = fn;
    this->lastName = ln;
    this->salary = money;
}

Employee::Employee(const Student &student)
{
    firstName = student.getFirstName();
    lastName = student.getLastName();

    float gpa = student.getGpa();

    if (gpa >= 4.)
        salary = 75000;
    else if (gpa >= 3.)
        salary = 60000;
    else
        salary = 50000;
}

void Employee::print()
{
    cout << firstName << " " << lastName << " " << salary << endl;
}

Student::Student(const string &fn, const string &ln, char mi, float gpa, const char *course)
{
    firstName = fn;
    lastName = ln;
    this->middleInitial = mi;
    this->gpa = gpa;
    currentCourse = new char[strlen(course) + 1];
    strcpy(currentCourse, course);
}

Student::Student(const Student &other)
{
    firstName = other.firstName;
    lastName = other.lastName;
    this->middleInitial = other.middleInitial;
    this->gpa = other.gpa;
    currentCourse = new char[strlen(other.currentCourse) + 1];
    strcpy(currentCourse, other.currentCourse);
}

void Student::cleanUp()
{
    delete[] currentCourse;
}

void Student::print()
{
    cout << firstName << " " << middleInitial << ". " << lastName << "\n";
    cout << "gpa: " << gpa << "\n";
    cout << "enrolled in: " << currentCourse << "\n";
}

float Student::getGpa() const
{
    return gpa;
}

const string &Student::getFirstName() const
{
    return firstName;
}

const string &Student::getLastName() const
{
    return lastName;
}