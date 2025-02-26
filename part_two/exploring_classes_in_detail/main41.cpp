#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl, std::string;

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
    void setFirstName(const string &);
    void cleanUp();
    void print();
};

int main()
{
    Student s1("Zachary", "Moon", 'R', 3.7, "C++");
    Student s2("Gabrielle", "Doone", 'A', 3.7, "C++");

    Student s3(s1);
    Student s4 = s2;
    s3.setFirstName("Zack");
    s4.setFirstName("Gabby");

    s1.print();
    s3.print();
    s2.print();
    s4.print();
    s1.cleanUp();
    s2.cleanUp();
    s3.cleanUp();
    s4.cleanUp();
    return 0;
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

void Student::setFirstName(const string &newFirstName)
{
    firstName = newFirstName;
}
